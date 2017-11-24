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
	, m_pAudioPacket(nullptr)
	, m_nAudioIndex(-1)
	, m_nCurrentVideoSeekPos(0)
	, m_bVideoSeek(false)
	, m_nCurrentAudioSeekPos(0)
	, m_bAudioSeek(false)
	, m_nCurrentFrame(0)
	, m_nCurrentSample(0)
	, m_nDesSamplePerSec(0)
	, m_nSrcSamplePerSec(0)
	, m_pAudioFifo(nullptr)
	, m_nLastSampleNum(0)
	, m_nDesChannelCount(0)
	, m_dFramePerUnit(0)
	, m_pAvIoBuffer(nullptr)
{
	InitializeCriticalSection(&m_lock);
}


ecCodecFFmpegProtocolDecoder::~ecCodecFFmpegProtocolDecoder()
{
	Release();
	DeleteCriticalSection(&m_lock);
}

bool ecCodecFFmpegProtocolDecoder::SetSourcePath(const char * pFullPath, void * pUserParam/* = nullptr*/, PCALLBACKINTERRUPT pCallbackInterupt /*= nullptr*/)
{
	if (m_bIsInitialized)
	{
		printf("release codec before open again\n");
		return false;
	}
	//注册所有支持的格式
	//av_register_all();
	//网络组件的初始化（非必须）,应该是解网络流的时候在用
	avformat_network_init();
	//创建解封装器
	m_pFormatCtx = avformat_alloc_context();
	if (m_pFormatCtx)
	{
		std::string strurl = pFullPath;
		AVDictionary * format_opts = nullptr;
		if ( std::string::npos != strurl.find("rtsp://") )
		{
			char option_key[]="rtsp_transport";  
			char option_value[]="http";  
			av_dict_set(&format_opts,option_key,option_value,0); 
		}
		else
		{
			char option_key[]="scan_all_pmts";  
			char option_value[]="1";  
			av_dict_set(&format_opts,option_key,option_value,0); 
		}

		//解封装
		if (avformat_open_input(&m_pFormatCtx, pFullPath, nullptr, &format_opts) == 0)
		{
			m_pFormatCtx->interrupt_callback.callback = pCallbackInterupt;
			m_pFormatCtx->interrupt_callback.opaque = pUserParam;
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
					AVStream * pStreams = m_pFormatCtx->streams[m_nVideoIndex];
					if (pStreams)
					{
						AVCodecParameters * pVideoCodecParm = pStreams->codecpar;
						if (pVideoCodecParm)
						{
							SDVideoMediaInfo videoInfo;
							videoInfo.enumColorFormat = FFmpegFormatCovert::ConvertColorFormat((AVPixelFormat)pVideoCodecParm->format);
							videoInfo.dwWidth = pVideoCodecParm->width;
							videoInfo.dwHeight = pVideoCodecParm->height;
							videoInfo.dwDataRateInBitsPerSec = (SD_UINT32)pVideoCodecParm->bit_rate;
							videoInfo.enumVideoType = FFmpegFormatCovert::ConvertVideoCodecType(pVideoCodecParm->codec_id);
							videoInfo.extradata = pVideoCodecParm->extradata;
							videoInfo.extradata_size = pVideoCodecParm->extradata_size;
							videoInfo.enumScanMode = FFmpegFormatCovert::ConvertVideoFieldOrder(pVideoCodecParm->field_order);
							videoInfo.dwStandardScale = pVideoCodecParm->profile;
							videoInfo.dwStandardRate = pVideoCodecParm->level;
							videoInfo.dwMaxDataRateInBitsPerSec = pVideoCodecParm->sample_aspect_ratio.den;
							videoInfo.dwMinDataRateInBitsPerSec = pVideoCodecParm->sample_aspect_ratio.num;
#if 0
							AVCodecContext * pCodecCtx = nullptr;
							AVCodecID codecID = pVideoCodecParm->codec_id;
							AVCodec * pVideoCodec = avcodec_find_decoder(codecID);
							if (pVideoCodec)
							{
								//解码参数转成解码上下文
								pCodecCtx = avcodec_alloc_context3(pVideoCodec);
								avcodec_parameters_to_context(pCodecCtx, pVideoCodecParm);
							}
							if (m_VideoDecoder.InitVideoDecoder(pCodecCtx, pVideoCodec))
#else if
							//创建解码器
							if (m_VideoDecoder.InitVideoDecoder(videoInfo))
#endif
							{
								m_pVideoPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
								av_init_packet(m_pVideoPacket);
								//每个时间单位对应的帧数，timebase是sec和unit的比值，r_frame_rate是frame和sec的比值，二者相乘得出frame/unit，av_seek_frame以unit为参考值
								m_dFramePerUnit = av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->time_base) * av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate);
								m_bIsInitialized = true;
							}
							else
							{
								printf("failed to initial video decoder\n");
							}
						}
						else
						{
							printf("failed to get video codecparam\n");
						}
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
					AVStream * pStream = m_pFormatCtx->streams[m_nAudioIndex];
					if (pAudioCodecParm)
					{
						if (AV_CODEC_ID_FIRST_AUDIO == pAudioCodecParm->codec_id)
						{
							//如果是PCM，则不需要初始化音频解码器
							m_bIsInitialized = true;
							m_pAudioPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
							av_init_packet(m_pAudioPacket);
							m_nSrcSamplePerSec = pAudioCodecParm->sample_rate;
							m_nDesChannelCount = pAudioCodecParm->channels;
						}
						else
						{
							SDAudioMediaInfo audioInfo;
							audioInfo.enumAudioType = FFmpegFormatCovert::ConvertAudioType(pAudioCodecParm->codec_id);		// 音频编解码类型。
							audioInfo.dwAudioSubType = pAudioCodecParm->codec_tag;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
							audioInfo.dwChannels = pAudioCodecParm->channels;			// 声道数目
							audioInfo.dwBitsPerSample = pAudioCodecParm->bits_per_raw_sample;	// 采样位数 
							audioInfo.dwSamplesPerSec = pAudioCodecParm->sample_rate;	// 每秒采样数量 
							audioInfo.dwAvgBitsPerSec = pAudioCodecParm->bit_rate;	// 音频码率 bits
							audioInfo.dwBlockAlign = pAudioCodecParm->block_align;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...										//Below is Version 2 Add.
							audioInfo.enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(pAudioCodecParm->channel_layout);		//声道属性
							audioInfo.enumChannelSamplesFormat = FFmpegFormatCovert::ConvertSamplesFormat((AVSampleFormat)pAudioCodecParm->format);	//音频声道采样数据格式
							audioInfo.dwBitsPerSample = pAudioCodecParm->bits_per_coded_sample;
							audioInfo.extradata = pAudioCodecParm->extradata;
							audioInfo.extradata_size = pAudioCodecParm->extradata_size;
							audioInfo.dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
																						//创建解码器
							if (m_AudioDecoder.InitAudioDecoder(audioInfo))
							{
								m_nSrcSamplePerSec = audioInfo.dwSamplesPerSec;
								m_pAudioPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
								av_init_packet(m_pAudioPacket);
								m_bIsInitialized = true;
							}
							else
							{
								printf("failed to initial audio decoder\n");
							}
						}
					}
					else
					{
						printf("failed to get audio codecparam\n");
					}
				}
				else
				{
					printf("failed to find audio stream\n");
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

bool ecCodecFFmpegProtocolDecoder::SetSourceCallback(PCALLBACKREADPACKET pCallbackReadPkt, void * pUserParam/* = nullptr*/, PCALLBACKINTERRUPT pCallbackInterupt /*= nullptr*/)
{
	if (m_bIsInitialized)
	{
		printf("release codec before open again\n");
		return false;
	}
	//注册所有支持的格式
	//av_register_all();
	//网络组件的初始化（非必须）,应该是解网络流的时候在用
	avformat_network_init();
	//创建解封装器
	m_pFormatCtx = avformat_alloc_context();
	if (m_pFormatCtx)
	{
		//给回调
		const int nBufferSize = 1920 * 1080 * 2;//大小是个经验值
		m_pAvIoBuffer = (unsigned char *)av_malloc(nBufferSize);
		AVIOContext * avio = avio_alloc_context(m_pAvIoBuffer, nBufferSize, 0, pUserParam, pCallbackReadPkt, NULL, NULL);
		if (avio)
		{
			m_pFormatCtx->pb = avio;
			m_pFormatCtx->interrupt_callback.callback = pCallbackInterupt;
			m_pFormatCtx->interrupt_callback.opaque = pUserParam;
			if (avformat_open_input(&m_pFormatCtx, nullptr, nullptr, nullptr) >= 0)
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
						AVStream * pStreams = m_pFormatCtx->streams[m_nVideoIndex];
						if (pStreams)
						{
							AVCodecParameters * pVideoCodecParm = pStreams->codecpar;
							if (pVideoCodecParm)
							{
								SDVideoMediaInfo videoInfo;
								videoInfo.enumColorFormat = FFmpegFormatCovert::ConvertColorFormat((AVPixelFormat)pVideoCodecParm->format);
								videoInfo.dwWidth = pVideoCodecParm->width;
								videoInfo.dwHeight = pVideoCodecParm->height;
								videoInfo.dwDataRateInBitsPerSec = (SD_UINT32)pVideoCodecParm->bit_rate;
								videoInfo.enumVideoType = FFmpegFormatCovert::ConvertVideoCodecType(pVideoCodecParm->codec_id);
								videoInfo.dwDisplayWidth = (SD_UINT32)(pVideoCodecParm->extradata);
								videoInfo.dwDisplayHeight = pVideoCodecParm->extradata_size;
								videoInfo.enumScanMode = FFmpegFormatCovert::ConvertVideoFieldOrder(pVideoCodecParm->field_order);
								videoInfo.dwStandardScale = pVideoCodecParm->profile;
								videoInfo.dwStandardRate = pVideoCodecParm->level;
								videoInfo.dwMaxDataRateInBitsPerSec = pVideoCodecParm->sample_aspect_ratio.den;
								videoInfo.dwMinDataRateInBitsPerSec = pVideoCodecParm->sample_aspect_ratio.num;
#if 0
								AVCodecContext * pCodecCtx = nullptr;
								AVCodecID codecID = pVideoCodecParm->codec_id;
								AVCodec * pVideoCodec = avcodec_find_decoder(codecID);
								if (pVideoCodec)
								{
									//解码参数转成解码上下文
									pCodecCtx = avcodec_alloc_context3(pVideoCodec);
									avcodec_parameters_to_context(pCodecCtx, pVideoCodecParm);
								}
								if (m_VideoDecoder.InitVideoDecoder(pCodecCtx, pVideoCodec))
#else if
								//创建解码器
								if (m_VideoDecoder.InitVideoDecoder(videoInfo))
#endif
								{
									m_pVideoPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
									av_init_packet(m_pVideoPacket);
									//每个时间单位对应的帧数，timebase是sec和unit的比值，r_frame_rate是frame和sec的比值，二者相乘得出frame/unit，av_seek_frame以unit为参考值
									m_dFramePerUnit = av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->time_base) * av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate);
									m_bIsInitialized = true;
								}
								else
								{
									printf("failed to initial video decoder\n");
								}
							}
							else
							{
								printf("failed to get video codecparam\n");
							}
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
						AVStream * pStream = m_pFormatCtx->streams[m_nAudioIndex];
						if (pAudioCodecParm)
						{
							if (AV_CODEC_ID_FIRST_AUDIO == pAudioCodecParm->codec_id)
							{
								//如果是PCM，则不需要初始化音频解码器
								m_bIsInitialized = true;
								m_pAudioPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
								av_init_packet(m_pAudioPacket);
								m_nSrcSamplePerSec = pAudioCodecParm->sample_rate;
								m_nDesChannelCount = pAudioCodecParm->channels;
							}
							else
							{
								SDAudioMediaInfo audioInfo;
								audioInfo.enumAudioType = FFmpegFormatCovert::ConvertAudioType(pAudioCodecParm->codec_id);		// 音频编解码类型。
								audioInfo.dwAudioSubType = pAudioCodecParm->codec_tag;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
								audioInfo.dwChannels = pAudioCodecParm->channels;			// 声道数目
								audioInfo.dwBitsPerSample = pAudioCodecParm->bits_per_raw_sample;	// 采样位数 
								audioInfo.dwSamplesPerSec = pAudioCodecParm->sample_rate;	// 每秒采样数量 
								audioInfo.dwAvgBitsPerSec = pAudioCodecParm->bit_rate;	// 音频码率 bits
								audioInfo.dwBlockAlign = pAudioCodecParm->block_align;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...										//Below is Version 2 Add.
								audioInfo.enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(pAudioCodecParm->channel_layout);		//声道属性
								audioInfo.enumChannelSamplesFormat = FFmpegFormatCovert::ConvertSamplesFormat((AVSampleFormat)pAudioCodecParm->format);	//音频声道采样数据格式
								audioInfo.dwBitsPerSample = pAudioCodecParm->bits_per_coded_sample;
								audioInfo.extradata = pAudioCodecParm->extradata;
								audioInfo.extradata_size = pAudioCodecParm->extradata_size;
								audioInfo.dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
								//创建解码器
								if (m_AudioDecoder.InitAudioDecoder(audioInfo))
								{
									m_nSrcSamplePerSec = audioInfo.dwSamplesPerSec;
									m_pAudioPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
									av_init_packet(m_pAudioPacket);
									m_bIsInitialized = true;
								}
								else
								{
									printf("failed to initial audio decoder\n");
								}
							}
						}
					}
					else
					{
						printf("failed to find audio stream\n");
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
			printf("failed to alloc aviocontext\n");
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
		if (m_nVideoIndex > -1)
		{
			AVStream * pVideoFrame = m_pFormatCtx->streams[m_nVideoIndex];
			if (pVideoFrame)
			{
				psMediaInfo->sVideoMediaInfo.dwStandardRate = pVideoFrame->r_frame_rate.num;
				psMediaInfo->sVideoMediaInfo.dwStandardScale = pVideoFrame->r_frame_rate.den;
			}
		}
	}

	if (m_AudioDecoder.IsInitialized())
	{
		psMediaInfo->dwAudioStreamCount = 1;//不管有几个，解码器目前只解一个
		m_AudioDecoder.GetAudioMediaInfo(&psMediaInfo->sAudioMediaInfo);
		if (m_nDesSamplePerSec < 1)
		{
			m_nDesSamplePerSec = psMediaInfo->sAudioMediaInfo.dwSamplesPerSec;
		}
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
	if (Start())
	{
		psMediaInfoEx->enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;//暂时不知道怎么拿，给空
		psMediaInfoEx->dwStreamMediaSubType = 0;//暂时不知道怎么拿，给空
		psMediaInfoEx->dwTotalAverDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
		psMediaInfoEx->dwTotalMaxDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定
		psMediaInfoEx->dwTotalMinDataRateInBitsPerSec = (SD_UINT32)m_pFormatCtx->bit_rate;//不确定

		psMediaInfoEx->dwVideoStreamCount = 1;//不管有几个，解码器目前只解一个
		if (m_VideoDecoder.IsInitialized())
		{
			m_VideoDecoder.GetVideoMediaInfo(&psMediaInfoEx->sVideoMediaInfo);
			if (m_nVideoIndex > -1)
			{
				AVStream * pVideoFrame = m_pFormatCtx->streams[m_nVideoIndex];
				if (pVideoFrame)
				{
					psMediaInfoEx->sVideoMediaInfo.dwStandardRate = pVideoFrame->r_frame_rate.num;
					psMediaInfoEx->sVideoMediaInfo.dwStandardScale = pVideoFrame->r_frame_rate.den;
				}
			}
		}

		if (m_AudioDecoder.IsInitialized())
		{
			psMediaInfoEx->dwAudioStreamCount = 1;//不管有几个，解码器目前只解一个
			m_AudioDecoder.GetAudioMediaInfo(&psMediaInfoEx->sAudioMediaInfo);
			if (m_nDesSamplePerSec < 1)
			{
				m_nDesSamplePerSec = psMediaInfoEx->sAudioMediaInfo.dwSamplesPerSec;
			}
		}
		else if (m_pFormatCtx && m_nAudioIndex > -1
			&& AV_CODEC_ID_FIRST_AUDIO == m_pFormatCtx->streams[m_nAudioIndex]->codecpar->codec_id)
		{
			psMediaInfoEx->dwAudioStreamCount = 1;
			psMediaInfoEx->sAudioMediaInfo.dwChannels = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->channels;								// 声道数目
			psMediaInfoEx->sAudioMediaInfo.dwBitsPerSample = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->bits_per_raw_sample;						// 采样位数 
			psMediaInfoEx->sAudioMediaInfo.dwSamplesPerSec = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->sample_rate;						// 每秒采样数量 
			psMediaInfoEx->sAudioMediaInfo.dwAvgBitsPerSec = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->bit_rate;						// 音频码率 bits
			psMediaInfoEx->sAudioMediaInfo.dwBlockAlign = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->block_align;							// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
			psMediaInfoEx->sAudioMediaInfo.enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(m_pFormatCtx->streams[m_nAudioIndex]->codecpar->channel_layout);				// 声道属性
			psMediaInfoEx->sAudioMediaInfo.enumChannelSamplesFormat = FFmpegFormatCovert::ConvertSamplesFormat((AVSampleFormat)m_pFormatCtx->streams[m_nAudioIndex]->codecpar->format);	// 音频声道采样数据格式
			if (m_nDesSamplePerSec < 1)
			{
				m_nDesSamplePerSec = psMediaInfoEx->sAudioMediaInfo.dwSamplesPerSec;
			}
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
				psMediaInfoEx->dwVideoFrameNum = psMediaInfoEx->dwVideoFrameNum * av_q2d(m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate);
			}
			if (m_nAudioIndex > -1)
			{
				AVRational time_base = m_pFormatCtx->streams[m_nAudioIndex]->time_base;
				psMediaInfoEx->dwAudioSamplesNum = (SD_UINT32)av_rescale(m_pFormatCtx->streams[m_nAudioIndex]->duration, time_base.num, time_base.den);
				psMediaInfoEx->dwAudioSamplesNum = psMediaInfoEx->dwAudioSamplesNum * av_q2d(m_pFormatCtx->streams[m_nAudioIndex]->r_frame_rate);
			}
		}
		psMediaInfoEx->dwAudioSamplesNum;		// 音频流数据长度	 (Unit:Sample)
		psMediaInfoEx->dwSubtitleFrameNum;		// 字幕流数据的长度(Unit:SubtitleFrame)

		psMediaInfoEx->dwStruSize = sizeof(SDStreamMediaInfoEx);
	}
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
	bool bRet = false;
	//目前将start视为解一gop画面
	if (m_bIsInitialized)
	{
		if (m_VideoDecoder.IsInitialized())
		{
			SD_UINT32 nVideoBufferSize = GetVideoBufferSize();
			uint8_t * pVideoData = new uint8_t[nVideoBufferSize];
			memset(pVideoData, 0, nVideoBufferSize * sizeof(uint8_t));
			bRet |= GetVideoBuffer(0, pVideoData, nullptr);
			deleteC(pVideoData);
		}
		if (m_AudioDecoder.IsInitialized())
		{
			SD_UINT32 nAudioBufferSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
			uint8_t * pAudioData = new uint8_t[nAudioBufferSize];
			memset(pAudioData, 0, nAudioBufferSize * sizeof(uint8_t));
			bRet |= GetAudioSamples(0, 1, pAudioData, nullptr);
			deleteC(pAudioData);
		}
	}
	return bRet;
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
	else if (m_pFormatCtx && m_nAudioIndex > -1
		&& AV_CODEC_ID_FIRST_AUDIO == m_pFormatCtx->streams[m_nAudioIndex]->codecpar->codec_id)
	{
		return m_nSrcSamplePerSec;
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

bool ecCodecFFmpegProtocolDecoder::SetAudioSamplesBufInfo(const SDAudioMediaInfo * pAudioInfo)
{
	if (m_AudioDecoder.IsInitialized() && pAudioInfo)
	{
		if (m_AudioDecoder.SetAudioMediaInfo(pAudioInfo))
		{
			m_nDesSamplePerSec = pAudioInfo->dwSamplesPerSec;
			m_nDesChannelCount = pAudioInfo->dwChannels;
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
			if (m_nDesSamplePerSec < 1)
			{
				m_nDesSamplePerSec = mediaInfo.dwSamplesPerSec;
			}
			return true;
		}
	}
	else if (m_pFormatCtx && m_nAudioIndex > -1
		&& AV_CODEC_ID_FIRST_AUDIO == m_pFormatCtx->streams[m_nAudioIndex]->codecpar->codec_id)
	{
		pAudioBufInfo->dwChannels = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->channels;								// 声道数目
		pAudioBufInfo->dwBitsPerSample = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->bits_per_raw_sample;						// 采样位数 
		pAudioBufInfo->dwSamplesPerSec = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->sample_rate;						// 每秒采样数量 
		pAudioBufInfo->dwAvgBitsPerSec = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->bit_rate;						// 音频码率 bits
		pAudioBufInfo->dwBlockAlign = m_pFormatCtx->streams[m_nAudioIndex]->codecpar->block_align;							// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
		pAudioBufInfo->enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(m_pFormatCtx->streams[m_nAudioIndex]->codecpar->channel_layout);				// 声道属性
		pAudioBufInfo->enumChannelSamplesFormat = FFmpegFormatCovert::ConvertSamplesFormat((AVSampleFormat)m_pFormatCtx->streams[m_nAudioIndex]->codecpar->format);	// 音频声道采样数据格式
		if (m_nDesSamplePerSec < 1)
		{
			m_nDesSamplePerSec = pAudioBufInfo->dwSamplesPerSec;
		}
		return true;
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
			m_nCurrentVideoSeekPos = dwCurFrameShowIndex;
			while (GetVideoFrame(dwCurFrameShowIndex, pCompressFrame, &frameInfo) && pCompressFrame)
			{
				if (m_VideoDecoder.PutVideoFrame(pCompressFrame, &frameInfo))
				{
					int64_t pktDts = frameInfo.qwDTS;
					if (pFrameBuf && m_VideoDecoder.GetUnCompressFrame(pFrameBuf, &frameInfo))
					{
						if (m_bVideoSeek)
						{
							int64_t pts;
							if (pktDts == AV_NOPTS_VALUE && frameInfo.qwPTS != AV_NOPTS_VALUE)
							{
								pts = frameInfo.qwPTS;
							}
							else if(pktDts != AV_NOPTS_VALUE) 
							{
								pts = pktDts;
							}
							else
							{
								pts = 0;
							}
							if (pts >= m_nCurrentVideoSeekPos / m_dFramePerUnit)
							{
								m_bVideoSeek = false;
							}
						}
						m_nCurrentFrame = dwCurFrameShowIndex;
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
						}
						if (!m_bVideoSeek)
						{
							return true;
						}
					}
				}
				else
				{
					return false;
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
			//对于视频来说，gap单位为帧，3帧以内都视为顺播
			int64_t nSeekGap = dwCurFrameShowIndex - m_nCurrentFrame;
			if (dwCurFrameShowIndex != (SD_UINT64)-1 && abs(nSeekGap) > 3)
			{
				if (m_bVideoSeek)
				{
					bContinue = true;
				}
				else
				{
					if (pVideoStream->nb_frames < 1)
					{
						//如果当前没有frame数，则计算一个出来
						double dTm = pVideoStream->duration * av_q2d(pVideoStream->time_base);
						pVideoStream->nb_frames = dTm * av_q2d(pVideoStream->r_frame_rate);
					}
					if (m_nCurrentVideoSeekPos > 0 && m_nCurrentVideoSeekPos <= pVideoStream->r_frame_rate.num * 1.0 / pVideoStream->r_frame_rate.den)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nVideoIndex, m_nCurrentVideoSeekPos / m_dFramePerUnit, AVSEEK_FLAG_FRAME);
						if (nRet >= 0)
						{
							bContinue = true;
						}
					}
					else if (m_nCurrentVideoSeekPos <= pVideoStream->nb_frames)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nVideoIndex, m_nCurrentVideoSeekPos / m_dFramePerUnit, AVSEEK_FLAG_BACKWARD);
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
					//seek动作要清空缓存的pkt
					ReleaseAudioPackQue();
					ReleaseVideoPackQue();
					m_nCurrentFrame = dwCurFrameShowIndex;
					//清空解码器中缓存待取的数据
					int nRet = 1;
					if (m_VideoDecoder.IsInitialized())
					{
						SDRFrameInfo frameInfo;
						SD_UINT8 * pBuffer = new SD_UINT8[m_VideoDecoder.GetBufferSize()];
						while(nRet > 0)
						{
							nRet = m_VideoDecoder.GetUnCompressFrame(pBuffer, &frameInfo);
						}
						delete[] pBuffer;
						pBuffer = nullptr;
					}
					m_bVideoSeek = true;
				}
			}
			else
			{
				m_nCurrentFrame = dwCurFrameShowIndex;
				bContinue = true;
			}
			if (bContinue)
			{
				while (true)
				{
					//如果缓存队列中有值，则取队列中值
					do
					{
						Lock();
						size_t nVideoPackQueSize = m_queVideoPack.size();
						Unlock();
						if (nVideoPackQueSize > 0)
						{
							if (m_pVideoPacket)
							{
								av_packet_free(&m_pVideoPacket);
							}
							Lock();
							m_pVideoPacket = m_queVideoPack.front();
							m_queVideoPack.pop();
							Unlock();
							break;
						}
						if (!m_pVideoPacket)
						{
							m_pVideoPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
							av_init_packet(m_pVideoPacket);
						}
						av_packet_unref(m_pVideoPacket);
						if (av_read_frame(m_pFormatCtx, m_pVideoPacket) < 0)
						{
							//没读到，直接返回（可能是文件尾）
							return false;
						}
					} while (false);
					if (m_pVideoPacket->stream_index != m_nVideoIndex)
					{
						//找出视频流，如果发现音频，则暂存到音频队列里
						Lock();
						m_queAudioPack.push(m_pVideoPacket);
						Unlock();
						m_pVideoPacket = nullptr;
						continue;
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
	if (dwSampleNum > 0)
	{
		if (dwCurSamplePos >= 0)
		{
			if (m_bIsInitialized && (m_AudioDecoder.IsInitialized()
				|| (m_pFormatCtx && m_nAudioIndex > -1
				&& AV_CODEC_ID_FIRST_AUDIO == m_pFormatCtx->streams[m_nAudioIndex]->codecpar->codec_id)))
			{
				SDRFrameInfo frameInfo;
				SD_UINT8 * pCompressFrame = nullptr;
				m_nCurrentAudioSeekPos = dwCurSamplePos;
				//转换到源采样率单位
				if (m_nDesSamplePerSec > 0
					&& m_nSrcSamplePerSec > 0)
				{
					m_nCurrentAudioSeekPos = m_nCurrentAudioSeekPos * 1.0 / m_nDesSamplePerSec * m_nSrcSamplePerSec;
				}
				while (GetAudioFrame(dwCurSamplePos, pCompressFrame, &frameInfo) && pCompressFrame)
				{
					if (m_pFormatCtx && m_nAudioIndex > -1
						&& AV_CODEC_ID_FIRST_AUDIO == m_pFormatCtx->streams[m_nAudioIndex]->codecpar->codec_id)
					{
						int nChannelCount = m_nDesChannelCount;
						if (dwSampleNum != m_nLastSampleNum)
						{
							if (m_pAudioFifo)
							{
								av_audio_fifo_free(m_pAudioFifo);
								m_pAudioFifo = nullptr;
							}
						}

						if (!m_pAudioFifo)
						{
							m_pAudioFifo = av_audio_fifo_alloc((AVSampleFormat)m_pFormatCtx->streams[m_nAudioIndex]->codecpar->format,
								2, dwSampleNum);
						}
						if (!m_pAudioFifo)
						{
							return false;
						}
						m_nLastSampleNum = dwSampleNum;

						int data_size = av_get_bytes_per_sample((AVSampleFormat)m_pFormatCtx->streams[m_nAudioIndex]->codecpar->format);
						if (data_size <= 0)
						{
							return false;
						}

						av_audio_fifo_write(m_pAudioFifo, (void**)&pCompressFrame, frameInfo.iSize / data_size / nChannelCount);
						if (av_audio_fifo_size(m_pAudioFifo) >= dwSampleNum)
						{
							av_audio_fifo_read(m_pAudioFifo, (void **)&pSamplesBuf, dwSampleNum);
							m_nCurrentSample = dwCurSamplePos;
							if (pdwRetSampleNum)
							{
								*pdwRetSampleNum = dwSampleNum;
							}
							return true;
						}
					}
					else
					{
						if (m_AudioDecoder.PutFrame(pCompressFrame, &frameInfo))
						{
							int nBufferSize = m_AudioDecoder.GetSample(pSamplesBuf, dwSampleNum);
							if (nBufferSize > 0)
							{
								m_nCurrentSample = dwCurSamplePos;
								if (pdwRetSampleNum)
								{
									*pdwRetSampleNum = nBufferSize;
								}
								if (!m_bVideoSeek)
								{
									return true;
								}
							}
							else if (nBufferSize == 0)
							{
								continue;
							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
				}
				//有一种情况是视音频存储相对比较集中，音频frame已经读完了（在缓冲队列里了）视频还有很多，此时应该检查一下解码器里还有没有东西
				//产生这种情况的原因是音频做了双重缓冲，除了读文件时的frame队列，还存在一个fifo的输出缓冲，可能有一批已经解码完成的音频还没被取走，而视频不存在输出缓冲，所以不存在这种问题
				if (m_AudioDecoder.IsInitialized())
				{
					int nBufferSize = m_AudioDecoder.GetSample(pSamplesBuf, dwSampleNum);
					if (nBufferSize > 0)
					{
						m_nCurrentSample = dwCurSamplePos;
						if (pdwRetSampleNum)
						{
							*pdwRetSampleNum = nBufferSize;
						}
						if (!m_bVideoSeek)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool ecCodecFFmpegProtocolDecoder::GetAudioFrame(SD_UINT32 dwCurFrameStreamIndex, SD_UINT8 *& pFrameBuf, SDRFrameInfo * pFrameInfo)
{
	bool bRet = false;
	if (m_bIsInitialized)
	{
		AVStream * pAudioStream = m_pFormatCtx->streams[m_nAudioIndex];
		if (pAudioStream)
		{
			//转换sample数到时间进而转为时码
			int64_t time_stamp = 0;
			if (m_nSrcSamplePerSec > 0)
			{
				double dTm = m_nCurrentAudioSeekPos * 1.0 / m_nSrcSamplePerSec;
				AVRational time_base = m_pFormatCtx->streams[m_nAudioIndex]->time_base;
				time_stamp = m_pFormatCtx->streams[m_nAudioIndex]->start_time + av_rescale(dTm, time_base.den, time_base.num);
			}
			int64_t llLength = pAudioStream->duration;
			if (llLength < 0)
			{
				if (m_pFormatCtx->duration > 0)//长度折算到Stream的time_base
					llLength = m_pFormatCtx->duration * pAudioStream->time_base.den / (AV_TIME_BASE * pAudioStream->time_base.num);
			}
			bool bContinue = false;
			//对于音频来说，gap单位为毫秒，100毫秒以内都视为顺播
			int64_t nSeekGap = 0;
			if (dwCurFrameStreamIndex != (SD_UINT32)-1 && m_nSrcSamplePerSec > 0)
			{
				nSeekGap = dwCurFrameStreamIndex - m_nCurrentSample;
				nSeekGap = nSeekGap * 1000.0 / m_nDesSamplePerSec;
			}
			if (abs(nSeekGap) > 100)
			{
				if (m_bAudioSeek)
				{
					bContinue = true;
				}
				else
				{
					if (m_nCurrentAudioSeekPos > 0 && m_nCurrentAudioSeekPos <= m_nSrcSamplePerSec)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nAudioIndex, time_stamp, AVSEEK_FLAG_FRAME);
						if (nRet >= 0)
						{
							bContinue = true;
						}
					}
					else if (time_stamp <= llLength)
					{
						int nRet = av_seek_frame(m_pFormatCtx, m_nAudioIndex, time_stamp, AVSEEK_FLAG_BACKWARD);
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
					m_nCurrentSample = dwCurFrameStreamIndex;
					//seek动作要清空缓存的pkt
					ReleaseAudioPackQue();
					ReleaseVideoPackQue();
					//清空解码器中缓存待取的数据
					int nRet = 1;
					if (m_AudioDecoder.IsInitialized())
					{
						SDRFrameInfo frameInfo;
						SD_UINT8 * pBuffer = new SD_UINT8[80];
						while(nRet > 0)
						{
							nRet = m_AudioDecoder.GetSample(pBuffer, 10);
						}
						delete[] pBuffer;
						pBuffer = nullptr;
					}
					m_bAudioSeek = true;
				}
			}
			else
			{
				m_nCurrentSample = dwCurFrameStreamIndex;
				bContinue = true;
			}
			if (bContinue)
			{
				while (true)
				{
					do
					{
						Lock();
						size_t nAudioPackQueSize = m_queAudioPack.size();
						Unlock();
						if (nAudioPackQueSize > 0)
						{
							if (m_pAudioPacket)
							{
								av_packet_free(&m_pAudioPacket);
							}
							Lock();
							m_pAudioPacket = m_queAudioPack.front();
							m_queAudioPack.pop();
							Unlock();
							break;
						}
						if (!m_pAudioPacket)
						{
							m_pAudioPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
							av_init_packet(m_pAudioPacket);
						}
						av_packet_unref(m_pAudioPacket);
						int nRet = av_read_frame(m_pFormatCtx, m_pAudioPacket);
						if (nRet < 0)
						{
							//没读到，直接返回（可能是文件尾）
							return false;
						}
					} while (false);
					if (m_pAudioPacket->stream_index != m_nAudioIndex)
					{
						//找出音频流，如果发现视频，则暂存到队列里
						Lock();
						m_queVideoPack.push(m_pAudioPacket);
						Unlock();
						m_pAudioPacket = nullptr;
						continue;
					}
					if (m_bAudioSeek)
					{
						if (m_pAudioPacket->dts >= time_stamp)
						{
							m_bAudioSeek = false;
						}
					}
					pFrameBuf = m_pAudioPacket->data;

					if (pFrameInfo)
					{
						pFrameInfo->iSize = m_pAudioPacket->size;
						pFrameInfo->qwDTS = m_pAudioPacket->dts;
						pFrameInfo->qwPTS = m_pAudioPacket->pts;
						pFrameInfo->qwDuration = m_pAudioPacket->duration;
						pFrameInfo->dwShowIndex = m_pAudioPacket->pos;
						pFrameInfo->emStreamFlag = m_pAudioPacket->pts == 0 ? STREAMSTATE_BEGIN : STREAMSTATE_CONTINUE;
						pFrameInfo->extradata_size = m_pAudioPacket->flags;
						//if (m_pAudioPacket->buf)
						//{
						//	pFrameInfo->iVersion = 1;
						//	pFrameInfo->dwFrameIndex = (uint64_t)m_pAudioPacket->buf;
						//	pFrameInfo->dwFrameNum = (uint32_t)m_pAudioPacket;
						//}
						//else
						//{
						//	pFrameInfo->iVersion = 0;
						//}
					}
					bRet = true;
					break;
				}
			}
		}
	}
	return bRet;
}

void ecCodecFFmpegProtocolDecoder::ReleasePackQue(std::queue<AVPacket*>& m_quePack)
{
	while (m_quePack.size())
	{
		AVPacket * packet = m_quePack.front();
		if (packet)
		{
			av_packet_free(&packet);
			packet = nullptr;
		}
		m_quePack.pop();
	}
}

void ecCodecFFmpegProtocolDecoder::ReleaseVideoPackQue()
{
	Lock();
	ReleasePackQue(m_queVideoPack);
	Unlock();
}

void ecCodecFFmpegProtocolDecoder::ReleaseAudioPackQue()
{
	Lock();
	ReleasePackQue(m_queAudioPack);
	Unlock();
}

bool ecCodecFFmpegProtocolDecoder::Release()
{
	m_nVideoIndex = -1;
	m_nAudioIndex = -1;
	m_nDesSamplePerSec = 0;
	m_nSrcSamplePerSec = 0;
	m_dFramePerUnit = 0;
	if (m_pVideoPacket)
	{
		av_packet_free(&m_pVideoPacket);
		m_pVideoPacket = nullptr;
	}
	m_VideoDecoder.Release();
	if (m_pAudioPacket)
	{
		av_packet_free(&m_pAudioPacket);
		m_pAudioPacket = nullptr;
	}
	m_AudioDecoder.Release();
	ReleaseAudioPackQue();
	ReleaseVideoPackQue();
	if (m_pFormatCtx)
	{
		avformat_free_context(m_pFormatCtx);
		m_pFormatCtx = nullptr;
	}
	if (m_pAudioFifo)
	{
		av_audio_fifo_free(m_pAudioFifo);
		m_pAudioFifo = nullptr;
	}
	m_nDesChannelCount = 0;
	m_nLastSampleNum = 0;
	m_nCurrentFrame = 0;
	m_nCurrentSample = 0;
	m_bIsInitialized = false;
	m_nCurrentVideoSeekPos = 0;
	m_bVideoSeek = false;
	m_nCurrentAudioSeekPos = 0;
	m_bAudioSeek = false;
	av_free(m_pAvIoBuffer);
	m_pAvIoBuffer = nullptr;
	return true;
}

void ecCodecFFmpegProtocolDecoder::Lock()
{
	EnterCriticalSection(&m_lock);
}

void ecCodecFFmpegProtocolDecoder::Unlock()
{
	LeaveCriticalSection(&m_lock);
}

bool ecCodecFFmpegProtocolDecoder::GetVABuffer(SD_UINT8* pFrameBuf, SD_UINT8* pSamplesBuf, SD_UINT32* pdwRetSampleNum)
{
	//从当前位置开始取一帧视频一帧音频
	SDRFrameInfo frameInfo;
	bool bVideo = GetVideoBuffer(-1, pFrameBuf, &frameInfo);
	SD_UINT32 nSampleNum = 1024;
	//算出每帧画面对应的音频数
	if (m_pFormatCtx && m_pFormatCtx->streams
		&& m_nVideoIndex > -1 && m_pFormatCtx->streams[m_nVideoIndex]
		&& m_nAudioIndex > -1 && m_pFormatCtx->streams[m_nAudioIndex])
	{
		//计算条件是VA的stream都存在，此时才能计算
		double dSamplePerSec = m_nDesSamplePerSec;//每秒sample数
		double dFramePerSec = m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate.num * 1.0 / m_pFormatCtx->streams[m_nVideoIndex]->r_frame_rate.den;//每秒的视频帧数
		nSampleNum = dSamplePerSec / dFramePerSec;
	}
	bool bAudio = GetAudioSamples(-1, nSampleNum, pSamplesBuf, pdwRetSampleNum);
	if (!bVideo && !bAudio)
	{
		return false;
	}
	else if ((bVideo && !bAudio)
		|| (!bVideo && bAudio))
	{
		//如果仅有视频或者仅有音频，不用搞什么同步了，直接返回相应的值就行了
		return true;
	}
	else
	{
		if (m_pFormatCtx && m_pFormatCtx->streams)
		{
			int nVNum = 0;
			int nVDen = 0;
			int nANum = 0;
			int nADen = 0;
			//将音频时间戳当作标准时间戳，将视频往音频上靠拢
			double dVideoTm = 0.0f;
			double dAudioTm = 0.0f;
			if (m_VideoDecoder.IsInitialized() && m_nVideoIndex > -1)
			{
				AVStream * pStream = m_pFormatCtx->streams[m_nVideoIndex];
				if (pStream)
				{
					nVNum = pStream->time_base.num;
					nVDen = pStream->time_base.den;
					dVideoTm = m_VideoDecoder.GetCurrentMilSecTimestamp(nVNum, nVDen);
				}
			}
			if (m_AudioDecoder.IsInitialized() && m_nAudioIndex > -1)
			{
				AVStream * pStream = m_pFormatCtx->streams[m_nAudioIndex];
				if (pStream)
				{
					nANum = pStream->time_base.num;
					nADen = pStream->time_base.den;
					dAudioTm = m_AudioDecoder.GetCurrentMilSecTimestamp(nANum, nADen);
				}
			}
#ifdef _DEBUG
#if 0
			FILE * pFile;
			fopen_s(&pFile, "debug.txt", "ab");
			if (pFile)
			{
				int n = dStTm;
				char pStr[20] = {0};
				itoa(n, pStr, 10);
				fwrite(pStr, strlen(pStr), 1, pFile);
				char c = '\n';
				fwrite(&c, sizeof(c), 1, pFile);
				fclose(pFile);
			}
#endif
#endif
			int nEvenCount = 0;
			int nTimeGap = 120;
			//将视音频都向标准时间戳上靠，差距在指定时间以内，不予理会，指定时间以外，需要处理
			int nLoopMax = 50;//每个循环最多走50次
			while (abs(dAudioTm - dVideoTm) > nTimeGap && nLoopMax--)
			{
				if (dVideoTm - dAudioTm > nTimeGap)
				{
					GetAudioSamples(-1, nSampleNum, pSamplesBuf, pdwRetSampleNum);
					dAudioTm = m_AudioDecoder.GetCurrentMilSecTimestamp(nVNum, nVDen);
				}
				else if (dAudioTm - dVideoTm > nTimeGap)
				{
					GetVideoBuffer(-1, pFrameBuf, &frameInfo);
					dVideoTm = m_VideoDecoder.GetCurrentMilSecTimestamp(nVNum, nVDen);
				}
			}
			return true;
		}
	}
	return false;
}
