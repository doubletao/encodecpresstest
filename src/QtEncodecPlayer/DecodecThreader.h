#pragma once
#include "IecCodecFactory.h"
#include <atomic>
#include "StdEvent.h"

//因为buf本身就是外部给定的，所以这里仅仅是通知一下，告诉外部本帧解完了，可以去拿了
typedef bool (__stdcall * OneFrameDecodecedFunc)(unsigned long long nCurFrame, void * pData, size_t nVideoBufSize, size_t nAudioSampleCount);
typedef bool(__stdcall * InfoMsgFunc)(std::string strErr, void * pData);

class DecodecThreader
{
public:
	DecodecThreader();
	~DecodecThreader();
	void Release();
protected:
	OneFrameDecodecedFunc m_pNotifyDecFunc;//解码完成回调
	void * m_pDecCallbackData;//存一个回调数据指针
	InfoMsgFunc m_pInfoMsgFunc;//非必须，错误，警告等信息回调（注意，这个回调一定不要阻塞）
	void * m_pInfoMsgCallbackData;//存一个回调数据指针
	std::atomic_ullong m_nCurFrame;//当前解码帧
	unsigned long long m_nLastFrame;//当前解码帧
	uint32_t m_nLastAudioPos;//当前解码音频sample位置
	unsigned int m_nSamplePerFrame;
	std::atomic_bool m_bLockPts;//强制pts对齐
	std::atomic_bool m_bLoop;//循环播放
	std::atomic_bool m_bPause;//暂停标记
	std::string m_cstrSourcePath;//源路径
	SDStreamMediaInfo m_srcMediaInfo;//源媒体信息
	SDStreamMediaInfoEx m_srcMediaInfoEx;//源媒体信息
	SDVideoFrameImageBufInfo m_desImageBufInfo;//目标画面信息
	SDAudioMediaInfo m_desAudioSamplesBufInfo;//目标音频信息
	unsigned char * m_pVideoBuf;
	size_t m_nVideoBufSize;
	unsigned char * m_pAudioBuf;
	size_t m_nAudioBufSize;
protected:
	IecCodecFactory * m_ecFactory;
	IecCodecProtocolDecoder * m_ecDecoder;
	CStdEvent m_evtQuit;
	std::thread * m_pDecodecThread;
	static void ThreadDecodec(DecodecThreader * pThis);
	bool DoDecodec();
	bool DecodecCurFrame();
protected:
	void EmitInfoMsg(std::string strInfo);
public:
	//为尽可能减少内存拷贝，内部不创建内存空间，完全由外部给定，内部线程只会往指定buf中写，然后通过回调通知外部去拿
	//如果运行过程中需要更换buf地址，可以在回调中更换
	bool SetVideoBuf(unsigned char * pVideoBuf, size_t nVideoBufSize);
	bool SetAudioBuf(unsigned char * pAudioBuf, size_t nAudioBufSize);
	bool SetDecCallbackFunc(OneFrameDecodecedFunc pFunc, void * pData);//运行过程中修改回调会被忽略
	bool SetInfoMsgCallbackFunc(InfoMsgFunc pFunc, void * pData);

	//初始化输入输出(内部会调用stop)
	//运行过程中修改InOut参数会被忽略，执行失败，重新加载文件前必须先停止
	bool SetInputSource(const std::string & cstrFilePath, SDStreamMediaInfo & mediaInfo);//路径给过来，参数传出去
	bool SetOutputParam(const SDVideoFrameImageBufInfo & imageBufInfo, const SDAudioMediaInfo & audioSamplesBufInfo);//需要的视音频参数给过来

	//控制
	bool SetPlayPause(bool bPlay);//播放或者暂停
	bool SetStop();
	//下边几个bPause是seek动作之后，是否自动暂停，如果是，则强制暂停，如果否，则保持原状（继续播放或者继续暂停）
	bool SetFirstFrame(bool bPause = false);
	bool SetPreFrame(bool bPause = false);
	bool SetNextFrame(bool bPause = false);
	bool SetLastFrame(bool bPause = false);
	bool SetSeekPos(unsigned long long m_nCurFrame, bool bPause = false);
	bool SetLockVAPts(bool bLock);//是否需要强制pts对齐(使用这个接口一定要保证视音频都有)
	bool SetLoop(bool bLoop);

	//查询
	unsigned long long GetCurSeekPos();
	bool IsPlaying();//注意，暂停也算playing
	bool IsStoped();//play线程整个停止了才叫stop
	bool IsPause();//play线程启动中，但处于暂停状态
	bool IsLockVAPts();
	bool IsLoop();
	std::string GetInputSourcePath();
	const SDStreamMediaInfo & GetSrcMediaInfo();
	const SDVideoFrameImageBufInfo & GetDesImageBufInfo();
	const SDAudioMediaInfo & GetDesAudioInfo();
	size_t GetVideoBufSize();
	size_t GetAudioBufSize();
	unsigned int GetSamplePerFrame();
};

