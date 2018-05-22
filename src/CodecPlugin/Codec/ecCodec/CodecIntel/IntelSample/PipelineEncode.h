//* ////////////////////////////////////////////////////////////////////////////// */
//*
//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//        Copyright (c) 2005-2012 Intel Corporation. All Rights Reserved.
//
//
//*/

#ifndef __PIPELINE_ENCODE_H__
#define __PIPELINE_ENCODE_H__

#define D3D_SURFACES_SUPPORT

#ifdef D3D_SURFACES_SUPPORT
#pragma warning(disable : 4201)
#include <d3d9.h>
#include <dxva2api.h>
#endif

#include "sample_defs.h"
#include "sample_utils.h"
#include "base_allocator.h"
#include "mfxmvc.h"
#include "mfxvideo.h"
#include "mfxvideo++.h"
#include <vector>
#include <list>
#include "SDVADefine.h"

enum
{
    MVC_DISABLED          = 0x0,
    MVC_ENABLED           = 0x1,
    MVC_VIEWOUTPUT        = 0x2,    // 2 output bitstreams
};

struct sInputParams
{
    mfxU16 nTargetUsage;
    mfxU32 CodecId;
    mfxU32 ColorFormat;
    mfxU16 nPicStruct;
    mfxU16 nWidth; // source picture width
    mfxU16 nHeight; // source picture height
    mfxF64 dFrameRate;
    mfxU16 nBitRate;   
    mfxU16 MVC_flags;
	mfxU16 RateControlMethod;

	mfxU16 nCodecProfile;//H264±‡¬Î÷ ¡ø

    mfxU32 numViews; // number of views for Multi-View-Codec

    mfxU16 nDstWidth; // destination picture width, specified if resizing required
    mfxU16 nDstHeight; // destination picture height, specified if resizing required

	mfxU16 nGopPicSize; //gop length should be enough to consume bitrate
	mfxU16 nGopRefDist; //Distance between I- or P- key frames (1 means no B-frames)

    bool bd3dAlloc; // true - frames in video memory (d3d surfaces), false - in system memory
    bool bUseHWLib; // true if application wants to use HW mfx library

    TCHAR strSrcFile[MSDK_MAX_FILENAME_LEN];

    std::vector<TCHAR*> srcFileBuff;
    std::vector<TCHAR*> dstFileBuff;

    mfxU8 nRotationAngle; // if specified, enables rotation plugin in mfx pipeline
    TCHAR strPluginDLLPath[MSDK_MAX_FILENAME_LEN]; // plugin dll path and name

    sInputParams()
    {
        nTargetUsage = 0; CodecId = 0; ColorFormat = 0; nPicStruct = 0;
        nWidth = 0; nHeight = 0; dFrameRate = 0; nBitRate = 0; MVC_flags = 0; numViews = 0; 
        nDstWidth = 0; nDstHeight = 0; bd3dAlloc = 0; bUseHWLib = 0; nRotationAngle = 0;
        strSrcFile[0] = '\0'; strPluginDLLPath[0] = '\0';nCodecProfile=MFX_PROFILE_AVC_BASELINE;
		nGopPicSize=25;nGopRefDist=3;RateControlMethod=MFX_RATECONTROL_CBR;
    };
};

struct sTask
{
    mfxBitstream mfxBS;
    mfxSyncPoint EncSyncP;
    std::list<mfxSyncPoint> DependentVppTasks;
    CSmplBitstreamWriter *pWriter;
	bool m_IsStart;
    char *m_Data;
	SDRFrameInfo *m_pVideoFrameInfo;
    sTask();
    mfxStatus WriteBitstream();
    mfxStatus Reset();
    mfxStatus Init(mfxU32 nBufferSize, CSmplBitstreamWriter *pWriter,char *Data,SDRFrameInfo&pVideoFrameInfo);
    mfxStatus Close();
	mfxStatus PutRawVideoFrame();
};

class CEncTaskPool
{
public:
    CEncTaskPool();
    virtual ~CEncTaskPool();

    virtual mfxStatus Init(MFXVideoSession* pmfxSession, CSmplBitstreamWriter* pWriter, mfxU32 nPoolSize, mfxU32 nBufferSize, CSmplBitstreamWriter *pOtherWriter, char* Data,SDRFrameInfo&pVideoFrameInfo);
    virtual mfxStatus GetFreeTask(sTask **ppTask);
    virtual mfxStatus SynchronizeFirstTask();      
    virtual void Close();

//protected:
    sTask* m_pTasks;
    mfxU32 m_nPoolSize;    
    mfxU32 m_nTaskBufferStart;

    MFXVideoSession* m_pmfxSession;

    virtual mfxU32 GetFreeTaskIndex();  
};


/* This class implements a pipeline with 2 mfx components: vpp (video preprocessing) and encode */
class CEncodingPipeline
{
public:
    CEncodingPipeline();
    virtual ~CEncodingPipeline();

    virtual mfxStatus Init(sInputParams *pParams);
    virtual mfxStatus Run();
    virtual void Close();
    virtual mfxStatus ResetMFXComponents(sInputParams* pParams);
    virtual mfxStatus ResetDevice();

    void SetMultiView();    
    void SetNumView(mfxU32 numViews) { m_nNumView = numViews; }
    virtual void PrintInfo();
	virtual mfxStatus Finish();

	void PutAudio(unsigned char*Audio);
	mfxStatus PutVideo(unsigned char*Video);

//protected:
    std::pair<CSmplBitstreamWriter *,
              CSmplBitstreamWriter *> m_FileWriters;
    CSmplYUVReader m_FileReader;  
    
    CEncTaskPool m_TaskPool; 
    mfxU16 m_nAsyncDepth; // depth of asynchronous pipeline, this number can be tuned to achieve better performance

    MFXVideoSession m_mfxSession;
    MFXVideoENCODE* m_pmfxENC;
    MFXVideoVPP* m_pmfxVPP;

    mfxVideoParam m_mfxEncParams; 
    mfxVideoParam m_mfxVppParams;         
    
    mfxU16 m_MVCflags; // MVC codec is in use
    
    MFXFrameAllocator* m_pMFXAllocator; 
    mfxAllocatorParams* m_pmfxAllocatorParams;
    bool m_bd3dAlloc; // use d3d surfaces
    bool m_bExternalAlloc; // use memory allocator as external for Media SDK

    //mfxFrameSurface1* m_pEncSurfaces; // frames array for encoder input (vpp output)
    mfxFrameSurface1* m_pVppSurfaces; // frames array for vpp input
    mfxFrameAllocResponse m_EncResponse;  // memory allocation response for encoder  
    mfxFrameAllocResponse m_VppResponse;  // memory allocation response for vpp  

    mfxU32 m_nNumView;

    // for disabling VPP algorithms
    mfxExtVPPDoNotUse m_VppDoNotUse; 
    // for MVC encoder and VPP configuration
    mfxExtMVCSeqDesc m_MVCSeqDesc;
    mfxExtCodingOption m_CodingOption;

    // external parameters for each component are stored in a vector
    std::vector<mfxExtBuffer*> m_VppExtParams;
    std::vector<mfxExtBuffer*> m_EncExtParams;

#ifdef D3D_SURFACES_SUPPORT
    IDirect3D9*              m_pd3d;
    IDirect3DDeviceManager9* m_pd3dDeviceManager; 
    IDirect3DDevice9* m_pd3dDevice;
    UINT m_resetToken;
#endif 

    virtual mfxStatus InitMfxEncParams(sInputParams *pParams);
    virtual mfxStatus InitMfxVppParams(sInputParams *pParams);
    
    virtual mfxStatus InitFileWriters(sInputParams *pParams);
    virtual void FreeFileWriters();
    virtual mfxStatus InitFileWriter(CSmplBitstreamWriter **ppWriter, const TCHAR *filename);

    virtual mfxStatus AllocAndInitVppDoNotUse();
    virtual void FreeVppDoNotUse(); 

    virtual mfxStatus AllocAndInitMVCSeqDesc();
    virtual void FreeMVCSeqDesc();   
  
    virtual mfxStatus CreateAllocator();
    virtual void DeleteAllocator();    

    virtual mfxStatus CreateDeviceManager(); 
    virtual void DeleteDeviceManager();

    virtual mfxStatus AllocFrames();
    virtual void DeleteFrames();             
    
    virtual mfxStatus AllocateSufficientBuffer(mfxBitstream* pBS);

    virtual mfxStatus GetFreeTask(sTask **ppTask);
    virtual mfxStatus SynchronizeFirstTask();
public:
	mfxFrameSurface1* m_pEncSurfaces; // frames array for encoder input (vpp output)
	bool    m_IsStop;
	TCHAR*  sImpl; 
	sTask * m_pCurrentTask; // a pointer to the current task
	char m_Data[1920*1080*2];
	char m_YUV420Buffer[1920*1080*2];
	SDRFrameInfo m_pVideoFrameInfo;
private:
	void UYVY_TO_NV12( unsigned char *dst, unsigned char *buffer, int width, int height );
	void UYVY_TO_NV12( unsigned char *dst_y,unsigned char *dst_uv,  unsigned char *buffer, int width, int height );
};

#endif // __PIPELINE_ENCODE_H__ 
typedef std::list<CEncodingPipeline*> CEncodingPipelineList;
