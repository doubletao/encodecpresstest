#ifndef __INTELCODECAPI_H__
#define __INTELCODECAPI_H__

#ifndef INTELCODEC_EXPORTS
#define INTELCODECAPI __declspec(dllimport)
#else
#define INTELCODECAPI __declspec(dllexport)
#endif

#include "VACommonDefine.h"
#include "IntelVideoEncoder.h"
#include "IntelVideoDecoder.h"

#ifdef _DEBUG
#pragma comment (lib,"IntelCodecU.lib")
#else
#pragma comment (lib,"IntelCodecU.lib")
#endif  

#endif 