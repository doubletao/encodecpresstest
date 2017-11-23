#include "VideoPlayer.h"
#include <stdio.h>
#include <assert.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

void VideoPlayer::fill_audio(void * udata, Uint8 * stream, int len)
{
	VideoPlayer * pThis = (VideoPlayer *)udata;
	if (pThis)
	{
		//SDL 2.0
		SDL_memset(stream, 0, len);
		pThis->m_AudioDataLoop.Pop(pThis->m_pAudioBuffer, len);
		SDL_MixAudio(stream, (const Uint8 *)pThis->m_pAudioBuffer, len, SDL_MIX_MAXVOLUME);
	}
}

VideoPlayer::VideoPlayer()
	: screen(nullptr)
	, sdlRenderer(nullptr)
	, sdlTexture(nullptr)
	, m_nWndWidth(0)
	, m_nWndHeight(0)
	, m_pAudioBuffer(nullptr)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) 
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		assert(false);
	}

	m_pAudioBuffer = new char[1024 * 1024];
}


VideoPlayer::~VideoPlayer()
{
	if (screen)
	{
		SDL_DestroyWindow(screen);
		screen = nullptr;
	}
	if (sdlRenderer)
	{
		SDL_DestroyRenderer(sdlRenderer);
		sdlRenderer = nullptr;
	}
	if (sdlTexture)
	{
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = nullptr;
	}
	SDL_Quit();
	delete[] m_pAudioBuffer;
	m_pAudioBuffer = nullptr;
}

int VideoPlayer::IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall)
{
	m_nWndWidth = nWndWidth;
	m_nWndHeight = nWndHeight;
	//先创建screen
	screen = SDL_CreateWindow("Simplest ffmpeg player's Window", x, y,
		nWndWidth, nWndHeight, SDL_WINDOW_OPENGL);
	if (!screen) 
	{
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return 0;
	}

	//创建渲染器
	sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	if (!sdlRenderer)
	{
		printf("SDL: could not create renderer - exiting:%s\n", SDL_GetError());
		return 0;
	}
	//创建纹理
	sdlTexture = SDL_CreateTexture(sdlRenderer, nFormat, SDL_TEXTUREACCESS_STREAMING, nBufWidth, nBufHeight);
	if (!sdlTexture)
	{
		printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
		return 0;
	}

	//打开音频并开始播放静音
	//SDL_AudioSpec
	SDL_AudioSpec wanted_spec;
	wanted_spec.freq = nAudioSampPerSec;
	wanted_spec.format = AUDIO_S16SYS;//16位整数写死
	wanted_spec.channels = 2;//双声道写死
	wanted_spec.silence = 0;
	wanted_spec.samples = nSamplePerCall;
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = this;

	if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
	{
		printf("can't open audio.\n");
		return 0;
	}
	SDL_PauseAudio(0);

	return 1;
}

int VideoPlayer::IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall)
{
	m_nWndWidth = nWndWidth;
	m_nWndHeight = nWndHeight;
	//先创建screen
	screen = SDL_CreateWindowFrom(hWnd);
	if (!screen)
	{
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return 0;
	}

	//创建渲染器
	sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	if (!sdlRenderer)
	{
		printf("SDL: could not create renderer - exiting:%s\n", SDL_GetError());
		return 0;
	}
	//创建纹理
	sdlTexture = SDL_CreateTexture(sdlRenderer, nFormat, SDL_TEXTUREACCESS_STREAMING, nBufWidth, nBufHeight);
	if (!sdlTexture)
	{
		printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
		return 0;
	}

	//打开音频并开始播放静音
	//SDL_AudioSpec
	SDL_AudioSpec wanted_spec;
	wanted_spec.freq = nAudioSampPerSec;
	wanted_spec.format = AUDIO_S16SYS;//16位整数写死
	wanted_spec.channels = 2;//双声道写死
	wanted_spec.silence = 0;
	wanted_spec.samples = nSamplePerCall;
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = this;

	if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
	{
		printf("can't open audio.\n");
		return 0;
	}
	SDL_PauseAudio(0);

	return 1;
}

int VideoPlayer::SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight)
{
	if (sdlTexture)
	{
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = nullptr;
	}
	sdlTexture = SDL_CreateTexture(sdlRenderer, nFormat, SDL_TEXTUREACCESS_STREAMING, nBufWidth, nBufHeight);
	if (!sdlTexture)
	{
		printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
		return 0;
	}
	return 0;
}

int VideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	//将数据刷出来
	SDL_UpdateTexture(sdlTexture, nullptr, data, linesize);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
	SDL_RenderPresent(sdlRenderer);
	return 1;
}

int VideoPlayer::PushYUVFrame(unsigned char **& data, int *& linesize)
{
	//将数据刷出来
	SDL_UpdateYUVTexture(sdlTexture, nullptr
		, data[0], linesize[0]
		, data[1], linesize[1]
		, data[2], linesize[2]);
	SDL_RenderClear(sdlRenderer);
	SDL_Rect rtDes;
	rtDes.x = 0;
	rtDes.y = 0;
	rtDes.w = m_nWndWidth;
	rtDes.h = m_nWndHeight;
	SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &rtDes);
	SDL_RenderPresent(sdlRenderer);
	return 1;
}

int VideoPlayer::PushAudioSample(unsigned char * data, int nBufSize)
{
	m_AudioDataLoop.Push((char *)data, nBufSize);
	return 1;
}

void VideoPlayer::ResetPlayer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int BUFFER_GROWTH = 5 * 1024 * 2014;
BufferLoop::BufferLoop()
	: m_pBuffer(nullptr)
	, m_nBufSize(0)
	, m_nCursor(0)
	, m_nRemainData(0)
	, data_lock(nullptr)
{
	data_lock = SDL_CreateMutex();
}

BufferLoop::~BufferLoop()
{
	Release();
	SDL_DestroyMutex(data_lock);
}

void BufferLoop::Lock()
{
	SDL_LockMutex(data_lock);
}

void BufferLoop::Unlock()
{
	SDL_UnlockMutex(data_lock);
}

void BufferLoop::Reset(int nBufSize)
{
	Lock();
	Release();
	if (nBufSize > 0)
	{
		m_pBuffer = new char[nBufSize];
		assert(m_pBuffer);
		m_nBufSize = nBufSize;
	}
	Unlock();
}

void BufferLoop::Release()
{
	Lock();
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
	m_nBufSize = 0;
	m_nCursor = 0;
	m_nRemainData = 0;
	Unlock();
}

void BufferLoop::Push(char * pBuf, int nSize)
{
	Lock();
	//nSize > 0才有得聊
	if (nSize > 0)
	{
		//当push量大于了缓冲区大小减去当前remain大小，则重新申请内存
		if (nSize > m_nBufSize - m_nRemainData)
		{
			int nNewSize = m_nBufSize + BUFFER_GROWTH + nSize;
			char  * pNewBuf = new char[nNewSize];
			assert(pNewBuf);
			//拷贝原数据
			Pop(pNewBuf, m_nRemainData);
			m_nCursor = 0;
			m_nBufSize = nNewSize;
			delete[] m_pBuffer;
			m_pBuffer = pNewBuf;
			//拷贝新数据
			Push(pBuf, nSize);
		}
		else
		{
			//如果从游标到缓冲区末尾放不下，则先往里填，剩下的往开头填
			if (nSize > m_nBufSize - m_nCursor)
			{
				SDL_memcpy(m_pBuffer + m_nCursor, pBuf, m_nBufSize - m_nCursor);
				SDL_memcpy(m_pBuffer, pBuf + m_nBufSize - m_nCursor, nSize - (m_nBufSize - m_nCursor));
			}
			//如果游标位置能放下，直接往里填
			else
			{
				SDL_memcpy(m_pBuffer + m_nCursor, pBuf, nSize);
			}
			m_nRemainData += nSize;
		}
	}
	Unlock();
}

void BufferLoop::Pop(char * pBuf, int nSize)
{
	Lock();
	//nSize > 0才有得聊
	if (nSize > 0)
	{
		if (nSize > m_nRemainData)
		{
			//如果不够，则将现有的填进去，其他的部分填0
			SDL_memset(pBuf, 0, nSize);
			Pop(pBuf, m_nRemainData);
		}
		else
		{
			//如果从游标到缓冲区末尾数据不够，则先往里填，剩下的从开头往里填
			if (nSize > m_nBufSize - m_nCursor)
			{
				SDL_memcpy(pBuf, m_pBuffer + m_nCursor, m_nBufSize - m_nCursor);
				m_nCursor = 0;
				m_nRemainData = m_nRemainData - (m_nBufSize - m_nCursor);
				SDL_memcpy(pBuf + m_nBufSize - m_nCursor, m_pBuffer, nSize - (m_nBufSize - m_nCursor));
				m_nCursor = nSize - (m_nBufSize - m_nCursor);
				m_nRemainData = m_nRemainData - (nSize - (m_nBufSize - m_nCursor));
			}
			//如果游标位置能放下，直接往里填
			else
			{
				SDL_memcpy(pBuf, m_pBuffer + m_nCursor, nSize);
				m_nRemainData = m_nRemainData - nSize;
			}
		}
	}
	Unlock();
}
