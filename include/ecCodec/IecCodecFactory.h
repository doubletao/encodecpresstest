#pragma once
#include "ecCodec.h"
#include "IecCodecProtocolDecoder.h"
#include "IecCodecProtocolEncoder.h"
#include "IecCodecVideoDecoder.h"
#include "IecCodecVideoEncoder.h"
#include "IecCodecAudioDecoder.h"
#include "IecCodecAudioEncoder.h"
enum EmCodecProvider
{
	EMCodec_Unknown = -1,
	EMCodec_FFmpeg,
	EMCodec_Intel,
};

class EASY_CODEC_API_EXPORT IecCodecFactory
{
public:
	virtual IecCodecProtocolDecoder * GetProtocolDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
	virtual IecCodecProtocolEncoder * GetProtocolEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
	virtual IecCodecVideoDecoder * GetVideoDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
	virtual IecCodecVideoEncoder * GetVideoEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
	virtual IecCodecAudioDecoder * GetAudioDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
	virtual IecCodecAudioEncoder * GetAudioEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg) = 0;
};

EASY_CODEC_API_EXPORT	IecCodecFactory * ecCodec_CreateCodecFactory();
EASY_CODEC_API_EXPORT	bool	ecCodec_ReleaseCodecFactory(IecCodecFactory * pCodecFactory);