// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/imgutils.h"
#include "libavutil/audio_fifo.h"
#include "libavutil/opt.h"
};

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

#ifndef LIBCODEC_EXPORTS
#define LIBCODEC_API __declspec(dllimport)
#else
#define LIBCODEC_API __declspec(dllexport)
#endif

// TODO: reference additional headers your program requires here
