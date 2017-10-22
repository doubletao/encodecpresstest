#pragma once
#include "IecCodecFactory.h"

class ecCodecFactory :
	public IecCodecFactory
{
public:
	ecCodecFactory();
	virtual ~ecCodecFactory();

	virtual IecCodecProtocolDecoder * GetProtocolDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual IecCodecProtocolEncoder * GetProtocolEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual IecCodecVideoDecoder * GetVideoDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual IecCodecVideoEncoder * GetVideoEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual IecCodecAudioDecoder * GetAudioDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual IecCodecAudioEncoder * GetAudioEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
};

