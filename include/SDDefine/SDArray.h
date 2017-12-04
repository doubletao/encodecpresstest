/***************************************************************************
* SDArray.h
*
* 公共头文件之一,EasyCode科技公司版权所有!
*
* 描述:		-仿MFC体系CArray类定义并实现的头文件。
*
* 目标:		-这个头文件实现了类似于MFC体系CArray类的功能,使用方式基本相同,并支持跨操作系统运行环境!
*
* Ver-0.9
*
****************************************************************************/
#ifndef _SD_CSDARRAY_H_
#define _SD_CSDARRAY_H_

#include <stdlib.h>
#include <assert.h>
#include <vector>

#include "SDType.h"

template< class TYPE, class ARG_TYPE = SD_CONST TYPE& >
class CSDArray 
{
public:		// Construction
	CSDArray();
	~CSDArray();

public:		// Attributes
	SD_INT_PTR	GetSize() SD_CONST;
	SD_UINT32	GetDWSize() SD_CONST;
	SD_INT_PTR	GetCount() SD_CONST;
	SD_BOOL		IsEmpty() SD_CONST;
	SD_INT_PTR	GetUpperBound() SD_CONST;
	SD_VOID		SetSize(SD_INT_PTR nNewSize, SD_INT_PTR nGrowBy = -1);

public:		// Operations --- Clean up
	SD_VOID FreeExtra();
	SD_VOID RemoveAll();

public:		// Accessing elements
	SD_CONST TYPE&	GetAt(SD_INT_PTR nIndex) SD_CONST;
	TYPE&			GetAt(SD_INT_PTR nIndex);
	SD_VOID			SetAt(SD_INT_PTR nIndex, ARG_TYPE newElement);
	SD_CONST TYPE&	ElementAt(SD_INT_PTR nIndex) SD_CONST;
	TYPE&			ElementAt(SD_INT_PTR nIndex);

public:		// Direct Access to the element data (may return SD_NULL)
	SD_CONST TYPE*	GetData() SD_CONST;
	TYPE*			GetData();

public:		// Potentially growing the array
	SD_VOID		SetAtGrow(SD_INT_PTR nIndex, ARG_TYPE newElement);
	SD_INT_PTR	Add(ARG_TYPE newElement);
	SD_INT_PTR	Append(SD_CONST CSDArray& src);
	SD_VOID		Copy(SD_CONST CSDArray& src);

public:		// overloaded operator helpers
	SD_CONST TYPE& operator[](SD_INT_PTR nIndex) SD_CONST;
	TYPE& operator[](SD_INT_PTR nIndex);

public:		// Operations that move elements around
	SD_VOID InsertAt(SD_INT_PTR nIndex, ARG_TYPE newElement, SD_INT_PTR nCount = 1);
	SD_VOID RemoveAt(SD_INT_PTR nIndex, SD_INT_PTR nCount = 1);
	SD_VOID InsertAt(SD_INT_PTR nStartIndex, CSDArray* pNewArray);

public:
	CSDArray(SD_CONST CSDArray &other)
    {
       *this = other;
    };  

    CSDArray & operator = (SD_CONST CSDArray &other)
    {
       this->Copy(other);
       return *this;
    };

protected:	// Implementation
	TYPE* m_pData;   // the actual array of data
	SD_INT_PTR m_nSize;     // # of elements (upperBound - 1)
	SD_INT_PTR m_nMaxSize;  // max allocated
	SD_INT_PTR m_nGrowBy;   // grow amount
};

/////////////////////////////////////////////////////////////////////////////
// CSDArray<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
CSDArray<TYPE, ARG_TYPE>::CSDArray()
{
	m_pData = SD_NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
};

template<class TYPE, class ARG_TYPE>
CSDArray<TYPE, ARG_TYPE>::~CSDArray()
{
	if(m_pData != SD_NULL)
	{
		for(SD_INT_PTR i = 0; i < m_nSize; i ++)
			(m_pData + i)->~TYPE();
		delete[] (SD_INT8*)m_pData;
	}
};


/////////////////////////////////////////////////////////////////////////////
// CSDArray<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_INT_PTR CSDArray<TYPE, ARG_TYPE>::GetSize() SD_CONST
{ 
	return m_nSize; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_UINT32 CSDArray<TYPE, ARG_TYPE>::GetDWSize() SD_CONST
{ 
	return (SD_UINT32)m_nSize; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_INT_PTR CSDArray<TYPE, ARG_TYPE>::GetCount() SD_CONST
{ 
	return m_nSize; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_BOOL CSDArray<TYPE, ARG_TYPE>::IsEmpty() SD_CONST
{ 
	return (m_nSize == 0); 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_INT_PTR CSDArray<TYPE, ARG_TYPE>::GetUpperBound() SD_CONST
{ 
	return (m_nSize - 1); 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_VOID CSDArray<TYPE, ARG_TYPE>::RemoveAll()
{ 
	SetSize(0, -1); 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE TYPE& CSDArray<TYPE, ARG_TYPE>::GetAt(SD_INT_PTR nIndex)
{ 
	if(nIndex >= m_nSize)
		nIndex = m_nSize - 1;
	if(nIndex < 0)
		nIndex = 0;

//	assert(nIndex < m_nSize);
	
	if(nIndex < m_nSize)
		return m_pData[nIndex];
	else
	{
		SetSize(1);
		return m_pData[0];
	}
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_CONST TYPE& CSDArray<TYPE, ARG_TYPE>::GetAt(SD_INT_PTR nIndex) SD_CONST
{
	if(nIndex >= m_nSize)
		nIndex = m_nSize - 1;
	if(nIndex < 0)
		nIndex = 0;

	assert(nIndex < m_nSize);

//	if(nIndex < m_nSize)
		return m_pData[nIndex]; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_VOID CSDArray<TYPE, ARG_TYPE>::SetAt(SD_INT_PTR nIndex, ARG_TYPE newElement)
{ 
	assert(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		m_pData[nIndex] = newElement; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_CONST TYPE& CSDArray<TYPE, ARG_TYPE>::ElementAt(SD_INT_PTR nIndex) SD_CONST
{ 
	if(nIndex >= m_nSize)
		nIndex = m_nSize - 1;
	if(nIndex < 0)
		nIndex = 0;

	assert(nIndex < m_nSize);

//	if(nIndex < m_nSize)
		return m_pData[nIndex]; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE TYPE& CSDArray<TYPE, ARG_TYPE>::ElementAt(SD_INT_PTR nIndex)
{ 
	if(nIndex >= m_nSize)
		nIndex = m_nSize - 1;
	if(nIndex < 0)
		nIndex = 0;

//	assert(nIndex < m_nSize);
	
	if(nIndex < m_nSize)
		return m_pData[nIndex];
	else
	{
		SetSize(1);
		return m_pData[0];
	}
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_CONST TYPE* CSDArray<TYPE, ARG_TYPE>::GetData() SD_CONST
{ 
	return (SD_CONST TYPE*)m_pData; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE TYPE* CSDArray<TYPE, ARG_TYPE>::GetData()
{ 
	return (TYPE*)m_pData; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_INT_PTR CSDArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
{ 
	SD_INT_PTR nIndex = m_nSize;
	SetAtGrow(nIndex, newElement);
	return nIndex; 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE SD_CONST TYPE& CSDArray<TYPE, ARG_TYPE>::operator[](SD_INT_PTR nIndex) SD_CONST
{ 
	return GetAt(nIndex); 
};

template<class TYPE, class ARG_TYPE>
SD_INLINE TYPE& CSDArray<TYPE, ARG_TYPE>::operator[](SD_INT_PTR nIndex)
{ 
	return ElementAt(nIndex); 
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::SetSize(SD_INT_PTR nNewSize, SD_INT_PTR nGrowBy/*= -1*/)
{
	assert(nNewSize >= 0);

	if(nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if(nNewSize == 0)	// shrink to nothing
	{
		if(m_pData != SD_NULL)
		{
			for(SD_INT_PTR i = 0; i < m_nSize; i++)
				(m_pData + i)->~TYPE();
			delete[] (SD_INT8*)m_pData;
			m_pData = SD_NULL;
		}
		m_nSize = m_nMaxSize = 0;
	}
	else if(m_pData == SD_NULL)
	{
		SD_INT_PTR nAllocSize = ((nNewSize >= m_nGrowBy) ? nNewSize : m_nGrowBy);
		m_pData = (TYPE*) new SD_INT8[ nAllocSize * sizeof(TYPE) ];
		memset((void*)m_pData, 0, nAllocSize * sizeof(TYPE));

		for(SD_INT_PTR i = 0; i < nNewSize; i++)
#pragma push_macro("new")
#undef new
			::new((void*)(m_pData + i)) TYPE;
#pragma pop_macro("new")

		m_nSize = nNewSize;
		m_nMaxSize = nAllocSize;
	}
	else if(nNewSize <= m_nMaxSize)
	{
		if(nNewSize > m_nSize)
		{
			memset((void*)(m_pData + m_nSize), 0, (nNewSize-m_nSize) * sizeof(TYPE));

			for(SD_INT_PTR i = 0; i < nNewSize-m_nSize; i++)
#pragma push_macro("new")
#undef new
				::new((void*)(m_pData + m_nSize + i)) TYPE;
#pragma pop_macro("new")
		}
		else if(m_nSize > nNewSize)
		{
			for(SD_INT_PTR i = 0; i < m_nSize-nNewSize; i++)
				(m_pData + nNewSize + i)->~TYPE();
		}
		m_nSize = nNewSize;
	}
	else
	{
		nGrowBy = m_nGrowBy;
		if(nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = m_nSize / 8;
			nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
		}
		SD_INT_PTR nNewMax;
		if(nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		assert(nNewMax >= m_nMaxSize);  // no wrap around

		TYPE* pNewData = (TYPE*) new SD_INT8[ nNewMax * sizeof(TYPE) ];

		memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));

		// construct remaining elements
		assert(nNewSize > m_nSize);
		memset((void*)(pNewData + m_nSize), 0, (nNewSize-m_nSize) * sizeof(TYPE));

		for(SD_INT_PTR i = 0; i < nNewSize-m_nSize; i++)
#pragma push_macro("new")
#undef new
			::new((void*)(pNewData + m_nSize + i)) TYPE;
#pragma pop_macro("new")

		// get rid of old stuff (note: no destructors called)
		delete[] (SD_INT8*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
};

template<class TYPE>
SD_INLINE SD_VOID SDCopyElements(TYPE* pDest, SD_CONST TYPE* pSrc, SD_INT_PTR nCount)
{
	// default is element-copy using assignment
	while(nCount--)
		*pDest++ = *pSrc++;
};


template<class TYPE, class ARG_TYPE>
SD_INT_PTR CSDArray<TYPE, ARG_TYPE>::Append(SD_CONST CSDArray& src)
{
	assert(this != &src);   // cannot append to itself

	SD_INT_PTR nOldSize = m_nSize;
	if(this != &src)
	{
		SetSize(m_nSize + src.m_nSize);
		SDCopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
	}
	return nOldSize;
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::Copy(SD_CONST CSDArray& src)
{
	assert(this != &src);   // cannot append to itself

	if(this != &src)
	{
		SetSize(src.m_nSize);
		SDCopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
	}
}

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::FreeExtra()
{
	if(m_nSize != m_nMaxSize)
	{
		TYPE* pNewData = SD_NULL;
		if(m_nSize != 0)
		{
			pNewData = (TYPE*) new SD_INT8[ m_nSize * sizeof(TYPE) ];
			memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));
		}

		delete[] (SD_INT8*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::SetAtGrow(SD_INT_PTR nIndex, ARG_TYPE newElement)
{
	assert(nIndex >= 0);

	if(nIndex >= m_nSize)
		SetSize(nIndex + 1, -1);
	m_pData[nIndex] = newElement;
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::InsertAt(SD_INT_PTR nIndex, ARG_TYPE newElement, SD_INT_PTR nCount /*=1*/)
{
	assert(nIndex >= 0);    // will expand to meet need
	assert(nCount > 0);     // zero or negative size not allowed

	if(nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		SD_INT_PTR nOldSize = m_nSize;
		SetSize(m_nSize + nCount, -1);  // grow it to new size

		// destroy intial data before copying over it
		for(SD_INT_PTR i = 0; i < nCount; i++)
			(m_pData + nOldSize + i)->~TYPE();
		// shift old data up to fill gap
		memmove(m_pData + nIndex + nCount, m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((void*)(m_pData + nIndex), 0, nCount * sizeof(TYPE));

		for(SD_INT_PTR i = 0; i < nCount; i++)
#pragma push_macro("new")
#undef new
			::new((void*)(m_pData + nIndex + i)) TYPE;
#pragma pop_macro("new")
	}

	// insert new value in the gap
	assert(nIndex + nCount <= m_nSize);
	while(nCount--)
		m_pData[nIndex++] = newElement;
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::RemoveAt(SD_INT_PTR nIndex, SD_INT_PTR nCount)
{
	assert(nIndex >= 0);
	assert(nCount >= 0);
	SD_INT_PTR nUpperBound = nIndex + nCount;
	assert(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	// just remove a range
	SD_INT_PTR nMoveCount = m_nSize - (nUpperBound);
	for(SD_INT_PTR i = 0; i < nCount; i++)
		(m_pData + nIndex + i)->~TYPE();
	if (nMoveCount)
		memmove(m_pData + nIndex, m_pData + nUpperBound, nMoveCount * sizeof(TYPE));
	m_nSize -= nCount;
};

template<class TYPE, class ARG_TYPE>
SD_VOID CSDArray<TYPE, ARG_TYPE>::InsertAt(SD_INT_PTR nStartIndex, CSDArray* pNewArray)
{
	assert(pNewArray != SD_NULL);
	assert(nStartIndex >= 0);

	SD_INT_PTR	nNewArraySize = pNewArray->GetSize();
	if(nNewArraySize > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), nNewArraySize);
		for(SD_INT_PTR i = 0; i < nNewArraySize; i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
};

#endif //_SD_CSDARRAY_H_
