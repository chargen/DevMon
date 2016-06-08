#include "StdAfx.h"
#include ".\deviceenumerator.h"

CDeviceEnumerator::CDeviceEnumerator(void)
{
	m_hDevInfo = NULL;
    m_DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	SetFilterGUID(NULL);	
}

CDeviceEnumerator::~CDeviceEnumerator(void)
{
    if(m_hDevInfo) SetupDiDestroyDeviceInfoList(m_hDevInfo);
}

void CDeviceEnumerator::SetFilterGUID(CONST GUID *ClassGuid)
{
	m_ClassGuid = *ClassGuid;
}
