//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 2005-2013 Intel Corporation. All Rights Reserved.
//

#include <tchar.h>
//#include <windows.h>
#include <numeric>
#include <ctime>
#include <algorithm>
#include "PipelineDecode.h"
#include "sysmem_allocator.h"
#include "d3d_allocator.h"
#include "d3d11_allocator.h"
#include "d3d_device.h"
#include "d3d11_device.h"
#pragma comment(lib, "igfx_s3dcontrol.lib")

#pragma warning(disable : 4100)

mfxStatus CDecodingPipeline::InitMfxParams(sInputParamsDecoding *pParams)
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);
    mfxStatus sts = MFX_ERR_NONE;
    mfxU32 &numViews = pParams->numViews;

    // try to find a sequence header in the stream
    // if header is not found this function exits with error (e.g. if device was lost and there's no header in the remaining stream)
    for(;;)
    {
        // trying to find PicStruct information in AVI headers
        if ( m_mfxVideoParams.mfx.CodecId == MFX_CODEC_JPEG )
            MJPEG_AVI_ParsePicStruct(&m_mfxBS);

        // parse bit stream and fill mfx params
        sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);
        if (MFX_ERR_MORE_DATA == sts)
        {
            if (m_mfxBS.MaxLength == m_mfxBS.DataLength)
            {
                sts = ExtendMfxBitstream(&m_mfxBS, m_mfxBS.MaxLength * 2); 
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
            // read a portion of data             
            sts = m_FileReader->ReadNextFrame(&m_mfxBS);
            if (MFX_ERR_MORE_DATA == sts && 
                !(m_mfxBS.DataFlag & MFX_BITSTREAM_EOS))
            {
                m_mfxBS.DataFlag |= MFX_BITSTREAM_EOS;
                sts = MFX_ERR_NONE;
            }
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            continue;
        }
        else
        {
            // Enter MVC mode
            if (m_bIsMVC)
            {
                // Check for attached external parameters - if we have them already,
                // we don't need to attach them again
                if (NULL != m_mfxVideoParams.ExtParam)
                    break;

                // allocate and attach external parameters for MVC decoder
                sts = AllocateExtBuffer<mfxExtMVCSeqDesc>(); 
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

                AttachExtParam();
                sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);

                if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
                {
                    sts = AllocateExtMVCBuffers();
                    SetExtBuffersFlag();

                    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
                    MSDK_CHECK_POINTER(m_mfxVideoParams.ExtParam, MFX_ERR_MEMORY_ALLOC);
                    continue;
                }
            }

            // if input is interlaced JPEG stream
            if ( m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_TFF || m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_BFF)
            {
                m_mfxVideoParams.mfx.FrameInfo.CropH *= 2;
                m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN16(m_mfxVideoParams.mfx.FrameInfo.CropH);
                m_mfxVideoParams.mfx.FrameInfo.PicStruct = m_mfxBS.PicStruct;
            }

            switch(pParams->nRotation)
            {
            case 0:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_0;
                break;
            case 90:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_90;
                break;
            case 180:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_180;
                break;
            case 270:
                m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_270;
                break;
            default:
                return MFX_ERR_UNSUPPORTED;
            }

            break;
        }
    }

    // check DecodeHeader status
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // If MVC mode we need to detect number of views in stream
    if (m_bIsMVC)
    {
        mfxExtMVCSeqDesc* pSequenceBuffer;
        pSequenceBuffer = (mfxExtMVCSeqDesc*) GetExtBuffer(m_mfxVideoParams.ExtParam, m_mfxVideoParams.NumExtParam, MFX_EXTBUFF_MVC_SEQ_DESC);
        MSDK_CHECK_POINTER(pSequenceBuffer, MFX_ERR_INVALID_VIDEO_PARAM);

        mfxU32 i = 0;
        numViews = 0;
        for (i = 0; i < pSequenceBuffer->NumView; ++i)
        {
            /* Some MVC streams can contain different information about
               number of views and view IDs, e.x. numVews = 2 
               and ViewId[0, 1] = 0, 2 instead of ViewId[0, 1] = 0, 1.
               numViews should be equal (max(ViewId[i]) + 1) 
               to prevent crashes during output files writing */
            if (pSequenceBuffer->View[i].ViewId >= numViews)
                numViews = pSequenceBuffer->View[i].ViewId + 1;
        }
    }
    else
    {
        numViews = 1;
    }
 
    // specify memory type 
    m_mfxVideoParams.IOPattern = (mfxU16)(m_memType != SYSTEM_MEMORY ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);

    m_mfxVideoParams.AsyncDepth = 1;

    return MFX_ERR_NONE;
}
mfxStatus CDecodingPipeline::InitMfxParamsFromHeader(char *lpFrameBuffer,const SDRFrameInfo *pFrameInfo)
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);
    mfxStatus sts = MFX_ERR_NONE;

    // try to find a sequence header in the stream
    // if header is not found this function exits with error (e.g. if device was lost and there's no header in the remaining stream)
    //m_mfxBS.Data=lpFrameBuffer;
	memcpy(m_mfxBS.Data,lpFrameBuffer,pFrameInfo->iSize);
	m_mfxBS.DataLength = pFrameInfo->iSize;
	m_mfxBS.DataOffset = pFrameInfo->iSamplesOffset;
	m_mfxBS.DataFlag = MFX_BITSTREAM_COMPLETE_FRAME;
    sts = m_pmfxDEC->DecodeHeader(&m_mfxBS, &m_mfxVideoParams);
    if (sts!=MFX_ERR_NONE)
    {
		return sts;
    }
    // if input is interlaced JPEG stream
    if ( m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_TFF || m_mfxBS.PicStruct == MFX_PICSTRUCT_FIELD_BFF)
    {
        m_mfxVideoParams.mfx.FrameInfo.CropH *= 2;
        m_mfxVideoParams.mfx.FrameInfo.Height = MSDK_ALIGN16(m_mfxVideoParams.mfx.FrameInfo.CropH);
        m_mfxVideoParams.mfx.FrameInfo.PicStruct = m_mfxBS.PicStruct;
    }

    //m_mfxVideoParams.mfx.Rotation = MFX_ROTATION_0;
    

    // specify memory type 
    m_mfxVideoParams.IOPattern = (mfxU16)(m_memType != SYSTEM_MEMORY ? MFX_IOPATTERN_OUT_VIDEO_MEMORY : MFX_IOPATTERN_OUT_SYSTEM_MEMORY);

    m_mfxVideoParams.AsyncDepth = 0;

	//////////////////////////////////////////////////////////////////////////
	sts = AllocFrames();
	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

	// init decoder
	if(MFX_ROTATION_90 == m_mfxVideoParams.mfx.Rotation || MFX_ROTATION_270 == m_mfxVideoParams.mfx.Rotation)
	{
		std::swap(m_mfxVideoParams.mfx.FrameInfo.Height, m_mfxVideoParams.mfx.FrameInfo.Width);
		std::swap(m_mfxVideoParams.mfx.FrameInfo.CropW, m_mfxVideoParams.mfx.FrameInfo.CropH);
		std::swap(m_mfxVideoParams.mfx.FrameInfo.AspectRatioW, m_mfxVideoParams.mfx.FrameInfo.AspectRatioH);
		std::swap(m_mfxVideoParams.mfx.FrameInfo.CropX, m_mfxVideoParams.mfx.FrameInfo.CropY);
	}
	/*m_mfxVideoParams.mfx.FrameInfo.AspectRatioW=12;
	m_mfxVideoParams.mfx.FrameInfo.AspectRatioH=11;
	m_mfxVideoParams.mfx.FrameInfo.CropW=1920;
	m_mfxVideoParams.mfx.FrameInfo.CropH=1080;*/
	
	sts = m_pmfxDEC->Init(&m_mfxVideoParams);

	if (MFX_WRN_PARTIAL_ACCELERATION == sts)
	{
		MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
	}
	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
	
    return MFX_ERR_NONE;
}
mfxStatus CDecodingPipeline::CreateHWDevice()
{
#if D3D_SURFACES_SUPPORT
    mfxStatus sts = MFX_ERR_NONE;

    HWND window = NULL;

    if (!m_bIsRender)
        window = 0;
    //else
        //window = m_d3dRender.GetWindowHandle();

#if MFX_D3D11_SUPPORT
    if (D3D11_MEMORY == m_memType)
        m_hwdev = new CD3D11Device();
    else
#endif // #if MFX_D3D11_SUPPORT
        m_hwdev = new CD3D9Device();

    if (NULL == m_hwdev)
        return MFX_ERR_MEMORY_ALLOC;
    if (m_bIsRender && m_bIsMVC && m_memType == D3D9_MEMORY)
    {
        sts = m_hwdev->SetHandle((mfxHandleType)MFX_HANDLE_GFXS3DCONTROL, m_pS3DControl);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }
    sts = m_hwdev->Init(
        window, 
        m_bIsRender ? (m_bIsMVC ? 2 : 1) : 0,
        GetMSDKAdapterNumber(m_mfxSession));
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    //if (m_bIsRender)
        //m_d3dRender.SetHWDevice(m_hwdev);    
#endif
    return MFX_ERR_NONE;
}

mfxStatus CDecodingPipeline::ResetDevice()
{
    return m_hwdev->Reset();
}

mfxStatus CDecodingPipeline::AllocFrames()
{
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    mfxFrameAllocRequest Request;

    mfxU16 nSurfNum = 0; // number of surfaces for decoder

    MSDK_ZERO_MEMORY(Request);

	sts = m_pmfxDEC->Query(&m_mfxVideoParams, &m_mfxVideoParams);
	MSDK_IGNORE_MFX_STS(sts, MFX_WRN_INCOMPATIBLE_VIDEO_PARAM); 
	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    // calculate number of surfaces required for decoder
    sts = m_pmfxDEC->QueryIOSurf(&m_mfxVideoParams, &Request);
    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    nSurfNum = MSDK_MAX(Request.NumFrameSuggested, 1);

    // prepare allocation request
    Request.NumFrameMin = nSurfNum;
    Request.NumFrameSuggested = nSurfNum;
	//////////////////////////////////////////////////////////////////////////
	memcpy(&(Request.Info), &(m_mfxVideoParams.mfx.FrameInfo), sizeof(mfxFrameInfo));
	Request.Type = MFX_MEMTYPE_EXTERNAL_FRAME | MFX_MEMTYPE_FROM_DECODE; 
	// add info about memory type to request 
	Request.Type |= (m_memType != SYSTEM_MEMORY) ? MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET : MFX_MEMTYPE_SYSTEM_MEMORY; 
	//////////////////////////////////////////////////////////////////////////

    // alloc frames for decoder
    sts = m_pMFXAllocator->Alloc(m_pMFXAllocator->pthis, &Request, &m_mfxResponse);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // prepare mfxFrameSurface1 array for decoder
    nSurfNum = m_mfxResponse.NumFrameActual;
    m_pmfxSurfaces = new mfxFrameSurface1 [nSurfNum];
    MSDK_CHECK_POINTER(m_pmfxSurfaces, MFX_ERR_MEMORY_ALLOC);       

    for (int i = 0; i < nSurfNum; i++)
    {
        MSDK_ZERO_MEMORY(m_pmfxSurfaces[i]);
		memset(&(m_pmfxSurfaces[i]), 0, sizeof(mfxFrameSurface1));
		memcpy(&(m_pmfxSurfaces[i].Info), &(m_mfxVideoParams.mfx.FrameInfo), sizeof(mfxFrameInfo));
        if (m_bExternalAlloc)
        {
            m_pmfxSurfaces[i].Data.MemId = m_mfxResponse.mids[i];    
        }
        else
        {
            sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, m_mfxResponse.mids[i], &(m_pmfxSurfaces[i].Data));
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        }
    }  

    return MFX_ERR_NONE;
}

mfxStatus CDecodingPipeline::CreateAllocator()
{   
    mfxStatus sts = MFX_ERR_NONE;
 
    if (m_memType != SYSTEM_MEMORY)
    {
#if D3D_SURFACES_SUPPORT  
        sts = CreateHWDevice();
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // provide device manager to MediaSDK
        mfxHDL hdl = NULL;
        mfxHandleType hdl_t = 
#if MFX_D3D11_SUPPORT
            D3D11_MEMORY == m_memType ? MFX_HANDLE_D3D11_DEVICE : 
#endif // #if MFX_D3D11_SUPPORT
            MFX_HANDLE_D3D9_DEVICE_MANAGER;

        sts = m_hwdev->GetHandle(hdl_t, &hdl);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        sts = m_mfxSession.SetHandle(hdl_t, hdl);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // create D3D allocator
#if MFX_D3D11_SUPPORT
        if (D3D11_MEMORY == m_memType)
        {
            m_pMFXAllocator = new D3D11FrameAllocator;
            MSDK_CHECK_POINTER(m_pMFXAllocator, MFX_ERR_MEMORY_ALLOC);

            D3D11AllocatorParams *pd3dAllocParams = new D3D11AllocatorParams;
            MSDK_CHECK_POINTER(pd3dAllocParams, MFX_ERR_MEMORY_ALLOC);
            pd3dAllocParams->pDevice = reinterpret_cast<ID3D11Device *>(hdl);

            m_pmfxAllocatorParams = pd3dAllocParams;
        }
        else
#endif // #if MFX_D3D11_SUPPORT
        {
            m_pMFXAllocator = new D3DFrameAllocator;
            MSDK_CHECK_POINTER(m_pMFXAllocator, MFX_ERR_MEMORY_ALLOC);

            D3DAllocatorParams *pd3dAllocParams = new D3DAllocatorParams;        
            MSDK_CHECK_POINTER(pd3dAllocParams, MFX_ERR_MEMORY_ALLOC);
            pd3dAllocParams->pManager = reinterpret_cast<IDirect3DDeviceManager9 *>(hdl);

            m_pmfxAllocatorParams = pd3dAllocParams;
        }

        /* In case of video memory we must provide MediaSDK with external allocator 
        thus we demonstrate "external allocator" usage model.
        Call SetAllocator to pass allocator to mediasdk */
        sts = m_mfxSession.SetFrameAllocator(m_pMFXAllocator);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        m_bExternalAlloc = true;
#endif

    }
    else
    {
        // create system memory allocator       
        m_pMFXAllocator = new SysMemFrameAllocator;         
        MSDK_CHECK_POINTER(m_pMFXAllocator, MFX_ERR_MEMORY_ALLOC);

        /* In case of system memory we demonstrate "no external allocator" usage model.  
        We don't call SetAllocator, MediaSDK uses internal allocator. 
        We use system memory allocator simply as a memory manager for application*/           
    }

    // initialize memory allocator
    sts = m_pMFXAllocator->Init(m_pmfxAllocatorParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return MFX_ERR_NONE;
}

void CDecodingPipeline::DeleteFrames()
{
    // delete surfaces array
    MSDK_SAFE_DELETE_ARRAY(m_pmfxSurfaces);    

    // delete frames
    if (m_pMFXAllocator)
    {
        m_pMFXAllocator->Free(m_pMFXAllocator->pthis, &m_mfxResponse);
    }

    return;
}

void CDecodingPipeline::DeleteAllocator()
{
    // delete allocator
    MSDK_SAFE_DELETE(m_pMFXAllocator);   
    MSDK_SAFE_DELETE(m_pmfxAllocatorParams);
    MSDK_SAFE_DELETE(m_hwdev);
}

CDecodingPipeline::CDecodingPipeline()
{
    m_nFrameIndex = 0;
    m_pmfxDEC = NULL;
    m_pMFXAllocator = NULL;
    m_pmfxAllocatorParams = NULL;
    m_memType = SYSTEM_MEMORY;
    m_bExternalAlloc = false;
    m_pmfxSurfaces = NULL; 
    m_bIsMVC = false;
    m_bIsExtBuffers = false;
    m_bIsRender = false;
    m_bOutput = true;
    m_bIsVideoWall = false;
    m_nTimeout = 0;
    m_bIsCompleteFrame = false;
    m_bPrintLatency = false;
    m_vLatency.reserve(1000); // reserve some space to reduce dynamic reallocation impact on pipeline execution
#if D3D_SURFACES_SUPPORT
    m_pS3DControl = NULL;
#endif


    m_hwdev = NULL;
	m_pmfxOutSurface = NULL;

    MSDK_ZERO_MEMORY(m_mfxVideoParams);
    MSDK_ZERO_MEMORY(m_mfxResponse);
    MSDK_ZERO_MEMORY(m_mfxBS);
	m_State = false;
}

CDecodingPipeline::~CDecodingPipeline()
{
    Close();
	DeleteFrames();
}

void CDecodingPipeline::SetMultiView()
{
    m_FileWriter.SetMultiView();
    m_bIsMVC = true;
}

#if D3D_SURFACES_SUPPORT
bool operator < (const IGFX_DISPLAY_MODE &l, const IGFX_DISPLAY_MODE& r)
{
    if (r.ulResWidth >= 0xFFFF || r.ulResHeight >= 0xFFFF || r.ulRefreshRate >= 0xFFFF)
        return false;

         if (l.ulResWidth < r.ulResWidth) return true;
    else if (l.ulResHeight < r.ulResHeight) return true;
    else if (l.ulRefreshRate < r.ulRefreshRate) return true;    
        
    return false;
}
#endif

mfxStatus CDecodingPipeline::Init(sInputParamsDecoding *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    // prepare input stream file reader        
    // create reader that supports completeframe mode for latency oriented scenarios
    if (pParams->bLowLat || pParams->bCalLat)
    {
        switch (pParams->videoType)
        {
        case MFX_CODEC_AVC:
            m_FileReader.reset(new CH264FrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        case MFX_CODEC_JPEG:
            //m_FileReader.reset(new CJPEGFrameReader());
            m_bIsCompleteFrame = true;
            m_bPrintLatency = pParams->bCalLat;
            break;
        default:
            return MFX_ERR_UNSUPPORTED; // latency mode is supported only for H.264 and JPEG codecs
        }
        
    }    
    else
    {
        //m_FileReader.reset(new CSmplBitstreamReader());
    }

	//sts = m_FileReader->Init(pParams->strSrcFile);
	//const msdk_char *strSrcFile=_T("D:\\11.avi");
	//sts = m_FileReader->Init(strSrcFile);
	//MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);     
    
    // API version
	/*APIChangeFeatures features = {};
	features.MVCDecode = pParams->bIsMVC;
	features.LowLatency = pParams->bLowLat;
	features.JpegDecode = (pParams->videoType == MFX_CODEC_JPEG);
	mfxVersion version = getMinimalRequiredVersion(features);*/
	mfxVersion version ={0,1};
	mfxIMPL implCheck = MFX_IMPL_AUTO;	
    // Init session
    if (pParams->bUseHWLib)
    {             
        // try searching on all display adapters
        mfxIMPL impl = MFX_IMPL_HARDWARE_ANY;
                
        // if d3d11 surfaces are used ask the library to run acceleration through D3D11
        // feature may be unsupported due to OS or MSDK API version
        if (D3D11_MEMORY == pParams->memType) 
            impl |= MFX_IMPL_VIA_D3D11;

        sts = m_mfxSession.Init(impl, &version);

        // MSDK API version may not support multiple adapters - then try initialize on the default
        if (MFX_ERR_NONE != sts)
            sts = m_mfxSession.Init(impl & !MFX_IMPL_HARDWARE_ANY | MFX_IMPL_HARDWARE, &version);        
    }
    else
        sts = m_mfxSession.Init(MFX_IMPL_SOFTWARE, &version);

	m_mfxSession.QueryIMPL(&implCheck);
	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // create decoder
    m_pmfxDEC = new MFXVideoDECODE(m_mfxSession);
    MSDK_CHECK_POINTER(m_pmfxDEC, MFX_ERR_MEMORY_ALLOC);    

    // set video type in parameters
    m_mfxVideoParams.mfx.CodecId = pParams->videoType;
    // set memory type
    m_memType = pParams->memType;

    // Initialize rendering window
    if (pParams->bRendering)
    {
        if (m_bIsMVC && m_memType == D3D9_MEMORY)
        {
#if D3D_SURFACES_SUPPORT

            m_pS3DControl = CreateIGFXS3DControl();
            MSDK_CHECK_POINTER(m_pS3DControl, MFX_ERR_DEVICE_FAILED);

            // check if s3d supported and get a list of supported display modes
            IGFX_S3DCAPS caps;
            MSDK_ZERO_MEMORY(caps);
            HRESULT hr = m_pS3DControl->GetS3DCaps(&caps);
            if (FAILED(hr) || 0 >= caps.ulNumEntries)
            {
                MSDK_SAFE_DELETE(m_pS3DControl);
                return MFX_ERR_DEVICE_FAILED;
            } 
            
            // switch to 3D mode
            ULONG max = 0;
            MSDK_CHECK_POINTER(caps.S3DSupportedModes, MFX_ERR_NOT_INITIALIZED);
            for (ULONG i = 0; i < caps.ulNumEntries; i++)
            {
                if (caps.S3DSupportedModes[max] < caps.S3DSupportedModes[i]) 
                    max = i;
            }
            
            if (0 == pParams->nWallCell)
            {
                hr = m_pS3DControl->SwitchTo3D(&caps.S3DSupportedModes[max]);
                if (FAILED(hr))
                {
                    MSDK_SAFE_DELETE(m_pS3DControl);
                    return MFX_ERR_DEVICE_FAILED;
                }
            }
#endif
        }
#if D3D_SURFACES_SUPPORT
        sWindowParams windowParams;

        windowParams.lpWindowName = pParams->bWallNoTitle ? NULL : MSDK_STRING("sample_decode");
        windowParams.nx           = pParams->nWallW;
        windowParams.ny           = pParams->nWallH;
        windowParams.nWidth       = CW_USEDEFAULT;
        windowParams.nHeight      = CW_USEDEFAULT;        
        windowParams.ncell        = pParams->nWallCell;
        windowParams.nAdapter     = pParams->nWallMonitor;
        windowParams.nMaxFPS      = pParams->nWallFPS;

        windowParams.lpClassName  = MSDK_STRING("Render Window Class");
        windowParams.dwStyle      = WS_OVERLAPPEDWINDOW;
        windowParams.hWndParent   = NULL;
        windowParams.hMenu        = NULL;
        windowParams.hInstance    = GetModuleHandle(NULL);
        windowParams.lpParam      = NULL;
        windowParams.bFullScreen  = FALSE;

        //m_d3dRender.Init(windowParams);
        
        SetRenderingFlag();
        //setting videowall flag
        m_bIsVideoWall = 0 != windowParams.nx;
        //setting timeout value
        if (m_bIsVideoWall && (pParams->nWallTimeout>0)) m_nTimeout = pParams->nWallTimeout;
#endif
    }

    // prepare bit stream
    sts = InitMfxBitstream(&m_mfxBS, 1024*1024*30);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);    

    // create device and allocator. SetHandle must be called after session Init and before any other MSDK calls, 
    // otherwise an own device will be created by MSDK
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // Populate parameters. Involves DecodeHeader call
    return MFX_ERR_NONE;
}

// function for allocating a specific external buffer
template <typename Buffer>
mfxStatus CDecodingPipeline::AllocateExtBuffer()
{
    std::auto_ptr<Buffer> pExtBuffer (new Buffer()); 
    if (!pExtBuffer.get())
        return MFX_ERR_MEMORY_ALLOC;

    init_ext_buffer(*pExtBuffer);

    m_ExtBuffers.push_back(reinterpret_cast<mfxExtBuffer*>(pExtBuffer.release()));

    return MFX_ERR_NONE;
}

void CDecodingPipeline::AttachExtParam()
{
    m_mfxVideoParams.ExtParam = reinterpret_cast<mfxExtBuffer**>(&m_ExtBuffers[0]);
    m_mfxVideoParams.NumExtParam = static_cast<mfxU16>(m_ExtBuffers.size());
}

void CDecodingPipeline::DeleteExtBuffers()
{
    for (std::vector<mfxExtBuffer *>::iterator it = m_ExtBuffers.begin(); it != m_ExtBuffers.end(); ++it)
        delete *it;
    m_ExtBuffers.clear();
}

mfxStatus CDecodingPipeline::AllocateExtMVCBuffers()
{
    mfxU32 i;

    mfxExtMVCSeqDesc* pExtMVCBuffer = (mfxExtMVCSeqDesc*) m_mfxVideoParams.ExtParam[0];
    MSDK_CHECK_POINTER(pExtMVCBuffer, MFX_ERR_MEMORY_ALLOC);

    pExtMVCBuffer->View = new mfxMVCViewDependency[pExtMVCBuffer->NumView];
    MSDK_CHECK_POINTER(pExtMVCBuffer->View, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < pExtMVCBuffer->NumView; ++i)
    {
        MSDK_ZERO_MEMORY(pExtMVCBuffer->View[i]);
    }
    pExtMVCBuffer->NumViewAlloc = pExtMVCBuffer->NumView;

    pExtMVCBuffer->ViewId = new mfxU16[pExtMVCBuffer->NumViewId];
    MSDK_CHECK_POINTER(pExtMVCBuffer->ViewId, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < pExtMVCBuffer->NumViewId; ++i)
    {
        MSDK_ZERO_MEMORY(pExtMVCBuffer->ViewId[i]);
    }
    pExtMVCBuffer->NumViewIdAlloc = pExtMVCBuffer->NumViewId;

    pExtMVCBuffer->OP = new mfxMVCOperationPoint[pExtMVCBuffer->NumOP];
    MSDK_CHECK_POINTER(pExtMVCBuffer->OP, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < pExtMVCBuffer->NumOP; ++i)
    {
        MSDK_ZERO_MEMORY(pExtMVCBuffer->OP[i]);
    }
    pExtMVCBuffer->NumOPAlloc = pExtMVCBuffer->NumOP;

    return MFX_ERR_NONE;
}

void CDecodingPipeline::DeallocateExtMVCBuffers()
{
    mfxExtMVCSeqDesc* pExtMVCBuffer = (mfxExtMVCSeqDesc*) m_mfxVideoParams.ExtParam[0];
    if (pExtMVCBuffer != NULL)
    {
        MSDK_SAFE_DELETE_ARRAY(pExtMVCBuffer->View);
        MSDK_SAFE_DELETE_ARRAY(pExtMVCBuffer->ViewId);
        MSDK_SAFE_DELETE_ARRAY(pExtMVCBuffer->OP);
    }

    MSDK_SAFE_DELETE(m_mfxVideoParams.ExtParam[0]);

    m_bIsExtBuffers = false;
}

void CDecodingPipeline::Close()
{
#if D3D_SURFACES_SUPPORT
    if (NULL != m_pS3DControl)
    {
        m_pS3DControl->SwitchTo2D(NULL);
        MSDK_SAFE_DELETE(m_pS3DControl);
    }
#endif
    WipeMfxBitstream(&m_mfxBS);
    MSDK_SAFE_DELETE(m_pmfxDEC);   

    DeleteFrames();
    
    // allocator if used as external for MediaSDK must be deleted after decoder
    DeleteAllocator();

    if (m_bIsExtBuffers)
    {
        DeallocateExtMVCBuffers();
        DeleteExtBuffers();
    }
#if D3D_SURFACES_SUPPORT
    if (m_pRenderSurface != NULL)
        m_pRenderSurface = NULL;
#endif
    m_mfxSession.Close();
    //m_FileWriter.Close();
    //if (m_FileReader.get())
    //    m_FileReader->Close();

    return;
}

mfxStatus CDecodingPipeline::ResetDecoder(sInputParamsDecoding *pParams)
{
    mfxStatus sts = MFX_ERR_NONE;    

    // close decoder
    sts = m_pmfxDEC->Close();
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_NOT_INITIALIZED);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // free allocated frames
    DeleteFrames();
    
    // initialize parameters with values from parsed header 
    sts = InitMfxParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // in case of HW accelerated decode frames must be allocated prior to decoder initialization
    sts = AllocFrames();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // init decoder
    sts = m_pmfxDEC->Init(&m_mfxVideoParams);

    if (MFX_WRN_PARTIAL_ACCELERATION == sts)
    {
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    }
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return MFX_ERR_NONE;
}

mfxStatus CDecodingPipeline::RunDecoding(char *lpFrameBuffer,const SDRFrameInfo *pFrameInfo)
{  
	bool m_bIsCompleteFrame = false;
	CTimeInterval<>     decodeTimer(m_bIsCompleteFrame);
    mfxStatus           sts = MFX_ERR_NONE;
    mfxU16              nIndex = 0; // index of free surface   
	memmove(m_mfxBS.Data, m_mfxBS.Data + m_mfxBS.DataOffset,m_mfxBS.DataLength);
	m_mfxBS.DataOffset=0;
	memcpy(m_mfxBS.Data + m_mfxBS.DataLength,lpFrameBuffer,pFrameInfo->iSize);
	m_mfxBS.DataLength = m_mfxBS.DataLength + pFrameInfo->iSize;
	//memcpy(m_mfxBS.Data,lpFrameBuffer,pFrameInfo->iSize);
	//m_mfxBS.DataLength=pFrameInfo->iSize;
	
	while(1)
	{
		//////////////////////////////////////////////////////////////////////////
		if (MFX_WRN_DEVICE_BUSY == sts)
		{
			MSDK_SLEEP(1); // just wait and then repeat the same call to DecodeFrameAsync
			
		}
		else if (MFX_ERR_MORE_DATA == sts )
		{
			return MFX_ERR_NONE;
		}
		//////////////////////////////////////////////////////////////////////////
		if (MFX_ERR_MORE_SURFACE == sts || MFX_ERR_NONE == sts)
		{
			nIndex = GetFreeSurfaceIndex(m_pmfxSurfaces, m_mfxResponse.NumFrameActual); // find new working surface 
			if (MSDK_INVALID_SURF_IDX == nIndex)
			{
				return MFX_ERR_MEMORY_ALLOC;            
			}
		}
		sts = m_pmfxDEC->DecodeFrameAsync(&m_mfxBS, &(m_pmfxSurfaces[nIndex]), &m_pmfxOutSurface, &syncp);

		//m_mfxBS.DataOffset+=pFrameInfo->iSize;
		if (MFX_ERR_NONE < sts && syncp)
		{
			sts = MFX_ERR_NONE;
		}

		if (MFX_ERR_NONE == sts)
		{
			sts = m_mfxSession.SyncOperation(syncp, MSDK_DEC_WAIT_INTERVAL);                  
		}          

		if (MFX_ERR_NONE == sts)
		{    
			sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, m_pmfxOutSurface->Data.MemId, &(m_pmfxOutSurface->Data));
			NV12toUYVY();
			m_State = true;
			sts = m_pMFXAllocator->Unlock(m_pMFXAllocator->pthis, m_pmfxOutSurface->Data.MemId, &(m_pmfxOutSurface->Data));
		} 
	}
	
}
void CDecodingPipeline::NV12toUYVY()
{
	int height05 = m_pmfxOutSurface->Info.CropH/2;
	int width    = m_pmfxOutSurface->Info.CropW;
	int width2   = m_pmfxOutSurface->Info.CropW*2;
	int width05    = m_pmfxOutSurface->Info.CropW/2;
	mfxU8 *UnCompressFrameBufA =(mfxU8*)m_UnCompressFrameBuf;
	mfxU8 *UnCompressFrameBufB =UnCompressFrameBufA+width2;
	mfxU8 * pY=m_pmfxOutSurface->Data.Y;
	mfxU8 * pU=m_pmfxOutSurface->Data.U;
	mfxU8 * pV=m_pmfxOutSurface->Data.V;
	for(int j = 1; j <= height05; j++)
	{
		if (j>1)
		{
			UnCompressFrameBufA+=width2;
			UnCompressFrameBufB+=width2;
			pY+=width;
		}

		for(int i = 1; i <= width05;i++ )
		{
			if (i*j>1)
			{			
				pU+=2;
				pV+=2;
				pY+=2;
				UnCompressFrameBufA+=4;
				UnCompressFrameBufB+=4;
			}
			*(UnCompressFrameBufA)   = *(pU);
			*(UnCompressFrameBufA+1) = *(pY);
			*(UnCompressFrameBufA+2) = *(pV);
			*(UnCompressFrameBufA+3) = *(pY+1);

			*(UnCompressFrameBufB)   = *(pU);
			*(UnCompressFrameBufB+1) = *(pY+width);
			*(UnCompressFrameBufB+2) = *(pV);
			*(UnCompressFrameBufB+3) = *(pY+width+1);			
		}
		
	}
}
bool CDecodingPipeline::GetState()
{
	return m_State;
}
void CDecodingPipeline::SetState()
{
	m_State = false;
}


