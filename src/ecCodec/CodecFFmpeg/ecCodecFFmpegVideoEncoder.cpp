#include "ecCodecFFmpegVideoEncoder.h"
#include "FFmpegFormatConverter.h"
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

ecCodecFFmpegVideoEncoder::ecCodecFFmpegVideoEncoder()
	: m_pSourceFrame(nullptr)
	, m_pts(0)
	, m_pCodecCtx(nullptr)
{
}


ecCodecFFmpegVideoEncoder::~ecCodecFFmpegVideoEncoder()
{
	Release();
}

bool ecCodecFFmpegVideoEncoder::InitVideoEncoder(const SDVideoMediaInfo * pDesVideoInfo)
{
	return false;
}

bool ecCodecFFmpegVideoEncoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pVideoBufInfo)
{
	return false;
}

bool ecCodecFFmpegVideoEncoder::PutFrame(const SD_UINT8 * pFrameBuffer, const SDRFrameInfo * pFrameInfo, bool bForceToKeyFrame)
{
	return false;
}

bool ecCodecFFmpegVideoEncoder::SetEndofInput()
{
	return false;
}

bool ecCodecFFmpegVideoEncoder::GetCompressFrame(SD_UINT8 *& pFrameBuffer, SDRFrameInfo * pFrameInfo)
{
	return false;
}

bool ecCodecFFmpegVideoEncoder::Release()
{
	if (m_pSourceFrame)
	{

	}
	if (m_pCodecCtx)
	{

	}
	return true;
}
