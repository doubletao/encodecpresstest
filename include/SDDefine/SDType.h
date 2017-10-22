/***************************************************************************
* SDType.H
*
* 公共头文件之一,EasyCode科技公司版权所有!
*
* 描述:		-跨平台编程环境下的数据类型定义头文件。
*
* 目标:		-这个头文件支持Window和Linux编程环境中的32位和64位编程。其依据C和C++的最基础数据类型定义。使用时请注意定义预定义变量。
*            建议在更高级的结构、类、函数等输入输出定义中仅使用这些数据类型定义,内部也仅可使用这些数据定义或最基础数据类型定义。
*
* Ver-0.9
*
****************************************************************************/
#ifndef _SD_TYPES_H_
#define _SD_TYPES_H_

#if (defined(_MSC_VER_) || defined(MSC_VER) || defined(_MSC_VER) || defined(__MSC_VER__))
	#ifndef _MSC_VER
		#define _MSC_VER
	#endif
#endif

#if (defined(_WIN32_) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
	#ifndef _WIN32
		#define _WIN32
	#endif
#endif

#if (defined(_WIN64_) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
	#ifndef _WIN64
		#define _WIN64
	#endif
#endif

#if (defined(_LINUX_VER_) || defined(LINUX_VER) || defined(_LINUX_VER) || defined(__LINUX_VER__))
#ifndef _LINUX_VER
#define _LINUX_VER
#endif
#endif

#if (defined(_LINUX32_) || defined(LINUX32) || defined(_LINUX32) || defined(__LINUX32__))
	#ifndef _LINUX32
		#define _LINUX32
	#endif
#endif

#if (defined(_LINUX64_) || defined(LINUX64) || defined(_LINUX64) || defined(__LINUX64__))
	#ifndef _LINUX64
		#define _LINUX64
	#endif
#endif

#if ((!defined(_MSC_VER)) && (defined(_WIN32) || defined(_WIN64)))
#define _MSC_VER
#endif

#if ((!defined(_LINUX_VER)) && (defined(_LINUX32) || defined(_LINUX64)))
	#define _LINUX_VER
#endif

#if ((!defined(_MSC_VER)) && (!defined(_LINUX_VER)))
	#define _MSC_VER
#endif

#if (defined(_MSC_VER) && defined(_LINUX_VER))
	#undef _LINUX_VER
#endif

#if (defined(_MSC_VER) && ((!defined(_WIN32)) && (!defined(_WIN64))))
	#define _WIN32
#endif

#if (defined(_LINUX_VER) && ((!defined(_LINUX32)) && (!defined(_LINUX64))))
	#define _LINUX64
#endif

#if (defined(_LINUX32) && defined(_LINUX64))
	#undef _LINUX64
#endif

//Add Mac os x platform
#if (defined(MAC_OSX) || defined(_MAC_OSX) || defined(_MAC_OSX_32) || defined(MAC_OSX_32) || defined(_MAC_OSX_32_))
	#ifndef _MAC_OSX_32
		#define _MAC_OSX_32
	#endif
#endif

#if (defined(_MAC_OSX_64) || defined(MAC_OSX_64) || defined(_MAC_OSX_64_))
	#ifdef _MAC_OSX_32
		#undef _MAC_OSX_32
	#endif
	#ifndef _MAC_OSX_64
		#define _MAC_OSX_64
	#endif
#endif

//Add Apple Iphone plat form
#if (defined(_APPLE_IOS) || defined(_APPLE__IOS_) || defined(APPLE_IOS))
	#ifndef _APPLE_IOS
		#define _APPLE_IOS
	#endif
	#ifdef _MAC_OSX_32
		#undef _MAC_OSX_32
	#endif
	#ifdef _MAC_OSX_64
		#undef _MAC_OSX_64
	#endif
	#define _IOS_VER
#endif

//
#if (defined(_MAC_OSX_32) || defined(_MAC_OSX_64) || defined(_APPLE_IOS))
	#ifndef _MAC_OSX_VER
		#define _MAC_OSX_VER
	#endif
	#ifdef _LINUX_VER
		#undef _LINUX_VER
	#endif
	#ifdef _LINUX64
		#undef _LINUX64
	#endif
	#ifdef _LINUX32
		#undef _LINUX32
	#endif
	#ifdef _MSC_VER
		#undef _MSC_VER
	#endif
	#ifdef _WIN64
		#undef _WIN64
	#endif
	#ifdef _WIN32
		#undef _WIN32
	#endif
#endif

#if (defined(_UNICODE_) || defined(UNICODE) || defined(_UNICODE) || defined(__UNICODE__))
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

//----------------------------------------------------------------------------------------------------------------
#define SD_CONST			const
#define SD_CALLBACK			__stdcall
#define SD_WINAPI			__stdcall

typedef	char				SD_INT8;
typedef	unsigned char		SD_UINT8;
typedef SD_INT8*			SD_PINT8;
typedef SD_UINT8*			SD_PUINT8;
typedef SD_INT8*			SD_LPINT8;
typedef SD_UINT8*			SD_LPUINT8;

typedef	short				SD_INT16;
typedef	unsigned short		SD_UINT16;
typedef SD_INT16*			SD_PINT16;
typedef SD_UINT16*			SD_PUINT16;
typedef SD_INT16*			SD_LPINT16;
typedef SD_UINT16*			SD_LPUINT16;

typedef	int					SD_INT32;
typedef	unsigned int		SD_UINT32;
typedef SD_INT32*			SD_PINT32;
typedef SD_UINT32*			SD_PUINT32;
typedef SD_INT32*			SD_LPINT32;
typedef SD_UINT32*			SD_LPUINT32;

typedef	long				SD_INT32L;
typedef	unsigned long		SD_UINT32L;
typedef SD_INT32L*			SD_PINT32L;
typedef SD_UINT32L*			SD_PUINT32L;
typedef SD_INT32L*			SD_LPINT32L;
typedef SD_UINT32L*			SD_LPUINT32L;

#ifdef _MSC_VER
typedef	__int64				SD_INT64;
typedef	unsigned __int64	SD_UINT64;
#else
typedef	long long			SD_INT64;
typedef	unsigned long long	SD_UINT64;
#endif
typedef SD_INT64*			SD_PINT64;
typedef SD_UINT64*			SD_PUINT64;
typedef SD_INT64*			SD_LPINT64;
typedef SD_UINT64*			SD_LPUINT64;

typedef	float				SD_FLOAT;
typedef SD_FLOAT*			SD_PFLOAT;
typedef SD_FLOAT*			SD_LPFLOAT;

typedef	double				SD_DOUBLE;
typedef SD_DOUBLE*			SD_PDOUBLE;
typedef SD_DOUBLE*			SD_LPDOUBLE;

typedef	void				SD_VOID;
typedef	SD_VOID*			SD_PVOID;
typedef	SD_VOID*			SD_LPVOID;
typedef	SD_CONST void*		SD_LPCVOID;
//----------------------------------------------------------------------------------------------------------------

//================================================================================================================
#if (defined(_WIN64) || defined(_LINUX64) || defined(_MAC_OSX_64)) 
	typedef int					SD_HALF_PTR;
	typedef SD_HALF_PTR*		SD_PHALF_PTR;

	typedef	SD_INT64			SD_INT_PTR; 
	typedef	SD_INT_PTR*			SD_PINT_PTR; 

	typedef	SD_UINT64			SD_UINT_PTR; 
	typedef	SD_UINT_PTR*		SD_PUINT_PTR; 
#else 
	typedef short				SD_HALF_PTR;
	typedef SD_HALF_PTR*		SD_PHALF_PTR;

	typedef int					SD_INT_PTR;
	typedef SD_INT_PTR*			SD_PINT_PTR;

	typedef	unsigned int		SD_UINT_PTR; 
	typedef	SD_UINT_PTR*		SD_PUINT_PTR; 
#endif

typedef	SD_INT32			SD_BOOL;
typedef	SD_BOOL*			SD_PBOOL;
typedef	SD_BOOL*			SD_LPBOOL;

typedef	SD_INT32			SD_HRESULT;
typedef	SD_HRESULT*			SD_PHRESULT;
typedef	SD_HRESULT*			SD_LPHRESULT;

typedef	SD_INT64			SD_LRESULT;
typedef	SD_LRESULT*			SD_PLRESULT;
typedef	SD_LRESULT*			SD_LPLRESULT;

typedef SD_PVOID			SD_HANDLE;
typedef SD_PVOID*			SD_PHANDLE;
typedef SD_PVOID*			SD_LPHANDLE;

typedef SD_HANDLE			SD_HINSTANCE;
typedef SD_HANDLE			SD_HGLOBAL;
typedef SD_HANDLE			SD_HMODULE;

typedef SD_UINT32			SD_FOURCC;
typedef SD_INT_PTR			SD_LPARAM;
typedef SD_UINT_PTR			SD_WPARAM;

typedef SD_UINT32			SD_COLORREF;
typedef SD_UINT32			SD_FRAMETIME;

typedef SD_UINT_PTR			SD_SIZE_T;
typedef SD_SIZE_T*			SD_PSIZE_T;
//================================================================================================================

//================================================================================================================
typedef SD_INT8				SD_CHAR;
typedef SD_CHAR*			SD_PCHAR;
typedef SD_CHAR*			SD_PSTR;
typedef SD_CHAR*			SD_LPSTR;

typedef wchar_t				SD_WCHAR;
typedef SD_WCHAR*			SD_PWCHAR;
typedef SD_WCHAR*			SD_PWSTR;
typedef SD_WCHAR*			SD_LPWSTR;

typedef SD_CONST SD_CHAR*	SD_PCSTR;
typedef SD_CONST SD_WCHAR*	SD_PCWSTR;
typedef SD_CONST SD_CHAR*	SD_LPCSTR;
typedef SD_CONST SD_WCHAR*	SD_LPCWSTR;

#ifdef _UNICODE
	typedef SD_WCHAR		SD_TCHAR;
	typedef SD_WCHAR*		SD_PTCHAR;
	typedef SD_LPWSTR		SD_PTSTR;
	typedef SD_LPWSTR		SD_LPTSTR;
	typedef SD_LPCWSTR		SD_PCTSTR; 
	typedef SD_LPCWSTR		SD_LPCTSTR; 

	typedef SD_WCHAR		SD_XCHAR;
	typedef SD_WCHAR*		SD_PXCHAR;
	typedef SD_LPWSTR		SD_PXSTR;
	typedef SD_LPWSTR		SD_LPXSTR;
	typedef SD_LPCWSTR		SD_PCXSTR; 
	typedef SD_LPCWSTR		SD_LPCXSTR; 

	typedef SD_CHAR			SD_YCHAR;
	typedef SD_CHAR*		SD_PYCHAR;
	typedef SD_LPSTR		SD_PYSTR;
	typedef SD_LPSTR		SD_LPYSTR;
	typedef SD_LPCSTR		SD_PCYSTR; 
	typedef SD_LPCSTR		SD_LPCYSTR; 
#else
	typedef SD_CHAR			SD_TCHAR;
	typedef SD_CHAR*		SD_PTCHAR;
	typedef SD_LPSTR		SD_PTSTR;
	typedef SD_LPSTR		SD_LPTSTR;
	typedef SD_LPCSTR		SD_PCTSTR; 
	typedef SD_LPCSTR		SD_LPCTSTR;

	typedef SD_CHAR			SD_XCHAR;
	typedef SD_CHAR*		SD_PXCHAR;
	typedef SD_LPSTR		SD_PXSTR;
	typedef SD_LPSTR		SD_LPXSTR;
	typedef SD_LPCSTR		SD_PCXSTR; 
	typedef SD_LPCSTR		SD_LPCXSTR;

	typedef SD_WCHAR		SD_YCHAR;
	typedef SD_WCHAR*		SD_PYCHAR;
	typedef SD_LPWSTR		SD_PYSTR;
	typedef SD_LPWSTR		SD_LPYSTR;
	typedef SD_LPCWSTR		SD_PCYSTR; 
	typedef SD_LPCWSTR		SD_LPCYSTR;
#endif
//================================================================================================================

#define SD_INLINE			inline

#define SD_IN
#define SD_OUT

#define SD_TRUE				1
#define SD_FALSE			0

#define SD_NULL				0

#define SD_OK				0
#define SD_NOERROR			0
#define SD_WARNING			1
#define SD_FAIL				-1
//================================================================================================================

#endif // _SD_TYPES_H_
