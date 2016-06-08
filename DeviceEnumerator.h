#pragma once

#include "DevGUID.h"
#include "dbt.h"
#include <setupapi.h>

class CDeviceEnumerator
{
public:
	CDeviceEnumerator(void);
	virtual ~CDeviceEnumerator(void);
	void SetFilterGUID(CONST GUID *ClassGuid);

private:
	SP_DEVINFO_DATA m_DeviceInfoData;
	HDEVINFO m_hDevInfo;
	GUID m_ClassGuid;
	CMapStringToPtr m_arClassMap;
};
