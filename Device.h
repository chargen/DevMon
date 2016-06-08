#ifndef _DEVICE_H__
#define _DEVICE_H__

extern "C" {
#include <cfgmgr32.h>
#include <setupapi.h>
#include <regstr.h>
}

#include <afxtempl.h>
#include "resource.h"
#define CM_DRP_HARDWAREDESC 0x24
#define CM_DRP_INSTALL_STATE_PROBLEM 0x25

class CAttribute
{
public:
    CAttribute(ULONG Type, LPCTSTR Value)
    {
	m_lProperty = Type;
	m_bHardwareDesc = FALSE;
	m_nValType = -1;
	m_strValue = Value;
	m_bProblem = FALSE;
    }
    int GetType()
    {
		return m_lProperty;
    }
    LPCTSTR GetValue()
    {
		return m_strValue.IsEmpty() ? NULL : (LPCTSTR)m_strValue;
    }
    DWORD GetDWValue()
    {
		return m_dwValue;
    }
public:
    ULONG m_lProperty;
    CString m_strValue;
	DWORD m_dwValue;
	BOOL m_bProblem;
	BOOL m_bHardwareDesc;
	int m_nValType;
	CM_POWER_DATA m_PowerData;
	CStringArray m_strStrList;
};

class CDevice
{
public:

    CDevice() 
    {
		m_pParent = NULL;
		m_pSibling = NULL;
		m_pChild = NULL;
		m_ImageIndex=0;
    }

    BOOL Create(HMACHINE hMachine, DEVNODE dn);

    ~CDevice();

    CDevice* GetSibling(void)
    {
	return m_pSibling;
    }
    CDevice* GetChild(void)
    {
	return m_pChild;
    }
    CDevice* GetParent(void)
    {
	return m_pParent;
    }
    void SetChild(CDevice* pChild)
    {
	m_pChild = pChild;
    }
    void SetSibling(CDevice* pSibling)
    {
	m_pSibling = pSibling;
    }
    void SetParent(CDevice* pParent)
    {
	m_pParent = pParent;
    }
    LPCTSTR GetDisplayName()
    {
	return (LPCTSTR)m_strDisplayName;
    }
    int NumberOfAttributes()
    {
	return (int)m_listAttributes.GetCount();
    }
    void SetClassGuid(LPGUID pGuid)
    {
	m_ClassGuid = *pGuid;
    }
    void SetImageIndex(int Index)
    {
	m_ImageIndex = Index;
    }
    int GetImageIndex()
    {
	return m_ImageIndex;
    }
	BOOL GetAttribute(int nType,CAttribute** ppAttr);
	BOOL EnumerateAttribute(int Index, CAttribute** ppAttribute);
public:
    CString	m_strDisplayName;
	HTREEITEM m_hItem;
public:
    CDevice*	m_pParent;
    CDevice*	m_pSibling;
    CDevice*	m_pChild;
    int 	m_ImageIndex;
	DEVNODE m_dnThis;
    void GetProperty(HMACHINE hMachine, DEVNODE DevNode, ULONG Property, int IdType);
    GUID    m_ClassGuid;
    CList<CAttribute*, CAttribute*>	m_listAttributes;
};

class CMachine : public CDevice
{
public:
    CMachine() : m_hMachine(NULL)
    {}
    ~CMachine();
    BOOL Create(LPCTSTR ComputerName);

    operator HMACHINE()
    {
	return m_hMachine;
    }
private:
    BOOL	m_IsLocal;
    HMACHINE	m_hMachine;
};

#endif