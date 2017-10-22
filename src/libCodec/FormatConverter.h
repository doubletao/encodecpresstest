#ifndef __FORMATCONVERTER_H_INCLUDED__
#define __FORMATCONVERTER_H_INCLUDED__

#include "VACommonDefine.h"

class FFmpegFormatCovert
{
public:
	static AVCodecID ConvertCodecId(VIDEO_TYPE emVideoType);
	static AVCodecID ConvertCodecId(AUDIO_TYPE emAudioType);
	static AVPixelFormat ConvertPixelFormat(COLOR_FORMAT emColorFormat);
	static int ConvertVideoProfile(CODEC_PROFILE emProfile);
	static int ConvertAudioProfile(SW_UINT32 emProfile);
	static AVSampleFormat ConvertSamplesFormat(CHANNELSAMPLE_FORMAT emSampleFormat);
	static SW_UINT64 ConvertChannelLayout(AUDIO_CHANNELCONFIGURATION channelCfg);
};

class IntelFormatConvert
{
public:


private:

};

#endif // __FORMATCONVERTER_H_INCLUDED__