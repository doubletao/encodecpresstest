#ifndef __FFMPEG_FORMATCONVERTER_H_INCLUDED__
#define __FFMPEG_FORMATCONVERTER_H_INCLUDED__

#include "ecCodec.h"
#include "SDVADefine.h"
#include "SDVADefineEx.h"
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
#include "libswscale\swscale.h"
}

class EASY_CODEC_API_EXPORT FFmpegFormatCovert
{
public:
	static AVCodecID ConvertCodecId(SD_VIDEO_TYPE emVideoType);
	static AVCodecID ConvertCodecId(SD_AUDIO_TYPE emAudioType);
	static SD_AUDIO_TYPE ConvertAudioType(AVCodecID emCodecID);
	static int ConvertVideoProfile(SD_CODEC_PROFILE emProfile);
	static int ConvertAudioProfile(SD_UINT32 emProfile);
	static AVSampleFormat ConvertSamplesFormat(SD_CHANNELSAMPLE_FORMAT emSampleFormat);
	static SD_UINT64 ConvertChannelLayout(SD_AUDIO_CHANNELCONFIGURATION channelCfg);
	static SD_AUDIO_CHANNELCONFIGURATION ConvertChannelLayout(SD_UINT64 channelCfg);
	//static SD_STREAM_TYPE ConvertStreamType();
	static SD_VIDEO_TYPE ConvertVideoCodecType(AVCodecID codecID);
	static SD_UINT32 ConvertVideoCodecSubType(SD_UINT32 codecTag);
	static SD_VIDEOSCAN_MODE ConvertVideoFieldOrder(AVFieldOrder fieldOrder);
	static SD_COLOR_FORMAT ConvertColorFormat(AVPixelFormat pixFmt);
	static AVPixelFormat ConvertPixelFormat(SD_COLOR_FORMAT emColorFormat);
	static SD_COLOR_PRIMARIES ConvertColorPrimaries(AVColorPrimaries colorPrimaries);
	static SD_COLOR_TRANSFER ConvertColorTransfer(AVColorTransferCharacteristic colorTrans);
	static SD_COLOR_MATRIX ConvertColorSpace(AVColorSpace colorSpace);
	static FRAME_COMPRESS_TYPE ConvertCompressType(AVPictureType compressType);
	static bool ConvertPDataToBuffer(unsigned char ** pInData, int * pInLinesize, SD_UINT8 * pFrameBuf, uint32_t nSize,
		enum AVPixelFormat pix_fmt, int width, int height, int align);
	static bool ConvertBufferToPData(SD_UINT8 * pFrameBuf, uint32_t * pSize, unsigned char ** pOutData, int * pOutLinesize,
		enum AVPixelFormat pix_fmt, int width, int height, int align);
};

#endif // __FFMPEG_FORMATCONVERTER_H_INCLUDED__