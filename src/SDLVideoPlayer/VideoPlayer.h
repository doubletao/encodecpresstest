#pragma once
#include "SDL2\SDL.h"

class VideoPlayer
{
private:
	SDL_Window *screen;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
	int m_nWndWidth;
	int m_nWndHeight;
public:
	VideoPlayer();
	~VideoPlayer();
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight);
	int IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight);
	int SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight);
	int PushFrame(unsigned char * data, int linesize);
	int PushYUVFrame(unsigned char **& data, int *& linesize);
};

