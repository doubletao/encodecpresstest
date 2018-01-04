//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ecCodecIntelProtocolEncoder.h"
#include "..\CodecFFmpeg\FFmpegFormatConverter.h"
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")


ecCodecIntelProtocolEncoder::ecCodecIntelProtocolEncoder()
	: m_pFormatCtx(nullptr)
	, m_pVideoStream(nullptr)
	, m_pAudioStream(nullptr)
	, m_bWritable(false)
	, m_nPts(0)
{
}


ecCodecIntelProtocolEncoder::~ecCodecIntelProtocolEncoder()
{
	Release();
}

bool ecCodecIntelProtocolEncoder::SetSinkFile(const SDStreamMediaInfo * pStreamMediaInfo, const char * pFileName)
{
	if (!pStreamMediaInfo || !pFileName) {
		return false;
	}

	if (avformat_alloc_output_context2(&m_pFormatCtx, nullptr, nullptr, pFileName) < 0) {
		return false;
	}
	AVOutputFormat* pOutputFormat = m_pFormatCtx->oformat;
	pStreamMediaInfo->sVideoMediaInfo.dwFlags = pOutputFormat->flags;

	pOutputFormat->flags &= ~AVFMT_NOTIMESTAMPS;
	if (pOutputFormat->flags & AVFMT_NOTIMESTAMPS)
	{
		assert(false);
	}

	if (pStreamMediaInfo->dwVideoStreamCount > 0 && !CreateVideoStream(pStreamMediaInfo->sVideoMediaInfo)) 
	{
		avformat_close_input(&m_pFormatCtx);
		return false;
	}

	if (pStreamMediaInfo->dwAudioStreamCount > 0 && !CreateAudioStream(pStreamMediaInfo->sAudioMediaInfo))
	{
		avformat_close_input(&m_pFormatCtx);
		return false;
	}

	if (!(m_pFormatCtx->flags & AVFMT_NOFILE))
	{
		if (avio_open(&m_pFormatCtx->pb, pFileName, AVIO_FLAG_READ_WRITE) < 0)
		{
			avformat_close_input(&m_pFormatCtx);
			m_bWritable = false;
			return false;
		}
		m_bWritable = true;
	}

	AVDictionary* opt = NULL;
	av_dict_set_int(&opt, "video_track_timescale", pStreamMediaInfo->sVideoMediaInfo.dwStandardRate, 0);

	int nRet = avformat_write_header(m_pFormatCtx, &opt);
	if (nRet < 0)
	{
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(nRet, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(nRet));
		avio_closep(&m_pFormatCtx->pb);
		avformat_close_input(&m_pFormatCtx);
		return false;
	}

	return true;
}

bool ecCodecIntelProtocolEncoder::GetMediaInfo(SDStreamMediaInfo * pStreamMediaInfo)
{
	return false;
}

bool ecCodecIntelProtocolEncoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pVideoBufInfo, const SDResamplerPara * pResamplerInfo)
{
	if (!m_pVideoEncoder) {
		return false;
	}

	if (!m_pVideoEncoder->SetVideoFrameBufInfo(pVideoBufInfo)) {
		return false;
	}

	return true;
}

bool ecCodecIntelProtocolEncoder::GetVideoFrameBufInfo(SDVideoFrameImageBufInfo * pVideoInfo, SDResamplerPara * pResamplerInfo)
{
	return false;
}

bool ecCodecIntelProtocolEncoder::SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo * pAudioBufInfo)
{
	if (!m_pAudioEncoder) {
		return false;
	}

	if (!m_pAudioEncoder->SetAudioSamplesBufInfo(pAudioBufInfo)) {
		return false;
	}

	return true;
}

bool ecCodecIntelProtocolEncoder::GetAudioSamplesBufInfo(SDAudioSamplesBufInfo * pAudioBufInfo)
{
	return false;
}

bool ecCodecIntelProtocolEncoder::IsCanWriteVideoFrame()
{
	return true;
}

bool ecCodecIntelProtocolEncoder::IsCanWriteAudioFrame()
{
	return true;
}

bool ecCodecIntelProtocolEncoder::PutVideoBuffer(const SD_UINT8 * pFrameBuf, bool bForceToKeyFrame, const SDRFrameInfo * pFrameInfo)
{
	if (!m_pVideoEncoder) {
		return false;
	}

	if (0)
	{
		FILE * file;
		fopen_s(&file, "h264.yuv", "wb+");
		if (file)
		{
			int nSize = pFrameInfo->iSize;
			fwrite(pFrameBuf, nSize, 1, file);
			fclose(file);
		}
	}
	
	if (!m_pVideoEncoder->PutFrame(pFrameBuf, pFrameInfo, bForceToKeyFrame)) {
		return false;
	}

	SDRFrameInfo frameInfo = *pFrameInfo;
	SD_UINT8* pCompressFrame = nullptr;
	if (m_pVideoEncoder->GetCompressFrame(pCompressFrame, &frameInfo) > 0) 
	{
		if (!PutVideoFrame(pCompressFrame, &frameInfo))
		{
			return false;
		}
	}
	return true;
}

bool ecCodecIntelProtocolEncoder::PutVideoFrame(const SD_UINT8 * pFrameBuf, const SDRFrameInfo * pFrameInfo)
{
	if (!m_bWritable || !m_pVideoStream || !pFrameInfo) {
		return false;
	}

	AVPacket avpkt;
	av_init_packet(&avpkt);

	int extradataSize = 0;
	if (pFrameInfo->emFrameType == FRAMETYPE_I) {
		avpkt.flags |= AV_PKT_FLAG_KEY;
		extradataSize = pFrameInfo->extradata_size;
	}

	avpkt.data = const_cast<uint8_t*>(pFrameBuf + extradataSize);
	avpkt.size = pFrameInfo->iSize - extradataSize;
	avpkt.pts = pFrameInfo->qwPTS;
	avpkt.dts = pFrameInfo->qwDTS;
	avpkt.duration = pFrameInfo->qwDuration;
	avpkt.stream_index = m_pVideoStream->index;

	//av_packet_rescale_ts(&avpkt, m_pVideoEncoder->GetCodecContext()->time_base, m_pVideoStream->time_base);

	if (0)
	{
		FILE * file;
		fopen_s(&file, "d.h264", "ab");
		if (file)
		{
			fwrite(avpkt.data, 1, avpkt.size, file);    //Y 
			fclose(file);
		}
	}

	int ret = av_interleaved_write_frame(m_pFormatCtx, &avpkt);
	if (ret < 0) {
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(ret, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(ret));
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);

	return true;
}

bool ecCodecIntelProtocolEncoder::PutAudioSamples(const SD_UINT8 * pSamplesBuf, SD_UINT32 dwSampleNum)
{
	if (!m_pAudioStream || !m_pAudioEncoder) {
		return false;
	}

	//如果流格式为PCM，则不走音频编码器，直接往流里边写
	if (m_pAudioStream->codecpar->codec_id == FFmpegFormatCovert::ConvertCodecId(SDAUDIOTYPE_WAVE_PCM))
	{
		int data_size = av_get_bytes_per_sample((AVSampleFormat)m_pAudioStream->codecpar->format) * m_pAudioStream->codecpar->channels;
		SDRFrameInfo frameInfo;
		frameInfo.iSize = dwSampleNum * data_size;
		frameInfo.qwPTS = 0;
		frameInfo.qwDTS = 0;
		frameInfo.qwDuration = 0;
		if (!PutAudioFrame(pSamplesBuf, &frameInfo))
		{
			return false;
		}
		return true;
	}
	else
	{
		bool ret = m_pAudioEncoder->WriteSample(pSamplesBuf, dwSampleNum, false);

		SDRFrameInfo frameInfo;
		SD_UINT8* pCompressFrame = nullptr;
		while (m_pAudioEncoder->GetCompressFrame(pCompressFrame, &frameInfo) > 0)
		{
			if (!PutAudioFrame(pCompressFrame, &frameInfo))
			{
				return false;
			}
		}
		return true;
	}
}

bool ecCodecIntelProtocolEncoder::PutAudioFrame(const SD_UINT8 * pFrameBuf, const SDRFrameInfo * pFrameInfo)
{
	if (!m_bWritable || !m_pAudioStream || !pFrameInfo) {
		return false;
	}

	AVPacket avpkt;
	av_init_packet(&avpkt);
	avpkt.data = const_cast<SD_UINT8*>(pFrameBuf);
	avpkt.size = pFrameInfo->iSize;
	avpkt.pts = pFrameInfo->qwPTS;
	avpkt.dts = pFrameInfo->qwDTS;
	avpkt.duration = pFrameInfo->qwDuration;
	avpkt.stream_index = m_pAudioStream->index;

	av_packet_rescale_ts(&avpkt, m_pAudioEncoder->GetCodecContext()->time_base, m_pAudioStream->time_base);

	int ret = av_interleaved_write_frame(m_pFormatCtx, &avpkt);
	if (ret < 0) {
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(ret, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(ret));
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);

	return true;
}

bool ecCodecIntelProtocolEncoder::Release()
{
	if (m_pFormatCtx)
	{
		SDRFrameInfo frameInfo;
		SD_UINT8* pCompressFrame = nullptr;
		int nRet = 0;
		//将编码器中缓存的帧flush掉
		int nLoopCount = 50;//不大于50次
		do 
		{
			nRet = m_pVideoEncoder->GetCompressFrame(pCompressFrame, &frameInfo);
			if (nRet == 0)
			{
				//flush
				m_pVideoEncoder->SetEndofInput();
			}
			else if (nRet > 0)
			{
				//put不进去了，算了
				if (!PutVideoFrame(pCompressFrame, &frameInfo))
				{
					break;
				}
			}
			else
			{
				//false了也算了
				break;
			}
		} while (nLoopCount-- > 0);

		m_nPts = 0;
		nRet = av_write_trailer(m_pFormatCtx);
		if (nRet != 0)
		{
			assert(false);
		}
		if (m_pFormatCtx->pb) {
			avio_closep(&m_pFormatCtx->pb);
		}
		avformat_close_input(&m_pFormatCtx);
	}

	return true;
}

bool ecCodecIntelProtocolEncoder::CreateVideoStream(const SDVideoMediaInfo & videoInfo)
{
	if (videoInfo.dwWidth <= 0 || videoInfo.dwHeight <= 0 ||
		videoInfo.enumVideoType == SDVIDEOTYPE_UNKNOW) {
		return false;
	}

	m_pVideoStream = avformat_new_stream(m_pFormatCtx, nullptr);
	if (!m_pVideoStream) {
		return false;
	}

	m_pVideoStream->start_time = 0;
	m_pVideoStream->time_base.num = 1;
	m_pVideoStream->time_base.den = videoInfo.dwStandardRate;
	m_pVideoStream->r_frame_rate.den = videoInfo.dwStandardScale;
	m_pVideoStream->r_frame_rate.num = videoInfo.dwStandardRate;

	m_pVideoEncoder.reset(new ecCodecIntelVideoEncoder());
	if (!m_pVideoEncoder->InitVideoEncoder(&videoInfo)) {
		return false;
	}

	m_pVideoStream->codecpar->bit_rate = videoInfo.dwDataRateInBitsPerSec;
	m_pVideoStream->codecpar->block_align = 1;
	m_pVideoStream->codecpar->codec_id = AV_CODEC_ID_H264;
	m_pVideoStream->codecpar->codec_tag = videoInfo.dwVideoSubType;
	m_pVideoStream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
	if (videoInfo.dwWidth > 800)
	{
		m_pVideoStream->codecpar->color_primaries = AVCOL_PRI_BT709;
		m_pVideoStream->codecpar->color_range = AVCOL_RANGE_MPEG;
		m_pVideoStream->codecpar->color_space = AVCOL_SPC_BT709;
	}
	else
	{
		m_pVideoStream->codecpar->color_primaries = AVCOL_PRI_BT470M;
		m_pVideoStream->codecpar->color_range = AVCOL_RANGE_MPEG;
		m_pVideoStream->codecpar->color_space = AVCOL_SPC_BT470BG;
	}
	m_pVideoStream->codecpar->field_order = AV_FIELD_PROGRESSIVE;
	m_pVideoStream->codecpar->format = FFmpegFormatCovert::ConvertPixelFormat(videoInfo.enumColorFormat);
	m_pVideoStream->codecpar->width = videoInfo.dwWidth;
	m_pVideoStream->codecpar->height = videoInfo.dwHeight;

	return true;
}

bool ecCodecIntelProtocolEncoder::CreateAudioStream(const SDAudioMediaInfo & audioInfo)
{
	if (audioInfo.dwSamplesPerSec <= 0 || audioInfo.dwChannels <= 0 ||
		audioInfo.enumAudioType == SDAUDIOTYPE_UNKNOW) {
		return false;
	}

	m_pAudioStream = avformat_new_stream(m_pFormatCtx, NULL);
	if (!m_pAudioStream) {
		return false;
	}
	m_pAudioStream->time_base.num = 1;
	m_pAudioStream->time_base.den = audioInfo.dwSamplesPerSec;

	m_pAudioEncoder.reset(new ecCodecFFmpegAudioEncoder());
	if (!m_pAudioEncoder->InitAudioEncoder(audioInfo)) 
	{
		if (audioInfo.enumAudioType != SDAUDIOTYPE_WAVE_PCM)
		{
			return false;
		}
		else
		{
			//对于普通音频格式，走正常流程，对于PCM格式，不需要创建编码器，直接填写stream参数
			AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(audioInfo.enumAudioType);
			AVCodec* pAudioCodec = avcodec_find_encoder(codecId);
			if (!pAudioCodec) {
				return false;
			}
			AVCodecContext * pCodecCtx = avcodec_alloc_context3(pAudioCodec);
			if (!pCodecCtx) 
			{
				return false;
			}

			pCodecCtx->profile = FFmpegFormatCovert::ConvertAudioProfile(audioInfo.dwAudioSubType);			// AV_SAMPLE_FMT_FLTP;
			pCodecCtx->sample_fmt = FFmpegFormatCovert::ConvertSamplesFormat(audioInfo.enumChannelSamplesFormat);
			pCodecCtx->sample_rate = audioInfo.dwSamplesPerSec;												// 48000;
			pCodecCtx->channels = audioInfo.dwChannels;	       												// av_get_channel_layout_nb_channels(m_pCodecCtx->channel_layout);
			pCodecCtx->channel_layout = FFmpegFormatCovert::ConvertChannelLayout(audioInfo.enumAudioCFG);	// AV_CH_LAYOUT_STEREO;
			pCodecCtx->bit_rate = audioInfo.dwAvgBitsPerSec;
			pCodecCtx->time_base.num = 1;
			pCodecCtx->time_base.den = pCodecCtx->sample_rate;
			pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
			pCodecCtx->thread_count = 1;
			pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;

			if (pCodecCtx->codec_id == AV_CODEC_ID_AAC) {
				pCodecCtx->profile = FF_PROFILE_AAC_LOW;
				pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
			}

			if (avcodec_open2(pCodecCtx, pAudioCodec, nullptr) < 0) 
			{
				if (pCodecCtx)
				{
					avcodec_close(pCodecCtx);
					avcodec_free_context(&pCodecCtx);
				}
				return false;
			}

			avcodec_parameters_from_context(m_pAudioStream->codecpar, pCodecCtx);
			if (pCodecCtx)
			{
				avcodec_close(pCodecCtx);
				avcodec_free_context(&pCodecCtx);
			}
		}
	}
	else
	{
		AVCodecContext* pCodecContext = m_pAudioEncoder->GetCodecContext();
		//avcodec_copy_context(m_pAudioStream->codec, pCodecContext);
		avcodec_parameters_from_context(m_pAudioStream->codecpar, pCodecContext);
	}

	return true;
}
