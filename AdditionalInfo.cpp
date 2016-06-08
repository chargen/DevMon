// AdditionalInfo.cpp : implementation file
//

#include "stdafx.h"
#include "AdditionalInfo.h"


// CAdditionalInfo

CAdditionalInfo::CAdditionalInfo()
{
	m_pDevice = NULL;
}

CAdditionalInfo::~CAdditionalInfo()
{
	LONG lReq;

	if(AfxIsMemoryBlock(m_pDevice,sizeof(CDevice),&lReq)) 
	{
		delete m_pDevice;
		m_pDevice = NULL;
	}
}


// CAdditionalInfo member functions
