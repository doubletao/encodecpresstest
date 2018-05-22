//* ////////////////////////////////////////////////////////////////////////////// */
//*
//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//        Copyright (c) 2005-2013 Intel Corporation. All Rights Reserved.
//
//
//*/
   
#ifndef __PIPELINE_DECODE_H__
#define __PIPELINE_DECODE_H__
#include "DecodeRender.h"
#include "sample_defs.h"
#include <vector>
#include "hw_device.h"
#include <memory>
#include "sample_defs.h"
#include "sample_utils.h"
#include "base_allocator.h"
#include "igfx_s3dcontrol.h"
#include "mfxmvc.h"
#include "mfxjpeg.h"
#include "mfxvideo.h"
#include "mfxvideo++.h"
#include "SDVADefine.h"

enum MemType {
    SYSTEM_MEMORY = 0x00,
    D3D9_MEMORY   = 0x01,
    D3D11_MEMORY  = 0x02,
};

struct sInputParamsDecoding
{
    mfxU32  videoType;
    bool    bOutput; // if renderer is enabled, possibly no need in output file
    MemType memType; 
    bool    bUseHWLib; // true if application wants to use HW mfx library
    bool    bIsMVC; // true if Multi-View Codec is in use
    bool    bRendering; // true if d3d rendering is in use
    bool    bLowLat; // low latency mode
    bool    bCalLat; // latency calculation
    mfxU32  nWallCell;
    mfxU32  nWallW;//number of windows located in each row
    mfxU32  nWallH;//number of windows located in each column
    mfxU32  nWallMonitor;//monitor id, 0,1,.. etc
    mfxU32  nWallFPS;//rendering limited by certain fps
    bool    bWallNoTitle;//whether to show title for each window with fps value
    mfxU32  nWallTimeout; //timeout for -wall option
    mfxU32  numViews; // number of views for Multi-View Codec
    mfxU32  nRotation; // rotation for Motion JPEG Codec

    sInputParamsDecoding()
    {
        MSDK_ZERO_MEMORY(*this);
    }
};

template<>struct mfx_ext_buffer_id<mfxExtMVCSeqDesc>{
    enum {id = MFX_EXTBUFF_MVC_SEQ_DESC};
};

class CDecodingPipeline
{
public:

    CDecodingPipeline();
    virtual ~CDecodingPipeline();

    virtual mfxStatus Init(sInputParamsDecoding *pParams);
    virtual mfxStatus RunDecoding(char *lpFrameBuffer,const SDRFrameInfo *pFrameInfo);
    virtual void Close();
    virtual mfxStatus ResetDecoder(sInputParamsDecoding *pParams);
    virtual mfxStatus ResetDevice();

    void SetMultiView();
    void SetExtBuffersFlag()       { m_bIsExtBuffers = true; }
    void SetRenderingFlag()        { m_bIsRender = true; }
    void SetOutputfileFlag(bool b) { m_bOutput = b; }
	void NV12toUYVY();
	bool GetState();
	void SetState();
protected:
    CSmplYUVWriter          m_FileWriter;
    std::auto_ptr<CSmplBitstreamReader>  m_FileReader;
    mfxU32                  m_nFrameIndex; // index of processed frame
    mfxBitstream            m_mfxBS; // contains encoded data

    MFXVideoSession     m_mfxSession;
    MFXVideoDECODE*     m_pmfxDEC;
    mfxVideoParam       m_mfxVideoParams; 

    std::vector<mfxExtBuffer *> m_ExtBuffers;
    
    MFXFrameAllocator*      m_pMFXAllocator; 
    mfxAllocatorParams*     m_pmfxAllocatorParams;
    MemType                 m_memType;      // memory type of surfaces to use
    bool                    m_bExternalAlloc; // use memory allocator as external for Media SDK
    mfxFrameSurface1*       m_pmfxSurfaces; // frames array
    mfxFrameAllocResponse   m_mfxResponse;  // memory allocation response for decoder  

    bool                    m_bIsMVC; // enables MVC mode (need to support several files as an output)
    bool                    m_bIsExtBuffers; // indicates if external buffers were allocated
    bool                    m_bIsRender; // enables rendering mode
    bool                    m_bOutput; // enables/disables output file
    bool                    m_bIsVideoWall;//indicates special mode: decoding will be done in a loop
    bool                    m_bIsCompleteFrame;
    bool                    m_bPrintLatency;

    mfxU32 m_nTimeout;  //enables timeout for video playback, measured in seconds

    std::vector<mfxF64>     m_vLatency;

    CHWDevice               *m_hwdev;

	mfxSyncPoint            syncp;
	mfxFrameSurface1        *m_pmfxOutSurface;
	bool                    m_State;
public:
	mfxU8                   m_UnCompressFrameBuf[1920*1080*3];
//#if D3D_SURFACES_SUPPORT
    IGFXS3DControl          *m_pS3DControl;
    
    IDirect3DSurface9*       m_pRenderSurface;
    //CDecodeD3DRender         m_d3dRender; 
//#endif
    virtual mfxStatus InitMfxParams(sInputParamsDecoding *pParams);
	mfxStatus InitMfxParamsFromHeader(char *lpFrameBuffer,const SDRFrameInfo *pFrameInfo);
    // function for allocating a specific external buffer
    template <typename Buffer>
    mfxStatus AllocateExtBuffer();
    virtual void DeleteExtBuffers();

    virtual mfxStatus AllocateExtMVCBuffers();
    virtual void    DeallocateExtMVCBuffers();

    virtual void AttachExtParam();

    virtual mfxStatus CreateAllocator();
    virtual mfxStatus CreateHWDevice(); 
    virtual mfxStatus AllocFrames();
    virtual void DeleteFrames();         
    virtual void DeleteAllocator();       
};

#endif // __PIPELINE_DECODE_H__ 