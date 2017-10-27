#include "ecCodecFactory.h"
#include "SDVADefine.h"
#include "SDVADefineEx.h"
#include "CodecFFmpeg\ecCodecFFmpegProtocolDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegProtocolEncoder.h"
#include "CodecFFmpeg\ecCodecFFmpegVideoDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegVideoEncoder.h"
#include "CodecFFmpeg\ecCodecFFmpegAudioDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegAudioEncoder.h"

EASY_CODEC_API_EXPORT	IecCodecFactory * ecCodec_CreateCodecFactory()
{
	IecCodecFactory * pCodecFactory = new ecCodecFactory;
	return pCodecFactory;
}
EASY_CODEC_API_EXPORT bool ecCodec_ReleaseCodecFactory(IecCodecFactory *& pCodecFactory)
{
	deleteC(pCodecFactory);
	return true;
}

ecCodecFactory::ecCodecFactory()
{
}


ecCodecFactory::~ecCodecFactory()
{
}

IecCodecProtocolDecoder * ecCodecFactory::GetProtocolDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecProtocolDecoder * pProtocolDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		pProtocolDecoder = new ecCodecFFmpegProtocolDecoder;
	}
		break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pProtocolDecoder;
}

IecCodecProtocolEncoder * ecCodecFactory::GetProtocolEncoder(EmCodecProvider emCodecProvider)
{
	return nullptr;
}

IecCodecVideoDecoder * ecCodecFactory::GetVideoDecoder(EmCodecProvider emCodecProvider)
{
	return nullptr;
}

IecCodecVideoEncoder * ecCodecFactory::GetVideoEncoder(EmCodecProvider emCodecProvider)
{
	return nullptr;
}

IecCodecAudioDecoder * ecCodecFactory::GetAudioDecoder(EmCodecProvider emCodecProvider)
{
	return nullptr;
}

IecCodecAudioEncoder * ecCodecFactory::GetAudioEncoder(EmCodecProvider emCodecProvider)
{
	return nullptr;
}

bool ecCodecFactory::DeleteProtocolDecoder(IecCodecProtocolDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}
