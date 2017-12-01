#pragma once
#include "IecCodecProtocolEncoder.h"
#include "ecCodecIntelVideoEncoder.h"
#include "..\CodecFFmpeg\ecCodecFFmpegAudioEncoder.h"
#include <memory>

extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
}

class ecCodecIntelProtocolEncoder :
	public IecCodecProtocolEncoder
{
private:
	AVFormatContext* m_pFormatCtx;
	AVStream* m_pVideoStream;
	AVStream* m_pAudioStream;
	bool	  m_bWritable;
	std::unique_ptr<ecCodecIntelVideoEncoder> m_pVideoEncoder;
	std::unique_ptr<ecCodecFFmpegAudioEncoder> m_pAudioEncoder;
public:
	ecCodecIntelProtocolEncoder();
	virtual ~ecCodecIntelProtocolEncoder();
private:
	bool CreateVideoStream(const SDVideoMediaInfo& videoInfo);
	bool CreateAudioStream(const SDAudioMediaInfo& audioInfo);
public:
	virtual bool SetSinkFile(const SDStreamMediaInfo *pStreamMediaInfo, const char* pFileName);
	virtual bool GetMediaInfo(SDStreamMediaInfo *pStreamMediaInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo, const SDResamplerPara *pResamplerInfo);
	virtual bool GetVideoFrameBufInfo(SDVideoFrameImageBufInfo *pVideoInfo, SDResamplerPara *pResamplerInfo);
	virtual bool SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo *pAudioBufInfo);
	virtual bool GetAudioSamplesBufInfo(SDAudioSamplesBufInfo *pAudioBufInfo);
	virtual bool IsCanWriteVideoFrame();
	virtual bool IsCanWriteAudioFrame();
	virtual bool PutVideoBuffer(const SD_UINT8* pFrameBuf, bool bForceToKeyFrame = false, const SDRFrameInfo *pFrameInfo = NULL);
	virtual bool PutVideoFrame(const SD_UINT8* pFrameBuf, const SDRFrameInfo *pFrameInfo);
	virtual bool PutAudioSamples(const SD_UINT8* pSamplesBuf, SD_UINT32 dwSampleNum);
	virtual bool PutAudioFrame(const SD_UINT8* pFrameBuf, const SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};

