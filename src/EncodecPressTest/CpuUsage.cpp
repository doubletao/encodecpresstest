#include "StdAfx.h"
//CpuUsage.cpp

//#include "GpuUsage.h"

#include <windows.h>
#include "CPUusage.h"
#include <strsafe.h>
#include <tlhelp32.h>
#include <dxgi.h>
#include <Psapi.h>
#include <assert.h>
#pragma comment(lib, "Psapi.lib ")

//#define USE_DEPRECATED_FUNCS
void ErrorMsg(LPTSTR lpszFunction);
BOOL SetPrivilege(HANDLE hProcess, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);

#ifdef USE_DEPRECATED_FUNCS
#define SystemBasicInformation                    0
#define SystemPerformanceInformation            2
#define SystemTimeInformation                    3
#define SystemProcessorPerformanceInformation    8
#define ProcessTimes                            4

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct
{
	DWORD dwUnknown1;
	ULONG uKeMaximumIncrement;
	ULONG uPageSize;
	ULONG uMmNumberOfPhysicalPages;
	ULONG uMmLowestPhysicalPage;
	ULONG uMmHighestPhysicalPage;
	ULONG uAllocationGranularity;
	PVOID pLowestUserAddress;
	PVOID pMmHighestUserAddress;
	ULONG uKeActiveProcessors;
	BYTE bKeNumberProcessors;
	BYTE bUnknown2;
	WORD wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
	LARGE_INTEGER liIdleTime;
	DWORD dwSpare[312];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liExpTimeZoneBias;
	ULONG uCurrentTimeZoneId;
	DWORD dwReserved;
} SYSTEMTEXTIME_INFORMATION;

typedef struct
	_SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
	LARGE_INTEGER IdleTime;
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER Reserved1[2];
	ULONG Reserved2;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

typedef struct _KERNEL_USERTEXTIMES
{
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER ExitTime;
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
} KERNEL_USERTEXTIMES, *PKERNEL_USERTEXTIMES;

typedef LONG (WINAPI *PROCNTQSI)(UINT, PVOID, ULONG, PULONG);
PROCNTQSI NtQuerySystemInformation;

typedef LONG (WINAPI *PROCNTQIP)(HANDLE, UINT, PVOID, ULONG, PULONG);
PROCNTQIP NtQueryInformationProcess;

ULONGLONG CpuUsage::GetSystemNonIdleTimes()
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEMTEXTIME_INFORMATION SysTimeInfo;
	SYSTEM_BASIC_INFORMATION SysBaseInfo;
	SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION SysProcPerfInfo[32];
	LONG status;
	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		return 0;
	status = NtQuerySystemInformation(SystemBasicInformation, &SysBaseInfo, sizeof(SysBaseInfo), NULL);
	if (status != NO_ERROR)
	{
		//MessageBox(TEXT("FailSystemInfo"));
		return 0;
	}
	status = NtQuerySystemInformation(SystemProcessorPerformanceInformation, SysProcPerfInfo, sizeof(SysProcPerfInfo), NULL);
	if(status != NO_ERROR) return 0;
	int nProcessors = SysBaseInfo.bKeNumberProcessors; //机器内部CPU的个数
	ULONGLONG ullSysTotal = 0;
	for(int i = 0; i < nProcessors; i++)
	{
		ullSysTotal += SysProcPerfInfo[i].KernelTime.QuadPart + SysProcPerfInfo[i].UserTime.QuadPart;
	}
	return ullSysTotal;
}

ULONGLONG CpuUsage::GetProcessNonIdleTimes()
{
	KERNEL_USERTEXTIMES KernelUserTimes;
	::ZeroMemory(&KernelUserTimes, sizeof(KernelUserTimes));
	NtQueryInformationProcess = (PROCNTQIP)GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtQueryInformationProcess");
	LONG status = NtQueryInformationProcess(m_hProcess, ProcessTimes, &KernelUserTimes, sizeof(KernelUserTimes), NULL);
	if(status == 0)
	{
		//ErrorExit(TEXT("GetProcessNonIdleTimes"));
		return 0;
	}
	return KernelUserTimes.KernelTime.QuadPart + KernelUserTimes.UserTime.QuadPart;

}

#endif

CpuUsage::CpuUsage(DWORD dwProcessID)
	: m_nCpuUsage(0),
	m_dwLastRun(0),
	m_lRunCount(0),
	m_dwProcessID(dwProcessID),
	m_ullPrevProcNonIdleTime(0),
	m_ullPrevSysNonIdleTime(0)
{
	HANDLE hProcess = GetCurrentProcess();
	SetPrivilege(hProcess, SE_DEBUG_NAME, TRUE);

	m_hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION , TRUE, m_dwProcessID);
	if(m_hProcess == 0)
	{
		ErrorMsg(TEXT("OpenProcess"));
	}
	ZeroMemory(&m_ftPrevSysKernel, sizeof(FILETIME));
	ZeroMemory(&m_ftPrevSysUser, sizeof(FILETIME));

	ZeroMemory(&m_ftPrevProcKernel, sizeof(FILETIME));
	ZeroMemory(&m_ftPrevProcUser, sizeof(FILETIME));


// 	GpuUsage gpuUsage;
// 	gpuUsage.Init();
// 	int nCnt = gpuUsage.GetDisplayCardCount();
// 	for (int i=0; i<nCnt; i++)
// 	{
// 		DISPLAY_INFO disPlayInfo;
// 		gpuUsage.GetDisplayInfo(i, &disPlayInfo);
// 		int a = 0;
// 	}
// 	gpuUsage.Unit();
}


ULONGLONG CpuUsage::SubtractTimes(const FILETIME &ftA, const FILETIME &ftB)
{
	LARGE_INTEGER a, b;
	a.LowPart = ftA.dwLowDateTime;
	a.HighPart = ftA.dwHighDateTime;

	b.LowPart = ftB.dwLowDateTime;
	b.HighPart = ftB.dwHighDateTime;

	return a.QuadPart - b.QuadPart;
}

ULONGLONG CpuUsage::AddTimes(const FILETIME &ftA, const FILETIME &ftB)
{
	LARGE_INTEGER a, b;
	a.LowPart = ftA.dwLowDateTime;
	a.HighPart = ftA.dwHighDateTime;

	b.LowPart = ftB.dwLowDateTime;
	b.HighPart = ftB.dwHighDateTime;

	return a.QuadPart + b.QuadPart;
}

bool CpuUsage::EnoughTimePassed()
{
	const int minElapsedMS = 250;//milliseconds

	ULONGLONG dwCurrentTickCount = GetTickCount();
	return (dwCurrentTickCount - m_dwLastRun) > minElapsedMS;
}
#ifndef USE_DEPRECATED_FUNCS

ULONGLONG CpuUsage::GetSystemNonIdleTimes()
{
	FILETIME ftSysIdle, ftSysKernel, ftSysUser;
	if(!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser))
	{
		ErrorMsg(TEXT("GetSystemTimes"));
		return 0;
	}
	return AddTimes(ftSysKernel, ftSysUser);
}


ULONGLONG CpuUsage::GetProcessNonIdleTimes()
{
	FILETIME ftProcCreation, ftProcExit, ftProcKernel, ftProcUser;
	if(!GetProcessTimes(m_hProcess, &ftProcCreation, &ftProcExit, &ftProcKernel, &ftProcUser) && false)
	{
		ErrorMsg(TEXT("GetProcessNonIdleTimes"));
		return 0;
	}
	return AddTimes(ftProcKernel, ftProcUser);
}
#endif

ULONGLONG CpuUsage::GetUsageEx()
{
// 	GpuUsage gpuUsage;
// 	gpuUsage.Init();
// 	int nCnt = gpuUsage.GetDisplayCardCount();
// 	for (int i=0; i<nCnt; i++)
// 	{
// 		DISPLAY_INFO disPlayInfo;
// 		gpuUsage.GetDisplayInfo(i, &disPlayInfo);
// 		int a = 0;
// 	}
// 	gpuUsage.Unit();

	ULONGLONG nCpuCopy = m_nCpuUsage;
	if (::InterlockedIncrement(&m_lRunCount) == 1)
	{
		if (!EnoughTimePassed())
		{
			::InterlockedDecrement(&m_lRunCount);
			return nCpuCopy;
		}
		ULONGLONG ullSysNonIdleTime = GetSystemNonIdleTimes();
		ULONGLONG ullProcNonIdleTime = GetProcessNonIdleTimes();
		if (!IsFirstRun())
		{
			ULONGLONG ullTotalSys = ullSysNonIdleTime - m_ullPrevSysNonIdleTime;
			if(ullTotalSys == 0)
			{
				::InterlockedDecrement(&m_lRunCount);
				return nCpuCopy;
			}
			m_nCpuUsage = ULONGLONG((ullProcNonIdleTime - m_ullPrevProcNonIdleTime) * 100.0 / (ullTotalSys));
			m_ullPrevSysNonIdleTime = ullSysNonIdleTime;
			m_ullPrevProcNonIdleTime = ullProcNonIdleTime;
		}
		m_dwLastRun = (ULONGLONG)GetTickCount();
		nCpuCopy = m_nCpuUsage;
	}
	::InterlockedDecrement(&m_lRunCount);
	return nCpuCopy;
}

BOOL SetPrivilege(HANDLE hProcess, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	HANDLE hToken;
	if(!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		ErrorMsg(TEXT("OpenProcessToken"));
		return FALSE;
	}
	LUID luid;
	if(!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
	{
		ErrorMsg(TEXT("LookupPrivilegeValue"));
		return FALSE;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = (bEnablePrivilege) ? SE_PRIVILEGE_ENABLED : FALSE;
	if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
	{
		ErrorMsg(TEXT("AdjustTokenPrivileges"));
		return FALSE;
	}
	return TRUE;
}

void ErrorMsg(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		LANG_USER_DEFAULT,
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

void EnumerateUsingDXGI( IDXGIFactory* pDXGIFactory )
{
	assert( pDXGIFactory != 0 );

	for( UINT index = 0; ; ++index )
	{
		IDXGIAdapter* pAdapter = nullptr;
		HRESULT hr = pDXGIFactory->EnumAdapters( index, &pAdapter );
		if( FAILED( hr ) ) // DXGIERR_NOT_FOUND is expected when the end of the list is hit
			break;

		DXGI_ADAPTER_DESC desc;
		memset( &desc, 0, sizeof( DXGI_ADAPTER_DESC ) );
		if( SUCCEEDED( pAdapter->GetDesc( &desc ) ) )
		{
			CString strMessage;
			strMessage.Format(_T("Adapter: [%u] %s\n"), index, desc.Description);
			TRACE(strMessage);

			for( UINT iOutput = 0; ; ++iOutput )
			{
				IDXGIOutput* pOutput = nullptr;
				hr = pAdapter->EnumOutputs( iOutput, &pOutput );
				if( FAILED( hr ) ) // DXGIERR_NOT_FOUND is expected when the end of the list is hit
					break;

				DXGI_OUTPUT_DESC outputDesc;
				memset( &outputDesc, 0, sizeof( DXGI_OUTPUT_DESC ) );
				if( SUCCEEDED( pOutput->GetDesc( &outputDesc ) ) )
				{
					//wprintf( L"hMonitor: 0x%0.8Ix\n", ( DWORD_PTR )outputDesc.Monitor );
					//wprintf( L"hMonitor Device Name: %s\n", outputDesc.DeviceName );
				}

				pOutput->Release();
			}

			strMessage.Format(_T("Dedicated Video Memory: %Iu MB\n \
								 Dedicated System Memory: %Iu MB\n \
								 Shared System Memory: %Iu MB\n"),
								 desc.DedicatedVideoMemory / 1024 / 1024, /*desc.DedicatedVideoMemory,*/
								 desc.DedicatedSystemMemory / 1024 / 1024, /*desc.DedicatedSystemMemory,*/
								 desc.SharedSystemMemory / 1024 / 1024/*, desc.SharedSystemMemory */);
			TRACE(strMessage);
		}

		pAdapter->Release();
	}
}

void GetDXGI()
{
	HINSTANCE hDXGI = LoadLibrary( _T("dxgi.dll"));

	typedef HRESULT ( WINAPI* LPCREATEDXGIFACTORY )( REFIID, void** );

	LPCREATEDXGIFACTORY pCreateDXGIFactory = nullptr;
	IDXGIFactory* pDXGIFactory = nullptr;

	// We prefer the use of DXGI 1.1  
	pCreateDXGIFactory = ( LPCREATEDXGIFACTORY )GetProcAddress( hDXGI, "CreateDXGIFactory1");

	if ( !pCreateDXGIFactory )
	{
		pCreateDXGIFactory = ( LPCREATEDXGIFACTORY )GetProcAddress( hDXGI, "CreateDXGIFactory");

		if ( !pCreateDXGIFactory )
		{
			FreeLibrary( hDXGI );
			TRACE(_T("ERROR: dxgi.dll missing entry-point\n"));
			return;
		}
	}

	HRESULT hr = pCreateDXGIFactory( __uuidof( IDXGIFactory ), ( LPVOID* )&pDXGIFactory );

	if ( SUCCEEDED(hr) )
	{
		EnumerateUsingDXGI( pDXGIFactory );
		pDXGIFactory->Release();
		return;
	}
	FreeLibrary( hDXGI );
} 

SIZE_T CalcWorkSetPrivate(HANDLE hProcess, SIZE_T pageSize)
{
	BOOL bRet = TRUE;
	PSAPI_WORKING_SET_INFORMATION workSetInfo;
	PBYTE pByte = NULL;
	PSAPI_WORKING_SET_BLOCK *pWorkSetBlock = workSetInfo.WorkingSetInfo;
	memset(&workSetInfo, 0, sizeof(workSetInfo));
	// 要求操作进程的权限：PROCESS_QUERY_INFORMATION and PROCESS_VM_READ
	// 第一次调用获取实际缓冲区大小
	bRet = ::QueryWorkingSet(hProcess, &workSetInfo, sizeof(workSetInfo));
	if(!bRet) // 调用失败
	{
		if(GetLastError() == ERROR_BAD_LENGTH) // 需要重新分配缓冲区
		{
			DWORD realSize = sizeof(workSetInfo.NumberOfEntries) 
				+ workSetInfo.NumberOfEntries*sizeof(PSAPI_WORKING_SET_BLOCK);
			try
			{
				pByte = new BYTE[realSize];
				memset(pByte, 0, realSize);
				pWorkSetBlock = (PSAPI_WORKING_SET_BLOCK *)(pByte + sizeof(workSetInfo.NumberOfEntries));
				// 重新获取
				if(!::QueryWorkingSet(hProcess, pByte, realSize))
				{
					delete[] pByte; // 清理内存
					return 0;
				}
			}
			catch(CMemoryException *e) // 分配内存失败
			{
				e->Delete();
				return 0;
			}
		}
		else // 其它错误，认为获取失败
			return 0;
	}
	SIZE_T workSetPrivate = 0;
	for (ULONG_PTR i = 0; i < workSetInfo.NumberOfEntries; ++i)
	{
		if(!pWorkSetBlock[i].Shared) // 如果不是共享页
			workSetPrivate += pageSize;
	}
	if(pByte)
		delete[] pByte;
	return workSetPrivate;
}

CString GetCpuInfoText(int * pValue/* = nullptr*/)
{
	DWORD curProcID = GetCurrentProcessId();
	static CpuUsage cpu(curProcID);
	CString temp;
	temp.Format(_T("CPU: %d%%"), cpu.GetUsageEx());
	if (pValue)
	{
		*pValue = cpu.GetUsageEx();
	}
	return temp;
}

CString GetMemInfoText(int * pValue/* = nullptr*/)
{
	DWORD curProcID = GetCurrentProcessId();
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	CString strInfo = _T("Memory get failed");

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, curProcID);
	if (NULL == hProcess)
		return strInfo;

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		//printf("\tPageFaultCount: %d\n", pmc.PageFaultCount);
		//printf("\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount);
		//printf("\tPeakWorkingSetSize: 0x%08X\n", pmc.PeakWorkingSetSize);
		//printf("\tWorkingSetSize: 0x%08X\n", pmc.WorkingSetSize);
		//printf("\tQuotaPeakPagedPoolUsage: 0x%08X\n", pmc.QuotaPeakPagedPoolUsage);
		//printf("\tQuotaPagedPoolUsage: 0x%08X\n", pmc.QuotaPagedPoolUsage);
		//printf("\tQuotaPeakNonPagedPoolUsage: 0x%08X\n", pmc.QuotaPeakNonPagedPoolUsage);
		//printf("\tQuotaNonPagedPoolUsage: 0x%08X\n", pmc.QuotaNonPagedPoolUsage);
		//printf("\tPagefileUsage: 0x%08X\n", pmc.PagefileUsage);
		//printf("\tPeakPagefileUsage: 0x%08X\n", pmc.PeakPagefileUsage);

		PERFORMANCE_INFORMATION performanceInfo;
		memset(&performanceInfo, 0, sizeof(performanceInfo));
		if (!::GetPerformanceInfo(&performanceInfo, sizeof(performanceInfo)))
			return strInfo;
		DWORD workSetPrivate = CalcWorkSetPrivate(hProcess, performanceInfo.PageSize);
		strInfo.Format(_T("Memory: %d MB"), workSetPrivate / (1024 * 1024));
		if (pValue)
		{
			*pValue = workSetPrivate / (1024 * 1024);
		}
	}
	CloseHandle(hProcess);
	return strInfo;
}
