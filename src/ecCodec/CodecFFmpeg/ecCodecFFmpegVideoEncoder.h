#pragma once
#include "IecCodecVideoEncoder.h"
class ecCodecFFmpegVideoEncoder :
	public IecCodecVideoEncoder
{
public:
	ecCodecFFmpegVideoEncoder();
	virtual ~ecCodecFFmpegVideoEncoder();
};

