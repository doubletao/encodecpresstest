#include "stdafx.h"
#include "FFmpegVideoEncoder.h"
#include "FormatConverter.h"

FFmpegVideoEncoder::FFmpegVideoEncoder()
	: m_pSourceFrame(nullptr)
	, m_pScaleFrame(nullptr)
	, m_pCodecCtx(nullptr)
	, m_pSwsCtx(nullptr)
	, m_pts(0)
	
{
	m_pDestBuffer.reset(new SW_UINT8[1920 * 1080 << 2]);   // 考虑RGBA
	memset(m_pDestBuffer.get(), 0, 1920 * 1080 << 2);
}

FFmpegVideoEncoder::~FFmpegVideoEncoder()
{
	Release();
}

bool FFmpegVideoEncoder::InitVideoEncoder(const SVideoMediaInfo *pDestVideoInfo)
{
	if (!pDestVideoInfo)
		return false;

	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(pDestVideoInfo->enumVideoType);
	AVCodec* pVideoEncoder = avcodec_find_encoder(codecId);
	if (!pVideoEncoder) {
		return false;
	}

	m_pCodecCtx = avcodec_alloc_context3(pVideoEncoder);
	if (!m_pCodecCtx) {
		return false;
	}
	
	m_pCodecCtx->pix_fmt = FFmpegFormatCovert::ConvertPixelFormat(pDestVideoInfo->enumColorFormat);
	m_pCodecCtx->width = pDestVideoInfo->dwWidth;
	m_pCodecCtx->height = pDestVideoInfo->dwHeight;
	m_pCodecCtx->bit_rate = pDestVideoInfo->dwDataRateInBitsPerSec;
	m_pCodecCtx->rc_min_rate = pDestVideoInfo->dwDataRateInBitsPerSec;
	m_pCodecCtx->rc_max_rate = pDestVideoInfo->dwDataRateInBitsPerSec;
	m_pCodecCtx->time_base.den = pDestVideoInfo->dwStandardRate;
	m_pCodecCtx->time_base.num = 1;
	m_pCodecCtx->framerate.den = 1;
	m_pCodecCtx->framerate.num = pDestVideoInfo->dwStandardRate;
	m_pCodecCtx->thread_count = 6; // more than one threads seem to increase delay
	m_pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;

	if (codecId == AV_CODEC_ID_H264)
	{
		m_pCodecCtx->gop_size = pDestVideoInfo->dwGOPSize;
		m_pCodecCtx->max_b_frames = 3;
		//该参数应当根据AVOutputFormat::flags & AVFMT_GLOBALHEADER来判定是否应该设置
		//m_pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
		//限制输出文件的profile。这个参数将覆盖其它所有值，此选项能保证输出profile兼容的视频流。如果使用了这个选项，将不能进行无损压缩（qp 0 or crf 0）。
		//m_pCodecCtx->profile = FFmpegFormatCovert::ConvertVideoProfile(pDestVideoInfo->enumVideoSubType);
	
		//m_pCodecCtx->refs = 3;
		//m_pCodecCtx->qmin = 10;
		//m_pCodecCtx->qmax = 51;
		//av_opt_set(m_pCodecCtx->priv_data, "preset", "superfast", 0);
		//av_opt_set(m_pCodecCtx->priv_data, "tune", "zerolatency", 0);
		//av_opt_set(m_pCodecCtx->priv_data, "profile", "baseline", 0);
	}

	int ret = avcodec_open2(m_pCodecCtx, pVideoEncoder, nullptr);  
	if (ret < 0) {
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(ret, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(ret));
		return false;
	}

	memcpy(m_pDestBuffer.get(), m_pCodecCtx->extradata, m_pCodecCtx->extradata_size);
	m_extradataSize = m_pCodecCtx->extradata_size;

	return true;
}

bool FFmpegVideoEncoder::SetVideoFrameBufInfo(const SVideoFrameImageBufInfo *pVideoBufInfo)
{
	if (!pVideoBufInfo || !m_pCodecCtx) {
		return false;
	}

	AVPixelFormat pixelFormat = FFmpegFormatCovert::ConvertPixelFormat(pVideoBufInfo->enumColorFormat);
	m_pSourceFrame = av_frame_alloc();
	m_pSourceFrame->format = pixelFormat;
	m_pSourceFrame->width = pVideoBufInfo->dwXSize;
	m_pSourceFrame->height = pVideoBufInfo->dwYSize;

	int ret = av_image_alloc(m_pSourceFrame->data, m_pSourceFrame->linesize, 
		pVideoBufInfo->dwXSize, pVideoBufInfo->dwYSize, pixelFormat, 4);
	if (ret < 0) {
		return false;
	}

	bool bScale = (pVideoBufInfo->dwXSize != m_pCodecCtx->width ||
		pVideoBufInfo->dwYSize != m_pCodecCtx->height || pixelFormat != m_pCodecCtx->pix_fmt);
	if (!bScale) {	// 无需缩放直接返回
		return true;
	}

	m_pScaleFrame = av_frame_alloc();
	m_pScaleFrame->format = m_pCodecCtx->pix_fmt;
	m_pScaleFrame->width = m_pCodecCtx->width;
	m_pScaleFrame->height = m_pCodecCtx->height;

	ret = av_image_alloc(m_pScaleFrame->data, m_pScaleFrame->linesize, 
		m_pCodecCtx->width, m_pCodecCtx->height, (AVPixelFormat)m_pScaleFrame->format, 4);
	if (ret < 0) {
		return false;
	}

	m_pSwsCtx = sws_getContext(pVideoBufInfo->dwXSize, pVideoBufInfo->dwYSize, pixelFormat,
		m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt,
		SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
	if (!m_pSwsCtx) {
		return false;
	}

	return true;
}

bool FFmpegVideoEncoder::PutFrame(const SW_UINT8* pFrameBuffer, const SRFrameInfo* pFrameInfo, bool bForceToKeyFrame)
{
	if (!m_pCodecCtx || !m_pSourceFrame || !pFrameInfo) {
		return false;
	}

	int imageBufSize = av_image_get_buffer_size((AVPixelFormat)m_pSourceFrame->format, 
		m_pSourceFrame->width, m_pSourceFrame->height, 4);
	if (pFrameInfo->iSize < imageBufSize) {
		return false;
	}

	if (0)
	{
		FILE * file;
		fopen_s(&file, "a.yuv", "wb+");
		if (file)
		{
			int y_size = m_pSourceFrame->width * m_pSourceFrame->height;
			fwrite((uint8_t *)pFrameBuffer[0], 1, y_size, file);    //Y 
			fwrite((uint8_t *)pFrameBuffer[1], 1, y_size / 4, file);  //U
			fwrite((uint8_t *)pFrameBuffer[2], 1, y_size / 4, file);  //V
			fclose(file);
		}
	}

	av_image_fill_arrays(m_pSourceFrame->data, m_pSourceFrame->linesize, pFrameBuffer,
		(AVPixelFormat)m_pSourceFrame->format, m_pSourceFrame->width, m_pSourceFrame->height, 4);

	if (0)
	{
		FILE * file;
		fopen_s(&file, "b.yuv", "wb+");
		if (file)
		{
			int y_size = m_pSourceFrame->width * m_pSourceFrame->height;
			fwrite(m_pSourceFrame->data[0], 1, y_size, file);    //Y 
			fwrite(m_pSourceFrame->data[1], 1, y_size / 4, file);  //U
			fwrite(m_pSourceFrame->data[2], 1, y_size / 4, file);  //V
			fclose(file);
		}
	}

	AVFrame* pSourceFrame = m_pSourceFrame;
	if (m_pSwsCtx) {
		sws_scale(m_pSwsCtx, m_pSourceFrame->data, m_pSourceFrame->linesize, 0, m_pSourceFrame->height,
			m_pScaleFrame->data, m_pScaleFrame->linesize);
		pSourceFrame = m_pScaleFrame;
	}

	pSourceFrame->pts = m_pts++;
	pSourceFrame->pict_type = bForceToKeyFrame ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_NONE;

	int ret = avcodec_send_frame(m_pCodecCtx, pSourceFrame);
	if (ret < 0) {
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(ret, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(ret));
		return false;
	}

	return true;
}

bool FFmpegVideoEncoder::SetEndofInput()
{
	return true;
}

bool FFmpegVideoEncoder::GetCompressFrame(SW_UINT8* &pFrameBuffer, SRFrameInfo *pFrameInfo)
{
	AVPacket avpkt = { 0 };
	av_init_packet(&avpkt);	// Note, this does not touch the data and size members, which have to be initialized separately.

	int ret = avcodec_receive_packet(m_pCodecCtx, &avpkt);
	if (ret < 0 || avpkt.size < 1) {
		char errbuf[128] = { 0 };
		const char *errbuf_ptr = errbuf;
		if (av_strerror(ret, errbuf, sizeof(errbuf)) < 0)
			strerror_s(errbuf, AVUNERROR(ret));
		av_packet_unref(&avpkt);
		return false;
	}

	if (0)
	{
		FILE * fp_debug = fopen("E:\\clip\\debug.h264", "ab");
		fwrite(avpkt.data, 1, avpkt.size, fp_debug);
		av_free_packet(&avpkt);
		fclose(fp_debug);
	}

	FRAME_COMPRESS_TYPE frameType = (avpkt.flags & AV_PKT_FLAG_KEY) ? FRAMETYPE_I : FRAMETYPE_UNKNOW;

	memcpy(m_pDestBuffer.get() + m_extradataSize, avpkt.data, avpkt.size);

	if (frameType == FRAMETYPE_I)
	{
		pFrameBuffer = m_pDestBuffer.get();
		pFrameInfo->iSize = avpkt.size + m_extradataSize;
		pFrameInfo->extradata_size = m_extradataSize;
	}
	else
	{
		pFrameBuffer = m_pDestBuffer.get() + m_extradataSize;
		pFrameInfo->iSize = avpkt.size;
		pFrameInfo->extradata_size = 0;
	}

	pFrameInfo->emFrameType = frameType;
	pFrameInfo->qwPTS = avpkt.pts;
	pFrameInfo->qwDTS = avpkt.dts;
	pFrameInfo->qwDuration = avpkt.duration;

	av_packet_unref(&avpkt);

	return true;
}

bool FFmpegVideoEncoder::Release()
{
	avcodec_close(m_pCodecCtx);
	avcodec_free_context(&m_pCodecCtx);	
	av_frame_free(&m_pSourceFrame);
	av_frame_free(&m_pScaleFrame);
	sws_freeContext(m_pSwsCtx);

	return true;
}

AVCodecContext* FFmpegVideoEncoder::GetCodecContext() const
{
	return m_pCodecCtx;
}