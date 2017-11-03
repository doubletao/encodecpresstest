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
	delete pCodecFactory;
	pCodecFactory = nullptr;
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
		av_register_all();
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
	IecCodecProtocolEncoder * pProtocolEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pProtocolEncoder = new ecCodecFFmpegProtocolEncoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pProtocolEncoder;
}

IecCodecVideoDecoder * ecCodecFactory::GetVideoDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecVideoDecoder * pVideoDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pVideoDecoder = new ecCodecFFmpegVideoDecoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pVideoDecoder;
}

IecCodecVideoEncoder * ecCodecFactory::GetVideoEncoder(EmCodecProvider emCodecProvider)
{
	IecCodecVideoEncoder * pVideoEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pVideoEncoder = new ecCodecFFmpegVideoEncoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pVideoEncoder;
}

IecCodecAudioDecoder * ecCodecFactory::GetAudioDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecAudioDecoder * pAudioDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pAudioDecoder = new ecCodecFFmpegAudioDecoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pAudioDecoder;
}

IecCodecAudioEncoder * ecCodecFactory::GetAudioEncoder(EmCodecProvider emCodecProvider)
{
	IecCodecAudioEncoder * pAudioEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pAudioEncoder = new ecCodecFFmpegAudioEncoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pAudioEncoder;
}

bool ecCodecFactory::DeleteProtocolEncoder(IecCodecProtocolEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteVideoDecoder(IecCodecVideoDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteVideoEncoder(IecCodecVideoEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteAudioDecoder(IecCodecAudioDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteAudioEncoder(IecCodecAudioEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteProtocolDecoder(IecCodecProtocolDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}
