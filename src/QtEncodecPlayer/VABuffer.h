#pragma once

class VABuffer
{
protected:
	unsigned char * m_pVideoBuf;
	size_t m_nVideoSize;
	unsigned char * m_pAudioBuf;
	size_t m_nAudioSampleCount;
public:
	VABuffer();
	~VABuffer();
	void Reset(size_t nVideoSize, size_t nAudioSampleCount);
	void Clear();
	void Copy(const VABuffer & va);
	void CopyVideo(const unsigned char * pVideoBuf);
	void CopyAudio(const unsigned char * pAudioBuf);
	size_t GetVideoBufSize();
	size_t GetAudioSampleCount();
	unsigned char * GetVideoBuf();
	unsigned char * GetAudioBuf();
};

