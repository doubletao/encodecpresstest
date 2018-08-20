#pragma once
#include "IVAPlayer.h"
#include "SDL2\include\SDL.h"
#include <mutex>
#include "AudioBufferLoop.h"

class SDL_VAPlayer : public IVAPlayer
{
protected:
	void * m_hWnd;
	int m_nWndX;
	int m_nWndY;
	int m_nWndWidth;
	int m_nWndHeight;
	EmVAPlayerColorFmt m_emColorFmt;
	int m_nBufWidth;
	int m_nBufHeight;
	EmVAPlayerSampleFmt m_emSampleFmt;
	int m_nAudioSampPerSec;
	unsigned __int8 m_nChannelCount;
	unsigned __int16 m_nSamplePerCall;
	std::mutex m_lock;

	CAudioBufferLoop m_AudioDataLoop;
	char * m_pAudioBuffer;

	SDL_Window * m_sdlScreen;
	SDL_Renderer* m_sdlRenderer;
	SDL_Texture* m_sdlTexture;
public:
	SDL_VAPlayer();
	~SDL_VAPlayer();
protected:
	void Lock();
	void Unlock();
public:
	static unsigned __int32 ConvertColorFmt(EmVAPlayerColorFmt emColorFmt);
	static EmVAPlayerColorFmt ConvertColorFmt(unsigned __int32 nFormat);
	static SDL_AudioFormat ConvertSampleFmt(EmVAPlayerSampleFmt emSampleFmt);
	static EmVAPlayerSampleFmt ConvertSampleFmt(SDL_AudioFormat nSampleFmt);
	//音频回调
	static void fill_audio(void *udata, Uint8 *stream, int len);
public:
	//创建播放器
	virtual bool CreatePayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight,
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall);
	//重置播放器（释放然后按照指定参数重新创建）
	virtual bool ResetPlayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight,
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall);
	//基于一个已经存在的窗体创建一个播放器
	virtual bool CreatePayer(void * hWnd, int nWndX, int nWndY, int nWndWidth, int nWndHeight,
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall);
	//重置播放器（释放然后按照原有参数重新创建）
	virtual bool ResetPlayer();
	virtual bool MoveWindow(int nX, int nY, int nWndWidth, int nWndHeight);
	virtual int PushFrame(unsigned char * data, int linesize);
	virtual int PushYUVFrame(unsigned char **& data, int *& linesize);
	virtual int PushAudioSample(unsigned char * data, int nBufSize);
	virtual bool ReleasePlayer();
};

