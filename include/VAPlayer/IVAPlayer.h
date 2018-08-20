#pragma once
enum EmVAPlayerColorFmt
{
	EmVAPlayerColorFmt_UYVY,
};

enum EmVAPlayerSampleFmt
{
	EmVAPlayerSampleFmt_S16SYS,
};

//注意，这是个被动播放器，初始化的时候需要告诉播放器每次调用push进来的声音sample数，而对于视频画面，按照push的速度进行显示，播放器本身不控制帧率
class IVAPlayer
{
public:
	virtual ~IVAPlayer() {};
	//创建播放器
	virtual bool CreatePayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight, 
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall) = 0;
	//重置播放器（释放然后按照指定参数重新创建）
	virtual bool ResetPlayer(int nWndX, int nWndY, int nWndWidth, int nWndHeight,
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall) = 0;
	//基于一个已经存在的窗体创建一个播放器
	virtual bool CreatePayer(void * hWnd, int nWndX, int nWndY, int nWndWidth, int nWndHeight,
		EmVAPlayerColorFmt emColorFmt, int nBufWidth, int nBufHeight,
		bool bStartAudio, EmVAPlayerSampleFmt emSampleFmt, int nAudioSampPerSec, unsigned __int8 nChannelCount, unsigned __int16 nSamplePerCall) = 0;
	//重置播放器（释放然后按照原有参数重新创建）
	virtual bool ResetPlayer() = 0;
	virtual bool MoveWindow(int nX, int nY, int nWndWidth, int nWndHeight) = 0;
	virtual int PushFrame(unsigned char * data, int linesize) = 0;
	virtual int PushAudioSample(unsigned char * data, int nBufSize) = 0;
	virtual int PushYUVFrame(unsigned char **& data, int *& linesize) = 0;
	virtual bool ReleasePlayer() = 0;
};