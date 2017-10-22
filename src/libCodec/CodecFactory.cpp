#include "stdafx.h"
#include "CodecFactory.h"
#include "FFmpegVideoEncoder.h"
#include "FFmpegVideoDecoder.h"
#include "FFmpegAudioEncoder.h"
#include "FFmpegAudioDecoder.h"
#include "FFmpegFileEncoder.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			\
	if (nullptr != (x))			\
	{							\
		delete (x);				\
		(x) = nullptr;			\
	}
#endif

CodecFactory::CodecFactory(void)
{
	av_register_all();
}

CodecFactory& CodecFactory::GetInstance()
{
	static CodecFactory codecFactory_;
	return codecFactory_;
}

IVideoEncoder* CodecFactory::Create_VideoEncoder(CODEC_MODEL codec)
{
	IVideoEncoder* pVideoEncoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		pVideoEncoder = new FFmpegVideoEncoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}
	return pVideoEncoder;
}

void CodecFactory::Delete_VideoEncoder(IVideoEncoder*& pEncoder)
{
	SAFE_DELETE(pEncoder);
}

IAudioEncoder* CodecFactory::Create_AudioEncoder(CODEC_MODEL codec)
{
	IAudioEncoder* pAudioEncoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		pAudioEncoder = new FFmpegAudioEncoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}
	return pAudioEncoder;
}

void CodecFactory::Delete_AudioEncoder(IAudioEncoder*& pEncoder)
{
	SAFE_DELETE(pEncoder);
}

IFileEncoder* CodecFactory::Create_FileEncoder(CODEC_MODEL codec)
{
	IFileEncoder* pFileEncoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		pFileEncoder = new FFmpegFileEncoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}

	return pFileEncoder;
}

void CodecFactory::Delete_FileEncoder(IFileEncoder*& pEncoder)
{
	SAFE_DELETE(pEncoder);
}

IVideoDecoder* CodecFactory::Create_VideoDecoder(CODEC_MODEL codec)
{
	IVideoDecoder* pVideoDecoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		pVideoDecoder = new FFmpegVideoDecoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}
	return pVideoDecoder;
}

void CodecFactory::Delete_VideoDecoder(IVideoDecoder*& pDecoder)
{
	SAFE_DELETE(pDecoder);
}

IAudioDecoder* CodecFactory::Create_AudioDecoder(CODEC_MODEL codec)
{
	IAudioDecoder* pAudioDecoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		pAudioDecoder = new FFmpegAudioDecoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}
	return pAudioDecoder;
}

void CodecFactory::Delete_AudioDecoder(IAudioDecoder*& pDecoder)
{
	SAFE_DELETE(pDecoder);
}

IFileDecoder* CodecFactory::Create_FileDecoder(CODEC_MODEL codec)
{
	IFileDecoder* pFileDecoder = nullptr;
	switch (codec)
	{
	case CodecModel_FFMPEG:
		//pFileDecoder = new FFmpegFileDecoder();
		break;
	case CodecModel_INTEL:
		break;
	case CodecModel_FFMPEG_INTEL:
		break;
	default:
		break;
	}
	return pFileDecoder;
}

void CodecFactory::Delete_FileDecoder(IFileDecoder*& pDecoder)
{
	SAFE_DELETE(pDecoder);
}