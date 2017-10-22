#pragma once
#include "IecCodecAudioDecoder.h"
class ecCodecFFmpegAudioDecoder :
	public IecCodecAudioDecoder
{
public:
	ecCodecFFmpegAudioDecoder();
	virtual ~ecCodecFFmpegAudioDecoder();
};

