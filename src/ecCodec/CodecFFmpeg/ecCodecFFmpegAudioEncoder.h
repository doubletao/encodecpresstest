#pragma once
#include "IecCodecAudioEncoder.h"
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

class ecCodecFFmpegAudioEncoder :
	public IecCodecAudioEncoder
{
public:
	ecCodecFFmpegAudioEncoder();
	virtual ~ecCodecFFmpegAudioEncoder();
private:
	AVFrame*		m_pSwrFrame;
	AVFrame*		m_pAudioFrame;
	AVCodecContext* m_pCodecCtx;
	SwrContext*		m_pSwrCtx;
	AVAudioFifo*	m_pAudioFifo;
	std::unique_ptr<SD_UINT8[]>	m_pDestBuffer;
	SD_UINT32		m_destSize;
	SD_INT64		m_pts;
	int			    m_nBytesPerSrcSample;
public:
	virtual bool InitAudioEncoder(const SDAudioMediaInfo &sAudioInfo);
	virtual bool SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo *pAudioBufInfo);
	virtual bool WriteSample(const SD_UINT8* pData, SD_UINT32 iSize, bool emInputFlag);
	virtual bool SetEndofInput();
	virtual int GetCompressFrame(SD_UINT8* &pData, SDRFrameInfo* pFrameInfo);
	virtual bool Release();
	AVCodecContext* GetCodecContext() const;
};

