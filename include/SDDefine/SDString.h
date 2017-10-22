/*********************************************************************************************************************************************
* SDString.h
*
* 公共头文件之一,EasyCode科技公司版权所有!
*
* 目标:		-这个头文件实现了类似于MFC体系CSDString类的功能,使用方式基本相同,并支持跨操作系统运行环境!
*
* 描述:		-几个有用的关于字符串处理及转换方面的API函数
*			-仿MFC体系CSDString类定义并实现。
*
* == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == =  =  = 
SD_INT32 SD_GetStrLen(SD_LPCSTR lpcsz);
SD_INT32 SD_GetStrLen(SD_LPCWSTR lpcwsz);
SD_INT32 SD_GetCharPos(SD_LPCTSTR lpctsz, SD_TCHAR tch);

SD_INT32 SD_StringConvertToWString(SD_LPWSTR lpwsz, SD_INT32 nSizeWChar, SD_LPCSTR lpcsz, SD_BOOL bNullTerminator = SD_TRUE);
SD_INT32 SD_WStringConvertToString(SD_LPSTR lpsz, SD_INT32 nSizeChar, SD_LPCWSTR lpcwsz, SD_BOOL bNullTerminator = SD_TRUE);

SD_INT32 SD_TStringCopyFrom(SD_LPTSTR lptstr, SD_INT32 nSizeInTChar, SD_LPCSTR lpcsz, SD_BOOL bNullTerminator = SD_TRUE);
SD_INT32 SD_TStringCopyFrom(SD_LPTSTR lptstr, SD_INT32 nSizeInTChar, SD_LPCWSTR lpcwsz, SD_BOOL bNullTerminator = SD_TRUE);

SD_INT32 SD_TStringCopyToStr(SD_LPCTSTR lpctstr, SD_LPSTR lpsz, SD_INT32 nSizeChar, SD_BOOL bNullTerminator = SD_TRUE);
SD_INT32 SD_TStringCopyToWStr(SD_LPCTSTR lpctstr, SD_LPWSTR lpwsz, SD_INT32 nSizeWChar, SD_BOOL bNullTerminator = SD_TRUE);
* == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == =  =  = 

* == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == =  =  = 
class CSDString
{
	CSDString();
	CSDString(SD_CHAR ch, SD_INT32 nRepeat = 1);
	CSDString(SD_WCHAR wch, SD_INT32 nRepeat = 1);
	CSDString(SD_LPCSTR lpcsz);
	CSDString(SD_LPCWSTR lpcwsz);
	CSDString(SD_LPCTSTR lpctsz, SD_INT32 nLength);
	CSDString(SD_CONST CSDString& stringSrc);
	CSDString(SD_CONST CSDString& strSrc);
	~CSDString();

	SD_INT32 GetLength() SD_CONST;
	SD_VOID		SetStringLength(SD_INT32 nNewLength, SD_BOOL bIfEmptyThisString = SD_FALSE);
	SD_BOOL		IsEmpty() SD_CONST;
	SD_VOID		Empty();
	SD_TCHAR	GetAt(SD_INT32 nIndex) SD_CONST;
	SD_TCHAR	operator[](SD_INT32 nIndex) SD_CONST;
	SD_VOID		SetAt(SD_INT32 nIndex, SD_TCHAR tch);
	SD_INT32 GetCharBuffer(SD_LPSTR pCharBuf, SD_INT32 nSizeChar) SD_CONST;
	SD_UINT32 GetWCharBuffer(SD_LPWSTR pWCharBuf, SD_INT32 nSizeWChar) SD_CONST;
	SD_LPCTSTR	GetTCharBuffer() SD_CONST;
	operator	SD_LPCTSTR() SD_CONST;
	SD_VOID		GetCSDString(CSDString& strDest) SD_CONST;
	CSDString		GetCSDString() SD_CONST;

	SD_CONST CSDString& operator = (SD_CHAR ch);
	SD_CONST CSDString& operator = (SD_WCHAR wch);
	SD_CONST CSDString& operator = (SD_LPCSTR lpcsz);
	SD_CONST CSDString& operator = (SD_LPCWSTR lpcwsz);
	SD_CONST CSDString& operator = (SD_CONST CSDString& stringSrc);
	SD_CONST CSDString& operator = (SD_CONST CSDString& strSrc);

	SD_CONST CSDString& operator +=  (SD_CHAR ch);
	SD_CONST CSDString& operator +=  (SD_WCHAR wch);
	SD_CONST CSDString& operator +=  (SD_LPCSTR lpcsz);
	SD_CONST CSDString& operator +=  (SD_LPCWSTR lpcwsz);
	SD_CONST CSDString& operator +=  (SD_CONST CSDString& stringAdd);
	SD_CONST CSDString& operator +=  (SD_CONST CSDString& strAdd);

	friend CSDString  operator + (SD_CONST CSDString& string1, SD_CONST CSDString& string2);
	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_CHAR ch);
	friend CSDString  operator + (SD_CHAR ch, SD_CONST CSDString& stringSrc);
	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_WCHAR ch);
	friend CSDString  operator + (SD_WCHAR ch, SD_CONST CSDString& stringSrc);
	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_LPCSTR lpcsz);
	friend CSDString  operator + (SD_LPCSTR lpcsz, SD_CONST CSDString& stringSrc);
	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_LPCWSTR lpcwsz);
	friend CSDString  operator + (SD_LPCWSTR lpcwsz, SD_CONST CSDString& stringSrc);
	friend CSDString  operator + (SD_CONST CSDString& s1, CSDString s2);
	friend CSDString  operator + (CSDString s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator == (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator == (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator == (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator == (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator !=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator !=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator !=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator !=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator < (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator < (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator < (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator < (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator > (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator > (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator > (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator > (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator <=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator <=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator <=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator <=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator >=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz);
	friend SD_BOOL  operator >=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator >=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz);
	friend SD_BOOL  operator >=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s);
	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);
	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2);

	SD_INT32 Compare(SD_LPCSTR lpcsz) SD_CONST;
	SD_INT32 Compare(SD_LPCWSTR lpcwsz) SD_CONST;
	SD_INT32 Compare(CSDString stringCmp) SD_CONST;
	SD_INT32 Compare(CSDString stringCmp) SD_CONST;
	SD_INT32 CompareNoCase(SD_LPCSTR lpcsz) SD_CONST;
	SD_INT32 CompareNoCase(SD_LPCWSTR lpcwsz) SD_CONST;
	SD_INT32 CompareNoCase(CSDString stringCmp) SD_CONST;
	SD_INT32 CompareNoCase(CSDString stringCmp) SD_CONST;

	CSDString Mid(SD_INT32 nFirst, SD_INT32 nCount) SD_CONST;
	CSDString Mid(SD_INT32 nFirst) SD_CONST;
	CSDString Left(SD_INT32 nCount) SD_CONST;
	CSDString Right(SD_INT32 nCount) SD_CONST;
	CSDString SpanIncluding(SD_LPCTSTR lpszCharSet) SD_CONST;
	CSDString SpanIncluding(CSDString strCharSet) SD_CONST;
	CSDString SpanIncluding(CSDString strCharSet) SD_CONST;
	CSDString SpanExcluding(SD_LPCTSTR lpszCharSet) SD_CONST;
	CSDString SpanExcluding(CSDString strCharSet) SD_CONST;
	CSDString SpanExcluding(CSDString strCharSet) SD_CONST;

	CSDString& MakeUpper();
	CSDString& MakeLower();
	CSDString& MakeReverse();

	CSDString& TrimRight(SD_TCHAR chTarget = _T(' '));
	CSDString& TrimRight(SD_LPCTSTR lpszTargets);
	CSDString& TrimRight(CSDString strTargets);
	CSDString& TrimRight(CSDString strTargets);
	CSDString& TrimLeft(SD_TCHAR chTarget = _T(' '));
	CSDString& TrimLeft(SD_LPCTSTR lpszTargets);
	CSDString& TrimLeft(CSDString strTargets);
	CSDString& TrimLeft(CSDString strTargets);
	CSDString& Trim(SD_TCHAR chTarget = _T(' '));
	CSDString& Trim(SD_LPCTSTR pszTargets);
	CSDString& Trim(CSDString strTargets);
	CSDString& Trim(CSDString strTargets);

	SD_INT32 Replace(SD_TCHAR chOld, SD_TCHAR chNew);
	SD_INT32 Replace(SD_LPCTSTR lpszOld, SD_LPCTSTR lpszNew);
	SD_INT32 Remove(SD_TCHAR chRemove);
	SD_INT32 Delete(SD_INT32 nIndex, SD_INT32 nCount = 1);
	SD_INT32 Append(SD_CHAR ch, SD_INT32 nRepeat = 1);
	SD_INT32 Append(SD_WCHAR wch, SD_INT32 nRepeat = 1);
	SD_INT32 Append(SD_LPCSTR lpcsz);
	SD_INT32 Append(SD_LPCWSTR lpcwsz);
	SD_INT32 Append(SD_LPCTSTR lpctsz, SD_INT32 nLength);
	SD_INT32 Append(SD_CONST CSDString& strSrc);
	SD_INT32 Append(SD_CONST CSDString& strSrc);
	SD_INT32 Insert(SD_INT32 nIndex, SD_CHAR ch, SD_INT32 nRepeat = 1);
	SD_INT32 Insert(SD_INT32 nIndex, SD_WCHAR wch, SD_INT32 nRepeat = 1);
	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCSTR lpcsz);
	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCWSTR lpcwsz);
	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCTSTR lpctsz, SD_INT32 nLength);
	SD_INT32 Insert(SD_INT32 nIndex, SD_CONST CSDString& strSrc);
	SD_INT32 Insert(SD_INT32 nIndex, SD_CONST CSDString& strSrc);

	SD_INT32 Find(SD_TCHAR tch, SD_INT32 nStart = 0) SD_CONST;
	SD_INT32 ReverseFind(SD_TCHAR tch, SD_INT32 nStart = -1) SD_CONST;
	SD_INT32 Find(SD_LPCTSTR lpszSub, SD_INT32 nStart = 0) SD_CONST;
	SD_INT32 Find(CSDString strSub, SD_INT32 nStart = 0) SD_CONST;
	SD_INT32 Find(CSDString strSub, SD_INT32 nStart = 0) SD_CONST;
	SD_INT32 FindOneOf(SD_LPCTSTR lpszCharSet) SD_CONST;
	SD_INT32 FindOneOf(CSDString strCharSet) SD_CONST;
	SD_INT32 FindOneOf(CSDString strCharSet) SD_CONST;
	CSDString Tokenize(SD_LPCTSTR pszTokens, SD_INT32& iStart) SD_CONST;
	CSDString Tokenize(CSDString strTokens, SD_INT32& iStart) SD_CONST;
	CSDString Tokenize(CSDString strTokens, SD_INT32& iStart) SD_CONST;

	SD_VOID Format(SD_LPCTSTR lpszFormat, ...);
	SD_VOID Format(CSDString strFormat, ...);
	SD_VOID Format(CSDString strFormat, ...);
	SD_VOID	AppendFormat(SD_LPCTSTR lpszFormat, ...);
	SD_VOID	AppendFormat(CSDString strFormat, ...);
	SD_VOID	AppendFormat(CSDString strFormat, ...);
}
* == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == = == =  =  = 
*
* Ver-0.9
*
*********************************************************************************************************************************************/
#ifndef _SD_SDSTRING_H_
#define _SD_SDSTRING_H_

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

#include "SDType.h"

#pragma warning(push)
#pragma warning(disable:4244)

#ifndef _MSC_VER
	#ifdef _UNICODE
		#define _T(x) L##x
	#else
		#define _T(x) x
	#endif
#else
	#include "tchar.h"
#endif

SD_INLINE SD_INT32 SD_GetStrLen(SD_LPCSTR lpcsz)
{
	if (lpcsz == SD_NULL)
		return 0;
	SD_INT32 nLen = (SD_INT32)(strlen(lpcsz));
	if (nLen < 0)
		nLen = 0;
	return nLen;
};

SD_INLINE SD_INT32 SD_GetStrLen(SD_LPCWSTR lpcwsz)
{
	if (lpcwsz == SD_NULL)
		return 0;
	SD_INT32 nLen = (SD_INT32)(wcslen(lpcwsz));
	if (nLen < 0)
		nLen = 0;
	return nLen;
};

SD_INLINE SD_INT32 SD_GetCharPos(SD_LPCTSTR lpctsz, SD_TCHAR tch)
{
	SD_INT32 nLen = SD_GetStrLen(lpctsz);
	if (lpctsz == SD_NULL || nLen <=  0 || tch == 0)
		return -1;
	for (SD_INT32 i = 0; i < nLen; i ++)
	{
		if (lpctsz[i] == tch)
			return i;
	}
	return -1;
};

struct _SD_UseDefaultLocale	//auto restore
{
	SD_CHAR	 pchSaveCurLocal[1024];
	SD_CHAR	 *pchTmpSaveCurLocal;

	_SD_UseDefaultLocale()
	{
		pchSaveCurLocal[0] = 0;
		pchTmpSaveCurLocal = SD_NULL;

		SD_CHAR	 *pchCurLocale = setlocale(LC_ALL, SD_NULL);		//get current locale
		SD_INT32 nLength = (SD_INT32)(strlen(pchCurLocale));
		if (nLength > 1023)
		{
			pchTmpSaveCurLocal = new SD_CHAR[nLength + 1];
			memcpy(pchTmpSaveCurLocal, pchCurLocale, nLength * sizeof(SD_CHAR));
			pchTmpSaveCurLocal[nLength] = 0;
		}
		else if (nLength > 0)
		{
			memcpy(pchSaveCurLocal, pchCurLocale, nLength * sizeof(SD_CHAR));
			pchSaveCurLocal[nLength] = 0;
		}

		setlocale(LC_ALL, "");										//set default locale
	};

	~_SD_UseDefaultLocale()
	{
		if (pchTmpSaveCurLocal)
		{
			setlocale(LC_ALL, pchTmpSaveCurLocal);					//restore old locale
			delete[] pchTmpSaveCurLocal;
		}
		else if (pchSaveCurLocal[0] !=  0)
			setlocale(LC_ALL, pchSaveCurLocal);						//restore old locale
	};
};

#define	_SD_USE_DEFAULT_LOCALE			_SD_UseDefaultLocale	_useDefaultLocale_;

SD_INLINE SD_INT32 SD_StringConvertToWString(SD_LPWSTR lpwsz, SD_INT32 nSizeWChar, SD_LPCSTR lpcsz, SD_BOOL bNullTerminator = SD_TRUE)
{
	SD_INT32 nLen = SD_GetStrLen(lpcsz);
	if (nLen <=  0)
		return 0;

	_SD_USE_DEFAULT_LOCALE;

	SD_INT32 nCountInWChar = 0;
	size_t stConvertedChars = 0;

#ifdef _MSC_VER
	if (mbstowcs_s(&stConvertedChars, SD_NULL, 0, lpcsz, _TRUNCATE/*-1*/) == 0)
		nCountInWChar = (SD_INT32)stConvertedChars - 1;
#else
	stConvertedChars = mbstowcs(SD_NULL, lpcsz, 2 * nLen + 2);
	nCountInWChar = (SD_INT32)stConvertedChars;
#endif //_MSC_VER

	if (lpwsz && nCountInWChar > 0 && nSizeWChar > 1)
	{
		if (nCountInWChar > nSizeWChar - 1)
			nCountInWChar = nSizeWChar - 1;
		SD_WCHAR	wch = lpwsz[nCountInWChar];
#ifdef _MSC_VER
		mbstowcs_s(&stConvertedChars, lpwsz, nCountInWChar + 1, lpcsz, _TRUNCATE/*-1*/);
#else
		stConvertedChars = mbstowcs(lpwsz, lpcsz, nCountInWChar + 1);
		stConvertedChars ++;
#endif //_MSC_VER
		if (nCountInWChar <=  (SD_INT32)stConvertedChars - 1)
		{
			if (bNullTerminator)
				lpwsz[nCountInWChar] = 0;
			else
				lpwsz[nCountInWChar] = wch;
		}
		else
			nCountInWChar = 0;
	}
	if (nCountInWChar < 0)
		nCountInWChar = 0;
	return nCountInWChar;
};

SD_INLINE SD_INT32 SD_WStringConvertToString(SD_LPSTR lpsz, SD_INT32 nSizeChar, SD_LPCWSTR lpcwsz, SD_BOOL bNullTerminator = SD_TRUE)
{
	SD_INT32 nLen = SD_GetStrLen(lpcwsz);
	if (nLen <=  0)
		return 0;

	_SD_USE_DEFAULT_LOCALE;

	mbstate_t	mbstate;
	::memset((void*)&mbstate, 0, sizeof(mbstate));

	SD_INT32 nCountInChar = 0;
	size_t stConvertedChars = 0;

#ifdef _MSC_VER
	if (wcsrtombs_s(&stConvertedChars, SD_NULL, 0, &lpcwsz, _TRUNCATE/*-1*/, &mbstate) == 0)
		nCountInChar = (SD_INT32)stConvertedChars - 1;
#else
	stConvertedChars = wcsrtombs(SD_NULL, &lpcwsz, 2 * nLen + 2, &mbstate);
	nCountInChar = (SD_INT32)stConvertedChars;
#endif //_MSC_VER

	if (lpsz && nCountInChar > 0 && nSizeChar > 1)
	{
		if (nCountInChar > nSizeChar - 1)
			nCountInChar = nSizeChar - 1;
		SD_CHAR	ch = lpsz[nCountInChar];
#ifdef _MSC_VER
		wcsrtombs_s(&stConvertedChars, lpsz, nCountInChar + 1, &lpcwsz, _TRUNCATE/*-1*/, &mbstate);
#else
		stConvertedChars = wcsrtombs(lpsz, &lpcwsz, nCountInChar + 1, &mbstate);
		stConvertedChars ++;
#endif //_MSC_VER
		if (nCountInChar <=  (SD_INT32)stConvertedChars - 1)
		{
			if (bNullTerminator)
				lpsz[nCountInChar] = 0;
			else
				lpsz[nCountInChar] = ch;
		}
		else
			nCountInChar = 0;
	}
	if (nCountInChar < 0)
		nCountInChar = 0;
	return nCountInChar;
};

SD_INLINE SD_INT32 SD_TStringCopyFrom(SD_LPTSTR lptstr, SD_INT32 nSizeInTChar, SD_LPCSTR lpcsz, SD_BOOL bNullTerminator = SD_TRUE)
{
#ifdef _UNICODE
	return SD_StringConvertToWString(lptstr, nSizeInTChar, lpcsz, bNullTerminator);
#else
	SD_INT32 nLen = SD_GetStrLen(lpcsz);
	if (nLen <=  0)
		return 0;
	if (lptstr == SD_NULL)
		return nLen;
	else if (nSizeInTChar > 1)
	{
		if (nLen > nSizeInTChar - 1)
			nLen = nSizeInTChar - 1;
		memcpy(lptstr, lpcsz, nLen * sizeof(SD_CHAR));
		if (bNullTerminator)
			lptstr[nLen] = 0;
		return nLen;
	} 
	else
		return 0;
#endif //_UNICODE
};

SD_INLINE SD_INT32 SD_TStringCopyFrom(SD_LPTSTR lptstr, SD_INT32 nSizeInTChar, SD_LPCWSTR lpcwsz, SD_BOOL bNullTerminator = SD_TRUE)
{
#ifdef _UNICODE
	SD_INT32 nLen = SD_GetStrLen(lpcwsz);
	if (nLen <=  0)
		return 0;
	if (lptstr == SD_NULL)
		return nLen;
	else if (nSizeInTChar > 1)
	{
		if (nLen > nSizeInTChar - 1)
			nLen = nSizeInTChar - 1;
		memcpy(lptstr, lpcwsz, nLen * sizeof(SD_WCHAR));
		if (bNullTerminator)
			lptstr[nLen] = 0;
		return nLen;
	}
	else
		return 0;
#else
	return SD_WStringConvertToString(lptstr, nSizeInTChar, lpcwsz, bNullTerminator);
#endif //_UNICODE
};

SD_INLINE SD_INT32 SD_TStringCopyToStr(SD_LPCTSTR lpctstr, SD_LPSTR lpsz, SD_INT32 nSizeChar, SD_BOOL bNullTerminator = SD_TRUE)
{
#ifdef _UNICODE
	return SD_WStringConvertToString(lpsz, nSizeChar, lpctstr, bNullTerminator);
#else
	SD_INT32 nLen = SD_GetStrLen(lpctstr);
	if (nLen <=  0)
		return 0;
	if (lpsz == SD_NULL)
		return nLen;
	else if (nSizeChar > 1)
	{
		if (nLen > nSizeChar - 1)
			nLen = nSizeChar - 1;
		memcpy(lpsz, lpctstr, nLen * sizeof(SD_CHAR));
		if (bNullTerminator)
			lpsz[nLen] = 0;
		return nLen;
	}
	else
		return 0;
#endif //_UNICODE
};

SD_INLINE SD_INT32 SD_TStringCopyToWStr(SD_LPCTSTR lpctstr, SD_LPWSTR lpwsz, SD_INT32 nSizeWChar, SD_BOOL bNullTerminator = SD_TRUE)
{
#ifdef _UNICODE
	SD_INT32 nLen = SD_GetStrLen(lpctstr);
	if (nLen <=  0)
		return 0;
	if (lpwsz == SD_NULL)
		return nLen;
	else if (nSizeWChar > 1)
	{
		if (nLen > nSizeWChar - 1)
			nLen = nSizeWChar - 1;
		memcpy(lpwsz, lpctstr, nLen * sizeof(SD_WCHAR));
		if (bNullTerminator)
			lpwsz[nLen] = 0;
		return nLen;
	}
	else
		return 0;
#else
	return SD_StringConvertToWString(lpwsz, nSizeWChar, lpctstr, bNullTerminator);
#endif //_UNICODE
};

#define		_CSDSTRING_SegLength						128
#define		_CSDSTRING_SkipLength						1024

class CSDString
{
public:		// Constructors
	CSDString(SD_UINT32 dwMaxTCharNumSet = 0)
	{
		m_lptstr = SD_NULL;
		_CreateNullString(dwMaxTCharNumSet);
	};

	CSDString(SD_CHAR ch, SD_INT32 nRepeat = 1)
	{
		m_lptstr = SD_NULL;
		if (nRepeat <=  0 || ch == 0)
			_CreateNullString();
		else
		{
			SD_CHAR	pstr[2];
			pstr[0] = ch;
			pstr[1] = 0;

			if (SD_StringConvertToWString(SD_NULL, 0, pstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pstr);
				if (nCount > 0)
				{
					_CalcTStrBufRange(0, 0, nCount * nRepeat);
				
					SD_INT32 k = 0;
					for (SD_INT32 i = 0; i < nRepeat; i ++)
					{
						for (SD_INT32 j = 0; j < nCount; j ++)
						{
							m_lptstr[k] = ptstr[j];
							k ++;
						}
					}
					m_lptstr[k] = 0;
				}
				else
					_CreateNullString();
			}
			else
				_CreateNullString();
		}
	};

	CSDString(SD_WCHAR wch, SD_INT32 nRepeat = 1)
	{
		m_lptstr = SD_NULL;
		if (nRepeat <=  0 || wch == 0)
			_CreateNullString();
		else
		{
			SD_WCHAR	pwstr[2];
			pwstr[0] = wch;
			pwstr[1] = 0;

			if (SD_WStringConvertToString(SD_NULL, 0, pwstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pwstr);
				if (nCount > 0)
				{
					_CalcTStrBufRange(0, 0, nCount * nRepeat);
				
					SD_INT32 k = 0;
					for (SD_INT32 i = 0; i < nRepeat; i ++)
					{
						for (SD_INT32 j = 0; j < nCount; j ++)
						{
							m_lptstr[k] = ptstr[j];
							k ++;
						}
					}
					m_lptstr[k] = 0;
				}
				else
					_CreateNullString();
			}
			else
				_CreateNullString();
		}
	};

	CSDString(SD_LPCSTR lpcsz)
	{
		m_lptstr = SD_NULL;
		SD_INT32 nStrLen = SD_GetStrLen(lpcsz);
		if (lpcsz == SD_NULL || nStrLen <=  0)
			_CreateNullString();
		else
		{
			SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcsz);
			if (nCount > 0)
			{
				_CalcTStrBufRange(0, 0, nCount);
				SD_TStringCopyFrom(m_lptstr, nCount + 1, lpcsz);
			}
			else
				_CreateNullString();
		}
	};

	CSDString(SD_LPCWSTR lpcwsz)
	{
		m_lptstr = SD_NULL;
		SD_INT32 nWStrLen = SD_GetStrLen(lpcwsz);
		if (lpcwsz == SD_NULL || nWStrLen <=  0)
			_CreateNullString();
		else
		{
			SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcwsz);
			if (nCount > 0)
			{
				_CalcTStrBufRange(0, 0, nCount);
				SD_TStringCopyFrom(m_lptstr, nCount + 1, lpcwsz);
			}
			else
				_CreateNullString();
		}
	};

	CSDString(SD_LPCTSTR lpctsz, SD_INT32 nLength)
	{
		m_lptstr = SD_NULL;
		SD_INT32 nTStrLen = SD_GetStrLen(lpctsz);
		if (nTStrLen <=  0 || nLength <=  0)
			_CreateNullString();
		else
		{
			if (nTStrLen > nLength)
				nTStrLen = nLength;
			_CalcTStrBufRange(0, 0, nTStrLen);
			memcpy(m_lptstr, lpctsz, nTStrLen * sizeof(SD_TCHAR));
			m_lptstr[nTStrLen] = 0;
		}
	};

	CSDString(SD_CONST CSDString& stringSrc)
	{
		m_lptstr = SD_NULL;
		SD_UINT32 dwTCharMax, dwTCharNum, dwBufSize;
		stringSrc._GetTStringBufInfo(&dwTCharNum, &dwTCharMax, &dwBufSize);
		if (dwTCharNum == 0)
			_CreateNullString();
		else
		{
			m_lptstr = (SD_LPTSTR) new SD_INT8[dwBufSize];
			memcpy(m_lptstr, stringSrc.m_lptstr, dwBufSize);
			_SetTStringBufInfo(-1, dwTCharMax, dwTCharMax);
		}
	};

	// Implementation
public:
	~CSDString()
	{
		if (m_lptstr)
		{
			delete[] m_lptstr;
			m_lptstr = SD_NULL;
		}
	};

public:		// Attributes & Operations

	SD_INT32 GetLength() SD_CONST
	{ 
		return SD_GetStrLen(m_lptstr);
	};

	SD_VOID	SetStringLength(SD_INT32 nNewLength, SD_BOOL bIfEmptyThisString = SD_FALSE)
	{
		if (nNewLength >=  0)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
			
			if (bIfEmptyThisString)
				dwTCharNum = 0;

			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, (SD_UINT32)nNewLength);
		}
	};

	SD_BOOL IsEmpty() SD_CONST
	{
		return (m_lptstr == SD_NULL || m_lptstr[0] == 0);
	};

	SD_VOID Empty()
	{
		if (m_lptstr)
		{
			SD_UINT32 dwBufSize;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(SD_NULL, SD_NULL, &dwBufSize);

			if (dwTCharMalloc > _CSDSTRING_SkipLength)
			{
				delete[] m_lptstr;
				m_lptstr = SD_NULL;
				_CreateNullString();
			} 
			else
			{
				memset(m_lptstr, 0, dwBufSize);
				_SetTStringBufInfo(0, dwTCharMalloc);
			}
		}
	};

	SD_TCHAR GetAt(SD_INT32 nIndex) SD_CONST
	{
		if (nIndex < 0 || nIndex >=  GetLength())
			return 0;
		else
			return m_lptstr[nIndex];
	};

	SD_TCHAR operator[](SD_INT32 nIndex) SD_CONST
	{
		if (nIndex < 0 || nIndex >=  GetLength())
			return 0;
		else
			return m_lptstr[nIndex];
	};

	SD_VOID SetAt(SD_INT32 nIndex, SD_TCHAR tch)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		
		if (nIndex >=  0 && nIndex < (SD_INT32)dwTCharNum)
		{
			m_lptstr[nIndex] = tch;
			if (tch == 0)
				_SetTStringBufInfo((SD_UINT32)nIndex, dwTCharMalloc);
		}
	};

	SD_INT32 GetCharBuffer(SD_LPSTR pCharBuf, SD_INT32 nSizeChar) SD_CONST
	{
		if (GetLength() <=  0)
		{
			if (pCharBuf)
				pCharBuf[0] = 0;
			return 0;
		}
		return SD_TStringCopyToStr(m_lptstr, pCharBuf, nSizeChar);
	};

	SD_UINT32 GetWCharBuffer(SD_LPWSTR pWCharBuf, SD_INT32 nSizeWChar) SD_CONST
	{
		if (GetLength() <=  0)
		{
			if (pWCharBuf)
				pWCharBuf[0] = 0;
			return 0;
		}
		return SD_TStringCopyToWStr(m_lptstr, pWCharBuf, nSizeWChar);
	};

	SD_LPCTSTR GetTCharBuffer() SD_CONST
	{
		return (SD_LPCTSTR)m_lptstr;
	};

	operator SD_LPCTSTR() SD_CONST
	{
		return (SD_LPCTSTR)m_lptstr;
	};

public:		// operator  = 

	SD_CONST CSDString& operator = (SD_CHAR ch)
	{
		if (ch)
		{
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();

			SD_CHAR	pstr[2];
			pstr[0] = ch;
			pstr[1] = 0;
			
			if (SD_StringConvertToWString(SD_NULL, 0, pstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pstr);
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, 0, nCount);
					memcpy(m_lptstr, ptstr, nCount * sizeof(SD_TCHAR));
					m_lptstr[nCount] = 0;
				}
				else
					Empty();
			}
			else
				Empty();
		}
		else
			Empty();
		return (*this);
	};

	SD_CONST CSDString& operator = (SD_WCHAR wch)
	{
		if (wch)
		{
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();

			SD_WCHAR	pwstr[2];
			pwstr[0] = wch;
			pwstr[1] = 0;
			
			if (SD_WStringConvertToString(SD_NULL, 0, pwstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pwstr);
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, 0, nCount);
					memcpy(m_lptstr, ptstr, nCount * sizeof(SD_TCHAR));
					m_lptstr[nCount] = 0;
				}
				else
					Empty();
			}
			else
				Empty();
		}
		else
			Empty();
		return (*this);
	};

	SD_CONST CSDString& operator = (SD_LPCSTR lpcsz)
	{
		if (m_lptstr !=  (SD_LPCTSTR)lpcsz)
		{
			SD_INT32 nSrcStrLen = SD_GetStrLen(lpcsz);
			if (lpcsz && nSrcStrLen > 0)
			{
				SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();

				SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcsz);
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, 0, nCount);
					SD_TStringCopyFrom(m_lptstr, nCount + 1, lpcsz);
				}
				else
					Empty();
			} 
			else
				Empty();
		}
		return (*this);
	};

	SD_CONST CSDString& operator = (SD_LPCWSTR lpcwsz)	
	{
		if (m_lptstr !=  (SD_LPCTSTR)lpcwsz)
		{
			SD_INT32 nSrcWStrLen = SD_GetStrLen(lpcwsz);
			if (lpcwsz && nSrcWStrLen > 0)
			{
				SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();

				SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcwsz);
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, 0, nCount);
					SD_TStringCopyFrom(m_lptstr, nCount + 1, lpcwsz);
				}
				else
					Empty();
			} 
			else
				Empty();
		}
		return (*this);
	};

	SD_CONST CSDString& operator = (SD_CONST CSDString& stringSrc)
	{
		if (m_lptstr !=  stringSrc.m_lptstr)
		{
			SD_INT32 nTCharNum_Src = stringSrc.GetLength();
			if (nTCharNum_Src > 0)
			{
				SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();
				_CalcTStrBufRange(dwTCharMalloc, 0, nTCharNum_Src);
				memcpy(m_lptstr, stringSrc.m_lptstr, nTCharNum_Src * sizeof(SD_TCHAR));
				m_lptstr[nTCharNum_Src] = 0;
			} 
			else
				Empty();
		}
		return (*this);
	};

public:		// operator += 

	SD_CONST CSDString& operator +=  (SD_CHAR ch)
	{
		if (ch)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

			SD_CHAR	pstr[2];
			pstr[0] = ch;
			pstr[1] = 0;
			
			if (SD_StringConvertToWString(SD_NULL, 0, pstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pstr);
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);
					memcpy(&m_lptstr[dwTCharNum], ptstr, nCount * sizeof(SD_TCHAR));
					m_lptstr[dwTCharNum + nCount] = 0;
				}
			}
		}
		return (*this);
	};

	SD_CONST CSDString& operator +=  (SD_WCHAR wch)
	{
		if (wch)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

			SD_WCHAR	pwstr[2];
			pwstr[0] = wch;
			pwstr[1] = 0;
			
			if (SD_WStringConvertToString(SD_NULL, 0, pwstr) > 0)
			{
				SD_TCHAR	ptstr[16];
				SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pwstr);			
				if (nCount > 0)
				{
					_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);
					memcpy(&m_lptstr[dwTCharNum], ptstr, nCount * sizeof(SD_TCHAR));
					m_lptstr[dwTCharNum + nCount] = 0;
				}
			}
		}
		return (*this);
	};

	SD_CONST CSDString& operator +=  (SD_LPCSTR lpcsz)
	{
		SD_INT32 nSrcStrLen = SD_GetStrLen(lpcsz);
		if (lpcsz && nSrcStrLen > 0)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

			SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcsz);
			if (nCount > 0)
			{
				_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);
				SD_TStringCopyFrom(&m_lptstr[dwTCharNum], nCount + 1, lpcsz);
			}
		}
		return (*this);
	};

	SD_CONST CSDString& operator +=  (SD_LPCWSTR lpcwsz)
	{
		SD_INT32 nSrcWStrLen = SD_GetStrLen(lpcwsz);
		if (lpcwsz && nSrcWStrLen > 0)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

			SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcwsz);
			if (nCount > 0)
			{
				_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);
				SD_TStringCopyFrom(&m_lptstr[dwTCharNum], nCount + 1, lpcwsz);
			}
		}
		return (*this);
	};

	SD_CONST CSDString& operator +=  (SD_CONST CSDString& stringAdd)
	{
		SD_INT32 nLength_Add = stringAdd.GetLength();
		if (nLength_Add > 0)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nLength_Add);
			memcpy(&m_lptstr[dwTCharNum], stringAdd.m_lptstr, nLength_Add * sizeof(SD_TCHAR));
			m_lptstr[dwTCharNum + nLength_Add] = 0;
		}
		return (*this);
	};

public:		// operator +,  =  = , != , >, <, >= , <= 

	friend CSDString  operator + (SD_CONST CSDString& string1, SD_CONST CSDString& string2)
	{
		CSDString str(string1);
		str +=  string2;
		return str;
	};

	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_CHAR ch)
	{
		CSDString str(stringSrc);
		str +=  ch;
		return str;
	};

	friend CSDString  operator + (SD_CHAR ch, SD_CONST CSDString& stringSrc)
	{
		CSDString str(ch);
		str +=  stringSrc;
		return str;
	};

	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_WCHAR ch)
	{
		CSDString str(stringSrc);
		str +=  ch;
		return str;
	};

	friend CSDString  operator + (SD_WCHAR ch, SD_CONST CSDString& stringSrc)
	{
		CSDString str(ch);
		str +=  stringSrc;
		return str;
	};

	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_LPCSTR lpcsz)
	{
		CSDString str(stringSrc);
		str +=  lpcsz;
		return str;
	};

	friend CSDString  operator + (SD_LPCSTR lpcsz, SD_CONST CSDString& stringSrc)
	{
		CSDString str(lpcsz);
		str +=  stringSrc;
		return str;
	};

	friend CSDString  operator + (SD_CONST CSDString& stringSrc, SD_LPCWSTR lpcwsz)
	{
		CSDString str(stringSrc);
		str +=  lpcwsz;
		return str;
	};

	friend CSDString  operator + (SD_LPCWSTR lpcwsz, SD_CONST CSDString& stringSrc)
	{
		CSDString str(lpcwsz);
		str +=  stringSrc;
		return str;
	};

// (operator  =  = )
	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) == 0); 
	};

	friend SD_BOOL  operator == (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) == 0); 
	};

	friend SD_BOOL  operator == (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) == 0); 
	};

	friend SD_BOOL  operator == (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) == 0); 
	};

	friend SD_BOOL  operator == (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) == 0); 
	};

// (operator != )
	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) !=  0); 
	};

	friend SD_BOOL  operator !=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) !=  0); 
	};

	friend SD_BOOL  operator !=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) !=  0); 
	};

	friend SD_BOOL  operator !=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) !=  0); 
	};

	friend SD_BOOL  operator !=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) !=  0); 
	};

// (operator <)
	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) < 0); 
	};

	friend SD_BOOL  operator < (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) < 0); 
	};

	friend SD_BOOL  operator < (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) > 0); 
	};

	friend SD_BOOL  operator < (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) < 0); 
	};

	friend SD_BOOL  operator < (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) > 0); 
	};

// (operator >)
	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) > 0); 
	};

	friend SD_BOOL  operator > (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) > 0); 
	};

	friend SD_BOOL  operator > (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) < 0); 
	};

	friend SD_BOOL  operator > (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) > 0); 
	};

	friend SD_BOOL  operator > (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) < 0); 
	};

// (operator <= )
	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) <=  0); 
	};

	friend SD_BOOL  operator <=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) <=  0); 
	};

	friend SD_BOOL  operator <=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) >=  0); 
	};

	friend SD_BOOL  operator <=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) <=  0); 
	};

	friend SD_BOOL  operator <=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) >=  0); 
	};

// (operator >= )
	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) >=  0); 
	};

	friend SD_BOOL  operator >=  (SD_CONST CSDString& s, SD_LPCSTR lpcsz)
	{ 
		return (s.Compare(lpcsz) >=  0); 
	};

	friend SD_BOOL  operator >=  (SD_LPCSTR lpcsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcsz) <=  0); 
	};

	friend SD_BOOL  operator >=  (SD_CONST CSDString& s, SD_LPCWSTR lpcwsz)
	{ 
		return (s.Compare(lpcwsz) >=  0); 
	};

	friend SD_BOOL  operator >=  (SD_LPCWSTR lpcwsz, SD_CONST CSDString& s)
	{ 
		return (s.Compare(lpcwsz) <=  0); 
	};

public:		// string comparison

	SD_INT32 Compare(SD_LPCSTR lpcsz) SD_CONST
	{
		return _CompareWith(lpcsz, SD_FALSE);
	};

	SD_INT32 Compare(SD_LPCWSTR lpcwsz) SD_CONST
	{
		return _CompareWith(lpcwsz, SD_FALSE);
	};

	SD_INT32 Compare(CSDString stringCmp) SD_CONST
	{
		return _CompareWith(stringCmp.m_lptstr, SD_FALSE);
	};

	SD_INT32 CompareNoCase(SD_LPCSTR lpcsz) SD_CONST
	{
		return _CompareWith(lpcsz, SD_TRUE);
	};

	SD_INT32 CompareNoCase(SD_LPCWSTR lpcwsz) SD_CONST
	{
		return _CompareWith(lpcwsz, SD_TRUE);
	};

	SD_INT32 CompareNoCase(CSDString stringCmp) SD_CONST
	{
		return _CompareWith(stringCmp.m_lptstr, SD_TRUE);
	};

public:		// simple sub-string extraction

	CSDString Mid(SD_INT32 nFirst, SD_INT32 nCount) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		if (nFirst < 0)
			nFirst = 0;

		if (nFirst >=  nLength || nCount <=  0)
		{
			CSDString	strRet;
			return strRet;
		}
		else
		{
			SD_INT32 nCount_Mid = nCount;
			if (nFirst + nCount > nLength)
				nCount_Mid = nLength - nFirst;
			CSDString	strRet(&m_lptstr[nFirst], nCount_Mid);
			return strRet;
		}
	};

	CSDString Mid(SD_INT32 nFirst) SD_CONST
	{
		if (nFirst < 0)
			nFirst = 0;
		return Mid(nFirst, GetLength() - nFirst);
	};

	CSDString Left(SD_INT32 nCount) SD_CONST
	{
		return Mid(0, nCount);
	};

	CSDString Right(SD_INT32 nCount) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		if (nCount >=  nLength)
			return Mid(0, nLength);
		else
			return Mid(nLength-nCount, nCount);
	};

	//  characters from beginning that are also in passed string
	CSDString SpanIncluding(SD_LPCTSTR lpszCharSet) SD_CONST
	{
		CSDString	strRet;
		
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		if (dwTCharNum <=  0 || SD_GetCharPos(lpszCharSet, m_lptstr[0]) < 0)
			return strRet;

		strRet._CalcTStrBufRange(0, 0, dwTCharNum);
		dwTCharMalloc = strRet._GetTStringBufInfo();

		SD_UINT32 i, k = 0;
		SD_TCHAR	tch;
		for (i = 0; i < dwTCharNum; i ++)
		{
			tch = m_lptstr[i];
			if (SD_GetCharPos(lpszCharSet, tch) >=  0)
			{
				strRet.m_lptstr[k] = tch;
				k ++;
			}
			else
				break;
		}
		strRet._SetTStringBufInfo(k, dwTCharMalloc);
		return strRet;
	};

	CSDString SpanIncluding(CSDString strCharSet) SD_CONST
	{
		return SpanIncluding((SD_LPCTSTR)strCharSet);
	};

	// characters from beginning that are not also in passed string
	CSDString SpanExcluding(SD_LPCTSTR lpszCharSet) SD_CONST
	{
		CSDString	strRet;

		SD_UINT32 dwTStrLen = SD_GetStrLen(lpszCharSet);
		if (lpszCharSet == SD_NULL || dwTStrLen <=  0)
		{
			strRet = m_lptstr;
			return strRet;
		}

		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		if (dwTCharNum <=  0 || SD_GetCharPos(lpszCharSet, m_lptstr[0]) >=  0)
			return strRet;

		strRet._CalcTStrBufRange(0, 0, dwTCharNum);
		dwTCharMalloc = strRet._GetTStringBufInfo();

		SD_UINT32 i, k = 0;
		SD_TCHAR	tch;
		for (i = 0; i < dwTCharNum; i ++)
		{
			tch = m_lptstr[i];
			if (SD_GetCharPos(lpszCharSet, tch) < 0)
			{
				strRet.m_lptstr[k] = tch;
				k ++;
			}
			else
				break;
		}
		strRet._SetTStringBufInfo(k, dwTCharMalloc);
		return strRet;
	};

	CSDString SpanExcluding(CSDString strCharSet) SD_CONST
	{
		return SpanExcluding((SD_LPCTSTR)strCharSet);
	};

public:		// upper/lower/reverse conversion

	CSDString& MakeUpper()
	{
		SD_INT32 nLength = GetLength();
		for (SD_INT32 i = 0; i < nLength; i ++)
		{
			int temp = (int)m_lptstr[i];
			if (0 == (temp>>8))  // 大于0xFF的中文字符，toupper函数可能会错误转换,原因不明
			{
				m_lptstr[i] = toupper(temp);
			}
		}
		return(*this);
	};

	CSDString& MakeLower()
	{
		SD_INT32 nLength = GetLength();
		for (SD_INT32 i = 0; i < nLength; i ++)
		{
			int temp = (int)m_lptstr[i];
			if (0 == (temp>>8))  // 大于0xFF的中文字符，toupper函数可能会错误转换,原因不明
			{
				m_lptstr[i] = tolower(m_lptstr[i]);
			}
		}
		return(*this);
	};

	CSDString& MakeReverse()
	{
		SD_INT32 nLength = GetLength();
		SD_INT32 nLength_12 = nLength/2;
		for (SD_INT32 i = 0; i < nLength_12; i ++)
		{
			SD_TCHAR tch = m_lptstr[i];
			m_lptstr[i] = m_lptstr[nLength - 1 - i];
			m_lptstr[nLength - 1 - i] = tch;
		}
		return(*this);
	};

public:		// trimming whitespace (either side)

	CSDString& TrimRight(SD_TCHAR chTarget = _T(' '))
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

		SD_INT32 i = (SD_INT32)dwTCharNum - 1;
		while (i >=  0)
		{
			if (m_lptstr[i] == chTarget)
			{
				m_lptstr[i] = 0;
				dwTCharNum = i;
				i --;
			} 
			else
				break;
		}
		_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		return(*this);
	};

	CSDString& TrimRight(SD_LPCTSTR lpszTargets)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		//SD_UINT32 dwTStrLen = SD_GetStrLen(lpszTargets);

		SD_INT32 i = (SD_INT32)dwTCharNum - 1;
		while (i >=  0)
		{
			if (SD_GetCharPos(lpszTargets, m_lptstr[i]) >=  0)
			{
				m_lptstr[i] = 0;
				dwTCharNum = i;
				i --;
			} 
			else
				break;
		}
		_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		return(*this);
	};

	CSDString& TrimRight(CSDString strTargets)
	{
		return TrimRight((SD_LPCTSTR)strTargets);
	};

	CSDString& TrimLeft(SD_TCHAR chTarget = _T(' '))
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

		SD_UINT32 j, i = 0;
		while (i < dwTCharNum)
		{
			if (m_lptstr[i] == chTarget)
				i ++;
			else
				break;
		}
		if (i > 0)
		{
			dwTCharNum -=  i;
			for (j = 0; j < dwTCharNum; j ++)
				m_lptstr[j] = m_lptstr[j + i];
			memset(&m_lptstr[dwTCharNum], 0, i * sizeof(SD_TCHAR));
			_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		}
		return(*this);
	};

	CSDString& TrimLeft(SD_LPCTSTR lpszTargets)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		//SD_UINT32 dwTStrLen = SD_GetStrLen(lpszTargets);

		SD_UINT32 j, i = 0;
		while (i < dwTCharNum)
		{
			if (SD_GetCharPos(lpszTargets, m_lptstr[i]) >=  0)
				i ++;
			else
				break;
		}
		if (i > 0)
		{
			dwTCharNum -=  i;
			for (j = 0; j < dwTCharNum; j ++)
				m_lptstr[j] = m_lptstr[j+i];
			memset(&m_lptstr[dwTCharNum], 0, i * sizeof(SD_TCHAR));
			_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		}
		return(*this);
	};

	CSDString& TrimLeft(CSDString strTargets)
	{
		return TrimLeft((SD_LPCTSTR)strTargets);
	};

	CSDString& Trim(SD_TCHAR chTarget = _T(' '))
	{
		TrimRight(chTarget);
		return TrimLeft(chTarget);
	};

	CSDString& Trim(SD_LPCTSTR pszTargets)
	{
		TrimRight(pszTargets);
		return TrimLeft(pszTargets);
	};

	CSDString& Trim(CSDString strTargets)
	{
		return TrimLeft((SD_LPCTSTR)strTargets);
	};

public:		// advanced manipulation

	SD_INT32 Replace(SD_TCHAR chOld, SD_TCHAR chNew)
	{
		SD_INT32 nLength = GetLength();
		SD_INT32 nCount = 0;
		for (SD_INT32 i = 0; i < nLength; i ++)
		{
			if (m_lptstr[i] == chOld)
			{
				m_lptstr[i] = chNew;
				nCount ++;
				if (chNew == 0 && nCount == 1)
				{
					_SetTStringBufInfo((SD_UINT32)i);
					break;
				}
			}
		}
		return nCount;
	};

	SD_INT32 Replace(SD_LPCTSTR lpszOld, SD_LPCTSTR lpszNew)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);	
		SD_UINT32 dwTStrLen_Old = SD_GetStrLen(lpszOld);
		if (lpszOld == SD_NULL || dwTStrLen_Old == 0 || dwTCharNum  == 0 || dwTCharNum < dwTStrLen_Old)
			return 0;

		SD_UINT32 dwTStrLen_New = SD_GetStrLen(lpszNew);
		SD_INT32 nCount = 0;
		SD_UINT32 i = 0, j, k;

		while (i <=  dwTCharNum - dwTStrLen_Old)
		{
			if (memcmp(&m_lptstr[i], lpszOld, dwTStrLen_Old * sizeof(SD_TCHAR)) == 0)
			{
				nCount ++;
				if (dwTStrLen_Old >=  dwTStrLen_New)
				{
					k = dwTStrLen_Old - dwTStrLen_New;
					dwTCharNum -=  k;
					for (j = 0; j < dwTStrLen_New; j ++)
						m_lptstr[j + i] = lpszNew[j];
					if (k > 0)
					{
						for (j = i + dwTStrLen_New; j < dwTCharNum; j ++)
							m_lptstr[j] = m_lptstr[j + k];
						memset(&m_lptstr[dwTCharNum], 0, k * sizeof(SD_TCHAR));
					}
					i +=  dwTStrLen_New;
				}
				else
				{
					k = dwTStrLen_New - dwTStrLen_Old;
					_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + k);
					dwTCharNum +=  k;
					for (j = dwTCharNum + k - 1; j >=  i + dwTStrLen_New; j --)
						m_lptstr[j] = m_lptstr[j-k];
					for (j = 0; j < dwTStrLen_New; j ++)
						m_lptstr[j+i] = lpszNew[j];
					i +=  dwTStrLen_New;
				}
			} 
			else
				i ++;
		}
		_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		return nCount;
	};

	SD_INT32 Remove(SD_TCHAR chRemove)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);	
		if (chRemove == 0 || dwTCharNum <=  0)
			return -1;

		SD_INT32 nCount = 0;
		SD_UINT32 j, i = 0;
		while (i < dwTCharNum)
		{
			if (m_lptstr[i] == chRemove)
			{
				for (j = i + 1; j < dwTCharNum; j ++)
					m_lptstr[j-1] = m_lptstr[j];
				dwTCharNum --;
				nCount ++;
				m_lptstr[dwTCharNum] = 0;
			}
			else
				i ++;
		}
		_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		return nCount;
	};

	SD_INT32 Delete(SD_INT32 nIndex, SD_INT32 nCount = 1)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		if (nCount <=  0 || nIndex < 0 || nIndex >=  (SD_INT32)dwTCharNum)
			return dwTCharNum;

		for (SD_UINT32 i = nIndex; i < dwTCharNum; i ++)
		{
			if (i + nCount < dwTCharNum)
				m_lptstr[i] = m_lptstr[i+nCount];
			else
				m_lptstr[i] = 0;
		}
		if (nIndex + nCount < (SD_INT32)dwTCharNum)
			dwTCharNum -=  nCount;
		else
			dwTCharNum = nIndex;
		_SetTStringBufInfo(dwTCharNum, dwTCharMalloc);
		return dwTCharNum;
	};

	SD_INT32 Append(SD_CHAR ch, SD_INT32 nRepeat = 1)
	{
		return Insert(0x7fffffff, ch, nRepeat);
	};

	SD_INT32 Append(SD_WCHAR wch, SD_INT32 nRepeat = 1)
	{
		return Insert(0x7fffffff, wch, nRepeat);
	};

	SD_INT32 Append(SD_LPCSTR lpcsz)
	{
		return Insert(0x7fffffff, lpcsz);
	};

	SD_INT32 Append(SD_LPCWSTR lpcwsz)
	{
		return Insert(0x7fffffff, lpcwsz);
	};

	SD_INT32 Append(SD_LPCTSTR lpctsz, SD_INT32 nLength)
	{
		return Insert(0x7fffffff, lpctsz, nLength);
	};

	SD_INT32 Append(SD_CONST CSDString& strSrc)
	{
		return Insert(0x7fffffff, strSrc);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_CHAR ch, SD_INT32 nRepeat = 1)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		if (ch == 0 || nRepeat <=  0)
			return dwTCharNum;

		SD_CHAR	pstr[2];
		pstr[0] = ch;
		pstr[1] = 0;
		if (SD_StringConvertToWString(SD_NULL, 0, pstr) <=  0)
			return dwTCharNum;
		
		if (nIndex < 0)
			nIndex = 0;
		if (nIndex > (SD_INT32)dwTCharNum)
			nIndex = dwTCharNum;

		SD_TCHAR	ptstr[16];
		SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pstr);		
		SD_INT32 nSize = nCount * nRepeat;
		if (nSize > 0)
		{
			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nSize);

			for (SD_INT32 i = (SD_INT32)dwTCharNum - 1; i >=  nIndex; i --)
				m_lptstr[i + nSize] = m_lptstr[i];

			SD_INT32 k = nIndex;
			for (SD_INT32 i = 0; i < nRepeat; i ++)
			{
				for (SD_INT32 j = 0; j < nCount; j ++)
				{
					m_lptstr[k] = ptstr[j];
					k ++;
				}
			}
		}
		return (dwTCharNum + nSize);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_WCHAR wch, SD_INT32 nRepeat = 1)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		if (wch == 0 || nRepeat <=  0)
			return dwTCharNum;

		SD_WCHAR	pwstr[2];
		pwstr[0] = wch;
		pwstr[1] = 0;
		if (SD_WStringConvertToString(SD_NULL, 0, pwstr) <=  0)
			return dwTCharNum;
		
		if (nIndex < 0)
			nIndex = 0;
		if (nIndex > (SD_INT32)dwTCharNum)
			nIndex = dwTCharNum;

		SD_TCHAR	ptstr[16];
		SD_INT32 nCount = SD_TStringCopyFrom(ptstr, 16, pwstr);
		SD_INT32 nSize = nCount * nRepeat;
		if (nSize > 0)
		{
			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nSize);

			for (SD_INT32 i = (SD_INT32)dwTCharNum - 1; i >=  nIndex; i --)
				m_lptstr[i + nSize] = m_lptstr[i];

			SD_INT32 k = nIndex;
			for (SD_INT32 i = 0; i < nRepeat; i ++)
			{
				for (SD_INT32 j = 0; j < nCount; j ++)
				{
					m_lptstr[k] = ptstr[j];
					k ++;
				}
			}
		}
		return (dwTCharNum + nSize);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCSTR lpcsz)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		SD_INT32 nStrLen = SD_GetStrLen(lpcsz);
		if (nStrLen <=  0)
			return dwTCharNum;

		if (nIndex < 0)
			nIndex = 0;
		if (nIndex > (SD_INT32)dwTCharNum)
			nIndex = dwTCharNum;

		SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcsz);
		if (nCount > 0)
		{
			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);

			for (SD_INT32 i = (SD_INT32)dwTCharNum - 1; i >=  nIndex; i --)
				m_lptstr[i + nCount] = m_lptstr[i];
			SD_TStringCopyFrom(&m_lptstr[nIndex], nCount + 1, lpcsz, SD_FALSE);
		}
		return (dwTCharNum + nCount);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCWSTR lpcwsz)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		SD_INT32 nWStrLen = SD_GetStrLen(lpcwsz);
		if (nWStrLen <=  0)
			return dwTCharNum;

		if (nIndex < 0)
			nIndex = 0;
		if (nIndex > (SD_INT32)dwTCharNum)
			nIndex = dwTCharNum;

		SD_INT32 nCount = SD_TStringCopyFrom(SD_NULL, 0, lpcwsz);
		if (nCount > 0)
		{
			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nCount);

			for (SD_INT32 i = (SD_INT32)dwTCharNum - 1; i >=  nIndex; i --)
				m_lptstr[i + nCount] = m_lptstr[i];
			SD_TStringCopyFrom(&m_lptstr[nIndex], nCount + 1, lpcwsz, SD_FALSE);
		}
		return (dwTCharNum + nCount);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_LPCTSTR lpctsz, SD_INT32 nLength)
	{
		SD_UINT32 dwTCharNum;
		SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		SD_INT32 nTStrLen = SD_GetStrLen(lpctsz);
		if (nTStrLen > nLength)
			nTStrLen = nLength;
		if (nTStrLen <=  0)
			return dwTCharNum;

		if (nIndex < 0)
			nIndex = 0;
		if (nIndex > (SD_INT32)dwTCharNum)
			nIndex = dwTCharNum;

		_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nTStrLen);

		for (SD_INT32 i = (SD_INT32)dwTCharNum - 1; i >=  nIndex; i --)
			m_lptstr[i + nTStrLen] = m_lptstr[i];
		memcpy(&m_lptstr[nIndex], lpctsz, nTStrLen * sizeof(SD_TCHAR));

		return (dwTCharNum + nTStrLen);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_CONST CSDString& strSrc)
	{
		return Insert(nIndex, strSrc.m_lptstr);
	};

public:		// searching

	SD_INT32 Find(SD_TCHAR tch, SD_INT32 nStart = 0) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		if (nStart < 0 || nStart >=  nLength || tch == 0)
			return -1;

		SD_INT32 nCount = 0;
#ifdef _UNICODE
		SD_WCHAR	pwstr[2];
		pwstr[0] = tch;
		pwstr[1] = 0;
		nCount = SD_WStringConvertToString(SD_NULL, 0, pwstr);
#else
		SD_CHAR	pstr[2];
		pstr[0] = tch;
		pstr[1] = 0;
		nCount = SD_StringConvertToWString(SD_NULL, 0, pstr);
#endif //_UNICODE
		if (nCount <=  0)
			return -1;

		for (SD_INT32 i = nStart; i < nLength; i ++)
		{
			if (m_lptstr[i] == tch)
				return i;
		}
		return -1;
	};

	SD_INT32 ReverseFind(SD_TCHAR tch, SD_INT32 nStart = -1) SD_CONST
	{
		if (tch == 0)
			return -1;

		SD_INT32 nCount = 0;
#ifdef _UNICODE
		SD_WCHAR	pwstr[2];
		pwstr[0] = tch;
		pwstr[1] = 0;
		nCount = SD_WStringConvertToString(SD_NULL, 0, pwstr);
#else
		SD_CHAR	pstr[2];
		pstr[0] = tch;
		pstr[1] = 0;
		nCount = SD_StringConvertToWString(SD_NULL, 0, pstr);
#endif //_UNICODE
		if (nCount <=  0)
			return -1;

		SD_INT32 nLength = GetLength();
		if (nStart >=  nLength || nStart < 0)
			nStart = nLength - 1;

		for (SD_INT32 i = nStart; i >=  0; i --)
		{
			if (m_lptstr[i] == tch)
				return i;
		}
		return -1;
	};

	SD_INT32 Find(SD_LPCTSTR lpszSub, SD_INT32 nStart = 0) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		SD_INT32 nTStrLen = SD_GetStrLen(lpszSub);
		if (nLength <=  0 || nTStrLen <=  0 || nStart < 0 || nLength < nTStrLen || nStart > nLength - nTStrLen)
			return -1;

		for (SD_INT32 i = nStart; i <=  nLength - nTStrLen; i ++)
		{
			if (memcmp(&m_lptstr[i], lpszSub, nTStrLen * sizeof(SD_TCHAR)) == 0)
				return i;
		}
		return -1;
	};

	SD_INT32 Find(CSDString strSub, SD_INT32 nStart = 0) SD_CONST
	{
		return Find((SD_LPCTSTR)strSub, nStart);
	};

	SD_INT32 FindOneOf(SD_LPCTSTR lpszCharSet) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		//SD_INT32 nTStrLen = SD_GetStrLen(lpszCharSet);

		SD_INT32 i, j;
		for (i = 0; i < nLength; i ++)
		{
			j = SD_GetCharPos(lpszCharSet, m_lptstr[i]);
			if (j >=  0)
				return i;
		}
		return -1;
	};

	SD_INT32 FindOneOf(CSDString strCharSet) SD_CONST
	{
		return FindOneOf((SD_LPCTSTR)strCharSet);
	};

	CSDString Tokenize(SD_LPCTSTR pszTokens, SD_INT32& iStart) SD_CONST
	{
		SD_INT32 nLength = GetLength();
		SD_INT32 nTStrLen = SD_GetStrLen(pszTokens);
		SD_INT32 i, j, m = -1, n = -1;
		
		if (iStart >=  0 && iStart < nLength && nTStrLen > 0)
		{
			for (i = iStart; i < nLength; i ++)
			{
				j = SD_GetCharPos(pszTokens, m_lptstr[i]);
				if (j < 0)
				{
					m = i;
					break;
				}
			}
			if (m >=  0)
			{
				for (i = m + 1; i < nLength; i ++)
				{
					j = SD_GetCharPos(pszTokens, m_lptstr[i]);
					if (j >=  0)
					{
						n = i;
						break;
					}
				}
				if (n < 0 && i >=  nLength)
					n = nLength;
				if (n - m > 0)
				{
					CSDString	strRet;
					strRet._CalcTStrBufRange(0, 0, (SD_UINT32)(n - m));
					memcpy(strRet.m_lptstr, &m_lptstr[m], (n - m) * sizeof(SD_TCHAR));
					iStart = n + 1;
					return strRet;
				}
			}
		}

		iStart = -1;
		CSDString	strRet;
		return strRet;
	};

	CSDString Tokenize(CSDString strTokens, SD_INT32& iStart) SD_CONST
	{
		return Tokenize((SD_LPCTSTR)strTokens, iStart);
	};

public:		// simple formatting
	
	SD_VOID Format(SD_LPCTSTR lpszFormat, ...)
	{
		va_list argList;
		va_start(argList, lpszFormat);

		_FormatV(lpszFormat, argList, SD_FALSE);

		va_end(argList);
	};

	SD_VOID Format(CSDString strFormat, ...)
	{
		va_list argList;
		va_start(argList, strFormat);

		_FormatV((SD_LPCTSTR)strFormat, argList, SD_FALSE);

		va_end(argList);
	};

	SD_VOID	AppendFormat(SD_LPCTSTR lpszFormat, ...)
	{
		va_list argList;
		va_start(argList, lpszFormat);

		_FormatV(lpszFormat, argList, SD_TRUE);

		va_end(argList);
	};

	SD_VOID	AppendFormat(CSDString strFormat, ...)
	{
		va_list argList;
		va_start(argList, strFormat);

		_FormatV((SD_LPCTSTR)strFormat, argList, SD_TRUE);

		va_end(argList);
	};

private:
	SD_LPTSTR	m_lptstr;

private:
	SD_UINT32 _GetTCharMaxNum(SD_UINT32 dwTCharNum) SD_CONST
	{
		if (dwTCharNum == 0)
			return _CSDSTRING_SegLength;
		else if ((dwTCharNum % _CSDSTRING_SegLength) == 0)
			return dwTCharNum;
		else
			return ((dwTCharNum / _CSDSTRING_SegLength + 1) * _CSDSTRING_SegLength);
	};

	SD_UINT32 _GetTSTRBufSize(SD_UINT32 dwTCharMax) SD_CONST
	{
		return ((dwTCharMax + 1) * sizeof(SD_TCHAR) + 2 * sizeof(SD_UINT32));
	};

	SD_UINT32 _GetTStringBufInfo(SD_PUINT32 pdwTCharNum = SD_NULL, SD_PUINT32 pdwTCharMax = SD_NULL, SD_PUINT32 pdwTStrBufSize = SD_NULL) SD_CONST
	{
		if (m_lptstr == SD_NULL)
		{
			if (pdwTCharNum)
				(*pdwTCharNum) = 0;
			if (pdwTCharMax)
				(*pdwTCharMax) = _CSDSTRING_SegLength;
			if (pdwTStrBufSize)
				(*pdwTStrBufSize) = (_CSDSTRING_SegLength + 1) * sizeof(SD_TCHAR) + 2 * sizeof(SD_UINT32);
			return 0;
		}
		else
		{
			SD_UINT32 dwTCharMax = _CSDSTRING_SegLength;
			while (m_lptstr[dwTCharMax])
				dwTCharMax +=  _CSDSTRING_SegLength;

			if (pdwTCharNum)
				(*pdwTCharNum) = (*((SD_UINT32 *)(&m_lptstr[dwTCharMax+1])));
			if (pdwTCharMax)
				(*pdwTCharMax) = dwTCharMax;
			if (pdwTStrBufSize)
				(*pdwTStrBufSize) = (dwTCharMax + 1) * sizeof(SD_TCHAR) + 2 * sizeof(SD_UINT32);
			return (*((SD_UINT32 *)(&(m_lptstr[dwTCharMax + 1])) + 1));
		}
	};

	SD_VOID		_SetTStringBufInfo(SD_INT32 nTCharNum = -1, SD_INT32 nTCharMalloc = -1, SD_UINT32 dwTCharMax = 0)
	{
		if (m_lptstr)
		{
			if (dwTCharMax == 0 && nTCharNum >=  0)
				dwTCharMax = _GetTCharMaxNum(nTCharNum);
			if (nTCharNum >=  0)
				(*((SD_UINT32 *)(&(m_lptstr[dwTCharMax + 1])))) = nTCharNum;
			if (nTCharMalloc >=  0)
				(*((SD_UINT32 *)(&(m_lptstr[dwTCharMax + 1])) + 1)) = nTCharMalloc;
		}
	};

	SD_VOID		_CreateNullString(SD_UINT32 dwMaxTCharNumSet = 0)
	{
		SD_UINT32 dwTCharMax = _GetTCharMaxNum(dwMaxTCharNumSet);
		SD_UINT32 dwBufSize = _GetTSTRBufSize(dwTCharMax);
		m_lptstr = (SD_LPTSTR) new SD_INT8[dwBufSize];
		memset(m_lptstr, 0, dwBufSize);
		_SetTStringBufInfo(-1, dwTCharMax, dwTCharMax);
	};

	SD_INT32 _CalcTStrBufRange(SD_UINT32 dwTStrBufLen, SD_UINT32 dwTCharNum_Old, SD_UINT32 dwTCharNum_New)
	{
		if (dwTCharNum_Old > dwTStrBufLen)
			dwTCharNum_Old = 0;
		SD_UINT32 dwTCharMax = _GetTCharMaxNum(dwTCharNum_New);
		SD_UINT32 dwBufSize = _GetTSTRBufSize(dwTCharMax);
		if (m_lptstr && dwTCharNum_New <=  dwTStrBufLen && dwTCharNum_New + _CSDSTRING_SkipLength > dwTStrBufLen)
		{
			if (dwTCharNum_Old <=  dwTCharNum_New)
				memset(&m_lptstr[dwTCharNum_Old], 0, (dwTStrBufLen - dwTCharNum_Old + 1) * sizeof(SD_TCHAR));
			else
				memset(&m_lptstr[dwTCharNum_New], 0, (dwTStrBufLen - dwTCharNum_New + 1) * sizeof(SD_TCHAR));
			_SetTStringBufInfo(dwTCharNum_New, dwTStrBufLen, dwTCharMax);
			return dwTCharMax;
		}

		SD_LPTSTR lptstr_Tmp = SD_NULL;
		if (m_lptstr && dwTCharNum_Old > 0)
		{
			lptstr_Tmp = new SD_TCHAR[dwTCharNum_Old];
			memcpy(lptstr_Tmp, m_lptstr, dwTCharNum_Old * sizeof(SD_TCHAR));
			delete[] m_lptstr;
		} 
		else if (m_lptstr)
			delete[] m_lptstr;

		m_lptstr = (SD_LPTSTR) new SD_INT8[dwBufSize];
		memset(m_lptstr, 0, dwBufSize);
		if (lptstr_Tmp)
		{
			if (dwTCharNum_Old <=  dwTCharNum_New)
				memcpy(m_lptstr, lptstr_Tmp, dwTCharNum_Old * sizeof(SD_TCHAR));
			else
				memcpy(m_lptstr, lptstr_Tmp, dwTCharNum_New * sizeof(SD_TCHAR));
			delete[] lptstr_Tmp;
		}

		_SetTStringBufInfo(dwTCharNum_New, dwTCharMax, dwTCharMax);
		return dwTCharMax;
	};

	SD_INT32 _CompareWith(SD_LPCSTR lpcsz, SD_BOOL bIsNoCase) SD_CONST
	{
		SD_INT32 nTCharNum = GetLength();
		SD_INT32 nTCharNum_Cmp = SD_TStringCopyFrom(SD_NULL, 0, lpcsz);

		if (nTCharNum > nTCharNum_Cmp)
			return 1;
		else if (nTCharNum < nTCharNum_Cmp)
			return -1;
		else if (nTCharNum == 0)
			return 0;
		else
		{
#ifdef _UNICODE
			SD_LPTSTR lptstr = new SD_TCHAR[nTCharNum_Cmp + 1];
			SD_TStringCopyFrom(lptstr, nTCharNum_Cmp + 1, lpcsz);

			SD_INT32 nRet = 0;
			if (bIsNoCase)
#ifdef _MSC_VER
				nRet = _wcsnicmp(m_lptstr, lptstr, nTCharNum);
#else
				nRet = wcsncasecmp(m_lptstr, lptstr, nTCharNum);
#endif	//_MSC_VER
			else
				nRet = wcsncmp(m_lptstr, lptstr, nTCharNum);

			delete[] lptstr;
			return nRet;
#else
			if (bIsNoCase)
#ifdef _MSC_VER
				return _strnicmp(m_lptstr, lpcsz, nTCharNum);
#else
				return strncasecmp(m_lptstr, lpcsz, nTCharNum);
#endif	//_MSC_VER
			else
				return strncmp(m_lptstr, lpcsz, nTCharNum);
#endif	//_UNICODE
		}
	};

	SD_INT32 _CompareWith(SD_LPCWSTR lpcwsz, SD_BOOL bIsNoCase) SD_CONST
	{
		SD_INT32 nTCharNum = GetLength();
		SD_INT32 nTCharNum_Cmp = SD_TStringCopyFrom(SD_NULL, 0, lpcwsz);

		if (nTCharNum > nTCharNum_Cmp)
			return 1;
		else if (nTCharNum < nTCharNum_Cmp)
			return -1;
		else if (nTCharNum == 0)
			return 0;
		else
		{
#ifdef _UNICODE
			if (bIsNoCase)
#ifdef _MSC_VER
				return _wcsnicmp(m_lptstr, lpcwsz, nTCharNum);
#else
				return wcsncasecmp(m_lptstr, lpcwsz, nTCharNum);
#endif	//_MSC_VER
			else
				return wcsncmp(m_lptstr, lpcwsz, nTCharNum);
#else
			SD_LPTSTR lptstr = new SD_TCHAR[nTCharNum_Cmp + 1];
			SD_TStringCopyFrom(lptstr, nTCharNum_Cmp + 1, lpcwsz);

			SD_INT32 nRet;
			if (bIsNoCase)
#ifdef _MSC_VER
				nRet = _strnicmp(m_lptstr, lptstr, nTCharNum);
#else
				nRet = strncasecmp(m_lptstr, lptstr, nTCharNum);
#endif	//_MSC_VER
			else
				nRet = strncmp(m_lptstr, lptstr, nTCharNum);
			delete[] lptstr;
			return nRet;
#endif	//_UNICODE
		}
	};

	SD_VOID	_FormatV(SD_LPCTSTR lpszFormat, va_list argList, SD_BOOL bIsAppend)
	{
		SD_UINT32 dwTCharMalloc, dwTCharNum = 0;
		if (bIsAppend)
			dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);
		else
			dwTCharMalloc = _GetTStringBufInfo();

#ifdef _MSC_VER

#ifdef _UNICODE
		SD_INT32 nBufLen = _vscwprintf(lpszFormat, argList);
#else //_UNICODE
		SD_INT32 nBufLen = _vscprintf(lpszFormat, argList);
#endif	//_UNICODE
		_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nBufLen);
		if (nBufLen > 0)
		{
#ifdef _UNICODE
			vswprintf_s(&m_lptstr[dwTCharNum], nBufLen + 1, lpszFormat, argList);
#else //_UNICODE
			vsprintf_s(&m_lptstr[dwTCharNum], nBufLen + 1, lpszFormat, argList);
#endif	//_UNICODE
		}

#else //_MSC_VER

		SD_TCHAR szBuffer[2048];
#ifdef _UNICODE
		SD_INT32 nBufLen = vswprintf(szBuffer, 2048, lpszFormat, argList);
#else //_UNICODE
		SD_INT32 nBufLen = vsprintf(szBuffer, lpszFormat, argList);
#endif	//_UNICODE
		_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + nBufLen);
		if (nBufLen > 0)
			memcpy(&m_lptstr[dwTCharNum], szBuffer, nBufLen * sizeof(SD_TCHAR));

#endif	//_MSC_VER
	};

#ifdef __AFX_H__
#if 0
public:

	CSDString(SD_CONST CSDString& strSrc)
	{
		m_lptstr = SD_NULL;
		SD_INT32 nStrLen = (SD_INT32)(strSrc.GetLength());
		if (nStrLen <=  0)
			_CreateNullString();
		else
		{
			_CalcTStrBufRange(0, 0, nStrLen);
			memcpy(m_lptstr, (SD_LPCTSTR)strSrc, nStrLen * sizeof(SD_TCHAR));
			m_lptstr[nStrLen] = 0;
		}
	};

	SD_CONST CSDString& operator = (SD_CONST CSDString& strSrc)
	{
		SD_UINT32 dwTCharNum_Src = (SD_UINT32)(strSrc.GetLength());
		if (dwTCharNum_Src > 0)
		{
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo();
			_CalcTStrBufRange(dwTCharMalloc, 0, dwTCharNum_Src);
			memcpy(m_lptstr, (SD_LPCTSTR)strSrc, dwTCharNum_Src * sizeof(SD_TCHAR));
			m_lptstr[dwTCharNum_Src] = 0;
		}
		else
			Empty();
		return (*this);
	};

	SD_CONST CSDString& operator +=  (SD_CONST CSDString& strAdd)
	{
		SD_UINT32 dwTCharNum_Add = (SD_UINT32)(strAdd.GetLength());
		if (dwTCharNum_Add > 0)
		{
			SD_UINT32 dwTCharNum;
			SD_UINT32 dwTCharMalloc = _GetTStringBufInfo(&dwTCharNum);

			_CalcTStrBufRange(dwTCharMalloc, dwTCharNum, dwTCharNum + dwTCharNum_Add);
			memcpy(&m_lptstr[dwTCharNum], (SD_LPCTSTR)strAdd, dwTCharNum_Add * sizeof(SD_TCHAR));
			m_lptstr[dwTCharNum + dwTCharNum_Add] = 0;
		}
		return (*this);
	};

	friend CSDString  operator + (SD_CONST CSDString& s1, CSDString s2)
	{
		CSDString str(s1);
		str +=  s2;
		return str;
	};

	friend CSDString  operator + (CSDString s1, SD_CONST CSDString& s2)
	{
		CSDString str(s1);
		str +=  s2;
		return str;
	};

	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) == 0); 
	};

	friend SD_BOOL  operator == (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s1) == 0); 
	};

	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) !=  0); 
	};

	friend SD_BOOL  operator !=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s1) !=  0); 
	};

	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) < 0); 
	};

	friend SD_BOOL  operator < (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s1) >=  0); 
	};

	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) > 0); 
	};

	friend SD_BOOL  operator > (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s1) <=  0); 
	};

	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) <=  0); 
	};

	friend SD_BOOL  operator <=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s1) > 0); 
	};

	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s1.Compare(s2) >=  0); 
	};

	friend SD_BOOL  operator >=  (SD_CONST CSDString& s1, SD_CONST CSDString& s2)
	{ 
		return (s2.Compare(s2) < 0); 
	};


	SD_INT32 Compare(CSDString stringCmp) SD_CONST
	{
		return _CompareWith((SD_LPCTSTR)stringCmp, SD_FALSE);
	};

	SD_INT32 CompareNoCase(CSDString stringCmp) SD_CONST
	{
		return _CompareWith((SD_LPCTSTR)stringCmp, SD_TRUE);
	};

	CSDString SpanIncluding(CSDString strCharSet) SD_CONST
	{
		return SpanIncluding((SD_LPCTSTR)strCharSet);
	};

	CSDString SpanExcluding(CSDString strCharSet) SD_CONST
	{
		return SpanExcluding((SD_LPCTSTR)strCharSet);
	};

	CSDString& TrimRight(CSDString strTargets)
	{
		return TrimRight((SD_LPCTSTR)strTargets);
	};

	CSDString& TrimLeft(CSDString strTargets)
	{
		return TrimLeft((SD_LPCTSTR)strTargets);
	};

	CSDString& Trim(CSDString strTargets)
	{
		return TrimLeft((SD_LPCTSTR)strTargets);
	};

	SD_INT32 Append(SD_CONST CSDString& strSrc)
	{
		return Insert(0x7fffffff, (SD_LPCTSTR)strSrc);
	};

	SD_INT32 Insert(SD_INT32 nIndex, SD_CONST CSDString& strSrc)
	{
		return Insert(0x7fffffff, (SD_LPCTSTR)strSrc);
	};

	SD_INT32 Find(CSDString strSub, SD_INT32 nStart = 0) SD_CONST
	{
		return Find((SD_LPCTSTR)strSub, nStart);
	};

	SD_INT32 FindOneOf(CSDString strCharSet) SD_CONST
	{
		return FindOneOf((SD_LPCTSTR)strCharSet);
	};

	CSDString Tokenize(CSDString strTokens, SD_INT32& iStart) SD_CONST
	{
		return Tokenize((SD_LPCTSTR)strTokens, iStart);
	};

	SD_VOID Format(CSDString strFormat, ...)
	{
		va_list argList;
		va_start(argList, strFormat);

		_FormatV((SD_LPCTSTR)strFormat, argList, SD_FALSE);

		va_end(argList);
	};

	SD_VOID	AppendFormat(CSDString strFormat, ...)
	{
		va_list argList;
		va_start(argList, strFormat);

		_FormatV((SD_LPCTSTR)strFormat, argList, SD_TRUE);

		va_end(argList);
	};

	SD_VOID GetCSDString(CSDString& strDest) SD_CONST
	{
		strDest = CSDString(m_lptstr);
	};

	CSDString GetCSDString() SD_CONST
	{
		CSDString	strRet = CSDString(m_lptstr);
		return strRet;
	};
#endif
#endif	//__AFX_H__

};

#pragma warning(pop)

#endif //_SD_SDSTRING_H_
