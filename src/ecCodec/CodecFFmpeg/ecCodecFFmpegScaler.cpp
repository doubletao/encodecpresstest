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
	memset(m_arrSrcLinesize, 0, sizeof(int) * AV_NUM_DATA_POINTERS);
}


ecCodecFFmpegScaler::~ecCodecFFmpegScaler()
{
	Release();
}

bool ecCodecFFmpegScaler::InitScaler(SD_UINT32 nSrcWidth, SD_UINT32 nSrcHeight, SD_COLOR_FORMAT emSrcColorFormat, SD_UINT32 nDesWidth, SD_UINT32 nDesHeight, SD_COLOR_FORMAT emDesColorFormat)
{
	m_nSrcWidth = nSrcWidth;
	m_nSrcHeight = nSrcHeight;
	m_emSrcPixFmt = FFmpegFormatCovert::ConvertPixelFormat(emSrcColorFormat);
	m_nDesWidth = nDesWidth;
	m_nDesHeight = nDesHeight;
	m_emDesPixFmt = FFmpegFormatCovert::ConvertPixelFormat(emDesColorFormat);
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
		for (size_t i = 0; i < AV_NUM_DATA_POINTERS; i++)
		{
			m_arrSrcLinesize[i] = pFrame->linesize[i];
		}
		if (pFrame)
		{
			av_frame_free(&pFrame);
		}
		m_bInitialized = true;
	}
	return true;
}

bool ecCodecFFmpegScaler::Scale(SD_UINT8 * pInBuf, SD_UINT8 *& pOutBuf)
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

bool ecCodecFFmpegScaler::Scale(uint8_t ** pInData, uint8_t **& pOutData)
{
	if (m_bInitialized)
	{
		sws_scale(m_pScaleCtx, pInData, m_arrSrcLinesize, 0, m_nSrcHeight,
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
	memset(m_arrSrcLinesize, 0, sizeof(int) * AV_NUM_DATA_POINTERS);
	return true;
}
