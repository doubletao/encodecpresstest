#include "SDL_VAPlayer.h"
#include <assert.h>
#pragma comment(lib, "SDL2\\lib\\SDL2.lib")
#pragma comment(lib, "SDL2\\lib\\SDL2main.lib")

SDL_VAPlayer::SDL_VAPlayer()
	: m_nWndX(0)
	, m_nWndY(0)
	, m_nWndWidth(0)
	, m_nWndHeight(0)
	, m_emColorFmt(EmVAPlayerColorFmt_UYVY)
	, m_nBufWidth(0)
	, m_nBufHeight(0)
	, m_bStartAudio(false)
	, m_emSampleFmt(EmVAPlayerSampleFmt_S16SYS)
	, m_nAudioSampPerSec(0)
	, m_nChannelCount(0)
	, m_nSamplePerCall(0)
	, m_pAudioBuffer(nullptr)
	, m_sdlScreen(nullptr)
	, m_sdlRenderer(nullptr)
	, m_sdlTexture(nullptr)
	, m_hWnd(nullptr)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		assert(false);
	}

	m_pAudioBuffer = new char[1024 * 1024];
}


SDL_VAPlayer::~SDL_VAPlayer()
{
	ReleasePlayer();
}

void SDL_VAPlayer::Lock()
{
	m_lock.lock();
}

void SDL_VAPlayer::Unlock()
{
	m_lock.unlock();
}

void SDL_VAPlayer::DealSDLEvent()
{
	//检测一下事件
	SDL_Event test_event;
	if (SDL_PollEvent(&test_event))
	{
		switch (test_event.type)
		{
		case SDL_WINDOWEVENT:
		{
			if (SDL_WINDOWEVENT_EXPOSED == test_event.window.event)
			{
				ResetPlayer();
			}
		}
		break;
		}
	}
}

unsigned __int32 SDL_VAPlayer::ConvertColorFmt(EmVAPlayerColorFmt emColorFmt)
{
	unsigned __int32 nRet = 0;
	switch (emColorFmt)
	{
	case EmVAPlayerColorFmt_UYVY:
		nRet = SDL_PIXELFORMAT_UYVY;
		break;
	default:
		break;
	}
	return nRet;
}

EmVAPlayerColorFmt SDL_VAPlayer::ConvertColorFmt(unsigned __int32 nFormat)
{
	EmVAPlayerColorFmt emRet = EmVAPlayerColorFmt_UYVY;
	switch (nFormat)
	{
	case SDL_PIXELFORMAT_UYVY:
		emRet = EmVAPlayerColorFmt_UYVY;
		break;
	default:
		break;
	}
	return EmVAPlayerColorFmt();
}

SDL_AudioFormat SDL_VAPlayer::ConvertSampleFmt(EmVAPlayerSampleFmt emSampleFmt)
{
	SDL_AudioFormat nFmt = AUDIO_S16SYS;
	switch (emSampleFmt)
	{
	case EmVAPlayerSampleFmt_S16SYS:
		nFmt = AUDIO_S16SYS;
		break;
	default:
		break;
	}
	return nFmt;
}

EmVAPlayerSampleFmt SDL_VAPlayer::ConvertSampleFmt(SDL_AudioFormat nSampleFmt)
{
	EmVAPlayerSampleFmt emSampleFmt = EmVAPlayerSampleFmt_S16SYS;
	switch (nSampleFmt)
	{
	case AUDIO_S16SYS:
		emSampleFmt = EmVAPlayerSampleFmt_S16SYS;
		break;
	default:
		break;
	}
	return emSampleFmt;
}

void SDL_VAPlayer::fill_audio(void * udata, Uint8 * stream, int len)
{
	SDL_VAPlayer * pThis = (SDL_VAPlayer *)udata;
	if (pThis)
	{
		//SDL 2.0
		SDL_memset(stream, 0, len);
		if (pThis->m_AudioDataLoop.WaitPop(pThis->m_pAudioBuffer, len, 100))
		{
			SDL_MixAudio(stream, (const Uint8 *)pThis->m_pAudioBuffer, len, SDL_MIX_MAXVOLUME);
		}
		else
		{
			char szOutput[256];
			sprintf_s(szOutput, 256, "fill_audio len = %d, clock = %d\r\n", len, clock());
			//OutputDebugStringA(szOutput);
		}
	}
}

bool SDL_VAPlayer::CreatePayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight, EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight, bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall)
{
	bool bRet = false;
	m_nWndX = nWndX;
	m_nWndY = nWndY;
	m_nWndWidth = nWndWidth;
	m_nWndHeight = nWndHeight;
	m_emColorFmt = emColorFmt;
	m_nBufWidth = nBufWidth;
	m_nBufHeight = nBufHeight;
	m_bStartAudio = bStartAudio;
	m_emSampleFmt = emSampleFmt;
	m_nAudioSampPerSec = nAudioSampPerSec;
	m_nChannelCount = nChannelCount;
	m_nSamplePerCall = nSamplePerCall;

	Lock();
	int nRet = 0;
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if (0 == nRet)
	{
		//先创建screen
		m_sdlScreen = SDL_CreateWindow("SDLWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			nWndWidth, nWndHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (m_sdlScreen)
		{
			//创建渲染器
			m_sdlRenderer = SDL_CreateRenderer(m_sdlScreen, -1, 0);
			//IYUV: Y + U + V  (3 planes)
			//YV12: Y + V + U  (3 planes)
			if (m_sdlRenderer)
			{
				SDL_PIXELFORMAT_UYVY;
				//创建纹理
				m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, ConvertColorFmt(emColorFmt), SDL_TEXTUREACCESS_STREAMING, nBufWidth, nBufHeight);
				if (m_sdlTexture)
				{
					if (bStartAudio)
					{
						//初始化音频播放器
						SDL_AudioSpec wanted_spec;
						wanted_spec.freq = nAudioSampPerSec;
						wanted_spec.format = ConvertSampleFmt(emSampleFmt);
						wanted_spec.channels = nChannelCount;
						wanted_spec.silence = 0;
						wanted_spec.samples = nSamplePerCall;
						wanted_spec.callback = fill_audio;
						wanted_spec.userdata = this;

						if (SDL_OpenAudio(&wanted_spec, NULL) == 0)
						{
							SDL_PauseAudio(0);
							bRet = true;
						}
						else
						{
							printf("can't open audio.\n");
						}
					}
					else
					{
						bRet = true;
					}
				}
				else
				{
					printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
				}
			}
			else
			{
				printf("SDL: could not create renderer - exiting:%s\n", SDL_GetError());
			}
		}
		else
		{
			printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		}
	}
	Unlock();

	return bRet;
}

bool SDL_VAPlayer::ResetPlayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight, EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight, bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall)
{
	bool bRet = false;
	m_nWndX = nWndX;
	m_nWndY = nWndY;
	m_nWndWidth = nWndWidth;
	m_nWndHeight = nWndHeight;
	m_emColorFmt = emColorFmt;
	m_nBufWidth = nBufWidth;
	m_nBufHeight = nBufHeight;
	m_bStartAudio = bStartAudio;
	m_emSampleFmt = emSampleFmt;
	m_nAudioSampPerSec = nAudioSampPerSec;
	m_nChannelCount = nChannelCount;
	m_nSamplePerCall = nSamplePerCall;
	//先简单的实现一下，只是删除再创建，为防止释放重建的过程中有画面push进来，所以锁一下
	Lock();
	if (ReleasePlayer())
	{
		if (CreatePayer(nWndX, nWndY, nWndWidth, nWndHeight, emColorFmt, nBufWidth, nBufHeight, bStartAudio, emSampleFmt, nAudioSampPerSec, nChannelCount, nSamplePerCall))
		{
			bRet = true;
		}
	}
	Unlock();
	return bRet;
}

bool SDL_VAPlayer::CreatePayer(void * hWnd, int nWndX, int nWndY, int nWndWidth, int nWndHeight, EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight, bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall)
{
	bool bRet = false;
	m_hWnd = hWnd;
	m_nWndX = nWndX;
	m_nWndY = nWndY;
	m_nWndWidth = nWndWidth;
	m_nWndHeight = nWndHeight;
	m_emColorFmt = emColorFmt;
	m_nBufWidth = nBufWidth;
	m_nBufHeight = nBufHeight;
	m_bStartAudio = bStartAudio;
	m_emSampleFmt = emSampleFmt;
	m_nAudioSampPerSec = nAudioSampPerSec;
	m_nChannelCount = nChannelCount;
	m_nSamplePerCall = nSamplePerCall;

	Lock();
	int nRet = 0;
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	nRet |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if (0 == nRet)
	{
		//先创建screen
		m_sdlScreen = SDL_CreateWindowFrom(hWnd);
		if (m_sdlScreen)
		{
			//创建渲染器
			m_sdlRenderer = SDL_CreateRenderer(m_sdlScreen, -1, 0);
			//IYUV: Y + U + V  (3 planes)
			//YV12: Y + V + U  (3 planes)
			if (m_sdlRenderer)
			{
				SDL_PIXELFORMAT_UYVY;
				//创建纹理
				m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, ConvertColorFmt(emColorFmt), SDL_TEXTUREACCESS_STREAMING, nBufWidth, nBufHeight);
				if (m_sdlTexture)
				{
					if (bStartAudio)
					{
						//初始化音频播放器
						SDL_AudioSpec wanted_spec;
						wanted_spec.freq = nAudioSampPerSec;
						wanted_spec.format = ConvertSampleFmt(emSampleFmt);
						wanted_spec.channels = nChannelCount;
						wanted_spec.silence = 0;
						wanted_spec.samples = nSamplePerCall;
						wanted_spec.callback = fill_audio;
						wanted_spec.userdata = this;

						if (SDL_OpenAudio(&wanted_spec, NULL) == 0)
						{
							SDL_PauseAudio(0);
							bRet = true;
						}
						else
						{
							printf("can't open audio.\n");
						}
					}
					else
					{
						bRet = true;
					}
				}
				else
				{
					printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
				}
			}
			else
			{
				printf("SDL: could not create renderer - exiting:%s\n", SDL_GetError());
			}
		}
		else
		{
			printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		}
	}
	Unlock();

	return bRet;
}

bool SDL_VAPlayer::ResetPlayer()
{
	Lock();
	if (ReleasePlayer())
	{
		if (m_hWnd)
		{
			return CreatePayer(m_hWnd, m_nWndX, m_nWndY, m_nWndWidth, m_nWndHeight, m_emColorFmt, m_nBufWidth, m_nBufHeight, m_bStartAudio, m_emSampleFmt, m_nAudioSampPerSec, m_nChannelCount, m_nSamplePerCall);
		}
		else
		{
			return CreatePayer(m_nWndX, m_nWndY, m_nWndWidth, m_nWndHeight, m_emColorFmt, m_nBufWidth, m_nBufHeight, m_bStartAudio, m_emSampleFmt, m_nAudioSampPerSec, m_nChannelCount, m_nSamplePerCall);
		}
	}
	Unlock();
}

bool SDL_VAPlayer::MoveWindow(int nX, int nY, int nWndWidth, int nWndHeight)
{
	bool bRet = false;
	if (m_sdlScreen)
	{
		SDL_SetWindowPosition(m_sdlScreen, nX, nY);
		SDL_SetWindowSize(m_sdlScreen, nWndWidth, nWndHeight);
		bRet = true;
	}
	return bRet;
}

int SDL_VAPlayer::PushFrame(unsigned char * data, int linesize)
{
	Lock();
	if (m_sdlTexture && m_sdlRenderer)
	{
		int nRet = SDL_UpdateTexture(m_sdlTexture, nullptr, data, linesize);
		nRet = SDL_RenderClear(m_sdlRenderer);
		nRet = SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, nullptr, nullptr);
		SDL_RenderPresent(m_sdlRenderer);
	}
	Unlock();
	//DealSDLEvent();
	return 0;
}

int SDL_VAPlayer::PushYUVFrame(unsigned char **& data, int *& linesize)
{
	Lock();
	if (m_sdlTexture && m_sdlRenderer)
	{
		SDL_UpdateYUVTexture(m_sdlTexture, nullptr
			, data[0], linesize[0]
			, data[1], linesize[1]
			, data[2], linesize[2]);
		SDL_RenderClear(m_sdlRenderer);
		SDL_Rect rtDes;
		rtDes.x = 0;
		rtDes.y = 0;
		rtDes.w = m_nWndWidth;
		rtDes.h = m_nWndHeight;
		SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, nullptr, &rtDes);
		SDL_RenderPresent(m_sdlRenderer);
	}
	Unlock();
	//DealSDLEvent();
	return 0;
}

int SDL_VAPlayer::PushAudioSample(unsigned char * data, int nBufSize)
{
	m_AudioDataLoop.Push((char *)data, nBufSize);
	return 0;
}

bool SDL_VAPlayer::ReleasePlayer()
{
	if (m_sdlScreen)
	{
		SDL_DestroyWindow(m_sdlScreen);
		m_sdlScreen = nullptr;
	}
	if (m_sdlRenderer)
	{
		SDL_DestroyRenderer(m_sdlRenderer);
		m_sdlRenderer = nullptr;
	}
	if (m_sdlTexture)
	{
		SDL_DestroyTexture(m_sdlTexture);
		m_sdlTexture = nullptr;
	}
	SDL_Quit();
	if (m_pAudioBuffer)
	{
		delete[] m_pAudioBuffer;
		m_pAudioBuffer = nullptr;
	}
	SDL_CloseAudio();
	m_hWnd = nullptr;
	return true;
}
