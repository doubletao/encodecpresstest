#ifndef __FFMPEGFILEENCODER_H_INCLUDED__
#define __FFMPEGFILEENCODER_H_INCLUDED__

#include <memory>
#include "VACommonDefine.h"
#include "IFileEncoder.h"

struct AVFormatContext;
struct AVStream;
struct AVCodec;
class FFmpegVideoEncoder;
class FFmpegAudioEncoder;

class FFmpegFileEncoder : public IFileEncoder
{
public:
	FFmpegFileEncoder();
	~FFmpegFileEncoder();

	bool SetSinkFile(const SStreamMediaInfo *pStreamMediaInfo, const char* pFileName);
	bool GetMediaInfo(SStreamMediaInfo *pStreamMediaInfo) { return false; }
	
	bool SetVideoFrameBufInfo(const SVideoFrameImageBufInfo *pVideoInfo, const SResamplerPara *pResamplerInfo) override;
	bool GetVideoFrameBufInfo(SVideoFrameImageBufInfo *pVideoInfo, SResamplerPara *pResamplerInfo) override { return false; }
	bool SetAudioSamplesBufInfo(const SAudioSamplesBufInfo *pAudioInfo) override;
	bool GetAudioSamplesBufInfo(SAudioSamplesBufInfo *pAudioInfo) override { return false; }
	
	bool IsCanWriteVideoFrame() { return true; }
	bool IsCanWriteAudioFrame() { return true; }

	bool PutVideoBuffer(const SW_UINT8* pFrameBuf, bool bForceToKeyFrame = false, const SRFrameInfo *pFrameInfo = NULL);
	bool PutVideoFrame(const SW_UINT8* pFrameBuf, const SRFrameInfo *pFrameInfo);
	bool PutAudioSamples(const SW_UINT8* pSamplesBuf, SW_UINT32 dwSampleNum);
	bool PutAudioFrame(const SW_UINT8* pFrameBuf, const SRFrameInfo *pFrameInfo);

	bool Release();

private:
	bool CreateVideoStream(const SVideoMediaInfo& videoInfo);
	bool CreateAudioStream(const SAudioMediaInfo& audioInfo);

private:
	AVFormatContext* m_pFormatCtx;
	AVStream* m_pVideoStream;
	AVStream* m_pAudioStream;
	bool	  m_bWritable;
	
	std::unique_ptr<FFmpegVideoEncoder> m_pVideoEncoder;
	std::unique_ptr<FFmpegAudioEncoder> m_pAudioEncoder;
};

#endif // __FFMPEGFILEENCODER_H_INCLUDED__