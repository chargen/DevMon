#include <afxtempl.h>
#include "resource.h"
#include <afxplex_.h>

class CMapDWordToPtr : public CObject
{

	DECLARE_DYNAMIC(CMapDWordToPtr)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		void* value;
		DWORD key;
	};

public:

// Construction
	/* explicit */ CMapDWordToPtr(INT_PTR nBlockSize = 10);

// Attributes
INT_PTR CMapDWordToPtr::GetCount() const
	{ return m_nCount; }
BOOL CMapDWordToPtr::IsEmpty() const
	{ return m_nCount == 0; }
void CMapDWordToPtr::SetAt(DWORD key, void* newValue)
	{ (*this)[key] = newValue; }
POSITION CMapDWordToPtr::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
UINT CMapDWordToPtr::GetHashTableSize() const
	{ return m_nHashTableSize; }

	// number of elements
	INT_PTR GetSize() const;

	// Lookup
	BOOL Lookup(DWORD key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	void*& operator[](DWORD key);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, void*& rValue) const;

	// advanced features for derived classes
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	INT_PTR m_nCount;
	CAssoc* m_pFreeList;
	struct CPlex* m_pBlocks;
	INT_PTR m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&, UINT&) const;

public:
	~CMapDWordToPtr();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif


protected:
	// local typedefs for CTypedPtrMap class template
	typedef DWORD BASE_KEY;
	typedef DWORD BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};

