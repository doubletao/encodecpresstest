#pragma once
#ifdef SDL_VIDEO_PLAYER_API
#define SDL_VIDEO_PLAYER_EXPORT __declspec(dllexport)
#else
#define SDL_VIDEO_PLAYER_EXPORT __declspec(dllimport)
#ifdef _DEBUG
#	pragma comment(lib, "SDLVideoPlayerD.lib")
#else
#	pragma comment(lib, "SDLVideoPlayerU.lib")
#endif
#endif // SDL_VIDEO_PLAYER_API

class SDL_VIDEO_PLAYER_EXPORT SDLVideoPlayer
{
private:
	void * m_wndPlayer;
public:
	SDLVideoPlayer();
	~SDLVideoPlayer();
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
	int IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
	int SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight);
	int PushFrame(unsigned char * data, int linesize);
	int PushYUVFrame(unsigned char **& data, int *& linesize);
	int PushAudioSample(unsigned char * data, int nBufSize);
};
