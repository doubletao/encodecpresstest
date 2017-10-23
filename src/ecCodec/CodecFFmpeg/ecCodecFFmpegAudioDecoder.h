#pragma once
#include "IecCodecAudioDecoder.h"
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
#include "libavutil\audio_fifo.h"
#include "libswresample\swresample.h"
}
#include <memory>

class ecCodecFFmpegAudioDecoder :
	public IecCodecAudioDecoder
{
private:
	bool m_bIsInitialized;
	AVCodecContext * m_pCodecCtx;
	AVFrame	* m_pSrcFrame;
	AVFrame*		m_pSwrFrame;
	SwrContext*		m_pSwrCtx;
	AVAudioFifo*	m_pAudioFifo;
	std::unique_ptr<SD_UINT8[]> m_pDestBuffer;
public:
	ecCodecFFmpegAudioDecoder();
	virtual ~ecCodecFFmpegAudioDecoder();
public:
	virtual bool InitAudioDecoder(const SDAudioMediaInfo &sAudioInfo);
	virtual bool GetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo);
	virtual bool SetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo);
	virtual bool PutFrame(const SD_UINT8* pData, const SDRFrameInfo* pFrameInfo);
	virtual int  GetSample(SD_UINT8* &lpBuffer);
	virtual SD_UINT32 GetBufferSize();
	virtual bool IsInitialized();
	virtual bool Release();
};

