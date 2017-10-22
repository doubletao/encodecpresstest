/***************************************************************************
* SDDefine.H
*
* 公共头文件之一,EasyCode科技公司版权所有!
*
* 描述:		-作为共用的最底层头文件，定义了涵盖不同层次模块使用到的最重要的常量、结构、类、函数等。
*			 考虑了跨平台的应用和减少编译依赖性。
*
* 目标:		- 1.常用宏定义, 如 SD_TRUE/SD_FALSE, SD_MAKEWORD/SD_LOBYTE ......
*			  2.常用结构定义, 如 SD_RECT/SD_POINT ......
*             3.具体化数组类定义, 如 CSDINT8Array/CSDGuidArray/CSDStringArray ......
*			  4.字符串处理宏, 如 tstrlen/tstrcpy ......
*             5.与FTP访问、路经、文件定义相关的枚举、结构及相关函数
*			  6.与GUID相关的函数
*			  7.与数据库、和目志等相关的公共数据定义
*			  8.Window环境下的注册表读写函数
*
* Ver-0.9
*
****************************************************************************/
#ifndef _SD_SDDEFINE_H_
#define _SD_SDDEFINE_H_

#include "SDType.h"
#include "SDString.h"
#include "SDArray.h"

#ifdef _MSC_VER
#include "windows.h"
#endif
#include "time.h"

#pragma warning(push)
#pragma warning(disable:4244)

//================================================================================================================
//常用宏定义
//================================================================================================================
#define SD_MAX(a,b)				(((a) > (b)) ? (a) : (b))
#define SD_MIN(a,b)				(((a) < (b)) ? (a) : (b))

#define SD_MAKEWORD(a, b)		(((SD_UINT16)(a) & 0xff) | ((((SD_UINT16)(b) & 0xff) << 8) & 0xff00))
#define SD_MAKEDWORD(a, b)      (((SD_UINT32)(a) & 0xffff) | ((((SD_UINT32)(b) & 0xffff) << 16) & 0xffff0000))
#define SD_MAKEUINT64(a, b)     (((SD_UINT64)(a) & 0xffffffff) | ((((SD_UINT64)(b) & 0xffffffff) << 32) & 0xffffffff00000000))

#define SD_LOBYTE(w)			(((SD_UINT8)(w)))
#define SD_HIBYTE(w)			(((SD_UINT8)((SD_UINT16)(w) >> 8)))
#define SD_LOWORD(dw)			(((SD_UINT16)(dw)))
#define SD_HIWORD(dw)			(((SD_UINT16)((SD_UINT32)(dw) >> 16)))
#define SD_LODWORD(dw64)		(((SD_UINT32)(dw64)))
#define SD_HIDWORD(dw64)		(((SD_UINT32)((SD_UINT64)(dw64) >> 32)))

#define	SD_DoubleToInt32(x)	((x)>=0 ? (SD_INT32)((x)+0.5) : (SD_INT32)((x)-0.5))
#define	SD_DoubleToInt64(x)	((x)>=0 ? (SD_INT64)((x)+0.5) : (SD_INT64)((x)-0.5))

#define	SD_PAI					3.1415926
#define	SD_ARGB(a, r, g, b)		((SD_UINT32)((((SD_UINT32)(SD_UINT8)(a))<<24)|(((SD_UINT32)(SD_UINT8)(r))<<16)|((SD_UINT16)((SD_UINT8)(g))<<8)|((SD_UINT8)(b))))
//================================================================================================================

//================================================================================================================
//常用结构定义
//================================================================================================================
struct SD_RECT
{
	SD_INT32    left;
	SD_INT32    top;
	SD_INT32    right;
	SD_INT32    bottom;

	SD_RECT()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	};
	SD_RECT(SD_CONST SD_RECT &other)
	{
		*this = other;
	};

	SD_RECT& operator = (SD_CONST SD_RECT& other) 
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
		return *this;
	};

	friend SD_BOOL operator == (SD_CONST SD_RECT& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_FALSE;
		else
			return SD_TRUE;
	};

	friend SD_BOOL operator != (SD_CONST SD_RECT& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_TRUE;
		else
			return SD_FALSE;
	};

#ifdef _WINDEF_
	SD_RECT(SD_CONST RECT &other)
	{
		*this = other;
	};
	SD_RECT& operator = (SD_CONST RECT& other) 
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
		return *this;
	};
	SD_VOID	GetRECT(RECT &rc)
	{
		rc.left = left;
		rc.top = top;
		rc.right = right;
		rc.bottom = bottom;
	};
	SD_UINT32 Width()
	{
		return right - left;
	};
	SD_UINT32 Height()
	{
		return bottom - top;
	};
	friend SD_BOOL operator == (SD_CONST SD_RECT& rc1, SD_CONST RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST RECT& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_RECT& rc1, SD_CONST RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST RECT& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//_WINDEF_

#ifdef __ATLTYPES_H__
	SD_RECT(SD_CONST CRect &other)
	{
		*this = other;
	};
	SD_RECT& operator = (SD_CONST CRect& other) 
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
		return *this;
	};
	SD_VOID	GetCRect(CRect &rc)
	{
		rc.left = left;
		rc.top = top;
		rc.right = right;
		rc.bottom = bottom;
	};
	friend SD_BOOL operator == (SD_CONST SD_RECT& rc1, SD_CONST CRect& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST CRect& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_RECT& rc1, SD_CONST CRect& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST CRect& rc1, SD_CONST SD_RECT& rc2)
	{
		if (rc1.left != rc2.left || rc1.top != rc2.top || rc1.right != rc2.right || rc1.bottom != rc2.bottom)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//__ATLTYPES_H__
};
typedef SD_RECT *SD_PRECT;

struct SD_POINT
{
	SD_INT32  x;
	SD_INT32  y;

	SD_POINT()
	{
		x = 0;
		y = 0;
	};

	SD_POINT(SD_CONST SD_POINT &other)
	{
		*this = other;
	};

	SD_POINT& operator = (SD_CONST SD_POINT& other) 
	{
		x = other.x;
		y = other.y;
		return *this;
	};

	friend SD_BOOL operator == (SD_CONST SD_POINT& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_FALSE;
		else
			return SD_TRUE;
	};

	friend SD_BOOL operator != (SD_CONST SD_POINT& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_TRUE;
		else
			return SD_FALSE;
	};

#ifdef _WINDEF_
	SD_POINT(SD_CONST POINT &other)
	{
		*this = other;
	};
	SD_POINT& operator = (SD_CONST POINT& other) 
	{
		x = other.x;
		y = other.y;
		return *this;
	};
	SD_VOID	GetPOINT(POINT &p)
	{
		p.x = x;
		p.y = y;
	};
	friend SD_BOOL operator == (SD_CONST SD_POINT& pt1, SD_CONST POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST POINT& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_POINT& pt1, SD_CONST POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST POINT& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//_WINDEF_

#ifdef __ATLTYPES_H__
	SD_POINT(SD_CONST CPoint &other)
	{
		*this = other;
	};
	SD_POINT& operator = (SD_CONST CPoint& other) 
	{
		x = other.x;
		y = other.y;
		return *this;
	};
	SD_VOID	GetCPoint(CPoint &p)
	{
		p.x = x;
		p.y = y;
	};
	friend SD_BOOL operator == (SD_CONST SD_POINT& pt1, SD_CONST CPoint& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST CPoint& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_POINT& pt1, SD_CONST CPoint& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST CPoint& pt1, SD_CONST SD_POINT& pt2)
	{
		if (pt1.x != pt2.x || pt1.y != pt2.y)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//__ATLTYPES_H__
};
typedef SD_POINT *SD_PPOINT;

struct SD_SIZE
{
	SD_INT32        cx;
	SD_INT32        cy;

	SD_SIZE()
	{
		cx = 0;
		cy = 0;
	};

	SD_SIZE(SD_CONST SD_SIZE &other)
	{
		*this = other;
	};

	SD_SIZE& operator = (SD_CONST SD_SIZE& other) 
	{
		cx = other.cx;
		cy = other.cy;
		return *this;
	};

	friend SD_BOOL operator == (SD_CONST SD_SIZE& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_FALSE;
		else
			return SD_TRUE;
	};

	friend SD_BOOL operator != (SD_CONST SD_SIZE& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_TRUE;
		else
			return SD_FALSE;
	};

#ifdef _WINDEF_
	SD_SIZE(SD_CONST SIZE &other)
	{
		*this = other;
	};
	SD_SIZE& operator = (SD_CONST SIZE& other) 
	{
		cx = other.cx;
		cy = other.cy;
		return *this;
	};
	SD_VOID	GetSIZE(SIZE &s)
	{
		s.cx = cx;
		s.cy = cy;
	};
	friend SD_BOOL operator == (SD_CONST SD_SIZE& s1, SD_CONST SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST SIZE& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_SIZE& s1, SD_CONST SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST SIZE& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//_WINDEF_

#ifdef __ATLTYPES_H__
	SD_SIZE(SD_CONST CSize &other)
	{
		*this = other;
	};
	SD_SIZE& operator = (SD_CONST CSize& other) 
	{
		cx = other.cx;
		cy = other.cy;
		return *this;
	};
	SD_VOID	GetCSize(CSize &s)
	{
		s.cx = cx;
		s.cy = cy;
	};
	friend SD_BOOL operator == (SD_CONST SD_SIZE& s1, SD_CONST CSize& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator == (SD_CONST CSize& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST SD_SIZE& s1, SD_CONST CSize& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST CSize& s1, SD_CONST SD_SIZE& s2)
	{
		if (s1.cx != s2.cx || s1.cy != s2.cy)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
#endif	//__ATLTYPES_H__
};
typedef SD_SIZE *SD_PSIZE;

struct SD_GUID 
{  
	SD_UINT32	Data1;  
	SD_UINT16	Data2;  
	SD_UINT16	Data3;  
	SD_UINT8	Data4[8];

	SD_GUID()
	{
		Data1 = 0;
		Data2 = 0;
		Data3 = 0;
		memset(Data4, 0, 8);
	};

	SD_GUID(SD_CONST SD_GUID &other)
	{
		*this = other;
	};

	SD_GUID& operator = (SD_CONST SD_GUID& other) 
	{
		Data1 = other.Data1;
		Data2 = other.Data2;
		Data3 = other.Data3;
		memcpy(Data4, other.Data4, 8);
		return *this;
	};

	friend SD_BOOL operator == (SD_CONST SD_GUID& id1, SD_CONST SD_GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_TRUE;
		else
			return SD_FALSE;
	};

	friend SD_BOOL operator != (SD_CONST SD_GUID& id1, SD_CONST SD_GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_FALSE;
		else
			return SD_TRUE;
	};

	SD_BOOL	IsEqualNULLGuid()
	{
		if (Data1 != 0 || Data2 != 0 || Data3 != 0)
			return SD_FALSE;
		else
		{
			for (SD_INT32 i=0; i<8; i++)
			{
				if (Data4[i] != 0)
					return SD_FALSE;
			}
		}
		return SD_TRUE;
	};

#ifdef GUID_DEFINED
	SD_GUID(SD_CONST GUID &other)
	{
		*this = other;
	};
	SD_GUID& operator = (SD_CONST GUID& other) 
	{
		Data1 = other.Data1;
		Data2 = other.Data2;
		Data3 = other.Data3;
		memcpy(Data4, other.Data4, 8);
		return *this;
	};
	SD_VOID	GetGuid(GUID &id)
	{
		id.Data1 = Data1;
		id.Data2 = Data2;
		id.Data3 = Data3;
		memcpy(id.Data4, Data4, 8);
	};
	friend SD_BOOL operator == (SD_CONST SD_GUID& id1, SD_CONST GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator == (SD_CONST GUID& id1, SD_CONST SD_GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_TRUE;
		else
			return SD_FALSE;
	};
	friend SD_BOOL operator != (SD_CONST SD_GUID& id1, SD_CONST GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
	friend SD_BOOL operator != (SD_CONST GUID& id1, SD_CONST SD_GUID& id2)
	{
		if (memcmp(&id1, &id2, sizeof(SD_GUID)) == 0)
			return SD_FALSE;
		else
			return SD_TRUE;
	};
#endif	//GUID_DEFINED
};
typedef SD_GUID *SD_PGUID;

//================================================================================================================

//================================================================================================================
//具体化数组类定义
//================================================================================================================
typedef CSDArray<SD_INT8, SD_INT8>				CSDINT8Array;
typedef CSDArray<SD_UINT8, SD_UINT8>			CSDUINT8Array;
typedef CSDArray<SD_INT16, SD_INT16>			CSDINT16Array;
typedef CSDArray<SD_UINT16, SD_UINT16>			CSDUINT16Array;
typedef CSDArray<SD_INT32, SD_INT32>			CSDINT32Array;
typedef CSDArray<SD_UINT32, SD_UINT32>			CSDUINT32Array;
typedef CSDArray<SD_INT64, SD_INT64>			CSDINT64Array;
typedef CSDArray<SD_UINT64, SD_UINT64>			CSDUINT64Array;
typedef CSDArray<SD_FLOAT, SD_FLOAT>			CSDFloatArray;
typedef CSDArray<SD_DOUBLE, SD_DOUBLE>			CSDDoubleArray;
typedef CSDArray<SD_PVOID, SD_PVOID>			CSDPtrArray;

typedef CSDArray<SD_TCHAR, SD_TCHAR>			CSDTCharArray;
typedef CSDArray<SD_HALF_PTR, SD_HALF_PTR>		CSDHalfPtrArray;
typedef CSDArray<SD_INT_PTR, SD_INT_PTR>		CSDINTPtrArray;
typedef CSDArray<SD_UINT_PTR, SD_UINT_PTR>		CSDUINTPtrArray;

typedef CSDArray<SD_POINT, SD_POINT&>			CSDPointArray;
typedef CSDArray<SD_SIZE, SD_SIZE&>				CSDSizeArray;
typedef CSDArray<SD_RECT, SD_RECT&>				CSDRectArray;
typedef CSDArray<SD_GUID, SD_GUID&>				CSDGuidArray;
typedef CSDArray<CSDString, CSDString&>			CSDStringArray;

#ifdef __AFXCOLL_H__
#if 0
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDUINT8Array &arrayDest, SD_CONST CByteArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CByteArray &arrayDest, SD_CONST CSDUINT8Array &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDUINT16Array &arrayDest, SD_CONST CWordArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CWordArray &arrayDest, SD_CONST CSDUINT16Array &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDUINT32Array &arrayDest, SD_CONST CdwordArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CdwordArray &arrayDest, SD_CONST CSDUINT32Array &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDPtrArray &arrayDest, SD_CONST CPtrArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CPtrArray &arrayDest, SD_CONST CSDPtrArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add(arraySrc.GetAt(i));
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDStringArray &arrayDest, SD_CONST CSDStringArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++) 
	{
		CSDString	str = CSDString((SD_LPCTSTR)(arraySrc.GetAt(i)));
		arrayDest.Add(str);
	}
};
SD_INLINE SD_VOID	SDArrayCopyAppend(CSDStringArray &arrayDest, SD_CONST CSDStringArray &arraySrc, SD_BOOL bIsCopy=SD_TRUE)
{
	if (bIsCopy)
		arrayDest.RemoveAll();
	SD_INT_PTR	size = (SD_INT_PTR)(arraySrc.GetSize());
	for (SD_INT_PTR i=0; i<size; i++)
		arrayDest.Add((SD_LPCTSTR)(arraySrc.GetAt(i)));
};
#endif
#endif	//__AFXCOLL_H__
//================================================================================================================

//================================================================================================================
//字符串处理宏
//================================================================================================================
#ifdef _MSC_VER
	#ifdef _UNICODE
		#define	tstrlen		wcslen
		#define	tstrcat		wcscat
		#define	tstrchr		wcschr
		#define	tstrcmp		wcscmp
		#define	tstrcpy		wcscpy
		#define	tstrcspn	wcscspn
		#define	tstrncat	wcsncat
		#define	tstrncmp	wcsncmp
		#define	tstrncpy	wcsncpy
		#define	tstrpbrk	wcspbrk
		#define	tstrrchr	wcsrchr
		#define	tstrspn		wcsspn
		#define	tstrstr		wcsstr
		#define	tstrtok		wcstok
		#define	_tstrdup	_wcsdup
		#define	_tstricmp	_wcsicmp
		#define	_tstrnicmp	_wcsnicmp
		#define	_tstrnset	_wcsnset
		#define	_tstrrev	_wcsrev
		#define	_tstrset	_wcsset
		#define	_tstrlwr	_wcslwr
		#define	_tstrupr	_wcsupr
		#define	tstrxfrm	wcsxfrm
		#define	tstrcoll	wcscoll
		#define	_tstricoll	_wcsicoll
		#define	_tstrncoll	_wcsncoll
		#define	_tstrnicoll	_wcsnicoll
		#define	tstrdup		wcsdup
		#define	tstricmp	wcsicmp
		#define	tstrnicmp	wcsnicmp
		#define	tstrnset	wcsnset
		#define	tstrrev		wcsrev
		#define	tstrset		wcsset
		#define	tstrlwr		wcslwr
		#define	tstrupr		wcsupr
		#define	tstricoll	wcsicoll

		#define	tfopen		_wfopen
		#define stprintf	swprintf
	#else /* UNICODE */
		#define	tstrlen		strlen
		#define	tstrcmp		strcmp
		#define	tstrcat		strcat
		#define	tstrcpy		strcpy
		#define	_tstrset	_strset
		#define	tstrupr		strupr
		#define	tstrchr		strchr
		#define	_tstrcmpi	_strcmpi
		#define	_tstricmp	_stricmp
		#define	tstrcoll	strcoll
		#define	_stricoll	_stricoll
		#define	_strncoll	_strncoll
		#define	_strnicoll	_strnicoll
		#define	tstrcspn	strcspn
		#define	_tstrdup	_strdup
		#define	_tstrerror	_strerror
		#define	tstrerror	strerror
		#define	_tstrlwr	_strlwr
		#define	tstrncat	strncat
		#define	tstrncmp	strncmp
		#define	tstrnicmp	strnicmp
		#define	tstrncpy	strncpy
		#define	_tstrnset	_strnset
		#define	tstrpbrk	strpbrk
		#define	tstrrchr	strrchr
		#define	_tstrrev	_strrev
		#define	tstrspn		strspn
		#define	tstrstr		strstr
		#define	tstrtok		strtok
		#define	_tstrupr	_strupr
		#define	tstrxfrm	strxfrm 
		#define	tc2pstr		c2pstr
		#define	tp2cstr		p2cstr
		#define	tstrupr		strupr
		#define	tstrrev		strrev
		#define	tstrnset	strnset
		#define	_tstrnicmp	_strnicmp
		#define	tstrlwr		strlwr
		#define	strdup		strdup
		#define	tstricmp	stricmp
		#define	tstrcmpi	strcmpi

		#define	tfopen		fopen
		#define stprintf	sprintf
	#endif /* UNICODE */
#else	/*_MSC_VER*/
	#if defined (_UNICODE) || defined (UNICODE)
		#define	tstrlen		wcslen
		#define	tstrcat		wcscat
		#define	tstrchr		wcschr
		#define	tstrcmp		wcscmp
		#define	tstrcpy		wcscpy
		#define	tstrcspn	wcscspn
		#define	tstrncat	wcsncat
		#define	tstrncmp	wcsncmp
		#define	tstrncpy	wcsncpy
		#define	tstrpbrk	wcspbrk
		#define	tstrrchr	wcsrchr
		#define	tstrspn		wcsspn
		#define	tstrstr		wcsstr
		#define	tstrtok		wcstok
		#define	_tstrdup	_wcsdup
		#define	_tstricmp	_wcsicmp
		#define	_tstrnicmp	_wcsnicmp
		#define	_tstrnset	_wcsnset
		#define	_tstrrev	_wcsrev
		#define	_tstrset	_wcsset
		#define	_tstrlwr	_wcslwr
		#define	_tstrupr	_wcsupr
		#define	tstrxfrm	wcsxfrm
		#define	tstrcoll	wcscoll
		#define	_tstricoll	_wcsicoll
		#define	_tstrncoll	_wcsncoll
		#define	_tstrnicoll	_wcsnicoll
		#define	tstrdup		wcsdup
		#define	tstricmp	wcsicmp
		#define	tstrnicmp	wcsnicmp
		#define	tstrnset	wcsnset
		#define	tstrrev		wcsrev
		#define	tstrset		wcsset
		#define	tstrlwr		wcslwr
		#define	tstrupr		wcsupr
		#define	tstricoll	wcsicoll
		#define	tfopen		_wfopen
		#define stprintf	swprintf
	#else /* UNICODE */
		#define	tstrlen		strlen
		#define	tstrcmp		strcmp
		#define	tstrcat		strcat
		#define	tstrcpy		strcpy
		#define	_tstrset	_strset
		#define	tstrupr		strupr
		#define	tstrchr		strchr
		#define	_tstrcmpi	_strcmpi
		#define	_tstricmp	_stricmp
		#define	tstrcoll	strcoll
		#define	_stricoll	_stricoll
		#define	_strncoll	_strncoll
		#define	_strnicoll	_strnicoll
		#define	tstrcspn	strcspn
		#define	_tstrdup	_strdup
		#define	_tstrerror	_strerror
		#define	tstrerror	strerror
		#define	_tstrlwr	_strlwr
		#define	tstrncat	strncat
		#define	tstrncmp	strncmp
		#define	tstrnicmp	strnicmp
		#define	tstrncpy	strncpy
		#define	_tstrnset	_strnset
		#define	tstrpbrk	strpbrk
		#define	tstrrchr	strrchr
		#define	_tstrrev	_strrev
		#define	tstrspn		strspn
		#define	tstrstr		strstr
		#define	tstrtok		strtok
		#define	_tstrupr	_strupr
		#define	tstrxfrm	strxfrm 
		#define	tc2pstr		c2pstr
		#define	tp2cstr		p2cstr
		#define	tstrupr		strupr
		#define	tstrrev		strrev
		#define	tstrnset	strnset
		#define	_tstrnicmp	_strnicmp
		#define	tstrlwr		strlwr
		#define	strdup		strdup
		#define	tstricmp	stricmp
		#define	tstrcmpi	strcmpi
		#define	tfopen		fopen
		#define stprintf	sprintf
	#endif /*UNICODE*/
#endif /*_MSC_VER*/
//=======================================================================================

//=======================================================================================
//与FTP访问、路经、文件定义相关的枚举、结构及相关函数
//=======================================================================================
//	定义枚举:
//		SD_FTPSERVER_TYPE;	//FTP服务器类型
//	定义结构: 
//		SDFTPConnectInfo;	SDFTPConnectInfoArray;	//FTP连接数据结构信息
//		SDFTPServerInfo;	SDFTPServerInfoArray;		//FTP访问数据结构信息
//		SDPathInfo;	SDPathInfoArray;				//含FTP访问的路经信息结构
//		SDFileInfo;	SDFileInfoArray;				//含FTP路经访问的文件信息结构
//	定义函数:
//		CSDString	GetFTPServerTypeString(SD_FTPSERVER_TYPE enumFTPServerType);	//得到FTP服务器类型定义名称
//		SD_FTPSERVER_TYPE GetFTPServerType(SD_LPCTSTR lpszFTPServerTypeString);	//从定义名称得到FTP服务器类型
//		SD_BOOL	IsIPAddressStrValid(SD_LPCTSTR lpszIPAddress);	//判断IP地址字符串的合法性
//		CSDString	GetFTPServerString(SDFTPServerInfo *pFTPServerInfo);	//得到FTP访问数据结构字符串
//		SD_BOOL GetFTPServerInfo(SD_LPCTSTR lpszFTPServerString, SDFTPServerInfo *pFTPServerInfo);//从字符串得到FTP访问数据结构
//		CSDString	GetSDPathString(SDPathInfo *pSDPathInfo);			//得到含FTP访问的路经信息数据结构字符串
//		SD_BOOL GetSDPathInfo(SD_LPCTSTR lpszSDPathString, SDPathInfo *pSDPathInfo);//从字符串得到含FTP访问的路经信息结构
//		CSDString	GetSDFileString(SDFileInfo *pSDFileInfo);			//得到含FTP路经访问的文件信息数据结构字符串
//		SD_BOOL GetSDFileInfo(SD_LPCTSTR lpszSDFileString, SDFileInfo *pSDFileInfo);//从字符串得到含FTP路经访问的文件信息结构
//=======================================================================================
enum SD_FTPSERVER_TYPE	//FTP服务器类型
{
	SDFTPSERVERTYPE_UNKNOW			=	-1,
	SDFTPSERVERTYPE_STANDARD		=	0,
	SDFTPSERVERTYPE_MAV70			=	1,
	SDFTPSERVERTYPE_PROFILE			=	2,
	SDFTPSERVERTYPE_MSS				=	3,
	SDFTPSERVERTYPE_SEACHANGE		=	4,
	SDFTPSERVERTYPE_EVTR			=	5,
	SDFTPSERVERTYPE_MSeries			=	6,
	SDFTPSERVERTYPE_VSR2000			=	7,
	SDFTPSERVERTYPE_LEITCH			=	8,
	SDFTPSERVERTYPE_XDCAM			=	9,
	SDFTPSERVERTYPE_P2  			=	10,

	SDFTPSERVERTYPE_FTP			=	51,
	SDFTPSERVERTYPE_UDP			=	52,
	SDFTPSERVERTYPE_TS			=	53,

	SDFTPSERVERTYPE_Reserve  		=	99,
};

//得到FTP服务器类型定义名称
SD_INLINE CSDString	GetFTPServerTypeString(SD_FTPSERVER_TYPE enumFTPServerType)
{
	CSDString	strFTPServerTypeString = _T("Unknow");
	switch(enumFTPServerType)
	{
		case SDFTPSERVERTYPE_STANDARD:
			strFTPServerTypeString = _T("NORMAL");
			break;
		case SDFTPSERVERTYPE_MAV70:
			strFTPServerTypeString = _T("MAV70");
			break;
		case SDFTPSERVERTYPE_PROFILE:
			strFTPServerTypeString = _T("PROFILE");
			break;
		case SDFTPSERVERTYPE_MSS:
			strFTPServerTypeString = _T("MSS");
			break;
		case SDFTPSERVERTYPE_SEACHANGE:
			strFTPServerTypeString = _T("SEACHANGE");
			break;
		case SDFTPSERVERTYPE_EVTR:
			strFTPServerTypeString = _T("E_VTR");
			break;
		case SDFTPSERVERTYPE_MSeries:
			strFTPServerTypeString = _T("MSeries");
			break;
		case SDFTPSERVERTYPE_VSR2000:
			strFTPServerTypeString = _T("VSR2000");
			break;
		case SDFTPSERVERTYPE_LEITCH:
			strFTPServerTypeString = _T("LEITCH");
			break;
		case SDFTPSERVERTYPE_XDCAM:
			strFTPServerTypeString = _T("XDCAM");
			break;
		case SDFTPSERVERTYPE_P2:
			strFTPServerTypeString = _T("P2");
			break;
		case SDFTPSERVERTYPE_FTP:
			strFTPServerTypeString = _T("FTP");
			break;
		case SDFTPSERVERTYPE_UDP:
			strFTPServerTypeString = _T("UDP");
			break;
		case SDFTPSERVERTYPE_TS:
			strFTPServerTypeString = _T("TS");
			break;
	};
	return strFTPServerTypeString;
};

//从定义名称得到FTP服务器类型
SD_INLINE SD_FTPSERVER_TYPE GetFTPServerType(SD_LPCTSTR lpszFTPServerTypeString)
{
	if (lpszFTPServerTypeString == SD_NULL)
		return SDFTPSERVERTYPE_STANDARD;
	CSDString	strFTPServerTypeString = CSDString(lpszFTPServerTypeString);
	if (strFTPServerTypeString.CompareNoCase(_T("NORMAL")) == 0)
		return SDFTPSERVERTYPE_STANDARD;
	else if (strFTPServerTypeString.CompareNoCase(_T("MAV70")) == 0)
		return SDFTPSERVERTYPE_MAV70;
	else if (strFTPServerTypeString.CompareNoCase(_T("PROFILE")) == 0)
		return SDFTPSERVERTYPE_PROFILE;
	else if (strFTPServerTypeString.CompareNoCase(_T("MSS")) == 0)
		return SDFTPSERVERTYPE_MSS;
	else if (strFTPServerTypeString.CompareNoCase(_T("SEACHANGE")) == 0)
		return SDFTPSERVERTYPE_SEACHANGE;
	else if (strFTPServerTypeString.CompareNoCase(_T("E_VTR")) == 0)
		return SDFTPSERVERTYPE_EVTR;
	else if (strFTPServerTypeString.CompareNoCase(_T("MSeries")) == 0)
		return SDFTPSERVERTYPE_MSeries;
	else if (strFTPServerTypeString.CompareNoCase(_T("VSR2000")) == 0)
		return SDFTPSERVERTYPE_VSR2000;
	else if (strFTPServerTypeString.CompareNoCase(_T("LEITCH")) == 0)
		return SDFTPSERVERTYPE_LEITCH;
	else if (strFTPServerTypeString.CompareNoCase(_T("XDCAM")) == 0)
		return SDFTPSERVERTYPE_XDCAM;
	else if (strFTPServerTypeString.CompareNoCase(_T("P2")) == 0)
		return SDFTPSERVERTYPE_P2;
	else if (strFTPServerTypeString.CompareNoCase(_T("SDFTP")) == 0)
		return SDFTPSERVERTYPE_FTP;
	else if (strFTPServerTypeString.CompareNoCase(_T("UDP")) == 0)
		return SDFTPSERVERTYPE_UDP;
	else if (strFTPServerTypeString.CompareNoCase(_T("TS")) == 0)
		return SDFTPSERVERTYPE_TS;
	else
		return SDFTPSERVERTYPE_STANDARD;
};

//判断IP地址字符串的合法性
SD_INLINE	SD_BOOL	IsIPAddressStrValid(SD_LPCTSTR lpszIPAddress)
{
	if (lpszIPAddress == SD_NULL)
		return SD_FALSE;
	CSDString strIPAddress = CSDString(lpszIPAddress);
	strIPAddress.TrimRight();
	strIPAddress.TrimLeft();
	SD_INT32	len = strIPAddress.GetLength();
	SD_INT32	nValue = 0, nTimes = 1, nCount = 0;
	SD_INT32	i = len-1; 
	if (len < 7 || strIPAddress[i] < '0' || strIPAddress[i] > '9')
		return SD_FALSE;
	while (i >= 0) 
	{
		if (strIPAddress[i] >= '0' && strIPAddress[i] <= '9') 
		{
			nValue += (strIPAddress[i]-'0')*nTimes;
			nTimes *= 10;
			i --;
		} 
		else if (strIPAddress[i] == '.') 
		{
			if (nValue < 0 || nValue > 255)
				return SD_FALSE;
			nCount ++;
			nValue = 0;
			nTimes = 1;
			i --;
		} 
		else
			return SD_FALSE;
	}
	if (nCount != 3 || nValue < 0 || nValue > 255)
		return SD_FALSE;
	else
		return SD_TRUE;
};


struct SDFTPConnectInfo	//FTP连接数据结构信息
{
	CSDString	strFTPServerIP;
	SD_UINT32	dwFTPServerPort;

	SDFTPConnectInfo()
	{
		strFTPServerIP = _T("");
		dwFTPServerPort = 21;
	};

	SDFTPConnectInfo(SD_CONST SDFTPConnectInfo & other) 
	{ 
		*this = other; 
	};	

	SDFTPConnectInfo& operator = (SD_CONST SDFTPConnectInfo& other)
	{
		strFTPServerIP = other.strFTPServerIP;
		dwFTPServerPort = other.dwFTPServerPort;
		return *this;
	};
};
typedef CSDArray<SDFTPConnectInfo, SDFTPConnectInfo&> SDFTPConnectInfoArray;

struct SDFTPServerInfo		//FTP访问数据结构信息
{
	SD_FTPSERVER_TYPE	enumFTPServerType;
	CSDString			strFTPServerIP;
	SD_UINT32			dwFTPServerPort;
	CSDString			strFTPServerUserName;
	CSDString			strFTPServerPassWord;

	SDFTPServerInfo()
	{
		enumFTPServerType = SDFTPSERVERTYPE_STANDARD;
		strFTPServerIP = _T("");
		strFTPServerUserName = _T("");
		strFTPServerPassWord = _T("");
		dwFTPServerPort = 21;
	};

	SDFTPServerInfo(SD_CONST SDFTPServerInfo & other) 
	{ 
		*this = other; 
	};	

	SDFTPServerInfo& operator = (SD_CONST SDFTPServerInfo& other)
	{
		enumFTPServerType = other.enumFTPServerType;
		strFTPServerIP = other.strFTPServerIP;
		strFTPServerUserName = other.strFTPServerUserName;
		strFTPServerPassWord = other.strFTPServerPassWord;
		dwFTPServerPort = other.dwFTPServerPort;
		return *this;
	};
};
typedef CSDArray<SDFTPServerInfo, SDFTPServerInfo&> SDFTPServerInfoArray;

//得到FTP访问数据结构字符串
SD_INLINE	CSDString	GetFTPServerString(SDFTPServerInfo *pFTPServerInfo)
{
	CSDString	strFTPServerString = _T("");
	if (pFTPServerInfo) 
	{
		CSDString	strFTPServerTypeString = GetFTPServerTypeString(pFTPServerInfo->enumFTPServerType);
		strFTPServerString.Format(_T("%s*%s*%s*%s*%d"), (SD_LPCTSTR)strFTPServerTypeString, (SD_LPCTSTR)pFTPServerInfo->strFTPServerIP, (SD_LPCTSTR)pFTPServerInfo->strFTPServerUserName, (SD_LPCTSTR)pFTPServerInfo->strFTPServerPassWord, pFTPServerInfo->dwFTPServerPort);
	}
	return strFTPServerString;
};

//从字符串得到FTP访问数据结构
SD_INLINE	SD_BOOL GetFTPServerInfo(SD_LPCTSTR lpszFTPServerString, SDFTPServerInfo *pFTPServerInfo)
{
	if (lpszFTPServerString == SD_NULL || pFTPServerInfo == SD_NULL)
		return SD_FALSE;
	CSDString strFTPServerString = CSDString(lpszFTPServerString);
	SD_INT32	nIndex1, nIndex2, nIndex3, nIndex4;
	nIndex1 = strFTPServerString.Find(_T("*"));
	nIndex2 = strFTPServerString.Find(_T("*"), nIndex1+1);
	nIndex3 = strFTPServerString.Find(_T("*"), nIndex2+1);
	nIndex4 = strFTPServerString.Find(_T("*"), nIndex3+1);
	if (nIndex1 < 1 || nIndex2 < nIndex1+1 || nIndex3 < nIndex2+1 || nIndex4 < nIndex3 || nIndex4 >= strFTPServerString.GetLength()-1)
		return SD_FALSE;
	pFTPServerInfo->enumFTPServerType = GetFTPServerType(strFTPServerString.Left(nIndex1));
	pFTPServerInfo->strFTPServerIP = strFTPServerString.Mid(nIndex1+1, nIndex2-nIndex1-1);
	if (IsIPAddressStrValid(pFTPServerInfo->strFTPServerIP) == SD_FALSE)
		return SD_FALSE;
	pFTPServerInfo->strFTPServerUserName = strFTPServerString.Mid(nIndex2+1, nIndex3-nIndex2-1);
	if (nIndex4-nIndex3-1 == 0)
		pFTPServerInfo->strFTPServerPassWord = _T("");
	else
		pFTPServerInfo->strFTPServerPassWord = strFTPServerString.Mid(nIndex3+1, nIndex4-nIndex3-1);
	CSDString	strTemp = strFTPServerString.Right(strFTPServerString.GetLength()-nIndex4-1);
	strTemp.TrimLeft();
	strTemp.TrimRight();
	SD_INT32	len = strTemp.GetLength();
	SD_INT32	nTimes = 1;
	pFTPServerInfo->dwFTPServerPort = 0;
	while (len >= 1 && strTemp[len-1] >= '0' && strTemp[len-1] <= '9') 
	{
		pFTPServerInfo->dwFTPServerPort += (strTemp[len-1]-'0')*nTimes;
		nTimes *= 10;
		len --;
	}
	return SD_TRUE;
};

struct SDPathInfo		//含FTP访问的路经信息结构
{
	SD_BOOL					bIsFTPFileType;
	CSDString				strFilePath;
	SDFTPServerInfo		sFTPServerInfo;

	SDPathInfo()
	{
		bIsFTPFileType = SD_FALSE;
		strFilePath = _T("");
	};

	SDPathInfo(SD_CONST SDPathInfo & other) 
	{ 
		*this = other; 
	};	

	SDPathInfo& operator = (SD_CONST SDPathInfo& other)
	{
		bIsFTPFileType = other.bIsFTPFileType;
		strFilePath = other.strFilePath;
		sFTPServerInfo = other.sFTPServerInfo;
		return *this;
	};
};
typedef CSDArray<SDPathInfo, SDPathInfo&> SDPathInfoArray;

//得到含FTP访问的路经信息数据结构字符串
SD_INLINE	CSDString	GetSDPathString(SDPathInfo *pSDPathInfo)
{
	CSDString	strSDPathString = _T("");
	if (pSDPathInfo) 
	{
		if (pSDPathInfo->bIsFTPFileType)
			strSDPathString.Format(_T("FTPINFO*%s*%s"), (SD_LPCTSTR)GetFTPServerString(&(pSDPathInfo->sFTPServerInfo)), (SD_LPCTSTR)pSDPathInfo->strFilePath);
		else
			strSDPathString = pSDPathInfo->strFilePath;
	}
	return strSDPathString;
};

//从字符串得到含FTP访问的路经信息结构
SD_INLINE	SD_BOOL GetSDPathInfo(SD_LPCTSTR lpszSDPathString, SDPathInfo *pSDPathInfo)
{
	if (lpszSDPathString == SD_NULL || pSDPathInfo == SD_NULL)
		return SD_FALSE;
	CSDString	strSDPathString = CSDString(lpszSDPathString);
	CSDString	strHeadFlag = strSDPathString.Left(8);
	if (strHeadFlag.CompareNoCase(_T("FTPINFO*")) != 0) 
	{
		pSDPathInfo->bIsFTPFileType = SD_FALSE;
		pSDPathInfo->strFilePath = strSDPathString;
		return SD_TRUE;
	} 
	else 
	{
		pSDPathInfo->bIsFTPFileType = SD_TRUE;
		CSDString	strTemp = strSDPathString.Right(strSDPathString.GetLength()-8);
		SD_INT32	nIndex = strTemp.ReverseFind('*');
		if (nIndex <= 7)
			return SD_FALSE;
		pSDPathInfo->strFilePath = strTemp.Right(strTemp.GetLength()-nIndex-1);
		return GetFTPServerInfo(strTemp.Left(nIndex), &(pSDPathInfo->sFTPServerInfo));
	}
};

struct SDFileInfo		//含FTP路经访问的文件信息结构
{
	SD_BOOL				bIsFTPFileType;
	CSDString			strFilePath;
	SDFTPServerInfo	sFTPServerInfo;
	CSDString			strFileName;				// 源文件名

	SDFileInfo()
	{
		bIsFTPFileType = SD_FALSE;
		strFilePath = _T("");
		strFileName = _T("");
	};

	SDFileInfo(SD_CONST SDFileInfo & other) 
	{ 
		*this = other; 
	};	

	SDFileInfo& operator = (SD_CONST SDFileInfo& other)
	{
		bIsFTPFileType = other.bIsFTPFileType;
		strFilePath = other.strFilePath;
		sFTPServerInfo = other.sFTPServerInfo;
		strFileName = other.strFileName;
		return *this;
	};
};
typedef CSDArray<SDFileInfo, SDFileInfo&> SDFileInfoArray;

//得到含FTP路经访问的文件信息数据结构字符串
SD_INLINE	CSDString	GetSDFileString(SDFileInfo *pSDFileInfo)
{
	CSDString	strSDFileString = _T("");
	if (pSDFileInfo) {
		pSDFileInfo->strFilePath.TrimLeft();
		pSDFileInfo->strFilePath.TrimRight();
		if (pSDFileInfo->bIsFTPFileType) {
			if (pSDFileInfo->strFilePath.GetLength() > 0)
			{
				strSDFileString.Format(_T("FTPINFO*%s*%s\\%s"), (SD_LPCTSTR)GetFTPServerString(&(pSDFileInfo->sFTPServerInfo)), (SD_LPCTSTR)pSDFileInfo->strFilePath, (SD_LPCTSTR)pSDFileInfo->strFileName);
			}
			else
			{
				strSDFileString.Format(_T("FTPINFO*%s*%s"), (SD_LPCTSTR)GetFTPServerString(&(pSDFileInfo->sFTPServerInfo)), (SD_LPCTSTR)pSDFileInfo->strFileName);
			}
		} 
		else 
		{
			if (pSDFileInfo->strFilePath.GetLength() > 0)
			{
#ifdef _MSC_VER
				strSDFileString.Format(_T("%s\\%s"), (SD_LPCTSTR)pSDFileInfo->strFilePath, (SD_LPCTSTR)pSDFileInfo->strFileName);
#else
				strSDFileString.Format(_T("%s/%s"), (SD_LPCTSTR)pSDFileInfo->strFilePath, (SD_LPCTSTR)pSDFileInfo->strFileName);
#endif
			}
			else
			{
				strSDFileString = pSDFileInfo->strFileName;
			}
		}
	}
	return strSDFileString;
};

//从字符串得到含FTP路经访问的文件信息结构
SD_INLINE	SD_BOOL GetSDFileInfo(SD_LPCTSTR lpszSDFileString, SDFileInfo *pSDFileInfo)
{
	if (lpszSDFileString == SD_NULL || pSDFileInfo == SD_NULL)
		return SD_FALSE;
	CSDString	strSDFileString = CSDString(lpszSDFileString);
	CSDString	strHeadFlag = strSDFileString.Left(8);

	if (0 == strSDFileString.Left(3).CompareNoCase(_T("P2*"))) 				// P2 file info
	{
		pSDFileInfo->bIsFTPFileType = SD_FALSE;
		pSDFileInfo->strFilePath = _T("");
		pSDFileInfo->strFileName = strSDFileString;
		return SD_TRUE;
	}
	else if (0 == strSDFileString.Left(6).CompareNoCase(_T("XDCAM*"))) 		// XDCAM file info
	{
		pSDFileInfo->bIsFTPFileType = SD_FALSE;
		pSDFileInfo->strFilePath = _T("");
		pSDFileInfo->strFileName = strSDFileString;
		return SD_TRUE;
	}
	else if (0 == strHeadFlag.CompareNoCase(_T("FTPINFO*")))					// ftp info 
	{
		pSDFileInfo->bIsFTPFileType = SD_TRUE;
		CSDString	strTemp = strSDFileString.Right(strSDFileString.GetLength()-8);
		if (strTemp.GetLength() < 3)
			return SD_FALSE;
		SD_INT32	nIndex = strTemp.ReverseFind('*');
		if (nIndex < 1)
			return SD_FALSE;
		CSDString	strTemp1 = strTemp.Right(strTemp.GetLength()-nIndex-1);
		SD_INT32 nIndex1 = strTemp1.ReverseFind('\\');
		if (nIndex1 < 0) 
		{
			pSDFileInfo->strFilePath = _T("");
			pSDFileInfo->strFileName = strTemp1;
		} 
		else 
		{
			pSDFileInfo->strFilePath = strTemp1.Left(nIndex1);
			pSDFileInfo->strFileName = strTemp1.Right(strTemp1.GetLength()-nIndex1-1);
		}
		return GetFTPServerInfo(strTemp.Left(nIndex), &(pSDFileInfo->sFTPServerInfo));
	}
	else 																		// disk file name
	{
		pSDFileInfo->bIsFTPFileType = SD_FALSE;
		CSDString strTemp = strSDFileString;
		if (strTemp.GetLength() < 3)
			return SD_FALSE;
#ifdef _MSC_VER
		SD_INT32	nIndex = strTemp.ReverseFind('\\');
#else
		SD_INT32	nIndex = strTemp.ReverseFind('/');
#endif
		if (nIndex < 1)
			return SD_FALSE;
		pSDFileInfo->strFilePath = strTemp.Left(nIndex);
		pSDFileInfo->strFileName = strTemp.Right(strTemp.GetLength()-nIndex-1);

		return SD_TRUE;
	} 
};
//=======================================================================================

//=======================================================================================
//与GUID相关的函数
//=======================================================================================
//	定义函数:
//		CSDString SDGuidToString(SD_GUID ID);			//得到GUID对应的字符串
//		SD_GUID	SDGuidFromString(SD_LPCTSTR lpszID);	//从字符串中得到GUID,若字串非法,返回空GUID
//		SD_GUID	SDCoCreateGuid();	//生成一个具有唯一性的GUID,它与时间和指针地址相关,严格环境下请在上层做进一步的唯一性验证
//		CSDString	SDCoCreateGuidString();	//生成一个具有唯一性的GUID字符串,严格环境下请在上层做进一步的唯一性验证
//=======================================================================================

//得到GUID对应的字符串
SD_INLINE CSDString SDGuidToString(SD_GUID ID)
{
	CSDString	strGuid;
	strGuid.Format(_T("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"), ID.Data1, ID.Data2, ID.Data3, ID.Data4[0], ID.Data4[1], ID.Data4[2], ID.Data4[3], ID.Data4[4], ID.Data4[5], ID.Data4[6], ID.Data4[7]);
	strGuid.MakeUpper();
	return strGuid;
};

//从字符串中得到GUID,若字串非法,返回空GUID
SD_INLINE SD_GUID SDGuidFromString(SD_LPCTSTR lpszID)
{
	SD_GUID guidNull;
	if (lpszID == SD_NULL)
		return guidNull;
	
	CSDString	strGuid = CSDString(lpszID);
	strGuid.MakeUpper();
	SD_INT32 len = strGuid.GetLength();
	if (len != 36)
		return guidNull;

	SD_GUID	idGuid;
	memset(&idGuid, 0, sizeof(SD_GUID));

	for (SD_INT32 i = 0; i<36; i++)
	{
		SD_INT32 ch = strGuid[i];
		if (i == 8 || i == 13 || i == 18 || i == 23) 
		{
			if (ch != '-')
				return guidNull;
		} 
		else if (ch >= '0' && ch <= '9')
		{
			if (i >= 0 && i <= 7)
				idGuid.Data1 += ((ch-'0')*(0x1<<((7-i)*4)));
			else if (i >= 9 && i <= 12)
				idGuid.Data2 += ((ch-'0')*(0x1<<((12-i)*4)));
			else if (i >= 14 && i <= 17)
				idGuid.Data3 += ((ch-'0')*(0x1<<((17-i)*4)));
			else if (i == 19 || i == 20)
				idGuid.Data4[0] += ((ch-'0')*(0x1<<((20-i)*4)));
			else if (i == 21 || i == 22)
				idGuid.Data4[1] += ((ch-'0')*(0x1<<((22-i)*4)));
			else if (i == 24 || i == 25)
				idGuid.Data4[2] += ((ch-'0')*(0x1<<((25-i)*4)));
			else if (i == 26 || i == 27)
				idGuid.Data4[3] += ((ch-'0')*(0x1<<((27-i)*4)));
			else if (i == 28 || i == 29)
				idGuid.Data4[4] += ((ch-'0')*(0x1<<((29-i)*4)));
			else if (i == 30 || i == 31)
				idGuid.Data4[5] += ((ch-'0')*(0x1<<((31-i)*4)));
			else if (i == 32 || i == 33)
				idGuid.Data4[6] += ((ch-'0')*(0x1<<((33-i)*4)));
			else if (i == 34 || i == 35)
				idGuid.Data4[7] += ((ch-'0')*(0x1<<((35-i)*4)));
		} 
		else if (ch >= 'A' && ch <= 'F')
		{
			if (i >= 0 && i <= 7)
				idGuid.Data1 += ((ch-'A'+10)*(0x1<<((7-i)*4)));
			else if (i >= 9 && i <= 12)
				idGuid.Data2 += ((ch-'A'+10)*(0x1<<((12-i)*4)));
			else if (i >= 14 && i <= 17)
				idGuid.Data3 += ((ch-'A'+10)*(0x1<<((17-i)*4)));
			else if (i == 19 || i == 20)
				idGuid.Data4[0] += ((ch-'A'+10)*(0x1<<((20-i)*4)));
			else if (i == 21 || i == 22)
				idGuid.Data4[1] += ((ch-'A'+10)*(0x1<<((22-i)*4)));
			else if (i == 24 || i == 25)
				idGuid.Data4[2] += ((ch-'A'+10)*(0x1<<((25-i)*4)));
			else if (i == 26 || i == 27)
				idGuid.Data4[3] += ((ch-'A'+10)*(0x1<<((27-i)*4)));
			else if (i == 28 || i == 29)
				idGuid.Data4[4] += ((ch-'A'+10)*(0x1<<((29-i)*4)));
			else if (i == 30 || i == 31)
				idGuid.Data4[5] += ((ch-'A'+10)*(0x1<<((31-i)*4)));
			else if (i == 32 || i == 33)
				idGuid.Data4[6] += ((ch-'A'+10)*(0x1<<((33-i)*4)));
			else if (i == 34 || i == 35)
				idGuid.Data4[7] += ((ch-'A'+10)*(0x1<<((35-i)*4)));
		}
		else
			return guidNull;
	}

	return idGuid;
};

//生成一个具有唯一性的GUID,它与时间和指针地址相关,严格环境下请在上层做进一步的唯一性验证
SD_INLINE SD_GUID	SDCoCreateGuid()
{
	SD_GUID	retGuid;

	time_t ltime;
	time(&ltime);

	retGuid.Data1 = (SD_UINT32)ltime;

	srand((SD_UINT32)time(SD_NULL));
	retGuid.Data2 = (SD_UINT16)rand();

	srand((SD_UINT32)(SD_INT64)(&ltime));
	retGuid.Data3 = (SD_UINT16)rand();

	srand((SD_UINT32)(SD_INT64)(&retGuid));
	retGuid.Data4[0] = 'D';
	retGuid.Data4[1] = 'Y';
	retGuid.Data4[2] = (SD_UINT8)(rand()&0xff);
	retGuid.Data4[3] = (SD_UINT8)(rand()&0xff);
	retGuid.Data4[4] = (SD_UINT8)(rand()&0xff);

	SD_UINT8 *pp = (SD_UINT8 *)malloc(16);
	srand((SD_UINT32)(SD_INT64)(&pp));
	free(pp);
	retGuid.Data4[5] = (SD_UINT8)(rand()&0xff);
	retGuid.Data4[6] = (SD_UINT8)(rand()&0xff);
	retGuid.Data4[7] = (SD_UINT8)(rand()&0xff);

	return retGuid;
};

//生成一个具有唯一性的GUID字符串,严格环境下请在上层做进一步的唯一性验证
SD_INLINE CSDString	SDCoCreateGuidString()
{
	SD_GUID retGuid = SDCoCreateGuid();
	return SDGuidToString(retGuid);
};
//=======================================================================================

//=======================================================================================
//与数据库、和目志等相关的公共数据定义
//=======================================================================================
//	定义枚举:
//		SD_DATABASE_TYPE;	//数据库类型定义
//		SD_LOGEVENT_CLASS;	//日志事件分类
//		SD_LOGEVENT_TYPE;	//日志事件类型
//	定义结构: 
//		SDDataBaseInfo;	SDDataBaseInfoArray;	//数据库连接访问接口信息
//		SDTrimInfo;	SDTrimInfoArray;			//与Trim相关的数据结构
//		SDDefRange;	SDDefRangeArray;			//与Range相关的数据结构
//		SDFileElementData;	SDFileElementArray;	//与读取播放相关的文件段落结构信息
//		SD32BitImageBuffer;	SD32BitImageBufferPtrArray;	//32bit图像数据块读写相关的结构信息
//		SDLogEventInfo;	SDLogEventInfoPtrArray;	//日志条目信息
//	定义函数:
//		SD_VOID SDRelease(SD32BitImageBufferPtrArray *paDataArray);
//		SD_BOOL SDClone(SD32BitImageBufferPtrArray *pNewData, SD_CONST SD32BitImageBufferPtrArray *pOldData);
//		SD_VOID SDRelease(SDLogEventInfoPtrArray *paDataArray);
//		SD_BOOL SDClone(SDLogEventInfoPtrArray *pNewData, SD_CONST SDLogEventInfoPtrArray *pOldData);
//=======================================================================================
enum SD_DATABASE_TYPE	//数据库类型定义
{
	SDDATABASETYPE_UNKNOW			=	0x00000000,
	SDDATABASETYPE_SQLSERVER		=	0x00000001,
	SDDATABASETYPE_ORACLE			=	0x00000002,
	SDDATABASETYPE_ODBCDRIVER		=	0x00000004,
	SDDATABASETYPE_ACCESS			=	0x00000008,
	SDDATABASETYPE_MYSQL			=	0x00000010,
	SDDATABASETYPE_DB2				=	0x00000020,
	SDDATABASETYPE_SYBASE			=	0x00000040,
	SDDATABASETYPE_INFOMIX			=	0x00000080,
	SDDATABASETYPE_ORACLEHTTP       =   0x00000100,
	SDDATABASETYPE_POSTGRESQL       =   0x00000200,  
};

struct SDDataBaseInfo	//数据库连接访问接口信息
{
	SD_DATABASE_TYPE	enumDBType;
	CSDString			strServerId;
	CSDString			strDataSource;
	CSDString			strUserId;
	CSDString			strPWD;

	SDDataBaseInfo()
	{
		enumDBType = SDDATABASETYPE_UNKNOW;
		strServerId = _T("");
		strDataSource = _T("");
		strUserId = _T("");
		strPWD = _T("");
	};

	SDDataBaseInfo(SD_CONST SDDataBaseInfo & other) 
	{ 
		*this = other; 
	};	

	SDDataBaseInfo& operator = (SD_CONST SDDataBaseInfo& other)
	{
		enumDBType = other.enumDBType;
		strServerId = other.strServerId;
		strDataSource = other.strDataSource;
		strUserId = other.strUserId;
		strPWD = other.strPWD;
		return *this;
	};
};
typedef CSDArray<SDDataBaseInfo, SDDataBaseInfo&> SDDataBaseInfoArray;

struct SDTrimInfo	//与Trim相关的数据结构
{
	SD_UINT32   dwTrimIn;
	SD_UINT32   dwTrimOut;

	SDTrimInfo()
	{
		dwTrimIn = 0;
		dwTrimOut = 0;
	};

	SDTrimInfo(SD_CONST SDTrimInfo &other)
	{
		*this = other;
	};

	SDTrimInfo& operator = (SD_CONST SDTrimInfo& other) 
	{
		dwTrimIn = other.dwTrimIn;
		dwTrimOut = other.dwTrimOut;
		return *this;
	};
};
typedef CSDArray<SDTrimInfo, SDTrimInfo&> SDTrimInfoArray;

struct	SDDefRange		//与Range相关的数据结构
{
	SD_DOUBLE	dMixValue;
	SD_DOUBLE	dMaxValue;
	SD_DOUBLE	dDefaultValue;

	SDDefRange()
	{
		dMixValue = 0.0;
		dMaxValue = 0.0;
		dDefaultValue = 0.0;
	};

	SDDefRange(SD_CONST SDDefRange &other)
	{
		*this = other;
	};

	SDDefRange& operator = (SD_CONST SDDefRange& other)
	{
		dMixValue = other.dMixValue;
		dMaxValue = other.dMaxValue;
		dDefaultValue = other.dDefaultValue;
		return *this;
	};
};
typedef CSDArray<SDDefRange, SDDefRange&> SDDefRangeArray;

struct SDFileElementData		//与读取播放相关的文件段落结构信息
{
	CSDString	strFileName;
	SD_UINT32	dwTrimIn;
	SD_UINT32	dwTrimOut;
	SD_UINT32	dwDuration;
	SD_BOOL		bIsSingleFrame;
	SD_BOOL		bIsNull;
	SD_UINT32	dwLoopTimes;
	SD_UINT32	dwIndex;			// 高16位对应节目流序号, 底16位对应视频流或音频流的流序号
	CSDString	strFile2Name;		// 双路文件读的第2路文件名
	SD_UINT8	pKey[16];			// 128位的解密种子

	SDFileElementData()
	{
		strFileName = _T("");
		dwTrimIn = 0;
		dwTrimOut = 0;
		dwDuration = 0;
		bIsSingleFrame = SD_FALSE;
		bIsNull = SD_FALSE;
		dwLoopTimes = 1;
		dwIndex = 0;
		strFile2Name = _T("");
		memset(pKey, 0, 16);
	};

	SDFileElementData(SD_CONST SDFileElementData &other)
	{
		*this = other;
	};

	SDFileElementData& operator = (SD_CONST SDFileElementData& other) 
	{
		strFileName = other.strFileName;
		dwTrimIn = other.dwTrimIn;
		dwTrimOut = other.dwTrimOut;
		dwDuration = other.dwDuration;
		bIsSingleFrame = other.bIsSingleFrame;
		bIsNull = other.bIsNull;
		dwLoopTimes = other.dwLoopTimes;
		dwIndex = other.dwIndex;
		strFile2Name = other.strFile2Name;
		memcpy(pKey, other.pKey, 16);
		return *this;
	};
};
typedef CSDArray<SDFileElementData, SDFileElementData&> SDFileElementArray;

struct SD32BitImageBuffer		//32bit图像数据块相关的结构信息
{
	SD_PUINT32	pdwBuffer;				// 32bit图像数据块指针
	SD_UINT32	dwXSize;				// 图象宽度像素数量
	SD_UINT32	dwYSize;				// 图象高度像素数量
	SD_UINT32	dwScanXSize;			// 跨距
	SD_BOOL		bIsDirUPtoDOWN;			// 图象缓存是否为正
	SD_BOOL		bIfDirectNewBufPtr;		// TRUE:结构用 new 方法分配图像指针的内存，结构负责删除此内存； FALSE：图像指针的分配、删除等完全由调用者来控制

	SD32BitImageBuffer()
	{
		pdwBuffer = SD_NULL;
		dwXSize = 0;
		dwYSize = 0;
		dwScanXSize = 0;		//if (dwScanXSize == 0) dwScanXSize = dwXSize;
		bIsDirUPtoDOWN = SD_TRUE;
		bIfDirectNewBufPtr = SD_TRUE;
	};

	SD32BitImageBuffer(SD_CONST SD32BitImageBuffer &other)
	{
		*this = other;
	};

	~SD32BitImageBuffer()
	{
		if (pdwBuffer && bIfDirectNewBufPtr)
			delete[] pdwBuffer;
	};

	SD_VOID	Release()
	{
		if (pdwBuffer && bIfDirectNewBufPtr) 
			delete[] pdwBuffer;
		pdwBuffer = SD_NULL;
		dwXSize = 0;
		dwYSize = 0;
		dwScanXSize = 0;
		bIsDirUPtoDOWN = SD_TRUE;
	};

	SD32BitImageBuffer& operator = (SD_CONST SD32BitImageBuffer& other)
	{
		Release();

		if (other.pdwBuffer && other.dwXSize > 0 && other.dwYSize > 0 && (other.dwScanXSize == 0 || other.dwScanXSize >= other.dwXSize))
		{
			dwXSize = other.dwXSize;
			dwYSize = other.dwYSize;
			dwScanXSize = other.dwScanXSize;
			if (dwScanXSize == 0)
				dwScanXSize = dwXSize;
			bIsDirUPtoDOWN = other.bIsDirUPtoDOWN;
			bIfDirectNewBufPtr = other.bIfDirectNewBufPtr;

			if (bIfDirectNewBufPtr)
			{
				pdwBuffer = new SD_UINT32[dwScanXSize*dwYSize];
				memcpy(pdwBuffer, other.pdwBuffer, dwScanXSize*dwYSize*sizeof(SD_UINT32));
			}
			else
				pdwBuffer = other.pdwBuffer;
		}
		return *this;
	};
};
typedef CSDArray<SD32BitImageBuffer*, SD32BitImageBuffer*&> SD32BitImageBufferPtrArray;

inline SD_VOID SDRelease(SD32BitImageBufferPtrArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SD32BitImageBuffer *pElement = paDataArray->GetAt(i);
			pElement->Release();
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

inline SD_BOOL SDClone(SD32BitImageBufferPtrArray *pNewData, SD_CONST SD32BitImageBufferPtrArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SD32BitImageBuffer *pNewElement = new SD32BitImageBuffer;
		SD32BitImageBuffer *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};

enum SD_LOGEVENT_CLASS		//日志事件分类
{
	SD_LOGEVENT_CLASS_UNKNOW		= 0x00000000,
	SD_LOGEVENT_CLASS_RUNTIME		= 0x00000001,			//运行日志
	SD_LOGEVENT_CLASS_SECURITY		= 0x00000002,			//安全日志
	SD_LOGEVENT_CLASS_OTHER			= 0x80000000,			//Other日志
};

enum SD_LOGEVENT_TYPE		//日志事件类型
{
	SD_LOGEVENT_TYPE_UNKNOW			= 0x00000000,
	SD_LOGEVENT_TYPE_ERROR			= 0x00000001,
	SD_LOGEVENT_TYPE_WARNING		= 0x00000002,
	SD_LOGEVENT_TYPE_INFO			= 0x00000004,
	SD_LOGEVENT_TYPE_DEBUG			= 0x00000008,
	SD_LOGEVENT_TYPE_OTHER			= 0x80000000,
};

struct  SDLogEventInfo		//日志条目信息
{
	SD_GUID				guidLog;					//	事件唯一标识
	CSDString			strEventGroup;				//	事件组名称
	CSDString			strEventName;				//	事件名称
	CSDString			strEventInfo;				//	事件描述
	CSDString			strEventHint;				//	事件备注
	SD_HRESULT			hRetValue;					//	事件返回值

	SD_LOGEVENT_CLASS	enumClass;
	SD_LOGEVENT_TYPE	enumType;
	time_t				ltime;						//	事件发生时间
	CSDString			strHostIPAddress;			//	机器IP地址
	CSDString			strHostName;				//	机器名称
	CSDString			strSysName;					//	系统标识
	CSDString			strLogUserName;				//	登录用户

	SD_UINT32			dwExtraDataType;			//	额外数据类型
	SD_UINT32			dwExtraDataSizeInByte;		//	额外数据大小
	SD_PUINT8			pbExtraData;				//	额外数据
	
	SDLogEventInfo()
	{
		guidLog = SDCoCreateGuid();
		strEventGroup = _T("");
		strEventName = _T("");
		strEventInfo = _T("");
		strEventHint = _T("");
		hRetValue = SD_NOERROR;

		enumClass = SD_LOGEVENT_CLASS_UNKNOW;
		enumType = SD_LOGEVENT_TYPE_UNKNOW;
		time(&ltime);
		strHostIPAddress = _T("");
		strHostName = _T("");
		strSysName = _T("");
		strLogUserName = _T("");

		dwExtraDataType = 0;
		dwExtraDataSizeInByte = 0;
		pbExtraData = SD_NULL;
	};

	~SDLogEventInfo()
	{
		if (pbExtraData) {
			delete[] pbExtraData;
			pbExtraData = SD_NULL;
		}
	};

	SDLogEventInfo(SD_CONST SDLogEventInfo & other) 
	{ 
		*this = other; 
	};	

	SDLogEventInfo& operator = (SD_CONST SDLogEventInfo& other)
	{
		guidLog = other.guidLog;
		strEventGroup = other.strEventGroup;
		strEventName = other.strEventName;
		strEventInfo = other.strEventInfo;
		strEventHint = other.strEventHint;
		hRetValue = other.hRetValue;

		enumClass = other.enumClass;
		enumType = other.enumType;
		ltime = other.ltime;
		strHostIPAddress = other.strHostIPAddress;
		strHostName = other.strHostName;
		strSysName = other.strSysName;
		strLogUserName = other.strLogUserName;

		if (pbExtraData) 
		{
			delete[] pbExtraData;
			pbExtraData = SD_NULL;
		}
		dwExtraDataType = other.dwExtraDataType;
		dwExtraDataSizeInByte = other.dwExtraDataSizeInByte;
		if (other.pbExtraData) 
		{
			pbExtraData = new SD_UINT8[dwExtraDataSizeInByte];
			memcpy(pbExtraData, other.pbExtraData, dwExtraDataSizeInByte);
		}
		return *this;
	};
};
typedef CSDArray<SDLogEventInfo*, SDLogEventInfo*&> SDLogEventInfoPtrArray;

SD_INLINE SD_VOID SDRelease(SDLogEventInfoPtrArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SDLogEventInfo *pElement = paDataArray->GetAt(i);
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

SD_INLINE SD_BOOL SDClone(SDLogEventInfoPtrArray *pNewData, SD_CONST SDLogEventInfoPtrArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SDLogEventInfo *pNewElement = new SDLogEventInfo;
		SDLogEventInfo *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};
//=======================================================================================

//=======================================================================================
//几个有用的公共函数
//=======================================================================================
//	定义函数:
//		SD_VOID	SDSafeDelete(TYPE *& ptr);		//定义成为宏或者模板函数用于释放对象指针问题
//		SD_VOID	SDSafeArrayDelete(TYPE *& ptr);	//定义成为宏或者模板函数用于释放对象指针问题
//		SD_VOID	SDWMemset(SD_VOID *pBuf, SD_INT16 value, SD_INT32 num);	//在Buf中按双字节设置值
//		SD_VOID	SDDMemset(SD_VOID *pBuf, SD_INT32 value, SD_INT32 num);	//在Buf中按4字节设置值
//=======================================================================================
template<class TYPE>
SD_INLINE SD_VOID	SDSafeDelete(TYPE *& ptr)	//申明为指针的引用
{
	if (ptr) 
	{
		delete ptr;
		ptr = SD_NULL;
	}
};

template<class TYPE>
SD_INLINE SD_VOID	SDSafeArrayDelete(TYPE *& ptr)	//申明为指针的引用
{
	if (ptr) 
	{
		delete[] ptr;
		ptr = SD_NULL;
	}
};

//在Buf中按双字节设置值
SD_INLINE SD_VOID	SDWMemset(SD_VOID *pBuf, SD_INT16 value, SD_INT32 num)
{
	SD_INT16 * pTempBuf = (SD_INT16 *)pBuf;
	for (SD_INT32 i = 0; i < num; i++)
	{
		*pTempBuf = value;
		pTempBuf++;
	}
};

//在Buf中按4字节设置值
SD_INLINE SD_VOID	SDDMemset(SD_VOID *pBuf, SD_INT32 value, SD_INT32 num)
{
	SD_INT32 * pTempBuf = (SD_INT32 *)pBuf;
	for (SD_INT32 i = 0; i < num; i++)
	{
		*pTempBuf = value;
		pTempBuf++;
	}
};

#ifdef _MSC_VER

//=======================================================================================
//判断文件是否存在? ---> 注意: 没有超时检测!!!
//=======================================================================================
SD_INLINE SD_BOOL	IsSDFileExist(SD_LPCTSTR lpszFileName, SD_BOOL bIfCheckFileSize = SD_TRUE)
{
	WIN32_FIND_DATA sFindFileData;
	HANDLE hFind = FindFirstFile(lpszFileName, &sFindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return SD_FALSE;

	FindClose(hFind);

	if (bIfCheckFileSize && sFindFileData.nFileSizeHigh == 0 && sFindFileData.nFileSizeLow == 0)
		return SD_FALSE;
	else 
		return SD_TRUE;
};

//=======================================================================================
//Windows环境下的注册表读写函数
//=======================================================================================
//	定义函数:
//		从注册表中读取一个整数
//		SD_INT32	SDHOTKEY_ReadInt(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_INT32 intDefaultValue=0);
//
//		从注册表中读取一个字符串
//		CSDString SDHOTKEY_ReadString(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_LPCTSTR lpszDefaultValue=SD_NULL);
//
//		在注册表中写入一个整数
//		SD_BOOL	SDHOTKEY_WriteInt(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_INT32 intValue);
//
//		在注册表中写入一个字符串
//		SD_BOOL	SDHOTKEY_WriteString(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_LPCTSTR strValue);
//=======================================================================================

#define SD_ROOT_KEY		HKEY_LOCAL_MACHINE
#define SD_SUB_KEY		_T("Software\\EasyCode")

//从注册表中读取一个整数
SD_INLINE SD_INT32	SDHOTKEY_ReadInt(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_INT32 intDefaultValue=0)
{
	HKEY hcpl;
	CSDString	strCombSubKey;
	if (lpSubKey == SD_NULL)
		strCombSubKey = CSDString(SD_SUB_KEY);
	else
		strCombSubKey.Format(_T("%s\\%s"), SD_SUB_KEY, lpSubKey);
	SD_INT32	intValue = intDefaultValue;
	if (RegOpenKeyEx(SD_ROOT_KEY, strCombSubKey, 0, KEY_READ, &hcpl) == ERROR_SUCCESS) 
	{
		SD_UINT32L	dwType = REG_DWORD;
		SD_UINT32	dwValue;
		SD_UINT32L	dwSize = sizeof(SD_UINT32);
		long ret = RegQueryValueEx(hcpl, lpValueName, SD_NULL, &dwType, (SD_LPUINT8)&dwValue, &dwSize);
		RegCloseKey(hcpl);
		if (ret == ERROR_SUCCESS)
			intValue = dwValue;
	}
	return intValue;
}

//从注册表中读取一个字符串
SD_INLINE CSDString SDHOTKEY_ReadString(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_LPCTSTR lpszDefaultValue=SD_NULL)
{
	HKEY hcpl;
	CSDString	strCombSubKey;
	if (lpSubKey == SD_NULL)
		strCombSubKey = CSDString(SD_SUB_KEY);
	else
		strCombSubKey.Format(_T("%s\\%s"), SD_SUB_KEY, lpSubKey);
	CSDString	strValue = _T("");
	if (lpszDefaultValue)
		strValue = CSDString(lpszDefaultValue);
	if (RegOpenKeyEx(SD_ROOT_KEY, strCombSubKey, 0, KEY_READ, &hcpl) == ERROR_SUCCESS) 
	{
		SD_UINT32L	dwType = REG_SZ;
		SD_UINT32L	dwSize = 512;
		TCHAR	strRead[512];
		long ret = RegQueryValueEx(hcpl, lpValueName, SD_NULL, &dwType, (SD_LPUINT8)strRead, &dwSize);
		RegCloseKey(hcpl);
		if (ret == ERROR_SUCCESS)
			strValue = CSDString(strRead);
	}
	return strValue;
}

//在注册表中写入一个整数
SD_INLINE SD_BOOL	SDHOTKEY_WriteInt(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_INT32 intValue)
{
	HKEY hcpl;
	CSDString	strCombSubKey;
	if (lpSubKey == SD_NULL)
		strCombSubKey = CSDString(SD_SUB_KEY);
	else
		strCombSubKey.Format(_T("%s\\%s"), SD_SUB_KEY, lpSubKey);
	SD_UINT32L dwDisposition;
	if (RegCreateKeyEx(SD_ROOT_KEY, strCombSubKey, 0, _T("EasyCode"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, SD_NULL, &hcpl, &dwDisposition) == ERROR_SUCCESS) 
	{
		long ret = RegSetValueEx(hcpl, lpValueName, SD_NULL, REG_DWORD, (SD_LPUINT8)&intValue, sizeof(SD_UINT32));
		RegCloseKey(hcpl);
		if (ret == ERROR_SUCCESS)
			return SD_TRUE;
	}
	return SD_FALSE;
}

//在注册表中写入一个字符串
SD_INLINE SD_BOOL	SDHOTKEY_WriteString(SD_LPCTSTR lpSubKey, SD_LPCTSTR lpValueName, SD_LPCTSTR strValue)
{
	HKEY hcpl;
	CSDString	strCombSubKey;
	if (lpSubKey == SD_NULL)
		strCombSubKey = CSDString(SD_SUB_KEY);
	else
		strCombSubKey.Format(_T("%s\\%s"), SD_SUB_KEY, lpSubKey);
	SD_UINT32L dwDisposition;
	if (RegCreateKeyEx(SD_ROOT_KEY, strCombSubKey, 0, _T("EasyCode"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, SD_NULL, &hcpl, &dwDisposition) == ERROR_SUCCESS) 
	{
		long ret = RegSetValueEx(hcpl, lpValueName, SD_NULL, REG_SZ, (SD_LPUINT8)strValue, (SD_UINT32)(_tcslen(strValue)+1)*sizeof(TCHAR));
		RegCloseKey(hcpl);
		if (ret == ERROR_SUCCESS)
			return SD_TRUE;
	}
	return SD_FALSE;
}
#endif	//_MSC_VER

//=======================================================================================

#pragma warning(pop)

#endif // !defined(_SD_SDDEFINE_H_)
