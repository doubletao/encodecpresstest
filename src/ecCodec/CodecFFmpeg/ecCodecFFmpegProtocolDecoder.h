#pragma once
#include "IecCodecProtocolDecoder.h"
#include "ecCodecFFmpegVideoDecoder.h"
#include "ecCodecFFmpegAudioDecoder.h"

extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
}

class ecCodecFFmpegProtocolDecoder :
	public IecCodecProtocolDecoder
{
private:
	bool m_bIsInitialized;
	int m_nVideoIndex;
	AVPacket * m_pVideoPacket;
	AVFormatContext	* m_pFormatCtx;
	ecCodecFFmpegVideoDecoder m_VideoDecoder;
	int64_t m_nCurrentSeekPos;
	bool m_bSeek;
public:
	ecCodecFFmpegProtocolDecoder();
	virtual ~ecCodecFFmpegProtocolDecoder();
public:
	virtual bool SetSourcePath(const char * pFullPath);
	virtual bool GetFileGlobalMediaInfo(SDStreamMediaInfo *psMediaInfo);
	virtual bool GetFileGlobalMediaInfo(SDStreamMediaInfoEx *psMediaInfoEx);
	virtual bool IsCanReadVideoFrame();
	virtual bool IsCanReadAudioFrame();
	virtual bool Start();
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo, const SDResamplerPara *pResamplerPara);
	virtual bool GetVideoFrameBufInfo(SDVideoFrameImageBufInfo *pVideoBufInfo, SDResamplerPara *pResamplerPara);
	virtual SD_UINT32 GetVideoBufferSize();
	virtual bool SetVideoDecoderThread(SD_INT32 dwDecoderThread);
	virtual SD_INT32 GetVideoDecoderThread();
	virtual bool SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo *pAudioBufInfo);
	virtual bool GetAudioSamplesBufInfo(SDAudioSamplesBufInfo *pAudioBufInfo);
	virtual bool GetVideoBuffer(SD_UINT64 dwCurFrameShowIndex, SD_UINT8* pFrameBuf, SDRFrameInfo *pFrameInfo = NULL);
	virtual bool GetVideoFrame(SD_UINT64 dwCurFrameStreamIndex, SD_UINT8* &pFrameBuf, SDRFrameInfo *pFrameInfo = NULL);
	virtual bool GetAudioSamples(SD_UINT32 dwCurSamplePos, SD_UINT32 dwSampleNum, SD_UINT8* pSamplesBuf, SD_UINT32* pdwRetSampleNum);
	virtual bool GetAudioFrame(SD_UINT32 dwCurFrameStreamIndex, SD_UINT32 dwFrameNum, SD_UINT8* &pFrameBuf, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};


