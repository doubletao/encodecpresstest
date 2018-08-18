#pragma once
#include "SDLVideoPlayer.h"
#ifdef PLAYER_USE_SDLPAINT
#include "SDL2\SDL.h"

#include "ddraw.h"
#else
#include "SDL2\SDL.h"
#include "ddraw.h"
#include "..\SDDefine\SDDefine.h"
#include "..\SDDefine\SDVADefine.h"
typedef RECT(* CallbackGetDrawRect)(HWND hWnd);
#endif

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
#ifdef PLAYER_USE_SDLPAINT
	HWND m_hWnd;
	SDL_Window *screen;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
	int m_nWndWidth;
	int m_nWndHeight;
#else
	bool m_bInitialize;

	LPDIRECTDRAW			m_pDDObject;            //DirexctDraw专用
	LPDIRECTDRAWSURFACE		m_pPrimary; 
	LPDIRECTDRAWSURFACE		m_pBack; 
	LPDIRECTDRAWCLIPPER		m_pDDClipper; 
	LPDDSURFACEDESC			m_pSurfdesc;

	HWND					m_hDrawWnd;
	unsigned int			m_dwSrcBufWidth;
	unsigned int			m_dwSrcBufHeight;
	SD_COLOR_FORMAT			m_enumSrcBufColorFormat;
	SD_COLOR_FORMAT			m_enumDisplayColorFormat;

	unsigned int			m_dwDstWidth;
	unsigned int			m_dwDstHeight;
	int						m_dwSrcLine;
	int						m_dwDstLine;
	LPBYTE					m_pDstImgBuf;
	CallbackGetDrawRect		m_pCallbackGetDrawRect;
#endif
	BufferLoop m_AudioDataLoop;
	char * m_pAudioBuffer;
public:
	VideoPlayer();
	~VideoPlayer();
protected:
	static void fill_audio(void *udata, Uint8 *stream, int len);
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
	int SetBufferFWH(unsigned int nFormat, int nBufWidth, int nBufHeight);
	int PushFrame(unsigned char * data, int linesize);
	int PushYUVFrame(unsigned char **& data, int *& linesize);
	int PushAudioSample(unsigned char * data, int nBufSize);
	void ResetPlayer();
#ifdef PLAYER_USE_SDLPAINT
	int IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall);
#else
	int IntialWnd(unsigned int nFormat, void * hWnd, int nWndWidth, int nWndHeight, int nBufWidth, int nBufHeight, int nAudioSampPerSec, unsigned __int16 nSamplePerCall, void * pCallbackGetDrawRect);
	void Render_SYCOLORFORMAT_YUV422toYUY2( unsigned char *dst, int stride, unsigned char *buffer, int Clip_Width, int Clip_Height );
	void Render_SYCOLORFORMAT_UYVYtoYUY2( unsigned char *dst, int stride, unsigned char *buffer, int Clip_Width, int Clip_Height );
#endif
};

