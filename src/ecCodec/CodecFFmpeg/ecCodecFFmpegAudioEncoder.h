#pragma once
#include "IecCodecAudioEncoder.h"
class ecCodecFFmpegAudioEncoder :
	public IecCodecAudioEncoder
{
public:
	ecCodecFFmpegAudioEncoder();
	virtual ~ecCodecFFmpegAudioEncoder();
};

