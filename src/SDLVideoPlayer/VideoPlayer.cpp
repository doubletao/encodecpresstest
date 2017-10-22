#include "VideoPlayer.h"
#include <stdio.h>
#include <assert.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

VideoPlayer::VideoPlayer()
	: screen(nullptr)
	, sdlRenderer(nullptr)
	, sdlTexture(nullptr)
	, m_nWndWidth(0)
	, m_nWndHeight(0)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) 
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		assert(false);
	}
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
}

int VideoPlayer::IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight)
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

	return 1;
}

int VideoPlayer::IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight)
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
	return 0;
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
