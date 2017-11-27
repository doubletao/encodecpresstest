#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "VideoPlayer.h"
#include <stdio.h>
#include <assert.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "ddraw.lib")

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
	: m_pAudioBuffer(nullptr)
#ifdef PLAYER_USE_SDLPAINT
	, sdlRenderer(nullptr)
	, sdlTexture(nullptr)
	, m_nWndWidth(0)
	, m_nWndHeight(0)
	, screen(nullptr)
#else
	, m_pDDObject(nullptr)
	, m_pPrimary(nullptr)
	, m_pBack(nullptr)
	, m_pDDClipper(nullptr)
	, m_pSurfdesc(nullptr)
	, m_hDrawWnd(nullptr)
	, m_pDstImgBuf(nullptr)
	, m_dwSrcBufWidth(0)
	, m_dwSrcBufHeight(0)
	, m_enumSrcBufColorFormat(SDCOLORFORMAT_UNKNOW)
	, m_enumDisplayColorFormat(SDCOLORFORMAT_UNKNOW)
	, m_dwDstWidth(0)
	, m_dwDstHeight(0)
	, m_dwSrcLine(0)
	, m_dwDstLine(0)
	, m_bInitialize(false)
#endif
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
#ifdef PLAYER_USE_SDLPAINT
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
#else
	if (m_pBack) 
	{
		m_pBack->Release();
		m_pBack = NULL;
	}

	if (m_pSurfdesc) 
	{
		delete m_pSurfdesc;
		m_pSurfdesc = NULL;
	}

	if (m_pDDClipper) 
	{
		m_pDDClipper->Release();
		m_pDDClipper = NULL;
	}
	if (m_pPrimary) 
	{
		m_pPrimary->Release();
		m_pPrimary = NULL;
	}

	if (m_pDDObject) 
	{
		m_pDDObject->Release();
		m_pDDObject = NULL;
	}

	if (m_pDstImgBuf)
	{
		delete[] m_pDstImgBuf;
		m_pDstImgBuf = NULL;
	}
	m_bInitialize = false;
#endif
	SDL_Quit();
	delete[] m_pAudioBuffer;
	m_pAudioBuffer = nullptr;
}

int VideoPlayer::IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall)
{
#ifdef PLAYER_USE_SDLPAINT
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
#endif

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

#ifdef PLAYER_USE_SDLPAINT
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
#else
int VideoPlayer::IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall, void * pCallbackGetDrawRect)
{
	m_hDrawWnd				= (HWND)hWnd;
	m_dwSrcBufWidth			= nBufWidth;
	m_dwSrcBufHeight		= nBufHeight;
	m_enumSrcBufColorFormat	= SDCOLORFORMAT_UYVY;
	m_dwDstWidth			= (nWndWidth + 1)/2*2;
	m_dwDstHeight			= (nWndHeight)/2*2;
	m_pDstImgBuf			= new BYTE[nWndWidth*m_dwDstHeight*4];
	m_dwSrcLine				= m_dwSrcBufWidth*2;
	m_dwDstLine				= nWndWidth*2;
	m_pCallbackGetDrawRect	= (CallbackGetDrawRect)pCallbackGetDrawRect;

	HRESULT hr = DirectDrawCreate(NULL, &m_pDDObject, NULL);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	DDCAPS ddCaps;
	ZeroMemory(&ddCaps, sizeof(DDCAPS));
	ddCaps.dwSize = sizeof(DDCAPS);
	hr = m_pDDObject->GetCaps(&ddCaps, NULL);
	if (hr != NO_ERROR || ddCaps.dwVidMemFree < 1024*1024)
	{
		return S_FALSE;
	}

	hr = m_pDDObject->SetCooperativeLevel(m_hDrawWnd, DDSCL_NORMAL);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	DDSURFACEDESC  ddsd;
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hr = m_pDDObject->CreateSurface(&ddsd, &m_pPrimary, NULL);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	hr = m_pDDObject->CreateClipper(0, &m_pDDClipper, NULL);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	hr = m_pDDClipper->SetHWnd(0, m_hDrawWnd);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	hr = m_pPrimary->SetClipper(m_pDDClipper);
	if (hr != NO_ERROR)
	{
		return S_FALSE;
	}

	ddsd.dwWidth		=  m_dwDstWidth;
	ddsd.dwHeight		= m_dwDstHeight;
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN|DDSCAPS_LIVEVIDEO;
	ZeroMemory(&ddsd.ddpfPixelFormat, sizeof(DDPIXELFORMAT));

	ddsd.ddpfPixelFormat.dwSize	= sizeof(DDPIXELFORMAT);
	if (m_enumSrcBufColorFormat == SDCOLORFORMAT_UYVY)
	{
		ddsd.ddpfPixelFormat.dwSize			= sizeof(DDPIXELFORMAT);
		ddsd.ddpfPixelFormat.dwFlags		= DDPF_YUV|DDPF_FOURCC;
		ddsd.ddpfPixelFormat.dwFourCC		= 'YVYU'/*MAKEFOURCC('U', 'Y', 'V', 'Y')*/;
		ddsd.ddpfPixelFormat.dwRGBBitCount	= 16;
		hr = m_pDDObject->CreateSurface(&ddsd, &m_pBack, NULL);
		if (hr != NO_ERROR)
		{
			ddsd.ddpfPixelFormat.dwFourCC		= '2YUY';
			ddsd.ddpfPixelFormat.dwRGBBitCount	= 16;
			hr = m_pDDObject->CreateSurface(&ddsd, &m_pBack, NULL);
			if (hr != NO_ERROR)
			{
				return S_FALSE;
			}
			m_enumDisplayColorFormat = SDCOLORFORMAT_YUYV;
		}
		else
		{
			m_enumDisplayColorFormat = SDCOLORFORMAT_UYVY;
		}
	} 
	else if (m_enumSrcBufColorFormat == SDCOLORFORMAT_BGRA) 
	{
		ddsd.ddpfPixelFormat.dwFlags       = DDPF_RGB;
		ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
		ddsd.ddpfPixelFormat.dwRBitMask    = 0x00FF0000; 
		ddsd.ddpfPixelFormat.dwGBitMask    = 0x0000FF00;
		ddsd.ddpfPixelFormat.dwBBitMask    = 0x000000FF; 
		ddsd.ddpfPixelFormat.dwRGBAlphaBitMask =0XFF000000;
		hr = m_pDDObject->CreateSurface(&ddsd, &m_pBack, NULL);
		if (hr != NO_ERROR)
		{
			return S_FALSE;
		}
		m_enumDisplayColorFormat = SDCOLORFORMAT_BGRA;
	}

	m_pSurfdesc = new DDSURFACEDESC;
	memset(m_pSurfdesc,0,sizeof(DDSURFACEDESC));
	m_pSurfdesc->dwSize = sizeof(DDSURFACEDESC);

	m_bInitialize = TRUE;
#endif

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
#ifdef PLAYER_USE_SDLPAINT
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
#else

#endif
	return 0;
}

int VideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	//将数据刷出来
#ifdef PLAYER_USE_SDLPAINT
	SDL_UpdateTexture(sdlTexture, nullptr, data, linesize);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
	SDL_RenderPresent(sdlRenderer);
#else
	if (m_bInitialize == FALSE)
	{
		return 0;
	}
	HRESULT	hr = NO_ERROR;

	if (data == NULL || m_pBack == NULL)
	{
		return E_FAIL;
	}

	PBYTE pDrawBuf	= data;

	hr = m_pBack->Lock(NULL, m_pSurfdesc, DDLOCK_WAIT, NULL);
	if (hr != NO_ERROR)
	{
		m_pBack->Restore();
		hr = m_pBack->Lock(NULL, m_pSurfdesc, DDLOCK_WAIT, NULL);
		if (hr != NO_ERROR)
		{
			return hr;
		}
	}
	BYTE* pBuffer = pDrawBuf;
	if (m_enumSrcBufColorFormat == SDCOLORFORMAT_BGRA)
	{
		BYTE* pAddress = (BYTE*) m_pSurfdesc->lpSurface;
		BYTE* pSource  = pBuffer;
		int iSrcPitch = m_dwDstWidth*4;
		for (DWORD y = 0; y < m_dwDstHeight; y++)
		{
			memcpy(pAddress, pSource, iSrcPitch);
			pAddress += m_pSurfdesc->lPitch;
			pSource  += iSrcPitch;
		}
	} 
	else if (m_enumSrcBufColorFormat == SDCOLORFORMAT_YUYV)
	{
		BYTE* pAddress = (BYTE*)m_pSurfdesc->lpSurface;
		BYTE* pSource  = pBuffer;
		for (DWORD y = 0; y < m_dwDstHeight; y++)
		{
			memcpy(pAddress, pSource, m_dwDstWidth*2);
			pAddress += m_pSurfdesc->lPitch;
			pSource  += (m_dwDstWidth*2);
		}
	} 
	else if (m_enumSrcBufColorFormat == SDCOLORFORMAT_UYVY)
	{
		if (m_enumDisplayColorFormat == SDCOLORFORMAT_UYVY)
		{
			BYTE* pAddress = (BYTE*)m_pSurfdesc->lpSurface;
			BYTE* pSource  = pBuffer;
			int iSrcPitch = m_dwDstWidth*2;

			for (DWORD y = 0; y < m_dwDstHeight; y++)
			{
				memcpy(pAddress, pSource, iSrcPitch);	
				pAddress += m_pSurfdesc->lPitch;
				pSource  += iSrcPitch;
			}

		} 
		else if (m_enumDisplayColorFormat == SDCOLORFORMAT_YUYV)
		{
			Render_SYCOLORFORMAT_UYVYtoYUY2((BYTE*)m_pSurfdesc->lpSurface,
				m_pSurfdesc->lPitch,
				pBuffer,
				m_dwDstWidth, m_dwDstHeight);
		}
	}

	hr = m_pBack->Unlock(m_pSurfdesc->lpSurface);
	if (hr != NO_ERROR)
	{
		return hr;
	}

	if (m_pPrimary->IsLost() == DDERR_SURFACELOST) 
	{
		hr = m_pPrimary->Restore();
	}

	if (m_pPrimary)
	{
		RECT rect = {0, 0, m_dwDstWidth, m_dwDstHeight};
		RECT rectDraw = {0};
		if (m_pCallbackGetDrawRect)
		{
			rectDraw = m_pCallbackGetDrawRect(m_hDrawWnd);
		}
		hr = m_pPrimary->Blt(&rectDraw, m_pBack, &rect, DDBLT_WAIT, NULL);
	}
#endif
	return 1;
}

int VideoPlayer::PushYUVFrame(unsigned char **& data, int *& linesize)
{
	//将数据刷出来
#ifdef PLAYER_USE_SDLPAINT
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
#endif
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

#ifndef PLAYER_USE_SDLPAINT
void VideoPlayer::Render_SYCOLORFORMAT_YUV422toYUY2(unsigned char *dst, int stride, unsigned char *buffer, int Clip_Width, int Clip_Height)
{
	BOOL IsU = FALSE;
	DWORD i,j;
	BYTE* m_pY = buffer;
	BYTE* m_pU = m_pY + Clip_Width*Clip_Height;
	BYTE* m_pV = m_pU + Clip_Width*Clip_Height/2;

	for (j = 0; j < DWORD(Clip_Height); j++) {
		IsU = TRUE;
		for (i = 0; i < DWORD(Clip_Width); i++)	
		{
			dst[2*i] = *m_pY;
			if(IsU)
			{
				dst[2*i+1] = *m_pU;  
				m_pU++;

				IsU = FALSE;
			}
			else
			{
				dst[2*i+1] = *m_pV;  
				m_pV++;

				IsU = TRUE;
			}
			m_pY++;
		}
		dst += stride;
	}
}

void VideoPlayer::Render_SYCOLORFORMAT_UYVYtoYUY2(unsigned char *dst, int stride, unsigned char *buffer, int Clip_Width, int Clip_Height)
{
	DWORD i,j;
	for (j = 0; j < DWORD(Clip_Height); j++)	
	{
		for (i = 0; i < DWORD(Clip_Width); i++)	
		{
			dst[2*i] = buffer[2*i+1];  
			dst[2*i+1] = buffer[2*i];  
		}
		dst += stride;
		buffer += Clip_Width*2;
	}
}
#endif
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
