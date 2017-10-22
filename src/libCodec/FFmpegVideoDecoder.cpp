#include "stdafx.h"
#include "FFmpegVideoDecoder.h"
#include "FormatConverter.h"

FFmpegVideoDecoder::FFmpegVideoDecoder()
	: m_pSourceFrame(nullptr)
	, m_pScaleFrame(nullptr)
	, m_pCodecCtx(nullptr)
	, m_pScaleCtx(nullptr)
{
}

FFmpegVideoDecoder::~FFmpegVideoDecoder()
{
	Release();
}

bool FFmpegVideoDecoder::InitVideoDecoder(const SVideoMediaInfo	*pSrcVideoInfo)
{
	if (!pSrcVideoInfo) {
		return false;
	}

	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(pSrcVideoInfo->enumVideoType);
	AVCodec* pVideoCodec = avcodec_find_decoder(codecId);
	if (!pVideoCodec) {
		return false;
	}

	AVPixelFormat pixelFormat = FFmpegFormatCovert::ConvertPixelFormat(pSrcVideoInfo->enumColorFormat);

	m_pCodecCtx = avcodec_alloc_context3(pVideoCodec);
	m_pCodecCtx->width = pSrcVideoInfo->dwWidth;
	m_pCodecCtx->height = pSrcVideoInfo->dwHeight;
	m_pCodecCtx->pix_fmt = pixelFormat;
	m_pCodecCtx->flags2 |= CODEC_FLAG2_FAST;
	m_pCodecCtx->thread_count = 1;

	if (avcodec_open2(m_pCodecCtx, pVideoCodec, nullptr)) {
		return false;
	}

	m_pSourceFrame = av_frame_alloc();
	m_pSourceFrame->format = pixelFormat;
	m_pSourceFrame->width = pSrcVideoInfo->dwWidth;
	m_pSourceFrame->height = pSrcVideoInfo->dwHeight;

	int ret = av_image_alloc(m_pSourceFrame->data, m_pSourceFrame->linesize,
		pSrcVideoInfo->dwWidth, pSrcVideoInfo->dwHeight, pixelFormat, 4);
	if (ret < 0) {
		return false;
	}
	return true;
}

bool FFmpegVideoDecoder::SetVideoFrameBufInfo(const SVideoFrameImageBufInfo *pOutBufInfo)
{
	if (!pOutBufInfo) {
		return false;
	}

	AVPixelFormat pixelFormat = FFmpegFormatCovert::ConvertPixelFormat(pOutBufInfo->enumColorFormat);
	bool bScale = (pOutBufInfo->dwXSize != m_pCodecCtx->width ||
		pOutBufInfo->dwYSize != m_pCodecCtx->height || pixelFormat != m_pCodecCtx->pix_fmt);
	if (!bScale) { // 无需缩放直接返回
		return true;
	}

	m_pScaleFrame = av_frame_alloc();
	m_pScaleFrame->format = pixelFormat;
	m_pScaleFrame->width = pOutBufInfo->dwXSize;
	m_pScaleFrame->height = pOutBufInfo->dwYSize;

	int ret = av_image_alloc(m_pScaleFrame->data, m_pScaleFrame->linesize,
		pOutBufInfo->dwXSize, pOutBufInfo->dwYSize, pixelFormat, 4);
	if (ret < 0) {
		return false;
	}

	m_pScaleCtx = sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt,
		pOutBufInfo->dwXSize, pOutBufInfo->dwYSize, pixelFormat,
		SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
	if (!m_pScaleCtx) {
		return false;
	}

	return true;
}

bool FFmpegVideoDecoder::PutVideoFrame(const SW_UINT8 *pFrameBuffer, const SRFrameInfo *pFrameInfo)
{
	AVPacket avpkt;
	av_init_packet(&avpkt);
	avpkt.data = (SW_UINT8*)pFrameBuffer;
	avpkt.size = pFrameInfo->iSize;

	if (avcodec_send_packet(m_pCodecCtx, &avpkt) < 0) {
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);

	return true;
}

bool FFmpegVideoDecoder::SetEndofInput()
{
	return true;
}

bool FFmpegVideoDecoder::GetUnCompressFrame(SW_UINT8* &lpFrameBuffer, SRFrameInfo *pFrameInfo)
{
	if (!m_pCodecCtx || !m_pSourceFrame) {
		return false;
	}

	if (avcodec_receive_frame(m_pCodecCtx, m_pSourceFrame) < 0) {
		return false;
	}

	if (m_pScaleCtx && m_pScaleFrame)
	{
		sws_scale(m_pScaleCtx, m_pSourceFrame->data, m_pSourceFrame->linesize, 0,
			m_pSourceFrame->height, m_pScaleFrame->data, m_pScaleFrame->linesize);

		lpFrameBuffer = m_pScaleFrame->data[0];
		pFrameInfo->iSize = m_pScaleFrame->linesize[0] * m_pScaleFrame->height;
	}
	else
	{
		lpFrameBuffer = m_pSourceFrame->data[0];
		pFrameInfo->iSize = m_pSourceFrame->linesize[0] * m_pSourceFrame->height;
	}

	return true;
}

bool FFmpegVideoDecoder::Release()
{
	avcodec_close(m_pCodecCtx);
	avcodec_free_context(&m_pCodecCtx);

	av_frame_free(&m_pSourceFrame);
	av_frame_free(&m_pScaleFrame);

	sws_freeContext(m_pScaleCtx);
	m_pScaleCtx = nullptr;

	return true;
}