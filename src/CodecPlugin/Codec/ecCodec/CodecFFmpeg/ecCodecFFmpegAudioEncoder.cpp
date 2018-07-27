//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ecCodecFFmpegAudioEncoder.h"
#include "FFmpegFormatConverter.h"


ecCodecFFmpegAudioEncoder::ecCodecFFmpegAudioEncoder()
	: m_pSwrFrame(nullptr)
	, m_pAudioFrame(nullptr)
	, m_pCodecCtx(nullptr)
	, m_pSwrCtx(nullptr)
	, m_pAudioFifo(nullptr)
	, m_pDestBuffer(nullptr)
	, m_pts(0)
	, m_nBytesPerSrcSample(0)
{
}


ecCodecFFmpegAudioEncoder::~ecCodecFFmpegAudioEncoder()
{
	Release();
}

bool ecCodecFFmpegAudioEncoder::InitAudioEncoder(const SDAudioMediaInfo & sAudioInfo)
{
	//av_log_set_level
	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(sAudioInfo.enumAudioType);
	AVCodec* pAudioCodec = avcodec_find_encoder(codecId);
	if (!pAudioCodec) {
		return false;
	}

	m_pCodecCtx = avcodec_alloc_context3(pAudioCodec);
	if (!m_pCodecCtx) {
		return false;
	}

	m_pCodecCtx->profile = FFmpegFormatCovert::ConvertAudioProfile(sAudioInfo.dwAudioSubType);			// FF_PROFILE_AAC_MAIN;
	m_pCodecCtx->sample_fmt = FFmpegFormatCovert::ConvertSamplesFormat(sAudioInfo.enumChannelSamplesFormat);//AV_SAMPLE_FMT_FLTP;
	//音频格式要做一个妥协，假如指定格式不被支持，则取支持的格式
	bool bFind = false;
	AVSampleFormat sample_fmt_bak = AV_SAMPLE_FMT_NONE;
	for (int i = 0; m_pCodecCtx->codec->sample_fmts[i] != AV_SAMPLE_FMT_NONE; i++) 
	{
		//策略上倾向一下AV_SAMPLE_FMT_FLTP
		if (sample_fmt_bak != AV_SAMPLE_FMT_FLTP)
		{
			sample_fmt_bak = m_pCodecCtx->codec->sample_fmts[i];
		}
		//如果支持，则保留用户设置
		if (m_pCodecCtx->sample_fmt == m_pCodecCtx->codec->sample_fmts[i])
		{
			bFind = true;
			break;
		}
		//如果是单声道，则是否平面存储都无所谓，可以直接转换
		if (m_pCodecCtx->channels == 1 &&
			av_get_planar_sample_fmt(m_pCodecCtx->sample_fmt) ==
			av_get_planar_sample_fmt(m_pCodecCtx->codec->sample_fmts[i])) 
		{
			bFind = true;
			m_pCodecCtx->sample_fmt = m_pCodecCtx->codec->sample_fmts[i];
			break;
		}
	}
	//用户设置格式不支持，则用一个支持的格式
	if (!bFind)
	{
		m_pCodecCtx->sample_fmt = sample_fmt_bak;
	}
	m_pCodecCtx->sample_rate = sAudioInfo.dwSamplesPerSec;												// 48000;
	m_pCodecCtx->channels = sAudioInfo.dwChannels;	       												// av_get_channel_layout_nb_channels(m_pCodecCtx->channel_layout);
	m_pCodecCtx->channel_layout = FFmpegFormatCovert::ConvertChannelLayout(sAudioInfo.enumAudioCFG);	// AV_CH_LAYOUT_STEREO;
	m_pCodecCtx->rc_min_rate = sAudioInfo.dwAvgBitsPerSec;
	m_pCodecCtx->rc_max_rate = sAudioInfo.dwAvgBitsPerSec;
	m_pCodecCtx->bit_rate_tolerance = 1;
	m_pCodecCtx->bit_rate = sAudioInfo.dwAvgBitsPerSec;
	m_pCodecCtx->time_base.num = 1;
	m_pCodecCtx->time_base.den = m_pCodecCtx->sample_rate;
	m_pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	m_pCodecCtx->thread_count = 1;
	m_pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;

	if (m_pCodecCtx->codec_id == AV_CODEC_ID_AAC) 
	{
		m_pCodecCtx->profile = FF_PROFILE_AAC_LOW;
		m_pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	}
	else if (m_pCodecCtx->codec_id == AV_CODEC_ID_MP2)
	{
		//这个数字是从ffmpeg里边抄出来的数，原来的数会导致open失败
		m_pCodecCtx->bit_rate = 64000;
	}

	int nRet = avcodec_open2(m_pCodecCtx, pAudioCodec, nullptr);
	if (nRet < 0) {
		return false;
	}

	return true;
}

bool ecCodecFFmpegAudioEncoder::SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo * pAudioBufInfo)
{
	if (!pAudioBufInfo || !m_pCodecCtx) {
		return false;
	}

	int srcChannels = pAudioBufInfo->dwChannels;
	int srcSample_rate = pAudioBufInfo->dwSamplesPerSec;
	AVSampleFormat srcFormat = FFmpegFormatCovert::ConvertSamplesFormat(pAudioBufInfo->enumChannelSamplesFormat);
	SD_UINT64 srcChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioBufInfo->enumAudioCFG);

	if (av_sample_fmt_is_planar(srcFormat))
	{
		return false;
	}

	int desChannels = m_pCodecCtx->channels;
	int desSample_rate = m_pCodecCtx->sample_rate;
	AVSampleFormat desFormat = m_pCodecCtx->sample_fmt;
	SD_UINT64 desChannelLayout = m_pCodecCtx->channel_layout;

	if (m_pCodecCtx->frame_size < 1)
	{
		m_pCodecCtx->frame_size = 1024;
	}

	m_pAudioFifo = av_audio_fifo_alloc(m_pCodecCtx->sample_fmt, m_pCodecCtx->channels, m_pCodecCtx->frame_size * 10);
	if (!m_pAudioFifo) {
		return false;
	}

	m_nBytesPerSrcSample = pAudioBufInfo->dwChannels * av_get_bytes_per_sample(srcFormat);
	m_pDestBuffer.reset(new SD_UINT8[AVCODEC_MAX_AUDIO_FRAME_SIZE]);

	m_pAudioFrame = av_frame_alloc();
	m_pAudioFrame->channels = m_pCodecCtx->channels;
	m_pAudioFrame->format = m_pCodecCtx->sample_fmt;
	m_pAudioFrame->sample_rate = m_pCodecCtx->sample_rate;
	m_pAudioFrame->channel_layout = m_pCodecCtx->channel_layout;
	if (m_pCodecCtx->frame_size > 0)
	{
		m_pAudioFrame->nb_samples = m_pCodecCtx->frame_size;
	}
	else
	{
		m_pAudioFrame->nb_samples = 1024;
	}
	if (av_frame_get_buffer(m_pAudioFrame, 0) < 0) 
	{
		av_frame_free(&m_pAudioFrame);
		return false;
	}

	bool bSwr = (srcChannels != m_pCodecCtx->channels || srcFormat != m_pCodecCtx->sample_fmt ||
		srcSample_rate != m_pCodecCtx->sample_rate);
	if (!bSwr)
	{
		// 无需重采样直接返回
		return true;
	}

	m_pSwrCtx = swr_alloc_set_opts(nullptr, desChannelLayout, desFormat, desSample_rate,
		srcChannelLayout, srcFormat, srcSample_rate, 0, 0);

	if (swr_is_initialized(m_pSwrCtx) == 0) {
		swr_init(m_pSwrCtx);
	}

	return true;
}

bool ecCodecFFmpegAudioEncoder::WriteSample(const SD_UINT8 * pData, SD_UINT32 nSamples, bool emInputFlag)
{
	if (!m_pAudioFifo) {
		return false;
	}

	if (!m_pSwrFrame || m_pSwrFrame->nb_samples<nSamples)
	{
		av_frame_free(&m_pSwrFrame);
		m_pSwrFrame = av_frame_alloc();
		m_pSwrFrame->channels = m_pCodecCtx->channels;
		m_pSwrFrame->format = m_pCodecCtx->sample_fmt;
		m_pSwrFrame->sample_rate = m_pCodecCtx->sample_rate;
		m_pSwrFrame->channel_layout = m_pCodecCtx->channel_layout;
		m_pSwrFrame->nb_samples = nSamples;
		if (av_frame_get_buffer(m_pSwrFrame, 0) < 0) {
			av_frame_free(&m_pSwrFrame);
			return false;
		}
	}

	if (m_pSwrCtx) 
	{
		swr_convert(m_pSwrCtx, m_pSwrFrame->data, nSamples, &pData, nSamples);
		int fifo = av_audio_fifo_write(m_pAudioFifo, (void**)m_pSwrFrame->data, nSamples);
	}
	else
	{
		int fifo = av_audio_fifo_write(m_pAudioFifo, (void**)&pData, nSamples);
	}

	return true;
}

bool ecCodecFFmpegAudioEncoder::SetEndofInput()
{
	return true;
}

int ecCodecFFmpegAudioEncoder::GetCompressFrame(SD_UINT8 *& pData, SDRFrameInfo * pFrameInfo)
{
	if (!m_pCodecCtx || !m_pAudioFrame) {
		return -2;
	}

	if (av_audio_fifo_size(m_pAudioFifo) < m_pCodecCtx->frame_size) {
		return 0;
	}

	av_audio_fifo_read(m_pAudioFifo, (void**)m_pAudioFrame->data, m_pCodecCtx->frame_size);

	m_pAudioFrame->pts = m_pts++*m_pCodecCtx->frame_size;
	AVRational timebase = { 1, m_pCodecCtx->sample_rate };
	m_pAudioFrame->pts = av_rescale_q(m_pAudioFrame->pts, timebase, m_pCodecCtx->time_base);

	int ret = avcodec_send_frame(m_pCodecCtx, m_pAudioFrame);
	if (ret < 0) {
		return -4;
	}

	AVPacket avpkt = { 0 };
	av_init_packet(&avpkt);
	ret = avcodec_receive_packet(m_pCodecCtx, &avpkt);
	if (ret == AVERROR(EAGAIN))
	{
		return 0;
	}
	else if (ret == AVERROR_EOF)
	{
		return -1;
	}
	else if (ret < 0 || avpkt.size < 1) 
	{
		av_packet_unref(&avpkt);
		return -5;
	}

	memcpy(m_pDestBuffer.get(), avpkt.data, avpkt.size);
	pData = m_pDestBuffer.get();
	pFrameInfo->iSize = avpkt.size;
	pFrameInfo->qwDTS = avpkt.dts;
	pFrameInfo->qwPTS = avpkt.pts;
	pFrameInfo->qwDuration = avpkt.duration;

	av_packet_unref(&avpkt);

	return 1;
}

bool ecCodecFFmpegAudioEncoder::Release()
{
	if (m_pCodecCtx)
	{
		avcodec_close(m_pCodecCtx);
		avcodec_free_context(&m_pCodecCtx);
	}
	if (m_pSwrFrame)
	{
		av_frame_free(&m_pSwrFrame);
	}
	if (m_pAudioFrame)
	{
		av_frame_free(&m_pAudioFrame);
	}
	if (m_pSwrCtx)
	{
		swr_close(m_pSwrCtx);
		swr_free(&m_pSwrCtx);
	}
	m_pts = 0;
	m_nBytesPerSrcSample = 0;
	av_audio_fifo_free(m_pAudioFifo);
	m_pAudioFifo = nullptr;

	return true;
}

AVCodecContext * ecCodecFFmpegAudioEncoder::GetCodecContext() const
{
	return m_pCodecCtx;
}
