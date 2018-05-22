//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 2005-2012 Intel Corporation. All Rights Reserved.
//

#include <tchar.h>
//#include <windows.h>
#include <afx.h> 
#include "PipelineEncode.h"
#include "sysmem_allocator.h"

#ifdef D3D_SURFACES_SUPPORT
#include "d3d_allocator.h"
#endif

#pragma comment(lib, "igfx_s3dcontrol.lib")

CEncTaskPool::CEncTaskPool()
{
    m_pTasks  = NULL;
    m_pmfxSession       = NULL;
    m_nTaskBufferStart  = 0;
    m_nPoolSize         = 0;
}
CEncTaskPool::~CEncTaskPool()
{
    Close();
}

mfxStatus CEncTaskPool::Init(MFXVideoSession* pmfxSession, CSmplBitstreamWriter* pWriter, mfxU32 nPoolSize, mfxU32 nBufferSize, CSmplBitstreamWriter *pOtherWriter, char* Data,SDRFrameInfo &pVideoFrameInfo)
{
    MSDK_CHECK_POINTER(pmfxSession, MFX_ERR_NULL_PTR);
    /*MSDK_CHECK_POINTER(pWriter, MFX_ERR_NULL_PTR);*/

    MSDK_CHECK_ERROR(nPoolSize, 0, MFX_ERR_UNDEFINED_BEHAVIOR);
    MSDK_CHECK_ERROR(nBufferSize, 0, MFX_ERR_UNDEFINED_BEHAVIOR);

    // nPoolSize must be even in case of 2 output bitstreams
  /*  if (pOtherWriter && (0 != nPoolSize % 2))
        return MFX_ERR_UNDEFINED_BEHAVIOR;*/

    m_pmfxSession = pmfxSession;
    m_nPoolSize = nPoolSize;

    m_pTasks = new sTask [m_nPoolSize];  
    MSDK_CHECK_POINTER(m_pTasks, MFX_ERR_MEMORY_ALLOC);

    mfxStatus sts = MFX_ERR_NONE;
    
    if (pOtherWriter) // 2 bitstreams on output
    {
        for (mfxU32 i = 0; i < m_nPoolSize; i+=2)
        {
            sts = m_pTasks[i+0].Init(nBufferSize, pWriter,Data,pVideoFrameInfo);
            sts = m_pTasks[i+1].Init(nBufferSize, pOtherWriter,Data,pVideoFrameInfo);
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        }        
    }
    else
    {
        for (mfxU32 i = 0; i < m_nPoolSize; i++)
        {  
            sts = m_pTasks[i].Init(nBufferSize, pWriter,Data,pVideoFrameInfo);
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);        
        }
    }

    return MFX_ERR_NONE;
}

mfxStatus CEncTaskPool::SynchronizeFirstTask()
{    
    MSDK_CHECK_POINTER(m_pTasks, MFX_ERR_NOT_INITIALIZED);
    MSDK_CHECK_POINTER(m_pmfxSession, MFX_ERR_NOT_INITIALIZED);

    mfxStatus sts  = MFX_ERR_NONE;

    // non-null sync point indicates that task is in execution
    if (NULL != m_pTasks[m_nTaskBufferStart].EncSyncP)
    { 
        sts = m_pmfxSession->SyncOperation(m_pTasks[m_nTaskBufferStart].EncSyncP, MSDK_WAIT_INTERVAL);        

        if (MFX_ERR_NONE == sts)
        {
            sts = m_pTasks[m_nTaskBufferStart].WriteBitstream();
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            sts = m_pTasks[m_nTaskBufferStart].Reset();
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

            // move task buffer start to the next executing task  
            // the first transform frame to the right with non zero sync point
            for (mfxU32 i = 0; i < m_nPoolSize; i++)
            {
                m_nTaskBufferStart = (m_nTaskBufferStart + 1) % m_nPoolSize;
                if (NULL != m_pTasks[m_nTaskBufferStart].EncSyncP)
                {
                    break;
                }
            }             
        } 
        else if (MFX_ERR_ABORTED == sts) 
        {
            while (!m_pTasks[m_nTaskBufferStart].DependentVppTasks.empty())
            {
                // find out if the error occurred in a VPP task to perform recovery procedure if applicable 
                sts = m_pmfxSession->SyncOperation(*m_pTasks[m_nTaskBufferStart].DependentVppTasks.begin(), 0);                

                if (MFX_ERR_NONE == sts)
                {
                    m_pTasks[m_nTaskBufferStart].DependentVppTasks.pop_front();
                    sts = MFX_ERR_ABORTED; // save the status of the encode task
                    continue; // go to next vpp task
                }
                else
                {
                    break;
                }
            }            
        }

        return sts;
    } 
    else
    {
        return MFX_ERR_NOT_FOUND; // no tasks left in task buffer
    }    
}

mfxU32 CEncTaskPool::GetFreeTaskIndex()
{
    mfxU32 off = 0;

    if (m_pTasks)
    {
        for (off = 0; off < m_nPoolSize; off++)
        {            
            if (NULL == m_pTasks[(m_nTaskBufferStart + off) % m_nPoolSize].EncSyncP)
            {                
                break;
            }
        }
    } 

    if (off >= m_nPoolSize)
        return m_nPoolSize;

    return (m_nTaskBufferStart + off) % m_nPoolSize;
}

mfxStatus CEncTaskPool::GetFreeTask(sTask **ppTask)
{   
    MSDK_CHECK_POINTER(ppTask, MFX_ERR_NULL_PTR);
    MSDK_CHECK_POINTER(m_pTasks, MFX_ERR_NOT_INITIALIZED);

    mfxU32 index = GetFreeTaskIndex();

    if (index >= m_nPoolSize)
    {
        return MFX_ERR_NOT_FOUND;
    }

    // return the address of the task
    *ppTask = &m_pTasks[index];    

    return MFX_ERR_NONE; 
}

void CEncTaskPool::Close()
{  
    if (m_pTasks)
    {         
        for (mfxU32 i = 0; i < m_nPoolSize; i++)
        {    
            m_pTasks[i].Close();
        }
    }

    MSDK_SAFE_DELETE_ARRAY(m_pTasks);

    m_pmfxSession = NULL;
    m_nTaskBufferStart = 0;
    m_nPoolSize = 0;        
}

sTask::sTask() 
    : EncSyncP(0)
    , pWriter(NULL)
{
    MSDK_ZERO_MEMORY(mfxBS);
	m_IsStart=false;
	
}

mfxStatus sTask::Init(mfxU32 nBufferSize, CSmplBitstreamWriter *pwriter,char *Data,SDRFrameInfo&pVideoFrameInfo)
{
    Close();
    m_Data=Data;
	m_pVideoFrameInfo = &pVideoFrameInfo;
    pWriter = pwriter;

    mfxStatus sts = Reset();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxBitstream(&mfxBS, nBufferSize);
    MSDK_CHECK_RESULT_SAFE(sts, MFX_ERR_NONE, sts, WipeMfxBitstream(&mfxBS));

    return sts;
}
mfxStatus sTask::Close()
{    
    WipeMfxBitstream(&mfxBS);
    EncSyncP = 0;
    DependentVppTasks.clear();
	
    return MFX_ERR_NONE;
}

mfxStatus sTask::WriteBitstream()
{
    /*if (!pWriter)
        return MFX_ERR_NOT_INITIALIZED;

    return pWriter->WriteNextFrame(&mfxBS);*/
	MSDK_CHECK_POINTER(&mfxBS, MFX_ERR_NULL_PTR);
	return PutRawVideoFrame();
}
mfxStatus sTask::PutRawVideoFrame()
{
	m_pVideoFrameInfo->emDataType = STREAM_DATATYPE_VIDEO;
	m_pVideoFrameInfo->iSize = mfxBS.DataLength;

	//1.4 CPU硬编
	switch(mfxBS.FrameType & (MFX_FRAMETYPE_I | MFX_FRAMETYPE_P| MFX_FRAMETYPE_B))
	{
	case MFX_FRAMETYPE_I :
		{
			//最新驱动改为全高清下1080-5m-h,+82
			if(*(mfxBS.Data+82)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,84);
				m_Data[84]=0x00;
				memcpy(m_Data+85,mfxBS.Data+84,mfxBS.DataLength-84);
				m_pVideoFrameInfo->iSize+=1;
			}
			//最新驱动改为全高清下1080-4m-h和1080-2m-h,+81
			else if(*(mfxBS.Data+81)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,83);
				m_Data[83]=0x00;
				memcpy(m_Data+84,mfxBS.Data+83,mfxBS.DataLength-83);
				m_pVideoFrameInfo->iSize+=1;
			}
			//最新驱动改为全高清下1024-1m-m,+78
			else if(*(mfxBS.Data+78)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,81);
				m_Data[81]=0x00;
				memcpy(m_Data+82,mfxBS.Data+81,mfxBS.DataLength-81);
				m_pVideoFrameInfo->iSize+=1;

			}
			//最新驱动改为全高清下720-2m-h,+79
			else if(*(mfxBS.Data+79)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,82);
				m_Data[82]=0x00;
				memcpy(m_Data+83,mfxBS.Data+82,mfxBS.DataLength-82);
				m_pVideoFrameInfo->iSize+=1;

			}
			else if(*(mfxBS.Data+80)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,83);
				m_Data[83]=0x00;
				memcpy(m_Data+84,mfxBS.Data+83,mfxBS.DataLength-83);
				m_pVideoFrameInfo->iSize+=1;

			}
			//20141210
			else if(*(mfxBS.Data+83)==0x80)
			{
				m_pVideoFrameInfo->emFrameType=FRAMETYPE_I;
				memcpy(m_Data,mfxBS.Data,84);
				m_Data[84]=0x00;
				memcpy(m_Data+85,mfxBS.Data+84,mfxBS.DataLength-84);
				m_pVideoFrameInfo->iSize+=1;
			}
			else
			{
				memcpy(m_Data,mfxBS.Data,mfxBS.DataLength);
			}
					
			break;
		}			            
	case MFX_FRAMETYPE_P :
		{
			m_pVideoFrameInfo->emFrameType=FRAMETYPE_P;

			memcpy(m_Data,mfxBS.Data,31);
			m_Data[31]=0x00;
			memcpy(m_Data+32,mfxBS.Data+31,mfxBS.DataLength-31);
			m_pVideoFrameInfo->iSize+=1;
			break;
		}			
	case MFX_FRAMETYPE_B:
		{
			m_pVideoFrameInfo->emFrameType=FRAMETYPE_B;
			memcpy(m_Data,mfxBS.Data,30);
			m_Data[30]=0x00;
			memcpy(m_Data+31,mfxBS.Data+30,mfxBS.DataLength-30);
			m_pVideoFrameInfo->iSize+=1;
			break;
		}
		
	}
    //不改变压缩数据
    //memcpy(m_Data,mfxBS.Data,mfxBS.DataLength);
    
	m_pVideoFrameInfo->dwFrameIndex++;
	m_pVideoFrameInfo->dwShowIndex++;
	return MFX_ERR_NONE;
}

mfxStatus sTask::Reset()
{
    // mark sync point as free
    EncSyncP = NULL;

    // prepare bit stream
    mfxBS.DataOffset = 0;
    mfxBS.DataLength = 0;

    DependentVppTasks.clear();

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::AllocAndInitMVCSeqDesc()
{
    // a simple example of mfxExtMVCSeqDesc structure filling
    // actually equal to the "Default dependency mode" - when the structure fields are left 0,
    // but we show how to properly allocate and fill the fields

    mfxU32 i;       

    // mfxMVCViewDependency array
    m_MVCSeqDesc.NumView = m_nNumView; 
    m_MVCSeqDesc.NumViewAlloc = m_nNumView;
    m_MVCSeqDesc.View = new mfxMVCViewDependency[m_MVCSeqDesc.NumViewAlloc];
    MSDK_CHECK_POINTER(m_MVCSeqDesc.View, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < m_MVCSeqDesc.NumViewAlloc; ++i)
    {
        MSDK_ZERO_MEMORY(m_MVCSeqDesc.View[i]);
        m_MVCSeqDesc.View[i].ViewId = (mfxU16) i; // set view number as view id
    }        

    // set up dependency for second view
    m_MVCSeqDesc.View[1].NumAnchorRefsL0 = 1;
    m_MVCSeqDesc.View[1].AnchorRefL0[0] = 0;     // ViewId 0 - base view

    m_MVCSeqDesc.View[1].NumNonAnchorRefsL0 = 1;
    m_MVCSeqDesc.View[1].NonAnchorRefL0[0] = 0;  // ViewId 0 - base view

    // viewId array
    m_MVCSeqDesc.NumViewId = m_nNumView;    
    m_MVCSeqDesc.NumViewIdAlloc = m_nNumView;
    m_MVCSeqDesc.ViewId = new mfxU16[m_MVCSeqDesc.NumViewIdAlloc];
    MSDK_CHECK_POINTER(m_MVCSeqDesc.ViewId, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < m_MVCSeqDesc.NumViewIdAlloc; ++i)
    {
        m_MVCSeqDesc.ViewId[i] = (mfxU16) i; 
    }   

    // create a single operation point containing all views
    m_MVCSeqDesc.NumOP = 1;
    m_MVCSeqDesc.NumOPAlloc = 1;  
    m_MVCSeqDesc.OP = new mfxMVCOperationPoint[m_MVCSeqDesc.NumOPAlloc];
    MSDK_CHECK_POINTER(m_MVCSeqDesc.OP, MFX_ERR_MEMORY_ALLOC);
    for (i = 0; i < m_MVCSeqDesc.NumOPAlloc; ++i)
    {
        MSDK_ZERO_MEMORY(m_MVCSeqDesc.OP[i]);
        m_MVCSeqDesc.OP[i].NumViews = (mfxU16) m_nNumView;
        m_MVCSeqDesc.OP[i].NumTargetViews = (mfxU16) m_nNumView;
        m_MVCSeqDesc.OP[i].TargetViewId = m_MVCSeqDesc.ViewId; // points to mfxExtMVCSeqDesc::ViewId
    } 

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::AllocAndInitVppDoNotUse()
{    
    m_VppDoNotUse.NumAlg = 4;

    m_VppDoNotUse.AlgList = new mfxU32 [m_VppDoNotUse.NumAlg];    
    MSDK_CHECK_POINTER(m_VppDoNotUse.AlgList,  MFX_ERR_MEMORY_ALLOC);

    m_VppDoNotUse.AlgList[0] = MFX_EXTBUFF_VPP_DENOISE; // turn off denoising (on by default)
    m_VppDoNotUse.AlgList[1] = MFX_EXTBUFF_VPP_SCENE_ANALYSIS; // turn off scene analysis (on by default)
    m_VppDoNotUse.AlgList[2] = MFX_EXTBUFF_VPP_DETAIL; // turn off detail enhancement (on by default)
    m_VppDoNotUse.AlgList[3] = MFX_EXTBUFF_VPP_PROCAMP; // turn off processing amplified (on by default)

    return MFX_ERR_NONE;

} // CEncodingPipeline::AllocAndInitVppDoNotUse()

void CEncodingPipeline::FreeMVCSeqDesc()
{

    MSDK_SAFE_DELETE_ARRAY(m_MVCSeqDesc.View);
    MSDK_SAFE_DELETE_ARRAY(m_MVCSeqDesc.ViewId);
    MSDK_SAFE_DELETE_ARRAY(m_MVCSeqDesc.OP);      
}

void CEncodingPipeline::FreeVppDoNotUse()
{
    MSDK_SAFE_DELETE_ARRAY(m_VppDoNotUse.AlgList);
}

mfxStatus CEncodingPipeline::InitMfxEncParams(sInputParams *pInParams)
{
    m_mfxEncParams.mfx.CodecId                 = pInParams->CodecId;
    m_mfxEncParams.mfx.TargetUsage             = pInParams->nTargetUsage; // trade-off between quality and speed
    m_mfxEncParams.mfx.TargetKbps              = pInParams->nBitRate; // in Kbps
    m_mfxEncParams.mfx.RateControlMethod       = MFX_RATECONTROL_CBR; 
    ConvertFrameRate(pInParams->dFrameRate, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtN, &m_mfxEncParams.mfx.FrameInfo.FrameRateExtD);    
    m_mfxEncParams.mfx.EncodedOrder            = 0; // binary flag, 0 signals encoder to take frames in display order

    // specify memory type
    if (pInParams->bd3dAlloc)
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
    else
    {
        m_mfxEncParams.IOPattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY;
    }    

    // frame info parameters
    m_mfxEncParams.mfx.FrameInfo.FourCC       = MFX_FOURCC_NV12;
    m_mfxEncParams.mfx.FrameInfo.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
    m_mfxEncParams.mfx.FrameInfo.PicStruct    = pInParams->nPicStruct;

    // set frame size and crops
    // width must be a multiple of 16 
    // height must be a multiple of 16 in case of frame picture and a multiple of 32 in case of field picture
    m_mfxEncParams.mfx.FrameInfo.Width  = MSDK_ALIGN16(pInParams->nDstWidth);
    m_mfxEncParams.mfx.FrameInfo.Height = (MFX_PICSTRUCT_PROGRESSIVE == m_mfxEncParams.mfx.FrameInfo.PicStruct)?
        MSDK_ALIGN16(pInParams->nDstHeight) : MSDK_ALIGN32(pInParams->nDstHeight);
	//m_mfxEncParams.mfx.FrameInfo.Height=pInParams->nDstHeight;
    
    m_mfxEncParams.mfx.FrameInfo.CropX = 0; 
    m_mfxEncParams.mfx.FrameInfo.CropY = 0;
    m_mfxEncParams.mfx.FrameInfo.CropW = pInParams->nDstWidth;
    m_mfxEncParams.mfx.FrameInfo.CropH = pInParams->nDstHeight;

	m_mfxEncParams.mfx.GopPicSize              = pInParams->nGopPicSize;//gop length should be enough to consume bitrate
	//m_mfxEncParams.mfx.GopRefDist              = pInParams->nGopRefDist;//Distance between I- or P- key frames (1 means no B-frames)
	m_mfxEncParams.mfx.GopRefDist              = 3;//Distance between I- or P- key frames (1 means no B-frames)
	m_mfxEncParams.AsyncDepth                  = 1;//internal buffering should be disabled in encode
    
    // we don't specify profile and level and let the encoder choose those basing on parameters
    // we must specify profile only for MVC codec
    if (MVC_ENABLED & m_MVCflags)
    {
        m_mfxEncParams.mfx.CodecProfile = MFX_PROFILE_AVC_STEREO_HIGH;
    }
    
	m_mfxEncParams.mfx.CodecProfile=pInParams->nCodecProfile;

    // configure and attach external parameters 
    
    if (MVC_ENABLED & pInParams->MVC_flags)
        m_EncExtParams.push_back((mfxExtBuffer *)&m_MVCSeqDesc);
        
    if (MVC_VIEWOUTPUT & pInParams->MVC_flags)
    {
        // ViewOuput option requested
        m_CodingOption.ViewOutput = MFX_CODINGOPTION_ON;
        m_EncExtParams.push_back((mfxExtBuffer *)&m_CodingOption);
    }

    if (!m_EncExtParams.empty())
    {
        m_mfxEncParams.ExtParam = &m_EncExtParams[0]; // vector is stored linearly in memory
        m_mfxEncParams.NumExtParam = (mfxU16)m_EncExtParams.size();
    }
    
    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::InitMfxVppParams(sInputParams *pInParams)
{
    MSDK_CHECK_POINTER(pInParams,  MFX_ERR_NULL_PTR);   

    // specify memory type
	if (pInParams->bd3dAlloc)
	{
        m_mfxVppParams.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY | MFX_IOPATTERN_OUT_VIDEO_MEMORY;
	}
	else
	{
		m_mfxVppParams.IOPattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY | MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
	}    

    // input frame info  
    m_mfxVppParams.vpp.In.FourCC    = MFX_FOURCC_NV12;
    m_mfxVppParams.vpp.In.PicStruct = pInParams->nPicStruct;
    ConvertFrameRate(pInParams->dFrameRate, &m_mfxVppParams.vpp.In.FrameRateExtN, &m_mfxVppParams.vpp.In.FrameRateExtD);

    // width must be a multiple of 16 
    // height must be a multiple of 16 in case of frame picture and a multiple of 32 in case of field picture
    m_mfxVppParams.vpp.In.Width     = MSDK_ALIGN16(pInParams->nWidth); 
    m_mfxVppParams.vpp.In.Height    = (MFX_PICSTRUCT_PROGRESSIVE == m_mfxVppParams.vpp.In.PicStruct)?
        MSDK_ALIGN16(pInParams->nHeight) : MSDK_ALIGN32(pInParams->nHeight);
     //m_mfxVppParams.vpp.In.Height  =pInParams->nHeight;

    // set crops in input mfxFrameInfo for correct work of file reader
    // VPP itself ignores crops at initialization
    m_mfxVppParams.vpp.In.CropW = pInParams->nWidth;
    m_mfxVppParams.vpp.In.CropH = pInParams->nHeight;

    // fill output frame info
    memcpy(&m_mfxVppParams.vpp.Out, &m_mfxVppParams.vpp.In, sizeof(mfxFrameInfo));

    // only resizing is supported   
    m_mfxVppParams.vpp.Out.Width = MSDK_ALIGN16(pInParams->nDstWidth);
    m_mfxVppParams.vpp.Out.Height = (MFX_PICSTRUCT_PROGRESSIVE == m_mfxVppParams.vpp.Out.PicStruct)?
        MSDK_ALIGN16(pInParams->nDstHeight) : MSDK_ALIGN32(pInParams->nDstHeight); 
	//m_mfxVppParams.vpp.Out.Height  =pInParams->nHeight;

    // configure and attach external parameters 
    AllocAndInitVppDoNotUse();
    m_VppExtParams.push_back((mfxExtBuffer *)&m_VppDoNotUse);
     
    if (MVC_ENABLED & pInParams->MVC_flags)
        m_VppExtParams.push_back((mfxExtBuffer *)&m_MVCSeqDesc);

    m_mfxVppParams.ExtParam = &m_VppExtParams[0]; // vector is stored linearly in memory
    m_mfxVppParams.NumExtParam = (mfxU16)m_VppExtParams.size();

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::CreateDeviceManager()
{    
#ifdef D3D_SURFACES_SUPPORT
   m_pd3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!m_pd3d)
        return MFX_ERR_NULL_PTR;

    POINT point = {0, 0};
    HWND window = WindowFromPoint(point);

    D3DPRESENT_PARAMETERS d3dParams;
    memset(&d3dParams, 0, sizeof(d3dParams));
    d3dParams.Windowed = TRUE;
    d3dParams.hDeviceWindow = window;
    d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dParams.Flags = D3DPRESENTFLAG_VIDEO;
    d3dParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    d3dParams.BackBufferCount = 1;
    d3dParams.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dParams.BackBufferWidth = 0;
    d3dParams.BackBufferHeight = 0;
    
    HRESULT hr = m_pd3d->CreateDevice(
        GetMSDKAdapterNumber(m_mfxSession),
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
        &d3dParams,
        &m_pd3dDevice);
    if (FAILED(hr))
        return MFX_ERR_NULL_PTR;

    UINT resetToken = 0;    
    hr = DXVA2CreateDirect3DDeviceManager9(&resetToken, &m_pd3dDeviceManager);
    if (FAILED(hr))
        return MFX_ERR_NULL_PTR;

    hr = m_pd3dDeviceManager->ResetDevice(m_pd3dDevice, resetToken);
    if (FAILED(hr))
        return MFX_ERR_UNDEFINED_BEHAVIOR;
    
    m_resetToken = resetToken;   
#endif
    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::ResetDevice()
{
    if (m_bd3dAlloc)
    {
#ifdef D3D_SURFACES_SUPPORT
    HRESULT hr = m_pd3dDeviceManager->ResetDevice(m_pd3dDevice, m_resetToken);
    if (FAILED(hr))
        return MFX_ERR_UNDEFINED_BEHAVIOR;
    else
        return MFX_ERR_NONE;
#endif
    }
    else
    {
        return MFX_ERR_NONE;
    }
}

mfxStatus CEncodingPipeline::AllocFrames()
{    
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_NOT_INITIALIZED);

    mfxStatus sts = MFX_ERR_NONE;
    mfxFrameAllocRequest EncRequest;
    mfxFrameAllocRequest VppRequest[2];

    mfxU16 nEncSurfNum = 0; // number of surfaces for encoder
    mfxU16 nVppSurfNum = 0; // number of surfaces for vpp

    MSDK_ZERO_MEMORY(EncRequest);
    MSDK_ZERO_MEMORY(VppRequest[0]);
    MSDK_ZERO_MEMORY(VppRequest[1]);

    // Calculate the number of surfaces for components.
    // QueryIOSurf functions tell how many surfaces are required to produce at least 1 output. 
    // To achieve better performance we provide extra surfaces. 
    // 1 extra surface at input allows to get 1 extra output.  
 
    sts = m_pmfxENC->QueryIOSurf(&m_mfxEncParams, &EncRequest);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);             

    if (m_pmfxVPP)
    {
        // VppRequest[0] for input frames request, VppRequest[1] for output frames request
        sts = m_pmfxVPP->QueryIOSurf(&m_mfxVppParams, VppRequest);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);               
    }

    // The number of surfaces shared by vpp output and encode input.
    // When surfaces are shared 1 surface at first component output contains output frame that goes to next component input
    nEncSurfNum = EncRequest.NumFrameSuggested + MSDK_MAX(VppRequest[1].NumFrameSuggested, 1) - 1 + (m_nAsyncDepth - 1); 

    // The number of surfaces for vpp input - so that vpp can work at async depth = m_nAsyncDepth
    nVppSurfNum = VppRequest[0].NumFrameSuggested + (m_nAsyncDepth - 1); 

    // prepare allocation requests
    EncRequest.NumFrameMin = nEncSurfNum;
    EncRequest.NumFrameSuggested = nEncSurfNum;
    memcpy(&(EncRequest.Info), &(m_mfxEncParams.mfx.FrameInfo), sizeof(mfxFrameInfo));    
    if (m_pmfxVPP)
    {
        EncRequest.Type |= MFX_MEMTYPE_FROM_VPPOUT; // surfaces are shared between vpp output and encode input 
    }
    
    // alloc frames for encoder
    sts = m_pMFXAllocator->Alloc(m_pMFXAllocator->pthis, &EncRequest, &m_EncResponse);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // alloc frames for vpp if vpp is enabled
    if (m_pmfxVPP)
    {
        VppRequest[0].NumFrameMin = nVppSurfNum;
        VppRequest[0].NumFrameSuggested = nVppSurfNum;
        memcpy(&(VppRequest[0].Info), &(m_mfxVppParams.mfx.FrameInfo), sizeof(mfxFrameInfo));
        
        sts = m_pMFXAllocator->Alloc(m_pMFXAllocator->pthis, &(VppRequest[0]), &m_VppResponse);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    // prepare mfxFrameSurface1 array for encoder    
    m_pEncSurfaces = new mfxFrameSurface1 [m_EncResponse.NumFrameActual];
    MSDK_CHECK_POINTER(m_pEncSurfaces, MFX_ERR_MEMORY_ALLOC);

    for (int i = 0; i < m_EncResponse.NumFrameActual; i++)
    {       
        memset(&(m_pEncSurfaces[i]), 0, sizeof(mfxFrameSurface1));
        memcpy(&(m_pEncSurfaces[i].Info), &(m_mfxEncParams.mfx.FrameInfo), sizeof(mfxFrameInfo));
        if (m_bExternalAlloc)
        {            
            m_pEncSurfaces[i].Data.MemId = m_EncResponse.mids[i];    
        }
        else
        {
            // get YUV pointers
            sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, m_EncResponse.mids[i], &(m_pEncSurfaces[i].Data));
            MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        }
		//m_pEncSurfaces[i].IsInit=false;
    }

    // prepare mfxFrameSurface1 array for vpp if vpp is enabled
    if (m_pmfxVPP)
    {        
        m_pVppSurfaces = new mfxFrameSurface1 [m_VppResponse.NumFrameActual]; 
        MSDK_CHECK_POINTER(m_pVppSurfaces, MFX_ERR_MEMORY_ALLOC);

        for (int i = 0; i < m_VppResponse.NumFrameActual; i++)
        {       
            memset(&(m_pVppSurfaces[i]), 0, sizeof(mfxFrameSurface1));
            memcpy(&(m_pVppSurfaces[i].Info), &(m_mfxVppParams.mfx.FrameInfo), sizeof(mfxFrameInfo));

            if (m_bExternalAlloc)
            {
                m_pVppSurfaces[i].Data.MemId = m_VppResponse.mids[i];    
            }
            else
            {
                sts = m_pMFXAllocator->Lock(m_pMFXAllocator->pthis, m_VppResponse.mids[i], &(m_pVppSurfaces[i].Data));
                MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
            }
        }        
    }

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::CreateAllocator()
{   
    mfxStatus sts = MFX_ERR_NONE;

    if (m_bd3dAlloc)
    {
#ifdef D3D_SURFACES_SUPPORT       
        sts = CreateDeviceManager();
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // provide device manager to MediaSDK
        sts = m_mfxSession.SetHandle(MFX_HANDLE_D3D9_DEVICE_MANAGER, m_pd3dDeviceManager);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // crate D3D allocator
        m_pMFXAllocator = new D3DFrameAllocator; 
        MSDK_CHECK_POINTER(m_pMFXAllocator, MFX_ERR_MEMORY_ALLOC);

        D3DAllocatorParams *pd3dAllocParams = new D3DAllocatorParams; 
        MSDK_CHECK_POINTER(pd3dAllocParams, MFX_ERR_MEMORY_ALLOC);

        pd3dAllocParams->pManager = m_pd3dDeviceManager;
        m_pmfxAllocatorParams = pd3dAllocParams;

        /* In case of video memory we must provide Media SDK with external allocator 
        thus we demonstrate "external allocator" usage model.
        Call SetAllocator to pass allocator to Media SDK */
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
        We don't call SetAllocator, Media SDK uses internal allocator. 
        We use system memory allocator simply as a memory manager for application*/           
    }   

    // initialize memory allocator
    sts = m_pMFXAllocator->Init(m_pmfxAllocatorParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return MFX_ERR_NONE; 
}

void CEncodingPipeline::DeleteFrames()
{
    // delete surfaces array
    MSDK_SAFE_DELETE_ARRAY(m_pEncSurfaces);    
    MSDK_SAFE_DELETE_ARRAY(m_pVppSurfaces);    

    // delete frames
    if (m_pMFXAllocator)
    {        
        m_pMFXAllocator->Free(m_pMFXAllocator->pthis, &m_EncResponse);
        m_pMFXAllocator->Free(m_pMFXAllocator->pthis, &m_VppResponse);
    }    
}

void CEncodingPipeline::DeleteDeviceManager()
{
#ifdef D3D_SURFACES_SUPPORT 
    MSDK_SAFE_RELEASE(m_pd3dDevice);
    MSDK_SAFE_RELEASE(m_pd3dDeviceManager);
    MSDK_SAFE_RELEASE(m_pd3d);
#endif      
}

void CEncodingPipeline::DeleteAllocator()
{    
    // delete allocator
    MSDK_SAFE_DELETE(m_pMFXAllocator);   
    MSDK_SAFE_DELETE(m_pmfxAllocatorParams);

    DeleteDeviceManager();
}

CEncodingPipeline::CEncodingPipeline()
{    
    m_pmfxENC = NULL;
    m_pmfxVPP = NULL;
    m_pMFXAllocator = NULL;
    m_pmfxAllocatorParams = NULL;
    m_bd3dAlloc = true;
    m_bExternalAlloc = false;
    m_pEncSurfaces = NULL;   
    m_pVppSurfaces = NULL;
    m_nAsyncDepth = 0;

    m_MVCflags = MVC_DISABLED;
    m_nNumView = 0;

    m_FileWriters.first = m_FileWriters.second = NULL;

    MSDK_ZERO_MEMORY(m_MVCSeqDesc);
    m_MVCSeqDesc.Header.BufferId = MFX_EXTBUFF_MVC_SEQ_DESC;
    m_MVCSeqDesc.Header.BufferSz = sizeof(m_MVCSeqDesc);

    MSDK_ZERO_MEMORY(m_VppDoNotUse);
    m_VppDoNotUse.Header.BufferId = MFX_EXTBUFF_VPP_DONOTUSE;
    m_VppDoNotUse.Header.BufferSz = sizeof(m_VppDoNotUse);

    MSDK_ZERO_MEMORY(m_CodingOption);
    m_CodingOption.Header.BufferId = MFX_EXTBUFF_CODING_OPTION;
    m_CodingOption.Header.BufferSz = sizeof(m_CodingOption);    

#ifdef D3D_SURFACES_SUPPORT
    m_pd3d = NULL;
    m_pd3dDeviceManager = NULL;  
    m_pd3dDevice        = NULL;
    m_resetToken        = 0;
#endif 

    MSDK_ZERO_MEMORY(m_mfxEncParams);
    MSDK_ZERO_MEMORY(m_mfxVppParams);

    MSDK_ZERO_MEMORY(m_EncResponse); 
    MSDK_ZERO_MEMORY(m_VppResponse);

}

CEncodingPipeline::~CEncodingPipeline()
{
    Close();
}

void CEncodingPipeline::SetMultiView()
{
    m_FileReader.SetMultiView();
}

mfxStatus CEncodingPipeline::InitFileWriter(CSmplBitstreamWriter **ppWriter, const TCHAR *filename)
{
    MSDK_CHECK_ERROR(ppWriter, NULL, MFX_ERR_NULL_PTR);

    MSDK_SAFE_DELETE(*ppWriter);
    *ppWriter = new CSmplBitstreamWriter;
    MSDK_CHECK_POINTER(*ppWriter, MFX_ERR_MEMORY_ALLOC);
    mfxStatus sts = (*ppWriter)->Init(filename);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return sts;
}

mfxStatus CEncodingPipeline::InitFileWriters(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;

    // prepare output file writers

    // ViewOutput mode: output in single bitstream
    if ( (MVC_VIEWOUTPUT & pParams->MVC_flags) && (pParams->dstFileBuff.size() <= 1))
    {
        sts = InitFileWriter(&m_FileWriters.first, pParams->dstFileBuff[0]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        m_FileWriters.second = m_FileWriters.first;        
    }
    // ViewOutput mode: 2 bitstreams in separate files
    else if ( (MVC_VIEWOUTPUT & pParams->MVC_flags) && (pParams->dstFileBuff.size() <= 2))
    {
        sts = InitFileWriter(&m_FileWriters.first, pParams->dstFileBuff[0]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        sts = InitFileWriter(&m_FileWriters.second, pParams->dstFileBuff[1]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }
    // ViewOutput mode: 3 bitstreams - 2 separate & 1 merged
    else if ( (MVC_VIEWOUTPUT & pParams->MVC_flags) && (pParams->dstFileBuff.size() <= 3))
    {
        std::auto_ptr<CSmplBitstreamDuplicateWriter> first(new CSmplBitstreamDuplicateWriter);

        // init first duplicate writer
        MSDK_CHECK_POINTER(first.get(), MFX_ERR_MEMORY_ALLOC);
        sts = first->Init(pParams->dstFileBuff[0]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        sts = first->InitDuplicate(pParams->dstFileBuff[2]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // init second duplicate writer
        std::auto_ptr<CSmplBitstreamDuplicateWriter> second(new CSmplBitstreamDuplicateWriter);
        MSDK_CHECK_POINTER(second.get(), MFX_ERR_MEMORY_ALLOC);
        sts = second->Init(pParams->dstFileBuff[1]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
        sts = second->JoinDuplicate(first.get());
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        m_FileWriters.first = first.release();
        m_FileWriters.second = second.release();
    }
    // not ViewOutput mode
    else
    {
        sts = InitFileWriter(&m_FileWriters.first, pParams->dstFileBuff[0]);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }
    return sts;

}

mfxStatus CEncodingPipeline::Init(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    mfxStatus sts = MFX_ERR_NONE;    
    mfxIMPL impl;
	mfxVersion version={3,1};
	if (pParams->bUseHWLib)
	{
		// try searching on all display adapters
		impl = MFX_IMPL_HARDWARE_ANY;

		// if d3d11 surfaces are used ask the library to run acceleration through D3D11
		// feature may be unsupported due to OS or MSDK API version


		sts = m_mfxSession.Init(impl, &version);

		// MSDK API version may not support multiple adapters - then try initialize on the default
		if (MFX_ERR_NONE != sts)
			sts = m_mfxSession.Init(impl & !MFX_IMPL_HARDWARE_ANY | MFX_IMPL_HARDWARE, &version);
	}
	else
		sts = m_mfxSession.Init(MFX_IMPL_SOFTWARE, &version);
	m_mfxSession.QueryIMPL(&impl);

	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    // set memory type
    m_bd3dAlloc = pParams->bd3dAlloc;     
    
    // create and init frame allocator 
    sts = CreateAllocator();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    sts = InitMfxEncParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts); 
    sts = InitMfxVppParams(pParams);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);    
    // MVC specific options
    if (MVC_ENABLED & m_MVCflags)
    {
        sts = AllocAndInitMVCSeqDesc();
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);      
    }

    // create encoder
    m_pmfxENC = new MFXVideoENCODE(m_mfxSession); 
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_MEMORY_ALLOC);

    // create preprocessor if resizing was requested from command line 
    // or if different FourCC is set in InitMfxVppParams
    if (pParams->nWidth  != pParams->nDstWidth ||
        pParams->nHeight != pParams->nDstHeight ||
        m_mfxVppParams.vpp.In.FourCC != m_mfxVppParams.vpp.Out.FourCC)
    {
        m_pmfxVPP = new MFXVideoVPP(m_mfxSession);
        MSDK_CHECK_POINTER(m_pmfxVPP, MFX_ERR_MEMORY_ALLOC);
    }  

    m_nAsyncDepth = 4; // this number can be tuned for better performance
    sts = ResetMFXComponents(pParams); 
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);	

	m_pCurrentTask=NULL;
    return MFX_ERR_NONE;
}

void CEncodingPipeline::Close()
{  
	m_IsStop=true;
	Sleep(100);
    
    MSDK_SAFE_DELETE(m_pmfxENC);
    MSDK_SAFE_DELETE(m_pmfxVPP);

    FreeMVCSeqDesc();
    FreeVppDoNotUse();

    DeleteFrames();    
    // allocator if used as external for MediaSDK must be deleted after SDK components
    DeleteAllocator();

    m_TaskPool.Close();
    m_mfxSession.Close();
	FreeFileWriters();

}

void CEncodingPipeline::FreeFileWriters()
{
    if (m_FileWriters.second == m_FileWriters.first)
    {
        m_FileWriters.second = NULL; // second do not own the writer - just forget pointer
    }
    
    if (m_FileWriters.first)
        m_FileWriters.first->Close();
    MSDK_SAFE_DELETE(m_FileWriters.first);

    if (m_FileWriters.second)
        m_FileWriters.second->Close();
    MSDK_SAFE_DELETE(m_FileWriters.second);
}

mfxStatus CEncodingPipeline::ResetMFXComponents(sInputParams* pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_NOT_INITIALIZED);

    mfxStatus sts = MFX_ERR_NONE;    

    sts = m_pmfxENC->Close();
    MSDK_IGNORE_MFX_STS(sts, MFX_ERR_NOT_INITIALIZED);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    if (m_pmfxVPP)
    {
        sts = m_pmfxVPP->Close();
        MSDK_IGNORE_MFX_STS(sts, MFX_ERR_NOT_INITIALIZED);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }    

    // free allocated frames
    DeleteFrames();

    m_TaskPool.Close();   
    
    sts = AllocFrames();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);   

    sts = m_pmfxENC->Init(&m_mfxEncParams);
    MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);    

    if (m_pmfxVPP)
    {
        sts = m_pmfxVPP->Init(&m_mfxVppParams);
        MSDK_IGNORE_MFX_STS(sts, MFX_WRN_PARTIAL_ACCELERATION);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    mfxU32 nEncodedDataBufferSize = m_mfxEncParams.mfx.FrameInfo.Width * m_mfxEncParams.mfx.FrameInfo.Height * 4; 
	//m_pVideoFrameInfo.dwShowIndex=0;
	//m_pVideoFrameInfo.dwFrameIndex=0;
    sts = m_TaskPool.Init(&m_mfxSession, m_FileWriters.first, m_nAsyncDepth * 2, nEncodedDataBufferSize, m_FileWriters.second,m_Data,m_pVideoFrameInfo);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::AllocateSufficientBuffer(mfxBitstream* pBS)
{    
    MSDK_CHECK_POINTER(pBS, MFX_ERR_NULL_PTR);
    MSDK_CHECK_POINTER(m_pmfxENC, MFX_ERR_NOT_INITIALIZED);

    mfxVideoParam par;
    MSDK_ZERO_MEMORY(par);

    // find out the required buffer size
    mfxStatus sts = m_pmfxENC->GetVideoParam(&par);
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts); 

    // reallocate bigger buffer for output
    sts = ExtendMfxBitstream(pBS, par.mfx.BufferSizeInKB * 1000); 
    MSDK_CHECK_RESULT_SAFE(sts, MFX_ERR_NONE, sts, WipeMfxBitstream(pBS));

    return MFX_ERR_NONE;
}

mfxStatus CEncodingPipeline::GetFreeTask(sTask **ppTask)
{
    mfxStatus sts = MFX_ERR_NONE;

    sts = m_TaskPool.GetFreeTask(ppTask);
    if (MFX_ERR_NOT_FOUND == sts)
    {
        sts = SynchronizeFirstTask(); 
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

        // try again
        sts = m_TaskPool.GetFreeTask(ppTask); 
    }

    return sts;
}

mfxStatus CEncodingPipeline::SynchronizeFirstTask()
{    
    mfxStatus sts = m_TaskPool.SynchronizeFirstTask();

    return sts;
}

mfxStatus CEncodingPipeline::Run()
{   
    return MFX_ERR_NONE; 
}
mfxStatus CEncodingPipeline::Finish()
{
	////////////////////////////////////////
	mfxStatus sts = MFX_ERR_NONE;
	int nTry = 0;
	mfxFrameSurface1* pSurf = NULL; // dispatching pointer

	sTask *pCurrentTask = NULL; // a pointer to the current task
	mfxU16 nEncSurfIdx = 0;     // index of free surface for encoder input (vpp output)
	mfxU16 nVppSurfIdx = 0;     // index of free surface for vpp input

	mfxSyncPoint VppSyncPoint = NULL; // a sync point associated with an asynchronous vpp call
	// than consumes at input. E.g. framerate conversion 30 fps -> 60 fps
	if (m_pmfxVPP)
	{
		// loop to get buffered frames from vpp
		while (MFX_ERR_NONE <= sts || MFX_ERR_MORE_DATA == sts || MFX_ERR_MORE_SURFACE == sts)
			// MFX_ERR_MORE_SURFACE can be returned only by RunFrameVPPAsync
			// MFX_ERR_MORE_DATA is accepted only from EncodeFrameAsync
		{
			// find free surface for encoder input (vpp output)
			nEncSurfIdx = GetFreeSurface(m_pEncSurfaces, m_EncResponse.NumFrameActual);
			MSDK_CHECK_ERROR(nEncSurfIdx, MSDK_INVALID_SURF_IDX, MFX_ERR_MEMORY_ALLOC);
			for (;;)
			{
				sts = m_pmfxVPP->RunFrameVPPAsync(NULL, &m_pEncSurfaces[nEncSurfIdx], NULL, &VppSyncPoint);

				if (MFX_ERR_NONE < sts && !VppSyncPoint) // repeat the call if warning and no output
				{
					if (MFX_WRN_DEVICE_BUSY == sts)
					{
						if (nTry > 200)		
						{
							break;
						}
						nTry++;
						Sleep(1); // wait if device is busy
					}
				}
				else if (MFX_ERR_NONE < sts && VppSyncPoint)
				{
					sts = MFX_ERR_NONE; // ignore warnings if output is available
					break;
				}
				else
					break; // not a warning
			}

			if (MFX_ERR_MORE_SURFACE == sts)
			{
				continue;
			}
			else
			{
				MSDK_BREAK_ON_ERROR(sts);
			}

			// get a free task (bit stream and sync point for encoder)
			sts = GetFreeTask(&pCurrentTask);
			MSDK_BREAK_ON_ERROR(sts);

			// save the id of preceding vpp task which will produce input data for the encode task
			if (VppSyncPoint)
			{
				pCurrentTask->DependentVppTasks.push_back(VppSyncPoint);
				VppSyncPoint = NULL;
			}

			for (;;)
			{
				sts = m_pmfxENC->EncodeFrameAsync(NULL, &m_pEncSurfaces[nEncSurfIdx], &pCurrentTask->mfxBS, &pCurrentTask->EncSyncP);

				if (MFX_ERR_NONE < sts && !pCurrentTask->EncSyncP) // repeat the call if warning and no output
				{
					if (MFX_WRN_DEVICE_BUSY == sts)
						Sleep(1); // wait if device is busy
				}
				else if (MFX_ERR_NONE < sts && pCurrentTask->EncSyncP)
				{
					sts = MFX_ERR_NONE; // ignore warnings if output is available
					break;
				}
				else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
				{
					sts = AllocateSufficientBuffer(&pCurrentTask->mfxBS);
					MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
				}
				else
				{
					// get next surface and new task for 2nd bitstream in ViewOutput mode
					MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_BITSTREAM);
					break;
				}
			}
		}

		// MFX_ERR_MORE_DATA is the correct status to exit buffering loop with
		// indicates that there are no more buffered frames
		MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
		// exit in case of other errors
		MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
	}

	// loop to get buffered frames from encoder
	while (MFX_ERR_NONE <= sts)
	{
		// get a free task (bit stream and sync point for encoder)
		sts = GetFreeTask(&pCurrentTask);
		MSDK_BREAK_ON_ERROR(sts);

		for (;;)
		{
			sts = m_pmfxENC->EncodeFrameAsync(NULL, NULL, &pCurrentTask->mfxBS, &pCurrentTask->EncSyncP);

			if (MFX_ERR_NONE < sts && !pCurrentTask->EncSyncP) // repeat the call if warning and no output
			{
				if (MFX_WRN_DEVICE_BUSY == sts)
				{
					if (nTry > 200)		
					{
						break;
					}
					nTry++;
					Sleep(1); // wait if device is busy
				}
			}
			else if (MFX_ERR_NONE < sts && pCurrentTask->EncSyncP)
			{
				sts = MFX_ERR_NONE; // ignore warnings if output is available
				break;
			}
			else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
			{
				sts = AllocateSufficientBuffer(&pCurrentTask->mfxBS);
				MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
			}
			else
			{
				// get new task for 2nd bitstream in ViewOutput mode
				MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_BITSTREAM);
				break;
			}
		}
		MSDK_BREAK_ON_ERROR(sts);
	}

	// MFX_ERR_MORE_DATA is the correct status to exit buffering loop with
	// indicates that there are no more buffered frames
	MSDK_IGNORE_MFX_STS(sts, MFX_ERR_MORE_DATA);
	// exit in case of other errors
	MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
	////////////////////////////////////////
	//mfxStatus sts = MFX_ERR_NONE;    
	while (MFX_ERR_NONE == sts)
	{
		sts = m_TaskPool.SynchronizeFirstTask();
	}
	return sts;
}
void CEncodingPipeline::PutAudio(unsigned char*Audio)
{
}
mfxStatus CEncodingPipeline::PutVideo(unsigned char*Video)
{
	if (m_pmfxENC)
	{
		//UYVY_TO_NV12(m_YUV420Buffer,Video,m_mfxVppParams.mfx.FrameInfo.CropW,m_mfxVppParams.mfx.FrameInfo.CropH);
	}
	else
		return MFX_ERR_UNKNOWN;

	
	mfxStatus sts = MFX_ERR_NONE;  

	mfxFrameSurface1* pSurf = NULL; // dispatching pointer  

	//sTask *pCurrentTask = NULL; // a pointer to the current task
	mfxU16 nEncSurfIdx = 0; // index of free surface for encoder input (vpp output)
	mfxU16 nVppSurfIdx = 0; // index of free surface for vpp input

	mfxSyncPoint VppSyncPoint = NULL; 
	bool bVppMultipleOutput = false; 
	mfxU16 currViewNum = 0;     

	sts = MFX_ERR_NONE;       
	sts = GetFreeTask(&m_pCurrentTask);
	nEncSurfIdx = GetFreeSurface(m_pEncSurfaces, m_EncResponse.NumFrameActual);
	if (nEncSurfIdx==MSDK_INVALID_SURF_IDX)
	{
		return MFX_ERR_UNKNOWN;
	}	
	if (m_pmfxVPP)
	{
		nVppSurfIdx = GetFreeSurface(m_pVppSurfaces, m_VppResponse.NumFrameActual);
		if (nVppSurfIdx==MSDK_INVALID_SURF_IDX)
		{
			return MFX_ERR_UNKNOWN;
		}
		if (m_pVppSurfaces)
		{
			if (m_pVppSurfaces[nVppSurfIdx].Data.Y)
			{
				//memcpy(m_pVppSurfaces[nVppSurfIdx].Data.Y,m_YUV420Buffer,m_pVppSurfaces[nVppSurfIdx].Info.CropW*m_pVppSurfaces[nVppSurfIdx].Info.CropH);
				//memcpy(m_pVppSurfaces[nVppSurfIdx].Data.UV,m_YUV420Buffer+m_pVppSurfaces[nVppSurfIdx].Info.CropW*m_pVppSurfaces[nVppSurfIdx].Info.CropH,m_pVppSurfaces[nVppSurfIdx].Info.CropW*m_pVppSurfaces[nVppSurfIdx].Info.CropH/2);
				UYVY_TO_NV12(m_pVppSurfaces[nVppSurfIdx].Data.Y,m_pVppSurfaces[nVppSurfIdx].Data.UV,Video,m_mfxVppParams.mfx.FrameInfo.CropW,m_mfxVppParams.mfx.FrameInfo.CropH);
			}
			else
			{				
				return sts;
			}				

		}
		else
		{			
			return MFX_ERR_UNKNOWN;
		}
	}
	else
	{
		if (m_pEncSurfaces)
		{
			if (m_pEncSurfaces[nEncSurfIdx].Info.CropW < 1024)
			{
				m_pEncSurfaces[nEncSurfIdx].Data.UV = m_pEncSurfaces[nEncSurfIdx].Data.Y + m_pEncSurfaces[nEncSurfIdx].Info.CropW*m_pEncSurfaces[nEncSurfIdx].Info.CropH;
				m_pEncSurfaces[nEncSurfIdx].Data.Pitch =  m_pEncSurfaces[nEncSurfIdx].Info.CropW;
				m_pEncSurfaces[nEncSurfIdx].Data.PitchLow = m_pEncSurfaces[nEncSurfIdx].Data.Pitch;

			}
			if (m_pEncSurfaces[nEncSurfIdx].Data.Y)
			{
				//memcpy(m_pEncSurfaces[nEncSurfIdx].Data.Y,m_YUV420Buffer,m_pEncSurfaces[nEncSurfIdx].Info.CropW*m_pEncSurfaces[nEncSurfIdx].Info.CropH);
				//memcpy(m_pEncSurfaces[nEncSurfIdx].Data.UV,m_YUV420Buffer+m_pEncSurfaces[nEncSurfIdx].Info.CropW*m_pEncSurfaces[nEncSurfIdx].Info.CropH,m_pEncSurfaces[nEncSurfIdx].Info.CropW*m_pEncSurfaces[nEncSurfIdx].Info.CropH/2);
                UYVY_TO_NV12(m_pEncSurfaces[nEncSurfIdx].Data.Y,m_pEncSurfaces[nEncSurfIdx].Data.UV,Video,m_pEncSurfaces[nEncSurfIdx].Info.CropW,m_pEncSurfaces[nEncSurfIdx].Info.CropH);
			}
			else
			{
				return sts;
			}

		}
		else
		{
			return MFX_ERR_UNKNOWN;
		}

	}	
	int nTry = 0;
	CString str;
	//////////////////////////////////////////////////////////////////////////
	if (m_pmfxVPP)
	{            
		bVppMultipleOutput = false; // reset the flag before a call to VPP
		for (;;)
		{
			sts = m_pmfxVPP->RunFrameVPPAsync(&m_pVppSurfaces[nVppSurfIdx], &m_pEncSurfaces[nEncSurfIdx], 
				NULL, &VppSyncPoint); 

			if (MFX_ERR_NONE < sts && !VppSyncPoint) // repeat the call if warning and no output
			{
				if (MFX_WRN_DEVICE_BUSY == sts)  
				{
					if (nTry > 200)		
					{
						break;
					}
					nTry++;
					Sleep(1); // wait if device is busy 
					
				}
			}
			else if (MFX_ERR_NONE < sts && VppSyncPoint)                 
			{
				sts = MFX_ERR_NONE; // ignore warnings if output is available 
				break;
			}
			else 
				break; // not a warning               
		} 
		if (VppSyncPoint)
		{
			m_pCurrentTask->DependentVppTasks.push_back(VppSyncPoint);
			VppSyncPoint = NULL;
		}

	} 

	nTry = 0;
	for (;;)
	{      

		sts = m_pmfxENC->EncodeFrameAsync(NULL, &m_pEncSurfaces[nEncSurfIdx], &m_pCurrentTask->mfxBS, &m_pCurrentTask->EncSyncP);

		if (MFX_ERR_NONE < sts && !m_pCurrentTask->EncSyncP) // repeat the call if warning and no output
		{
			if (MFX_WRN_DEVICE_BUSY == sts)    
			{
				if (nTry > 200)		
				{
					break;
				}
				nTry++;
				Sleep(1); // wait if device is busy 
				
			}
		}
		else if (MFX_ERR_NONE < sts && m_pCurrentTask->EncSyncP)                 
		{
			sts = MFX_ERR_NONE; // ignore warnings if output is available                                    
			break;
		}
		else if (MFX_ERR_NOT_ENOUGH_BUFFER == sts)
		{
			sts = AllocateSufficientBuffer(&m_pCurrentTask->mfxBS);
			break;
		}
		else
		{

			break;
		}
	} 
	if (MFX_ERR_NONE == sts)
	{
		sts = m_mfxSession.SyncOperation(m_pCurrentTask->EncSyncP, MSDK_ENC_WAIT_INTERVAL);             
	}
	return sts; 
}

void CEncodingPipeline::UYVY_TO_NV12( unsigned char *dst,  unsigned char *buffer, int width, int height )
{
	int i,j,ysize;
	unsigned char *up = NULL, *vp = NULL,*yp1 = NULL,*yp2 = NULL, *in1 = NULL,*in2 = NULL,*uvp=NULL;

	int width05=width/2;
    int width2=width*2;
	int height05=height/2;

	ysize = width*height; 
	uvp = dst + ysize;
	yp1 = dst;
	yp2 = dst+width;

	in1 = buffer;
	in2 = buffer + width2;

	for(i = 0; i < height05; i++)
	{
		if(i)
		{
			yp1 +=width;
			yp2 +=width;
			in1 += width2;
			in2 += width2;
		}
		for(j = 0; j < width05; j++)
		{
			//for line 2n-1
			*uvp++ = *in1;
			*yp1++ = *(in1+1);
			*yp1++ = *(in1+3);
			//for line 2n
			*yp2++ = *(in2 + 1);
			*yp2++ = *(in2 + 3);
			*uvp++ =  *(in2 + 2);

			in1 += 4;
			in2 += 4;
		}
	}
}
void CEncodingPipeline::UYVY_TO_NV12( unsigned char *dst_y,unsigned char *dst_uv,  unsigned char *buffer, int width, int height )
{
	int i,j,ysize;
	unsigned char *yp1 = NULL,*yp2 = NULL, *in1 = NULL,*in2 = NULL,*uvp=NULL;

	int width05=width/2;
	int width2=width*2;
	int height05=height/2;

	ysize = width*height; 
	uvp = dst_uv;
	yp1 = dst_y;
	yp2 = dst_y+width;

	in1 = buffer;
	in2 = buffer + width2;

	for(i = 0; i < height05; i++)
	{
		if(i)
		{
			yp1 +=width;
			yp2 +=width;
			in1 += width2;
			in2 += width2;
		}
		for(j = 0; j < width05; j++)
		{
			//for line 2n-1
			*uvp++ = *in1;
			*yp1++ = *(in1+1);
			*yp1++ = *(in1+3);
			//for line 2n
			*yp2++ = *(in2 + 1);
			*yp2++ = *(in2 + 3);
			*uvp++ =  *(in2 + 2);

			in1 += 4;
			in2 += 4;
		}
	}
}
void CEncodingPipeline::PrintInfo()
{       
} 