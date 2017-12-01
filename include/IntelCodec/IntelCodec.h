#pragma once
#ifdef INTEL_CODEC_API
#define INTEL_CODEC_API_EXPORT __declspec(dllexport)
#else
#define INTEL_CODEC_API_EXPORT __declspec(dllimport)
#ifdef _DEBUG
#	pragma comment(lib, "IntelCodecxyD.lib")
#else
#	pragma comment(lib, "IntelCodecxyU.lib")
#endif
#endif // INTEL_CODEC_API

