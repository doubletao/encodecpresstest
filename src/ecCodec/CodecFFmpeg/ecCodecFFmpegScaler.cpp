//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ecCodecFFmpegScaler.h"
#include "FFmpegFormatConverter.h"
#pragma comment(lib, "swscale.lib")


ecCodecFFmpegScaler::ecCodecFFmpegScaler()
	: m_pScaleCtx(nullptr)
	, m_pScaleFrame(nullptr)
	, m_bInitialized(false)
	, m_nSrcWidth(0)
	, m_nSrcHeight(0)
	, m_emSrcPixFmt(AV_PIX_FMT_NONE)
	, m_nDesWidth(0)
	, m_nDesHeight(0)
	, m_emDesPixFmt(AV_PIX_FMT_NONE)
{
}


ecCodecFFmpegScaler::~ecCodecFFmpegScaler()
{
	Release();
}

bool ecCodecFFmpegScaler::InitScaler(SD_UINT32 nSrcWidth, SD_UINT32 nSrcHeight, SD_COLOR_FORMAT emSrcColorFormat, SD_UINT32 nDesWidth, SD_UINT32 nDesHeight, SD_COLOR_FORMAT emDesColorFormat)
{
	Release();
	m_nSrcWidth = nSrcWidth;
	m_nSrcHeight = nSrcHeight;
	m_emSrcPixFmt = FFmpegFormatCovert::ConvertPixelFormat(emSrcColorFormat);
	m_nDesWidth = nDesWidth;
	m_nDesHeight = nDesHeight;
	m_emDesPixFmt = FFmpegFormatCovert::ConvertPixelFormat(emDesColorFormat);
	if (m_emSrcPixFmt == AV_PIX_FMT_NONE || m_emDesPixFmt == AV_PIX_FMT_NONE)
	{
		return false;
	}
	if (nSrcWidth != nDesWidth
		|| nSrcHeight != nDesHeight
		|| m_emSrcPixFmt != m_emDesPixFmt)
	{
		if (m_pScaleCtx)
		{
			sws_freeContext(m_pScaleCtx);
			m_pScaleCtx = nullptr;
		}
		m_pScaleCtx = sws_getContext(m_nSrcWidth, m_nSrcHeight, m_emSrcPixFmt,
			m_nDesWidth, m_nDesHeight, m_emDesPixFmt, SWS_SINC, nullptr, nullptr, nullptr);
		if (!m_pScaleCtx)
		{
			printf("sws_getContext failed\n");
			return false;
		}

		if (m_pScaleFrame)
		{
			av_frame_free(&m_pScaleFrame);
			m_pScaleFrame = nullptr;
		}
		m_pScaleFrame = av_frame_alloc();
		m_pScaleFrame->width = m_nDesWidth;
		m_pScaleFrame->height = m_nDesHeight;
		m_pScaleFrame->format = m_emDesPixFmt;
		int nRet = av_image_alloc(m_pScaleFrame->data, m_pScaleFrame->linesize, m_nDesWidth, m_nDesHeight, m_emDesPixFmt, sizeof(SD_UINT8));
		if (nRet < 0)
		{
			printf("av_image_alloc failed\n");
			return false;
		}

		AVFrame * pFrame = av_frame_alloc();
		pFrame->width = m_nSrcWidth;
		pFrame->height = m_nSrcHeight;
		pFrame->format = m_emSrcPixFmt;
		nRet = av_image_alloc(pFrame->data, pFrame->linesize, m_nSrcWidth, m_nSrcHeight, m_emSrcPixFmt, sizeof(SD_UINT8));
		if (nRet < 0)
		{
			printf("av_image_alloc failed\n");
			return false;
		}
		if (pFrame)
		{
			av_frame_free(&pFrame);
		}
		m_bInitialized = true;
	}
	return true;
}

bool ecCodecFFmpegScaler::Scale(SD_UINT8 * pInBuf, SD_UINT8 * pOutBuf)
{
	if (m_bInitialized)
	{
		AVFrame * pFrame = av_frame_alloc();
		pFrame->width = m_nSrcWidth;
		pFrame->height = m_nSrcHeight;
		pFrame->format = m_emSrcPixFmt;
		int nRet = av_image_alloc(pFrame->data, pFrame->linesize, m_nSrcWidth, m_nSrcHeight, m_emSrcPixFmt, sizeof(SD_UINT8));
		if (nRet < 0)
		{
			printf("av_image_alloc failed\n");
			return false;
		}
		FFmpegFormatCovert::ConvertBufferToPData(pInBuf, nullptr, pFrame->data, pFrame->linesize, m_emSrcPixFmt,
			m_nSrcWidth, m_nSrcHeight, sizeof(SD_UINT8));
		sws_scale(m_pScaleCtx, pFrame->data, pFrame->linesize, 0, m_nSrcHeight,
			m_pScaleFrame->data, m_pScaleFrame->linesize);
		FFmpegFormatCovert::ConvertPDataToBuffer(m_pScaleFrame->data, m_pScaleFrame->linesize, pOutBuf, GetBufferSize(), m_emDesPixFmt,
			m_nDesWidth, m_nDesHeight, sizeof(SD_UINT8));
		if (pFrame)
		{
			av_frame_free(&pFrame);
		}
		if (1)
		{
			FILE * file;
			fopen_s(&file, "src.yuv", "wb+");
			if (file)
			{
				int y_size = m_pScaleFrame->width * m_pScaleFrame->height;
				fwrite(m_pScaleFrame->data[0], 1, y_size, file);    //Y 
				fwrite(m_pScaleFrame->data[1], 1, y_size / 4, file);  //U
				fwrite(m_pScaleFrame->data[2], 1, y_size / 4, file);  //V
				fclose(file);
			}
		}
		return true;
	}
	return false;
}

bool ecCodecFFmpegScaler::Scale(uint8_t ** pInData, const int srcStride[], uint8_t **& pOutData)
{
	if (m_bInitialized)
	{
		sws_scale(m_pScaleCtx, pInData, srcStride, 0, m_nSrcHeight,
			m_pScaleFrame->data, m_pScaleFrame->linesize);
		pOutData = m_pScaleFrame->data;
		if (0)
		{
			FILE * file;
			fopen_s(&file, "src.yuv", "wb+");
			if (file)
			{
				int y_size = m_pScaleFrame->width * m_pScaleFrame->height;
				fwrite(m_pScaleFrame->data[0], 1, y_size, file);    //Y 
				fwrite(m_pScaleFrame->data[1], 1, y_size / 4, file);  //U
				fwrite(m_pScaleFrame->data[2], 1, y_size / 4, file);  //V
				fclose(file);
			}
		}
		if (0)
		{
			FILE * file;
			fopen_s(&file, "src.yuv", "wb+");
			if (file)
			{
				int nSize = m_pScaleFrame->width * m_pScaleFrame->height * 2;
				char * video_decode_buf = new char[nSize];
				int i = 0;
				int j = 0;
				int k = 0;
				for (i = 0; i < m_pScaleFrame->height; i++)
				{
					memcpy(video_decode_buf + m_pScaleFrame->width*i,
						m_pScaleFrame->data[0] + m_pScaleFrame->linesize[0] * i,
						m_pScaleFrame->width);
				}
				for (j = 0; j < m_pScaleFrame->height; j++)
				{
					memcpy(video_decode_buf + m_pScaleFrame->width*i + m_pScaleFrame->width / 2 * j,
						m_pScaleFrame->data[1] + m_pScaleFrame->linesize[1] * j,
						m_pScaleFrame->width / 2);
				}
				for (k = 0; k < m_pScaleFrame->height; k++)
				{
					memcpy(video_decode_buf + m_pScaleFrame->width*i + m_pScaleFrame->width / 2 * j + m_pScaleFrame->width / 2 * k,
						m_pScaleFrame->data[2] + m_pScaleFrame->linesize[2] * k,
						m_pScaleFrame->width / 2);
				}
				fwrite(video_decode_buf, nSize, 1, file);
				fclose(file);
			}
		}
		return true;
	}
	return false;
}

int * ecCodecFFmpegScaler::GetDesLineSize()
{
	return m_pScaleFrame->linesize;
}

bool ecCodecFFmpegScaler::IsInitialized()
{
	return m_bInitialized;
}

SD_UINT32 ecCodecFFmpegScaler::GetBufferSize()
{
	return av_image_get_buffer_size(m_emDesPixFmt, m_nDesWidth, m_nDesHeight, sizeof(SD_UINT8));
}

bool ecCodecFFmpegScaler::Release()
{
	if (m_pScaleCtx)
	{
		sws_freeContext(m_pScaleCtx);
		m_pScaleCtx = nullptr;
	}
	if (m_pScaleFrame)
	{
		av_frame_free(&m_pScaleFrame);
	}
	m_nSrcWidth = 0;
	m_nSrcHeight = 0;
	m_emSrcPixFmt = AV_PIX_FMT_NONE;
	m_nDesWidth = 0;
	m_nDesHeight = 0;
	m_emDesPixFmt = AV_PIX_FMT_NONE;
	m_bInitialized = false;
	return true;
}
