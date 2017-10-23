/***************************************************************************
* ecCodec.h
*
* ec编解码库,EasyCode科技公司版权所有!
*
* 描述:		-集成了编解码器常用功能
*			 依赖SDDefine定义
*
* 目标:		- 1.实现对不同编解码底层库的封装，如ffmpeg，intel等
*			  2.与视音频压缩编码、文件(流)封装、节目复用等功能
*
* Ver-0.9
*
****************************************************************************/
#pragma once
#ifdef EASY_CODEC_API
#define EASY_CODEC_API_EXPORT __declspec(dllexport)
#else
#define EASY_CODEC_API_EXPORT __declspec(dllimport)
#ifdef _DEBUG
#	pragma comment(lib, "ecCodecD.lib")
#else
#	pragma comment(lib, "ecCodecU.lib")
#endif
#include "IecCodecFactory.h"
#endif // EASY_CODEC_API

//基础数据结构定义
#include "SDVADefine.h"
#include "SDVADefineEx.h"

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

