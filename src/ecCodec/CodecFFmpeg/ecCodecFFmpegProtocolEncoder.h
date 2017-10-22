#pragma once
#include "IecCodecProtocolEncoder.h"
class ecCodecFFmpegProtocolEncoder :
	public IecCodecProtocolEncoder
{
public:
	ecCodecFFmpegProtocolEncoder();
	virtual ~ecCodecFFmpegProtocolEncoder();
};

