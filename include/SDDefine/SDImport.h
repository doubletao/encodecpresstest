#ifndef _SD_MODULEIMPORTDEF_H_
#define _SD_MODULEIMPORTDEF_H_

//模块特性定义为IMPORT

#undef	SD_EXT_CLASS
#undef	SD_EXT_API
#undef	SD_EXT_DATA

#ifdef _MSC_VER

#define SD_EXT_CLASS	__declspec(dllimport)			//AFX_CLASS_IMPORT
#define SD_EXT_API		__declspec(dllimport)			//AFX_API_IMPORT
#define SD_EXT_DATA		__declspec(dllimport)			//AFX_DATA_IMPORT

#else

#define SD_EXT_CLASS
#define SD_EXT_API
#define SD_EXT_DATA

#endif //_MSC_VER

#endif // _SD_MODULEIMPORTDEF_H_
