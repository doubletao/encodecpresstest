#pragma once
#include "IecCodecAudioDecoder.h"
#include "ecCodecFFmpegResampler.h"
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
#include "libswresample\swresample.h"
#include "libavutil/audio_fifo.h"
}
#include <memory>

#define DEBUG_USE_RESAMPLER

class ecCodecFFmpegAudioDecoder :
	public IecCodecAudioDecoder
{
private:
	bool m_bIsInitialized;
	AVCodecContext * m_pCodecCtx;
	AVFrame	* m_pSrcFrame;
	AVAudioFifo*	m_pAudioFifo;
	SD_UINT64 m_nDesChannelLayout;
	AVSampleFormat m_emDesSampleFormat;
	SD_INT32 m_nDesSampleRate;
	SD_INT32 m_nDesChannelCount;
	SD_INT32 m_nLastSampleNum;
#ifdef DEBUG_USE_RESAMPLER
	ecCodecFFmpegResampler m_AudioResampler;
#else
	AVFrame*		m_pSwrFrame;
	SwrContext*		m_pSwrCtx;
#endif
public:
	ecCodecFFmpegAudioDecoder();
	virtual ~ecCodecFFmpegAudioDecoder();
public:
	virtual bool InitAudioDecoder(const SDAudioMediaInfo &sAudioInfo);
	virtual bool GetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo);
	virtual bool SetAudioMediaInfo(const SDAudioMediaInfo * pAudioInfo);
	virtual bool PutFrame(const SD_UINT8* pData, const SDRFrameInfo* pFrameInfo);
	virtual int  GetSample(SD_UINT8* &lpBuffer, SD_UINT32 nSampleNum);
	virtual double GetCurrentMilSecTimestamp(int num, int den);
	virtual SD_UINT32 GetBufferSize();
	virtual bool IsInitialized();
	virtual bool Release();
};

