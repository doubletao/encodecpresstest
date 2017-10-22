#include "VADecoder.h"
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
//#pragma comment(lib, "avdevice.lib")
//#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avutil.lib")
//#pragma comment(lib, "postproc.lib")
//#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")

#define DEBUG_FILE_IPB
//#define FFMPEG_LEISHEN
#ifdef FFMPEG_LEISHEN
extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
};
#pragma comment(lib, "..\\..\\lib\\LibFFmpeg\\avcodec.lib")
#pragma comment(lib, "..\\..\\lib\\LibFFmpeg\\avutil.lib")
AVCodec *pEncodec;
AVCodecContext *pEncodecCtx = NULL;
int i = 0;
int ret = 0;
int got_output = 0;
FILE *fp_out;
AVPacket pkt;
int y_size;
int framecnt = 0;

int width = 720;
int height = 576;
int bit_rate = 400000;
AVPixelFormat EMColor = AV_PIX_FMT_YUV420P;
#endif

VADecoder::VADecoder()
	: nVideoIndex(-1)
	, pFormatCtx(nullptr)
	, pCodecCtx(nullptr)
	, pCodecParm(nullptr)
	, pCodec(nullptr)
	, packet(nullptr)
	, pFrame(nullptr)
	, m_pScaleCtx(nullptr)
	, m_pScaleFrame(nullptr)
{
}

VADecoder::~VADecoder()
{
	CloseFile();
}

int VADecoder::OpenFile(const char * szFilePath)
{
#ifdef FFMPEG_LEISHEN
	fp_out = fopen("E:\\clip\\encodec.h264", "wb");
	avcodec_register_all();
	pEncodec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (pEncodec)
	{
		pEncodecCtx = avcodec_alloc_context3(pEncodec);
		if (pEncodecCtx)
		{
			pEncodecCtx->bit_rate = bit_rate;
			pEncodecCtx->width = width;
			pEncodecCtx->height = height;
			pEncodecCtx->time_base.num = 1;
			pEncodecCtx->time_base.den = 25;
			pEncodecCtx->gop_size = 12;
			pEncodecCtx->max_b_frames = 1;
			pEncodecCtx->pix_fmt = EMColor;

			//av_opt_set(pEncodecCtx->priv_data, "preset", "slow", 0);
			av_opt_set(pEncodecCtx->priv_data, "preset", "superfast", 0);
			av_opt_set(pEncodecCtx->priv_data, "tune", "zerolatency", 0);

			if (avcodec_open2(pEncodecCtx, pEncodec, NULL) >= 0)
			{
				//pFrame = av_frame_alloc();
				//if (pFrame)
				//{
				//	pFrame->format = pEncodecCtx->pix_fmt;
				//	pFrame->width = pEncodecCtx->width;
				//	pFrame->height = pEncodecCtx->height;

				//	ret = av_image_alloc(pFrame->data, pFrame->linesize, pEncodecCtx->width,
				//		pEncodecCtx->height, pEncodecCtx->pix_fmt, 16);
					if (ret >= 0)
					{
						y_size = pEncodecCtx->width * pEncodecCtx->height;
					}
				//}
			}
		}
	}
#endif
	//注册所有支持的格式
	av_register_all();
	//网络组件的初始化（非必须）,应该是解网络流的时候在用
	//avformat_network_init();
	//创建解封装器
	pFormatCtx = avformat_alloc_context();
	if (pFormatCtx)
	{
		//解封装
		if (avformat_open_input(&pFormatCtx, szFilePath, nullptr, nullptr) == 0)
		{
			//得到流数据
			if (avformat_find_stream_info(pFormatCtx, nullptr) >= 0)
			{
				//查找视频流
				nVideoIndex = -1;
				for (size_t i = 0; i < pFormatCtx->nb_streams; i++)
				{
					if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
					{
						nVideoIndex = (int)i;
						break;
					}
				}
				if (nVideoIndex > -1)
				{
					//根据编码格式查找解码器
					//先拿到解码参数
					pCodecParm = pFormatCtx->streams[nVideoIndex]->codecpar;
					if (pCodecParm)
					{
						//查找解码器
						pCodec = avcodec_find_decoder(pCodecParm->codec_id);
						if (pCodec)
						{
							//解码参数转成解码上下文
							pCodecCtx = avcodec_alloc_context3(pCodec);
							avcodec_parameters_to_context(pCodecCtx, pCodecParm);
							if (pCodecCtx)
							{
								//根据解码上下文打开解码器
								if (avcodec_open2(pCodecCtx, pCodec, nullptr) == 0)
								{
									if (packet)
									{
										av_packet_free(&packet);
									}
									packet = (AVPacket *)av_malloc(sizeof(AVPacket));
									if (pFrame)
									{
										av_frame_free(&pFrame);
									}
									pFrame = av_frame_alloc();
									if (packet && pFrame)
									{
#ifdef DEBUG_FILE_IPB
										if (1)
										{
											FILE * fp_out = fopen("E:\\packet.txt", "w+");
											fwrite("flags\tpts\tdts\t\n", strlen("flags\tpts\tdts\t\n"), 1, fp_out);
											fclose(fp_out);

											fp_out = fopen("E:\\pFrame.txt", "w+");
											fwrite("pkt_dts\tpkt_pts\tpts\tpkt_duration\tpict_type\t\n", strlen("pkt_dts\tpkt_pts\tpts\tpkt_duration\tpict_type\t\n"), 1, fp_out);
											fclose(fp_out);
										}
#endif //DEBUG_FILE_IPB 
										return 1;
									}
									else
									{
										printf("failed to alloc packet or frame\n");
									}
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
	CloseFile();
	return 0;
}

int VADecoder::GetVideoBasicInfo(int & nWidth, int & nHeight, AVPixelFormat & emPixFmt)
{
	if (pCodecCtx)
	{
		nWidth = pCodecCtx->width;
		nHeight = pCodecCtx->height;
		emPixFmt = pCodecCtx->pix_fmt;
		return 1;
	}
	else
	{
		printf("file not open or open failed\n");
		return 0;
	}
}

int VADecoder::SetVideoScaleInfo(int nWidth, int nHeight, unsigned long emPixFmt)
{
	if (pCodecCtx)
	{
		int nSrcWidth = pCodecCtx->width;
		int nSrcHeight = pCodecCtx->height;
		unsigned long emSrcPixFmt = pCodecCtx->pix_fmt;
		if (nSrcWidth != nWidth
			|| nSrcHeight != nHeight
			|| emSrcPixFmt != emPixFmt)
		{
			if (m_pScaleCtx)
			{
				sws_freeContext(m_pScaleCtx);
				m_pScaleCtx = nullptr;
			}
			m_pScaleCtx = sws_getContext(nSrcWidth, nSrcHeight, (AVPixelFormat)emSrcPixFmt,
				nWidth, nHeight, (AVPixelFormat)emPixFmt, SWS_SINC, nullptr, nullptr, nullptr);
			if (!m_pScaleCtx)
			{
				printf("sws_getContext failed\n");
				return 0;
			}

			if (m_pScaleFrame)
			{
				av_frame_free(&m_pScaleFrame);
				m_pScaleFrame = nullptr;
			}
			m_pScaleFrame = av_frame_alloc();
			m_pScaleFrame->width = nWidth;
			m_pScaleFrame->height = nHeight;
			m_pScaleFrame->format = emPixFmt;
			int nRet = av_image_alloc(m_pScaleFrame->data, m_pScaleFrame->linesize, nWidth, nHeight, (AVPixelFormat)emPixFmt, 4);
			if (nRet < 0)
			{
				sws_freeContext(m_pScaleCtx);
				printf("av_image_alloc failed\n");
				return 0;
			}
		}
		return 1;
	}
	else
	{
		printf("file not open or open failed\n");
		return 0;
	}
}

int VADecoder::DecodeOneFrame(unsigned char **& data, int *& linesize)
{
	if (pFormatCtx && packet && nVideoIndex > -1)
	{
		while (true)
		{
			if (av_read_frame(pFormatCtx, packet) < 0)
			{
				//没读到，直接返回（可能是文件尾）
				return 0;
			}
			if (packet->stream_index != nVideoIndex)
			{
				//找出视频流
				continue;
			}
#ifdef DEBUG_FILE_IPB
			if (1)
			{
				FILE * fp_out = fopen("E:\\packet.txt", "a+");

				char pOut[256] = {0};
				char pNum[10] = {0};
				memset(pNum, 0, 10);
				itoa(packet->flags, pNum, 10);
				strcat(pOut, pNum);
				strcat(pOut, "\t");

				memset(pNum, 0, 10);
				itoa(packet->pts, pNum, 10);
				strcat(pOut, pNum);
				strcat(pOut, "\t");

				memset(pNum, 0, 10);
				itoa(packet->dts, pNum, 10);
				strcat(pOut, pNum);
				strcat(pOut, "\t\n");
				
				fwrite(pOut, strlen(pOut), 1, fp_out);
				fclose(fp_out);
			}
#endif //DEBUG_FILE_IPB 
			//解码
			if (avcodec_send_packet(pCodecCtx, packet) == 0)
			{
				av_free_packet(packet);
				int nRet = -1;
				if ((nRet = avcodec_receive_frame(pCodecCtx, pFrame)) == 0)
				{
#ifdef DEBUG_FILE_IPB
					if (1)
					{
						FILE * fp_out = fopen("E:\\pFrame.txt", "a+");

						char pOut[256] = { 0 };
						char pNum[10] = { 0 };
						memset(pNum, 0, 10);
						itoa(pFrame->pkt_dts, pNum, 10);
						strcat(pOut, pNum);
						strcat(pOut, "\t");

						memset(pNum, 0, 10);
						itoa(pFrame->pkt_pts, pNum, 10);
						strcat(pOut, pNum);
						strcat(pOut, "\t");

						memset(pNum, 0, 10);
						itoa(pFrame->pts, pNum, 10);
						strcat(pOut, pNum);
						strcat(pOut, "\t");

						memset(pNum, 0, 10);
						itoa(pFrame->pkt_duration, pNum, 10);
						strcat(pOut, pNum);
						strcat(pOut, "\t");

						switch (pFrame->pict_type)
						{
						case AV_PICTURE_TYPE_I:
							strcat(pOut, "I");
							break;
						case AV_PICTURE_TYPE_P:
							strcat(pOut, "P");
							break;
						case AV_PICTURE_TYPE_B:
							strcat(pOut, "B");
							break;
						default:
							break;
						}
						strcat(pOut, "\t\n");

						fwrite(pOut, strlen(pOut), 1, fp_out);
						fclose(fp_out);
					}
#endif //DEBUG_FILE_IPB 
					//如果需要转码，则转
					if (m_pScaleCtx && m_pScaleFrame)
					{
						sws_scale(m_pScaleCtx, pFrame->data, pFrame->linesize, 0, pFrame->height,
							m_pScaleFrame->data, m_pScaleFrame->linesize);
						linesize = m_pScaleFrame->linesize;
						data = m_pScaleFrame->data;
#ifdef FFMPEG_LEISHEN
						av_init_packet(&pkt);
						pkt.data = NULL;
						pkt.size = 0;
						m_pScaleFrame->pts = i;
						ret = avcodec_encode_video2(pEncodecCtx, &pkt, m_pScaleFrame, &got_output);
						if (ret >= 0 && got_output)
						{
							fwrite(pkt.data, 1, pkt.size, fp_out);
							av_free_packet(&pkt);
						}
#endif
					}
					else
					{
						linesize = pFrame->linesize;
						data = pFrame->data;
#ifdef FFMPEG_LEISHEN
						av_init_packet(&pkt);
						pkt.data = NULL;
						pkt.size = 0;
						pFrame->pts = i;
						ret = avcodec_encode_video2(pEncodecCtx, &pkt, pFrame, &got_output);
						if (ret >= 0 && got_output)
						{
							fwrite(pkt.data, 1, pkt.size, fp_out);
							av_free_packet(&pkt);
						}
#endif
					}
					return 1;
				}
				else
				{
					continue;
					switch (nRet) {
					case 0:
						break;
					case AVERROR_EOF:
						printf("the decoder has been fully flushed,\
                               and there will be no more output frames.\n");
						break;

					case AVERROR(EAGAIN):
						printf("Resource temporarily unavailable\n");
						break;

					case AVERROR(EINVAL):
						printf("Invalid argument\n");
						break;
					default:
						break;
					}
					printf("failed to receive frame\n");
				}
			}
			else
			{
				printf("falied to send packet\n");
			}
		}
	}
	else
	{
		printf("file not open or open failed\n");
	}
	CloseFile();
	return 0;
}

int VADecoder::CloseFile()
{
#ifdef FFMPEG_LEISHEN
	for (got_output = 1; got_output; i++)
	{
		ret = avcodec_encode_video2(pEncodecCtx, &pkt, NULL, &got_output);
		if (ret >= 0)
		{
			if (got_output)
			{
				fwrite(pkt.data, 1, pkt.size, fp_out);
				av_free_packet(&pkt);
			}
		}
	}
	fclose(fp_out);
	avcodec_close(pEncodecCtx);
	av_free(pEncodecCtx);
#endif

	nVideoIndex = -1;
	if (pFrame)
	{
		av_frame_free(&pFrame);
	}
	if (packet)
	{
		av_packet_free(&packet);
	}
	if (pCodecCtx)
	{
		avcodec_close(pCodecCtx);
	}
	if (pFormatCtx)
	{
		avformat_free_context(pFormatCtx);
	}
	if (m_pScaleCtx)
	{
		sws_freeContext(m_pScaleCtx);
	}
	if (m_pScaleFrame)
	{
		av_frame_free(&m_pScaleFrame);
	}
	return 1;
}
