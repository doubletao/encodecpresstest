#ifndef	_SD_MODULEEXPORTDEF_H_
#define	_SD_MODULEEXPORTDEF_H_

//模块特性定义为EXPORT

#undef	SD_EXT_CLASS
#undef	SD_EXT_API
#undef	SD_EXT_DATA

#ifdef _MSC_VER

#define SD_EXT_CLASS	__declspec(dllexport)			//AFX_CLASS_EXPORT
#define SD_EXT_API		__declspec(dllexport)			//AFX_API_EXPORT
#define SD_EXT_DATA		__declspec(dllexport)			//AFX_DATA_EXPORT

#else

#define SD_EXT_CLASS
#define SD_EXT_API
#define SD_EXT_DATA

#endif //_MSC_VER

#endif // _SD_MODULEEXPORTDEF_H_

