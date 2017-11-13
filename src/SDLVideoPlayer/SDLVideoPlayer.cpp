#include "SDLVideoPlayer.h"
#include "VideoPlayer.h"

static VideoPlayer * StaticCast(void * pPlayer)
{
	return static_cast<VideoPlayer *>(pPlayer);
}

SDLVideoPlayer::SDLVideoPlayer()
	: m_wndPlayer(nullptr)
{
	m_wndPlayer = new VideoPlayer;
}


SDLVideoPlayer::~SDLVideoPlayer()
{
	if (m_wndPlayer)
	{
		delete StaticCast(m_wndPlayer);
		m_wndPlayer = nullptr;
	}
}

int SDLVideoPlayer::IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall)
{
	return StaticCast(m_wndPlayer)->IntialWnd(nFormat, x, y, nWndWidth, nWndHeight, nBufWidth, nBufHeight, nAudioSampPerSec, nSamplePerCall);
}

int SDLVideoPlayer::IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall)
{
	return StaticCast(m_wndPlayer)->IntialWnd(nFormat, hWnd, nWndWidth, nWndHeight, nBufWidth, nBufHeight, nAudioSampPerSec, nSamplePerCall);
}

int SDLVideoPlayer::SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight)
{
	return StaticCast(m_wndPlayer)->SetBufferFWH(nFormat, nBufWidth, nBufHeight);
}

int SDLVideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	return StaticCast(m_wndPlayer)->PushFrame(data, linesize);
}

int SDLVideoPlayer::PushYUVFrame(unsigned char **& data, int *& linesize)
{
	return StaticCast(m_wndPlayer)->PushYUVFrame(data, linesize);
}

int SDLVideoPlayer::PushAudioSample(unsigned char * data, int nBufSize)
{
	return StaticCast(m_wndPlayer)->PushAudioSample(data, nBufSize);
}
