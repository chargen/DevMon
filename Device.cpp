#include "stdafx.h"
#include "device.h"
#include <objbase.h>
#include <initguid.h>
#include <devguid.h>
#include <rpc.h>
void
CDevice::GetProperty(
    HMACHINE hMachine,
    DEVNODE dn,
    ULONG Property,
    int IdType
    )
{
    CString strType,str;
	LPTSTR p;
    TCHAR Buffer[REGSTR_VAL_MAX_HCID_LEN];
    ULONG Type;
	DWORD Data=0;
    ULONG Size = sizeof(Buffer);
    strType.LoadString(IdType);
    // preload default string
    strType.LoadString(IDS_UNKNOWN);
    lstrcpy(Buffer, (LPCTSTR)strType);
    strType.LoadString(IdType);

	if(Property==CM_DRP_INSTALL_STATE_PROBLEM)
	{
		int xxx = 1;
	}

    if (CR_SUCCESS == CM_Get_DevNode_Registry_Property_Ex(dn, Property,
							  &Type,
							  Buffer,
							  &Size,
							  0, hMachine))
    {
		switch(Type)
		{
			case REG_DWORD:
				Data = *((DWORD*)Buffer);
				wsprintf(Buffer, _T("%08x"), *((DWORD*)Buffer) );
				break;

			case REG_MULTI_SZ:
				break;

			case REG_BINARY:
				{
					switch(Property)
					{
						case CM_DRP_DEVICE_POWER_DATA:
							break;
						case CM_DRP_BUSTYPEGUID:
						{
							char buf2[32];
							for(int x=0;x<16;x++) buf2[x]=Buffer[x];
							sprintf(Buffer,"{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
								(BYTE)buf2[3],(BYTE)buf2[2],(BYTE)buf2[1],(BYTE)buf2[0],
								(BYTE)buf2[5],(BYTE)buf2[4],(BYTE)buf2[7],(BYTE)buf2[6],
								(BYTE)buf2[8],(BYTE)buf2[9],(BYTE)buf2[10],(BYTE)buf2[11],
								(BYTE)buf2[12],(BYTE)buf2[13],(BYTE)buf2[14],(BYTE)buf2[15]);
						}
						break;
					}
				}
				break;
		}
    }

    CAttribute* pAttr = new CAttribute(Property, Buffer);

	if(Property==CM_DRP_DEVICE_POWER_DATA)
	{
		PCM_POWER_DATA PD = (PCM_POWER_DATA)Buffer;
		pAttr->m_PowerData.PD_Size = PD->PD_Size;
		pAttr->m_PowerData.PD_MostRecentPowerState = PD->PD_MostRecentPowerState;
		pAttr->m_PowerData.PD_DeepestSystemWake = PD->PD_DeepestSystemWake;
		pAttr->m_PowerData.PD_Capabilities = PD->PD_Capabilities;
		pAttr->m_PowerData.PD_D1Latency = PD->PD_D1Latency;
		pAttr->m_PowerData.PD_D2Latency = PD->PD_D2Latency;
		pAttr->m_PowerData.PD_D3Latency = PD->PD_D3Latency;
		pAttr->m_PowerData.PD_PowerStateMapping[0] = PD->PD_PowerStateMapping[0];
		pAttr->m_PowerData.PD_PowerStateMapping[1] = PD->PD_PowerStateMapping[1];
		pAttr->m_PowerData.PD_PowerStateMapping[2] = PD->PD_PowerStateMapping[2];
		pAttr->m_PowerData.PD_PowerStateMapping[3] = PD->PD_PowerStateMapping[3];
		pAttr->m_PowerData.PD_PowerStateMapping[4] = PD->PD_PowerStateMapping[4];
		pAttr->m_PowerData.PD_PowerStateMapping[5] = PD->PD_PowerStateMapping[5];
		pAttr->m_PowerData.PD_PowerStateMapping[6] = PD->PD_PowerStateMapping[6];
		pAttr->m_PowerData.PD_PowerStateMapping[7] = PD->PD_PowerStateMapping[7];
	}

	pAttr->m_dwValue = Data;

	if(Property==CM_DRP_DEVICEDESC)
	{		
		pAttr->m_bHardwareDesc = FALSE;
	}

	pAttr->m_nValType = Type;
	if(Type==REG_MULTI_SZ)
	{
		p = Buffer;
		str = p;
		pAttr->m_strStrList.Add(str);
		do 
		{
			p += lstrlen(p);
			
			if (*p==0) *p++;
			if(lstrlen(p))
			{
				str = p;
				pAttr->m_strStrList.Add(str);
				p += lstrlen(p);
				*p++;
			}
		} while (*p != 0);
	
	} else pAttr->m_strStrList.Add(Buffer);

    m_listAttributes.AddTail(pAttr);
}


// prepare device's attributes
BOOL CDevice::Create(HMACHINE hMachine,DEVNODE  DevNode)
{
    CString	strType;
    CString	strValue;
    LPTSTR	Buffer;
    int  BufferSize = MAX_PATH + MAX_DEVICE_ID_LEN;
    ULONG  BufferLen = BufferSize * sizeof(TCHAR);
    m_pSibling = NULL;
    m_pParent = NULL;
    m_pChild = NULL;
    m_ImageIndex = 0;
	m_dnThis = DevNode;

    Buffer  = strValue.GetBuffer(BufferSize);
    if (CR_SUCCESS == CM_Get_DevNode_Registry_Property_Ex(DevNode,
					CM_DRP_FRIENDLYNAME, NULL,
					Buffer, &BufferLen, 0, hMachine))
    {
		m_strDisplayName = Buffer;
    }
    else
    {
		BufferLen = BufferSize * sizeof(TCHAR);
		if (CR_SUCCESS == CM_Get_DevNode_Registry_Property_Ex(DevNode,
					CM_DRP_DEVICEDESC, NULL,
					Buffer, &BufferLen, 0, hMachine))
		{
			m_strDisplayName = Buffer;
		}
		else
		{
			m_strDisplayName.LoadString(IDS_UNKNOWN);
		}
    }

    CAttribute* pAttr;
    // pepare device' attributes
    // do standard ones first;
    if (CR_SUCCESS == CM_Get_Device_ID_Ex(DevNode, Buffer, BufferSize, 0, hMachine))
    {
		strType.LoadString(IDS_DEVICEID);
		pAttr = new CAttribute(CM_DRP_HARDWAREDESC, Buffer);
		pAttr->m_strStrList.Add(Buffer);
		pAttr->m_bHardwareDesc = TRUE;
		m_listAttributes.AddTail(pAttr);
    }

    ULONG Status, Problem;

	if (CR_SUCCESS == CM_Get_DevNode_Status_Ex(&Status, &Problem, DevNode, 0, hMachine))
    {
		strValue.Format(_T("%08x"), Status);
		pAttr = new CAttribute(CM_DRP_INSTALL_STATE, strValue);
		pAttr->m_strStrList.Add(strValue);
		pAttr->m_dwValue = Status;
		m_listAttributes.AddTail(pAttr);
		strValue.Format(_T("%08x"), Problem);
		pAttr = new CAttribute(CM_DRP_INSTALL_STATE_PROBLEM, strValue);
		pAttr->m_strStrList.Add(strValue);
		pAttr->m_bProblem = TRUE;
		pAttr->m_dwValue = Status;
		m_listAttributes.AddTail(pAttr);
    }

    GetProperty(hMachine, DevNode, CM_DRP_SERVICE, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_CAPABILITIES, REG_DWORD);
    GetProperty(hMachine, DevNode, CM_DRP_CONFIGFLAGS, REG_DWORD);
    GetProperty(hMachine, DevNode, CM_DRP_MFG, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_CLASS, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_HARDWAREID, REG_MULTI_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_COMPATIBLEIDS, REG_MULTI_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_CLASSGUID, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_LOCATION_INFORMATION, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_BUSNUMBER, REG_DWORD);
    GetProperty(hMachine, DevNode, CM_DRP_ENUMERATOR_NAME, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_DEVICEDESC, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_FRIENDLYNAME, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_DRIVER, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_PHYSICAL_DEVICE_OBJECT_NAME, REG_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_UI_NUMBER, REG_DWORD);
    GetProperty(hMachine, DevNode, CM_DRP_UPPERFILTERS, REG_MULTI_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_LOWERFILTERS, REG_MULTI_SZ);
    GetProperty(hMachine, DevNode, CM_DRP_BUSTYPEGUID, REG_BINARY);
    GetProperty(hMachine, DevNode, CM_DRP_LEGACYBUSTYPE, REG_DWORD);
	GetProperty(hMachine, DevNode, CM_DRP_DEVICE_POWER_DATA, REG_BINARY);
	GetProperty(hMachine, DevNode, CM_DRP_REMOVAL_POLICY, REG_DWORD);
    return TRUE;
}

BOOL CDevice::GetAttribute(int nType,CAttribute** ppAttr)
{
	CAttribute* pAtt;

	for(int i=0;i<NumberOfAttributes();i++)
	{
		EnumerateAttribute(i,&pAtt);
		if(pAtt->GetType()==nType)
		{
			*ppAttr = pAtt;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CDevice::EnumerateAttribute(int Index,CAttribute** ppAttr)
{
    if (m_listAttributes.IsEmpty() || Index >= m_listAttributes.GetCount())
	return FALSE;
    POSITION pos = m_listAttributes.FindIndex(Index);
    *ppAttr = m_listAttributes.GetAt(pos);
    return TRUE;
}

CDevice::~CDevice()
{
	LONG lReq;

    if (!m_listAttributes.IsEmpty())
    {
		POSITION pos = m_listAttributes.GetHeadPosition();
		while (NULL != pos)
		{
			CAttribute* pAtt = (CAttribute*)m_listAttributes.GetNext(pos);
			pAtt->m_strStrList.RemoveAll();
			delete pAtt;
		}
		m_listAttributes.RemoveAll();
    }
	if (AfxIsMemoryBlock(m_pChild,sizeof(CDevice),&lReq))
	{
		delete m_pChild;
		m_pChild = NULL;
	}
	if (AfxIsMemoryBlock(m_pSibling,sizeof(CDevice),&lReq))
	{
		delete m_pSibling;
		m_pSibling = NULL;
	}
}

BOOL CMachine::Create(LPCTSTR ComputerName)
{
    TCHAR LocalComputer[MAX_PATH];
    DWORD Size = MAX_PATH - 2;
    GetComputerName(LocalComputer + 2, &Size);
    LocalComputer[0] = _T('\\');
    LocalComputer[1] = _T('\\');
    if (ComputerName && _T('\0') != *ComputerName &&
	_T('\\') == ComputerName[0] && _T('\\') == ComputerName[1])
    {
		m_strDisplayName = ComputerName + 2;
		m_IsLocal = (0 == lstrcmpi(ComputerName, LocalComputer));
		CONFIGRET cr;
	
		if (CR_SUCCESS != (cr = CM_Connect_Machine(ComputerName, &m_hMachine)))
		{
			m_hMachine = NULL;
			SetLastError(ERROR_INVALID_COMPUTERNAME);
			OutputDebugString(_T("Connect computer failed\n"));
			TCHAR Text[MAX_PATH];
			wsprintf(Text, _T("Machine Connection failed, cr= %lx(hex)\n"), cr);
			MessageBox(NULL, Text, _T("List Device"), MB_ICONSTOP | MB_OK);
			return FALSE;
		}
    }
    else
    {
		m_strDisplayName = LocalComputer + 2;
		m_IsLocal = TRUE;
		m_hMachine = NULL;
    }
    return TRUE;
}

CMachine::~CMachine()
{
    CM_Disconnect_Machine(m_hMachine);
}

