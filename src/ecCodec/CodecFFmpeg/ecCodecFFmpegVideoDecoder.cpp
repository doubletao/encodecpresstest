#include "ecCodecFFmpegVideoDecoder.h"
#include "FFmpegFormatConverter.h"
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")


ecCodecFFmpegVideoDecoder::ecCodecFFmpegVideoDecoder()
	: m_pCodecCtx(nullptr)
	, m_bIsInitialized(false)
	, m_pFrame(nullptr)
	, m_nDesWidth(0)
	, m_nDesHeight(0)
	, m_emDesColorFormat(SDCOLORFORMAT_UNKNOW)
{
}


ecCodecFFmpegVideoDecoder::~ecCodecFFmpegVideoDecoder()
{
	Release();
}

bool ecCodecFFmpegVideoDecoder::InitVideoDecoder(const SDVideoMediaInfo & pSrcVideoInfo)
{
	Release();
	//查找解码器
	AVCodecID codecID = FFmpegFormatCovert::ConvertCodecId(pSrcVideoInfo.enumVideoType);
	AVCodec * pVideoCodec = avcodec_find_decoder(codecID);
	if (pVideoCodec)
	{
		//解码参数转成解码上下文
		m_pCodecCtx = avcodec_alloc_context3(pVideoCodec);
		m_pCodecCtx->pix_fmt = FFmpegFormatCovert::ConvertPixelFormat(pSrcVideoInfo.enumColorFormat);
		m_pCodecCtx->width = pSrcVideoInfo.dwWidth;
		m_pCodecCtx->height = pSrcVideoInfo.dwHeight;
		m_pCodecCtx->bit_rate = pSrcVideoInfo.dwDataRateInBitsPerSec;
		m_pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
		m_pCodecCtx->extradata = (uint8_t *)pSrcVideoInfo.dwDisplayWidth;
		m_pCodecCtx->extradata_size = pSrcVideoInfo.dwDisplayHeight;
		if (m_pCodecCtx)
		{
			//根据解码上下文打开解码器
			if (avcodec_open2(m_pCodecCtx, pVideoCodec, nullptr) == 0)
			{
				if (m_pFrame)
				{
					av_frame_free(&m_pFrame);
				}
				m_pFrame = av_frame_alloc();
				m_nDesWidth = m_pCodecCtx->width;
				m_nDesHeight = m_pCodecCtx->height;
				m_emDesColorFormat = FFmpegFormatCovert::ConvertColorFormat(m_pCodecCtx->pix_fmt);
				m_bIsInitialized = true;
			}
			else
			{
				printf("failed to open codec\n");
			}
		}
		else
		{
			printf("failed to find codec\n");
		}
	}
	else
	{
		printf("failed to get codexcontext\n");
	}
	return m_bIsInitialized;
}

bool ecCodecFFmpegVideoDecoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pOutBufInfo)
{
	SDVideoMediaInfo mediaInfo;
	if (GetVideoMediaInfo(&mediaInfo))
	{
		int nSrcWidth = mediaInfo.dwWidth;
		int nSrcHeight = mediaInfo.dwHeight;
		SD_COLOR_FORMAT emSrcColorFormat = mediaInfo.enumColorFormat;
		m_nDesWidth = pOutBufInfo->dwXSize;
		m_nDesHeight = pOutBufInfo->dwYSize;
		m_emDesColorFormat = pOutBufInfo->enumColorFormat;
		if (nSrcWidth != m_nDesWidth
			|| nSrcHeight != m_nDesHeight
			|| emSrcColorFormat != m_emDesColorFormat)
		{
			return m_VideoScaler.InitScaler(nSrcWidth, nSrcHeight, emSrcColorFormat, m_nDesWidth, m_nDesHeight, m_emDesColorFormat);
		}
		return true;
	}
	return false;
}

bool ecCodecFFmpegVideoDecoder::PutVideoFrame(const SD_UINT8 * pFrameBuffer, const SDRFrameInfo * pFrameInfo)
{
	AVPacket avpkt;
	av_init_packet(&avpkt);
	avpkt.data = (SD_UINT8*)pFrameBuffer;
	avpkt.size = pFrameInfo->iSize;
	avpkt.dts = pFrameInfo->qwDTS;
	avpkt.pts = pFrameInfo->qwPTS;
	avpkt.duration = pFrameInfo->qwDuration;

	if (avcodec_send_packet(m_pCodecCtx, &avpkt) < 0) {
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);
	return true;
}

bool ecCodecFFmpegVideoDecoder::SetEndofInput()
{
	if (m_bIsInitialized)
	{
		avcodec_send_packet(m_pCodecCtx, nullptr);
		return true;
	}
	return false;
}

bool ecCodecFFmpegVideoDecoder::GetUnCompressFrame(SD_UINT8 *& lpFrameBuffer, SDRFrameInfo * pFrameInfo)
{
	if (!m_pCodecCtx || !m_pFrame) {
		return false;
	}

	if (avcodec_receive_frame(m_pCodecCtx, m_pFrame) < 0) {
		return false;
	}

	if (m_pFrame)
	{
		pFrameInfo->emFrameType = FFmpegFormatCovert::ConvertCompressType(m_pFrame->pict_type);
		if (m_VideoScaler.IsInitialized())
		{
			uint8_t ** pScaledData = nullptr;
			m_VideoScaler.Scale(m_pFrame->data, pScaledData);
			if (0)
			{
				FILE * file;
				fopen_s(&file, "scaled.yuv", "wb+");
				if (file)
				{
					int y_size = m_nDesWidth * m_nDesHeight;
					fwrite(pScaledData[0], 1, y_size, file);    //Y 
					fwrite(pScaledData[1], 1, y_size / 4, file);  //U
					fwrite(pScaledData[2], 1, y_size / 4, file);  //V
					fclose(file);
				}
			}
			FFmpegFormatCovert::ConvertPDataToBuffer(pScaledData, m_VideoScaler.GetDesLineSize(), lpFrameBuffer, m_VideoScaler.GetBufferSize(),
				FFmpegFormatCovert::ConvertPixelFormat(m_emDesColorFormat), m_nDesWidth, m_nDesHeight, sizeof(SD_UINT8));
			pFrameInfo->iSize = m_VideoScaler.GetBufferSize();
		}
		else
		{
			FFmpegFormatCovert::ConvertPDataToBuffer(m_pFrame->data, m_pFrame->linesize, lpFrameBuffer, GetBufferSize(),
				FFmpegFormatCovert::ConvertPixelFormat(m_emDesColorFormat), m_nDesWidth, m_nDesHeight, sizeof(SD_UINT8));
			pFrameInfo->iSize = GetBufferSize();
		}
	}

	return true;
}

bool ecCodecFFmpegVideoDecoder::GetVideoMediaInfo(SDVideoMediaInfo * mediaInfo)
{
	if (mediaInfo && m_bIsInitialized)
	{
		mediaInfo->dwWidth = m_pCodecCtx->width;//图像宽度（水平分辨率）
		mediaInfo->dwHeight = m_pCodecCtx->height;//图像高度（垂直分辨率）
		mediaInfo->dwStandardRate = m_pCodecCtx->time_base.den;//不确定
		mediaInfo->dwStandardScale = m_pCodecCtx->time_base.num;//不确定
		mediaInfo->enumScanMode = FFmpegFormatCovert::ConvertVideoFieldOrder(m_pCodecCtx->field_order);//视频扫描帧场数据排列方式
		mediaInfo->enumColorFormat = FFmpegFormatCovert::ConvertColorFormat(m_pCodecCtx->pix_fmt);//视频颜色格式
		mediaInfo->enumVideoType = FFmpegFormatCovert::ConvertVideoCodecType(m_pCodecCtx->codec_id);//视频编解码类型
		mediaInfo->dwVideoSubType = FFmpegFormatCovert::ConvertVideoCodecSubType(m_pCodecCtx->codec_tag);//不确定视频编解码的子类型,子类型定义随enumVideoType不同而不同
		mediaInfo->enumDataRateType = SDDATARATE_CONSTANT;//暂时不知道怎么拿，给空				// Mpeg专用设置
		mediaInfo->dwGOPSize = m_pCodecCtx->gop_size;// IBP帧压缩类型时的IBP帧组大小		// Mpeg专用设置
		mediaInfo->dwReferencePeriod = 0;//暂时不知道怎么拿，给空
		mediaInfo->bIsClipped = 0;//暂时不知道怎么拿，给空
		mediaInfo->dwDisplayWidth = m_pCodecCtx->width;				// 视频显示幅宽度值
		mediaInfo->dwDisplayHeight = m_pCodecCtx->height;			// 视频显示幅高度值
		mediaInfo->enumColorPrimaries = FFmpegFormatCovert::ConvertColorPrimaries(m_pCodecCtx->color_primaries);			// 源基色的色度坐标(ISO13818-2)
		mediaInfo->enumColorTransfer = FFmpegFormatCovert::ConvertColorTransfer(m_pCodecCtx->color_trc);			// 光电转换特性(ISO13818-2)
		mediaInfo->enumColorMatrix = FFmpegFormatCovert::ConvertColorSpace(m_pCodecCtx->colorspace);			// 颜色空间变换系数(ISO13818-2)
		mediaInfo->enumAFD = SDAFD_UNKNOW;//暂时不知道怎么拿，给空
		mediaInfo->dwDataRateInBitsPerSec = (SD_UINT32)m_pCodecCtx->bit_rate;//不确定
		mediaInfo->dwMaxDataRateInBitsPerSec = (SD_UINT32)m_pCodecCtx->rc_max_rate;//不确定
		mediaInfo->dwMinDataRateInBitsPerSec = (SD_UINT32)m_pCodecCtx->rc_min_rate;//不确定
		mediaInfo->dwStruSize = sizeof(SDVideoMediaInfo);
		return true;
	}
	return false;
}

bool ecCodecFFmpegVideoDecoder::IsInitialized()
{
	return m_bIsInitialized;
}

SD_UINT32 ecCodecFFmpegVideoDecoder::GetBufferSize()
{
	if (m_VideoScaler.IsInitialized())
	{
		return m_VideoScaler.GetBufferSize();
	}
	else if (m_pCodecCtx)
	{
		return av_image_get_buffer_size(m_pCodecCtx->pix_fmt, m_pCodecCtx->width, m_pCodecCtx->height, sizeof(SD_UINT8));
	}
	return 0;
}

bool ecCodecFFmpegVideoDecoder::Release()
{
	if (m_pCodecCtx)
	{
		avcodec_close(m_pCodecCtx);
		avcodec_free_context(&m_pCodecCtx);
	}
	if (m_pFrame)
	{
		av_frame_free(&m_pFrame);
	}
	m_nDesWidth = 0;
	m_nDesHeight = 0;
	m_emDesColorFormat = SDCOLORFORMAT_UNKNOW;
	m_VideoScaler.Release();
	m_bIsInitialized = false;
	return true;
}
