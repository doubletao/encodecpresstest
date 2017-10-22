#ifndef __CODECFACTORY_H_INCLUDED__
#define __CODECFACTORY_H_INCLUDED__

#ifndef LIBCODEC_EXPORTS
#define LIBCODEC_API __declspec(dllimport)
#else
#define LIBCODEC_API __declspec(dllexport)
#endif

#include "VACommonDefine.h"
#include "IVideoEncoder.h"
#include "IVideoDecoder.h"
#include "IAudioEncoder.h"
#include "IAudioDecoder.h"
#include "IFileEncoder.h"
#include "IFileDecoder.h"

class LIBCODEC_API CodecFactory
{
public:
	static CodecFactory& GetInstance();
	virtual ~CodecFactory() = default;

	IVideoEncoder* Create_VideoEncoder(CODEC_MODEL codec = CodecModel_INTEL);
	void Delete_VideoEncoder(IVideoEncoder*& pEncoder);

	IAudioEncoder* Create_AudioEncoder(CODEC_MODEL codec = CodecModel_FFMPEG);
	void Delete_AudioEncoder(IAudioEncoder*& pEncoder);

	IFileEncoder* Create_FileEncoder(CODEC_MODEL codec = CodecModel_FFMPEG);
	void Delete_FileEncoder(IFileEncoder*& pEncoder);

	IVideoDecoder* Create_VideoDecoder(CODEC_MODEL codec = CodecModel_INTEL);
	void Delete_VideoDecoder(IVideoDecoder*& pDecoder);

	IAudioDecoder* Create_AudioDecoder(CODEC_MODEL codec = CodecModel_FFMPEG);
	void Delete_AudioDecoder(IAudioDecoder*& pDecoder);

	IFileDecoder* Create_FileDecoder(CODEC_MODEL codec = CodecModel_FFMPEG);
	void Delete_FileDecoder(IFileDecoder*& pDecoder);
	
private:
	CodecFactory(void);
	CodecFactory(const CodecFactory& src) = delete;
	CodecFactory(CodecFactory &&) = delete;
	CodecFactory& operator=(const CodecFactory& rhs) = delete;
	CodecFactory& operator=(CodecFactory &&) = delete;
};

#endif // __CODECFACTORY_H_INCLUDED__