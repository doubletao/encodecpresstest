#pragma once
#include "SDL2\SDL.h"

struct BufferLoop
{
	char * m_pBuffer;
	int m_nBufSize;//缓冲区大小
	int m_nCursor;//当前读取游标
	int m_nRemainData;//当前数据size
	SDL_mutex * data_lock;

	BufferLoop();
	~BufferLoop();

	void Lock();
	void Unlock();
	void Reset(int nBufSize);
	void Release();
	void Push(char * pBuf, int nSize);
	void Pop(char * pBuf, int nSize);
};

class VideoPlayer
{
private:
	SDL_Window *screen;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
	int m_nWndWidth;
	int m_nWndHeight;
	BufferLoop m_AudioDataLoop;
	char * m_pAudioBuffer;
public:
	VideoPlayer();
	~VideoPlayer();
protected:
	static void fill_audio(void *udata, Uint8 *stream, int len);
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
	int IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
	int SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight);
	int PushFrame(unsigned char * data, int linesize);
	int PushYUVFrame(unsigned char **& data, int *& linesize);
	int PushAudioSample(unsigned char * data, int nBufSize);
	void ResetPlayer();
};

