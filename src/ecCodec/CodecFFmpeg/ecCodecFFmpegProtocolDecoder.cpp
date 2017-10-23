#include "ecCodecFFmpegProtocolDecoder.h"
#include "FFmpegFormatConverter.h"
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

ecCodecFFmpegProtocolDecoder::ecCodecFFmpegProtocolDecoder()
	: m_bIsInitialized(false)
	, m_nVideoIndex(-1)
	, m_pFormatCtx(nullptr)
	, m_pVideoPacket(nullptr)
	, m_nAudioIndex(-1)
	, m_nCurrentSeekPos(0)
	, m_bSeek(false)
{
}


ecCodecFFmpegProtocolDecoder::~ecCodecFFmpegProtocolDecoder()
{
	Release();
}

bool ecCodecFFmpegProtocolDecoder::SetSourcePath(const char * pFullPath)
{
	if (m_bIsInitialized)
	{
		printf("release codec before open again\n");
		return false;
	}
	//注册所有支持的格式
	av_register_all();
	//网络组件的初始化（非必须）,应该是解网络流的时候在用
	//avformat_network_init();
	//创建解封装器
	m_pFormatCtx = avformat_alloc_context();
	if (m_pFormatCtx)
	{
		//解封装
		if (avformat_open_input(&m_pFormatCtx, pFullPath, nullptr, nullptr) == 0)
		{
			//得到流数据
			if (avformat_find_stream_info(m_pFormatCtx, nullptr) >= 0)
			{
				//查找视频流
				m_nVideoIndex = av_find_best_stream(m_pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
				if (m_nVideoIndex > -1)
				{
					//找到视频流后处理视频
					//根据编码格式查找解码器
					//先拿到解码参数
					AVCodecParameters * pVideoCodecParm = m_pFormatCtx->streams[m_nVideoIndex]->codecpar;
					if (pVideoCodecParm)
					{
						SDVideoMediaInfo videoInfo;
						videoInfo.enumColorFormat = FFmpegFormatCovert::ConvertColorFormat((AVPixelFormat)m_pFormatCtx->streams[m_nVideoIndex]->codecpar->format);
						videoInfo.dwWidth = m_pFormatCtx->streams[m_nVideoIndex]->codecpar->width;
						videoInfo.dwHeight = m_pFormatCtx->streams[m_nVideoIndex]->codecpar->height;
						videoInfo.dwDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->streams[m_nVideoIndex]->codecpar->bit_rate;
						videoInfo.enumVideoType = FFmpegFormatCovert::ConvertVideoCodecType(m_pFormatCtx->streams[m_nVideoIndex]->codecpar->codec_id);
						videoInfo.dwDisplayWidth = (SD_UINT32)(m_pFormatCtx->streams[m_nVideoIndex]->codecpar->extradata);
						videoInfo.dwDisplayHeight = m_pFormatCtx->streams[m_nVideoIndex]->codecpar->extradata_size;
						//创建解码器
						if (m_VideoDecoder.InitVideoDecoder(videoInfo))
						{
							m_pVideoPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
							av_init_packet(m_pVideoPacket);
							m_bIsInitialized = true;
						}
						else
						{
							printf("failed to initial video decoder\n");
						}
					}
					else
					{
						printf("failed to get codecparam\n");
					}
				}
				else
				{
					printf("failed to find video stream\n");
				}
				//查找音频流
				m_nAudioIndex = av_find_best_stream(m_pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
				if (m_nAudioIndex > -1)
				{
					//找到音频流后处理音频
					//根据编码格式查找解码器
					//先拿到解码参数
					AVCodecParameters * pAudioCodecParm = m_pFormatCtx->streams[m_nAudioIndex]->codecpar;
					if (pAudioCodecParm)
					{
						SDAudioMediaInfo audioInfo; 
						audioInfo.enumAudioType = FFmpegFormatCovert::ConvertAudioType(pAudioCodecParm->codec_id);		// 音频编解码类型。
						audioInfo.dwAudioSubType = 0;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
						audioInfo.dwChannels = pAudioCodecParm->channels;			// 声道数目
						audioInfo.dwBitsPerSample = pAudioCodecParm->bits_per_raw_sample;	// 采样位数 
						audioInfo.dwSamplesPerSec = pAudioCodecParm->sample_rate;	// 每秒采样数量 
						audioInfo.dwAvgBitsPerSec = pAudioCodecParm->bit_rate;	// 音频码率 bits
						audioInfo.dwBlockAlign = pAudioCodecParm->block_align;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...										//Below is Version 2 Add.
						audioInfo.enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(pAudioCodecParm->channel_layout);		//声道属性
						audioInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Unknow;	//音频声道采样数据格式
						audioInfo.dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
						//创建解码器
						if (m_AudioDecoder.InitAudioDecoder(audioInfo))
						{
							m_bIsInitialized = true;
						}
						else
						{
							printf("failed to initial video decoder\n");
						}
					}
					else
					{
						printf("failed to get codecparam\n");
					}
				}
				else
				{
					printf("failed to find video stream\n");
				}
				if (m_bIsInitialized)
				{
					return true;
				}
			}
			else
			{
				printf("failed to find stream\n");
			}
		}
		else
		{
			printf("failed to open input\n");
		}
	}
	else
	{
		printf("failed to alloc context\n");
	}
	Release();
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetFileGlobalMediaInfo(SDStreamMediaInfo * psMediaInfo)
{
	if (!psMediaInfo || !m_bIsInitialized)
	{
		return false;
	}
	psMediaInfo->enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;//暂时不知道怎么拿，给空
	psMediaInfo->dwStreamMediaSubType = 0;//暂时不知道怎么拿，给空
	psMediaInfo->dwTotalAverDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
	psMediaInfo->dwTotalMaxDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
	psMediaInfo->dwTotalMinDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
	
	psMediaInfo->dwVideoStreamCount = 1;//不管有几个，解码器目前只解一个
	if (m_VideoDecoder.IsInitialized())
	{
		m_VideoDecoder.GetVideoMediaInfo(&psMediaInfo->sVideoMediaInfo);
	}

	if (m_AudioDecoder.IsInitialized())
	{
		psMediaInfo->dwAudioStreamCount = 1;//不管有几个，解码器目前只解一个
		m_AudioDecoder.GetAudioMediaInfo(&psMediaInfo->sAudioMediaInfo);
	}
	//字幕信息目前不解
	psMediaInfo->dwSubtitleStreamCount = 0;
	psMediaInfo->sSubtitleMediaInfo;

	psMediaInfo->dwStruSize = sizeof(SDStreamMediaInfo);
	return true;
}

bool ecCodecFFmpegProtocolDecoder::GetFileGlobalMediaInfo(SDStreamMediaInfoEx * psMediaInfoEx)
{
	if (!psMediaInfoEx || !m_bIsInitialized)
	{
		return false;
	}
	psMediaInfoEx->enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;//暂时不知道怎么拿，给空
	psMediaInfoEx->dwStreamMediaSubType = 0;//暂时不知道怎么拿，给空
	psMediaInfoEx->dwTotalAverDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
	psMediaInfoEx->dwTotalMaxDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
	psMediaInfoEx->dwTotalMinDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定

	psMediaInfoEx->dwVideoStreamCount = 1;//不管有几个，解码器目前只解一个
	if (m_VideoDecoder.IsInitialized())
	{
		m_VideoDecoder.GetVideoMediaInfo(&psMediaInfoEx->sVideoMediaInfo);
	}

	if (m_AudioDecoder.IsInitialized())
	{
		psMediaInfoEx->dwAudioStreamCount = 1;//不管有几个，解码器目前只解一个
		m_AudioDecoder.GetAudioMediaInfo(&psMediaInfoEx->sAudioMediaInfo);
	}
	//字幕信息目前不解
	psMediaInfoEx->dwSubtitleStreamCount = 0;
	psMediaInfoEx->sSubtitleMediaInfo;

	if (m_pFormatCtx)
	{
		FILE * fp = nullptr;
		fopen_s(&fp, m_pFormatCtx->filename, "r");
		if (fp)
		{
			fseek(fp, 0L, SEEK_END);
			psMediaInfoEx->llFileSize = ftell(fp);
			fclose(fp);
		}
		if (m_nVideoIndex > -1)
		{
			AVRational time_base = m_pFormatCtx->streams[m_nVideoIndex]->time_base;
			psMediaInfoEx->dwVideoFrameNum = (SD_UINT32)av_rescale(m_pFormatCtx->streams[m_nVideoIndex]->duration, time_base.num, time_base.den);
		}
		if (m_nAudioIndex > -1)
		{
			AVRational time_base = m_pFormatCtx->streams[m_nAudioIndex]->time_base;
			psMediaInfoEx->dwAudioSamplesNum = (SD_UINT32)av_rescale(m_pFormatCtx->streams[m_nAudioIndex]->duration, time_base.num, time_base.den);
		}
	}
	psMediaInfoEx->dwAudioSamplesNum;		// 音频流数据长度	 (Unit:Sample)
	psMediaInfoEx->dwSubtitleFrameNum;		// 字幕流数据的长度(Unit:SubtitleFrame)

	psMediaInfoEx->dwStruSize = sizeof(SDStreamMediaInfoEx);
	return true;
}

bool ecCodecFFmpegProtocolDecoder::IsCanReadVideoFrame()
{
	return true;
}

bool ecCodecFFmpegProtocolDecoder::IsCanReadAudioFrame()
{
	return true;
}

bool ecCodecFFmpegProtocolDecoder::Start()
{
	return false;
}

bool ecCodecFFmpegProtocolDecoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pVideoBufInfo, const SDResamplerPara * pResamplerPara)
{
	if (m_VideoDecoder.IsInitialized() && pVideoBufInfo)
	{
		return m_VideoDecoder.SetVideoFrameBufInfo(pVideoBufInfo);
	}
	printf("file not open or open failed\n");
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetVideoFrameBufInfo(SDVideoFrameImageBufInfo * pVideoBufInfo, SDResamplerPara * pResamplerPara)
{
	if (m_VideoDecoder.IsInitialized() && pVideoBufInfo)
	{
		SDVideoMediaInfo mediaInfo;
		if (m_VideoDecoder.GetVideoMediaInfo(&mediaInfo))
		{
			pVideoBufInfo->dwXSize = mediaInfo.dwWidth;
			pVideoBufInfo->dwYSize = mediaInfo.dwHeight;
			pVideoBufInfo->enumColorFormat = mediaInfo.enumColorFormat;
		}
		return true;
	}
	return false;
}

SD_UINT32 ecCodecFFmpegProtocolDecoder::GetVideoBufferSize()
{
	if (m_VideoDecoder.IsInitialized())
	{
		return m_VideoDecoder.GetBufferSize();
	}
	else
	{
		return 0;
	}
}

SD_UINT32 ecCodecFFmpegProtocolDecoder::GetAudioBufferSize()
{
	if (m_AudioDecoder.IsInitialized())
	{
		return m_AudioDecoder.GetBufferSize();
	}
	else
	{
		return 0;
	}
}

bool ecCodecFFmpegProtocolDecoder::SetVideoDecoderThread(SD_INT32 dwDecoderThread)
{
	return false;
}

SD_INT32 ecCodecFFmpegProtocolDecoder::GetVideoDecoderThread()
{
	return SD_INT32();
}

bool ecCodecFFmpegProtocolDecoder::SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo * pAudioBufInfo)
{
	if (m_AudioDecoder.IsInitialized() && pAudioBufInfo)
	{
		SDAudioMediaInfo mediaInfo;
		mediaInfo.dwChannels = pAudioBufInfo->dwChannels;
		mediaInfo.dwBitsPerSample = pAudioBufInfo->dwBitsPerSample;
		mediaInfo.dwSamplesPerSec = pAudioBufInfo->dwSamplesPerSec;
		mediaInfo.dwAvgBitsPerSec = pAudioBufInfo->dwAvgBitsPerSec;
		mediaInfo.dwBlockAlign = pAudioBufInfo->dwBlockAlign;
		mediaInfo.enumAudioCFG = pAudioBufInfo->enumAudioCFG;
		mediaInfo.enumChannelSamplesFormat = pAudioBufInfo->enumChannelSamplesFormat;
		if (m_AudioDecoder.SetAudioMediaInfo(&mediaInfo))
		{
			return true;
		}
	}
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetAudioSamplesBufInfo(SDAudioSamplesBufInfo * pAudioBufInfo)
{
	if (m_AudioDecoder.IsInitialized() && pAudioBufInfo)
	{
		SDAudioMediaInfo mediaInfo;
		if (m_AudioDecoder.GetAudioMediaInfo(&mediaInfo))
		{
			pAudioBufInfo->dwChannels = mediaInfo.dwChannels;								// 声道数目
			pAudioBufInfo->dwBitsPerSample = mediaInfo.dwBitsPerSample;						// 采样位数 
			pAudioBufInfo->dwSamplesPerSec = mediaInfo.dwSamplesPerSec;						// 每秒采样数量 
			pAudioBufInfo->dwAvgBitsPerSec = mediaInfo.dwAvgBitsPerSec;						// 音频码率 bits
			pAudioBufInfo->dwBlockAlign = mediaInfo.dwBlockAlign;							// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
			pAudioBufInfo->enumAudioCFG = mediaInfo.enumAudioCFG;				// 声道属性
			pAudioBufInfo->enumChannelSamplesFormat = mediaInfo.enumChannelSamplesFormat;	// 音频声道采样数据格式
			return true;
		}
	}
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetVideoBuffer(SD_UINT64 dwCurFrameShowIndex, SD_UINT8 * pFrameBuf, SDRFrameInfo * pFrameInfo)
{
	bool bRet = false;
	if (dwCurFrameShowIndex >= 0)
	{
		if (m_bIsInitialized && m_VideoDecoder.IsInitialized())
		{
			SDRFrameInfo frameInfo;
			SD_UINT8 * pCompressFrame = nullptr;
			AVRational time_base = m_pFormatCtx->streams[m_nVideoIndex]->time_base;
			m_nCurrentSeekPos = m_pFormatCtx->streams[m_nVideoIndex]->start_time + av_rescale(dwCurFrameShowIndex, time_base.den, time_base.num);
			while (GetVideoFrame(dwCurFrameShowIndex, pCompressFrame, &frameInfo) && pCompressFrame)
			{
				if (m_VideoDecoder.PutVideoFrame(pCompressFrame, &frameInfo))
				{
					if (pFrameBuf && m_VideoDecoder.GetUnCompressFrame(pFrameBuf, &frameInfo))
					{
						if (pFrameInfo)
						{
							pFrameInfo->iVersion = 0;
							pFrameInfo->emDataType = STREAM_DATATYPE_VIDEO;
							pFrameInfo->emStreamFlag = frameInfo.emStreamFlag;
							pFrameInfo->iSize = GetVideoBufferSize();
							pFrameInfo->dwFrameIndex = dwCurFrameShowIndex;
							pFrameInfo->dwFrameNum = 1;
							pFrameInfo->iSamplesOffset = 0;
							pFrameInfo->qwDTS = frameInfo.qwDTS;
							pFrameInfo->qwPTS = frameInfo.qwPTS;
							pFrameInfo->qwDuration = frameInfo.qwDuration;
							pFrameInfo->dwShowIndex = pFrameInfo->dwFrameIndex;
							pFrameInfo->emFrameType = frameInfo.emFrameType;
							pFrameInfo->extradata_size = 0;
							if (!m_bSeek)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetVideoFrame(SD_UINT64 dwCurFrameShowIndex, SD_UINT8 *& pFrameBuf, SDRFrameInfo * pFrameInfo)
{
	bool bRet = false;
	if (m_bIsInitialized)
	{
		AVStream * pVideoStream = m_pFormatCtx->streams[m_nVideoIndex];
		if (pVideoStream)
		{
			bool bContinue = false;
			if (dwCurFrameShowIndex != (SD_UINT64)-1)
			{
				if (m_bSeek)
				{
					bContinue = true;
				}
				else
				{
					if (m_nCurrentSeekPos == 0)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nVideoIndex, m_nCurrentSeekPos, AVSEEK_FLAG_FRAME);
						if (nRet >= 0)
						{
							bContinue = true;
						}
					}
					else if (m_nCurrentSeekPos <= pVideoStream->duration)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nVideoIndex, m_nCurrentSeekPos, AVSEEK_FLAG_BACKWARD);
						if (nRet >= 0)
						{
							bContinue = true;
						}
					}
					else
					{
						//seek pos已经到头了，直接退出
						return false;
					}
					m_bSeek = true;
				}
			}
			else
			{
				bContinue = true;
			}
			if (bContinue)
			{
				while (m_pVideoPacket)
				{
					av_packet_unref(m_pVideoPacket);
					if (av_read_frame(m_pFormatCtx, m_pVideoPacket) < 0)
					{
						//没读到，直接返回（可能是文件尾）
						return false;
					}
					if (m_pVideoPacket->stream_index != m_nVideoIndex)
					{
						//找出视频流
						continue;
					}
					if (m_bSeek)
					{
						if (m_pVideoPacket->dts >= m_nCurrentSeekPos)
						{
							m_bSeek = false;
						}
					}
					pFrameBuf = m_pVideoPacket->data;
					if (pFrameInfo)
					{
						pFrameInfo->iSize = m_pVideoPacket->size;
						pFrameInfo->qwDTS = m_pVideoPacket->dts;
						pFrameInfo->qwPTS = m_pVideoPacket->pts;
						pFrameInfo->qwDuration = m_pVideoPacket->duration;
						pFrameInfo->emStreamFlag = m_pVideoPacket->pts == 0 ? STREAMSTATE_BEGIN : STREAMSTATE_CONTINUE;
					}
					bRet = true;
					break;
				}
			}
		}
	}
	return bRet;
}

bool ecCodecFFmpegProtocolDecoder::GetAudioSamples(SD_UINT32 dwCurSamplePos, SD_UINT32 dwSampleNum, SD_UINT8 * pSamplesBuf, SD_UINT32 * pdwRetSampleNum)
{
	bool bRet = false;
	if (dwCurSamplePos >= 0)
	{
		if (m_bIsInitialized && m_AudioDecoder.IsInitialized())
		{
			SDRFrameInfo frameInfo;
			SD_UINT8 * pCompressFrame = nullptr;
			AVRational time_base = m_pFormatCtx->streams[m_nAudioIndex]->time_base;
			m_nCurrentSeekPos = m_pFormatCtx->streams[m_nAudioIndex]->start_time + av_rescale(dwCurSamplePos, time_base.den, time_base.num);
			AVStream * pAudioStream = m_pFormatCtx->streams[m_nAudioIndex];
			int i = 0;
			i++;
#if 0
			while (GetAudioFrame(dwCurSamplePos, , &frameInfo) && pCompressFrame)
			{
				if (m_VideoDecoder.PutVideoFrame(pCompressFrame, &frameInfo))
				{
					if (pFrameBuf && m_VideoDecoder.GetUnCompressFrame(pFrameBuf, &frameInfo))
					{
						if (pFrameInfo)
						{
							pFrameInfo->iVersion = 0;
							pFrameInfo->emDataType = STREAM_DATATYPE_VIDEO;
							pFrameInfo->emStreamFlag = frameInfo.emStreamFlag;
							pFrameInfo->iSize = GetVideoBufferSize();
							pFrameInfo->dwFrameIndex = dwCurFrameShowIndex;
							pFrameInfo->dwFrameNum = 1;
							pFrameInfo->iSamplesOffset = 0;
							pFrameInfo->qwDTS = frameInfo.qwDTS;
							pFrameInfo->qwPTS = frameInfo.qwPTS;
							pFrameInfo->qwDuration = frameInfo.qwDuration;
							pFrameInfo->dwShowIndex = pFrameInfo->dwFrameIndex;
							pFrameInfo->emFrameType = frameInfo.emFrameType;
							pFrameInfo->extradata_size = 0;
							if (!m_bSeek)
							{
								return true;
							}
						}
					}
				}
			}
#endif
		}
	}
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetAudioFrame(SD_UINT32 dwCurFrameStreamIndex, SD_UINT32 dwFrameNum, SD_UINT8 *& pFrameBuf, SDRFrameInfo * pFrameInfo)
{
	return false;
}

bool ecCodecFFmpegProtocolDecoder::Release()
{
	m_nVideoIndex = -1;
	m_nAudioIndex = -1;
	if (m_pFormatCtx)
	{
		avformat_free_context(m_pFormatCtx);
		m_pFormatCtx = nullptr;
	}
	if (m_pVideoPacket)
	{
		av_packet_free(&m_pVideoPacket);
		m_pVideoPacket = nullptr;
	}
	m_VideoDecoder.Release();
	m_bIsInitialized = false;
	m_nCurrentSeekPos = 0;
	m_bSeek = false;
	return true;
}
