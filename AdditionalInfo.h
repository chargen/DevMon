#pragma once



#include "device.h"

// CAdditionalInfo command target

class CAdditionalInfo : public CObject
{
public:
	CAdditionalInfo();
	virtual ~CAdditionalInfo();

public:
	CDevice* m_pDevice;
	CString m_strINF;
	CString m_strProvider;
	CString m_strVersion;
	CString m_strDate;
	CString m_strSymbolicName;
	CString m_strImagePath;
};


