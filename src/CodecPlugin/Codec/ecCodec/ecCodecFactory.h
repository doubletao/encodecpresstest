#pragma once
#include "IecCodecFactory.h"

class ecCodecFactory :
	public IecCodecFactory
{
private:
	CRITICAL_SECTION m_Log_lock;
	static void logFF(void *, int level, const char *fmt, va_list ap);
public:
	ecCodecFactory();
	virtual ~ecCodecFactory();

	virtual IecCodecProtocolDecoder * GetProtocolDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteProtocolDecoder(IecCodecProtocolDecoder *& pObj);
	virtual IecCodecProtocolEncoder * GetProtocolEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteProtocolEncoder(IecCodecProtocolEncoder *& pObj);
	virtual IecCodecVideoDecoder * GetVideoDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteVideoDecoder(IecCodecVideoDecoder *& pObj);
	virtual IecCodecVideoEncoder * GetVideoEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteVideoEncoder(IecCodecVideoEncoder *& pObj);
	virtual IecCodecAudioDecoder * GetAudioDecoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteAudioDecoder(IecCodecAudioDecoder *& pObj);
	virtual IecCodecAudioEncoder * GetAudioEncoder(EmCodecProvider emCodecProvider = EMCodec_FFmpeg);
	virtual bool DeleteAudioEncoder(IecCodecAudioEncoder *& pObj);
	virtual IecCodecAudioEquliazer * GetAudioEquliazer();
	virtual bool DeleteAudioEquliazer(IecCodecAudioEquliazer *& pObj);
};

