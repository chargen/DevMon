// DevMonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DevMon.h"
#include "DevMonDlg.h"
#include ".\DevMondlg.h"
#include "strsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PNP_TIMER 7777

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnIdcancel();
//	afx_msg void OnIdcancel();
//	afx_msg void OnIdclose();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
//	ON_COMMAND(IDCANCEL, &CAboutDlg::OnIdcancel)
//ON_COMMAND(IDCANCEL, &CAboutDlg::OnIdcancel)
//ON_COMMAND(IDCLOSE, &CAboutDlg::OnIdclose)
END_MESSAGE_MAP()


// CDevMonDlg dialog



char strCMStatus[][64] =
{
"Filler",
"CM_PROB_NOT_CONFIGURED",
"CM_PROB_DEVLOADER_FAILED",
"CM_PROB_OUT_OF_MEMORY",
"CM_PROB_ENTRY_IS_WRONG_TYPE",
"CM_PROB_LACKED_ARBITRATOR",
"CM_PROB_BOOT_CONFIG_CONFLICT",
"CM_PROB_FAILED_FILTER",
"CM_PROB_DEVLOADER_NOT_FOUND",
"CM_PROB_INVALID_DATA",
"CM_PROB_FAILED_START",
"CM_PROB_LIAR",
"CM_PROB_NORMAL_CONFLICT",
"CM_PROB_NOT_VERIFIED",
"CM_PROB_NEED_RESTART",
"CM_PROB_REENUMERATION",
"CM_PROB_PARTIAL_LOG_CONF",
"CM_PROB_UNKNOWN_RESOURCE",
"CM_PROB_REINSTALL",
"CM_PROB_REGISTRY",
"CM_PROB_VXDLDR",
"CM_PROB_WILL_BE_REMOVED",
"CM_PROB_DISABLED",
"CM_PROB_DEVLOADER_NOT_READY",
"CM_PROB_DEVICE_NOT_THERE",
"CM_PROB_MOVED",
"CM_PROB_TOO_EARLY",
"CM_PROB_NO_VALID_LOG_CONF",
"CM_PROB_FAILED_INSTALL",
"CM_PROB_HARDWARE_DISABLED",
"CM_PROB_CANT_SHARE_IRQ",
"CM_PROB_FAILED_ADD",
"CM_PROB_DISABLED_SERVICE",
"CM_PROB_TRANSLATION_FAILED",
"CM_PROB_NO_SOFTCONFIG",
"CM_PROB_BIOS_TABLE",
"CM_PROB_IRQ_TRANSLATION_FAILED",
"CM_PROB_FAILED_DRIVER_ENTRY",
"CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD",
"CM_PROB_DRIVER_FAILED_LOAD",
"CM_PROB_DRIVER_SERVICE_KEY_INVALID",
"CM_PROB_LEGACY_SERVICE_NO_DEVICES",
"CM_PROB_DUPLICATE_DEVICE",
"CM_PROB_FAILED_POST_START",
"CM_PROB_HALTED",
"CM_PROB_PHANTOM",
"CM_PROB_SYSTEM_SHUTDOWN",
"CM_PROB_HELD_FOR_EJECT",
"CM_PROB_DRIVER_BLOCKED",
"CM_PROB_REGISTRY_TOO_LARGE",
};
char strDNStatus[][32] =
{
"DN_ROOT_ENUMERATED",
"DN_DRIVER_LOADED",
"DN_ENUM_LOADED",
"DN_STARTED",
"DN_MANUAL",
"DN_NEED_TO_ENUM",
"DN_NOT_FIRST_TIME",
"DN_HARDWARE_ENUM",
"DN_LIAR",
"DN_HAS_MARK",
"DN_HAS_PROBLEM",
"DN_FILTERED",
"DN_MOVED",
"DN_DISABLEABLE",
"DN_REMOVABLE",
"DN_PRIVATE_PROBLEM",
"DN_MF_PARENT",
"DN_MF_CHILD",
"DN_WILL_BE_REMOVED",
"DN_NOT_FIRST_TIME",
"DN_STOP_FREE_RES",
"DN_REBAL_CANDIDATE",
"DN_BAD_PARTIAL",
"DN_NT_ENUMERATOR",
"DN_NT_DRIVER",
"DN_NEEDS_LOCKING",
"DN_ARM_WAKEUP",
"DN_APM_ENUMERATOR",
"DN_APM_DRIVER",
"DN_SILENT_INSTALL",
"DN_NO_SHOW_IN_DM",
"DN_BOOT_LOG_PROB"
};

char strCRStatus[][64] =
{
"CR_SUCCESS",
"CR_DEFAULT",
"CR_OUT_OF_MEMORY",
"CR_INVALID_POINTER",
"CR_INVALID_FLAG",
"CR_INVALID_DEVNODE",
"CR_INVALID_DEVINST",
"CR_INVALID_RES_DES",
"CR_INVALID_LOG_CONF",
"CR_INVALID_ARBITRATOR",
"CR_INVALID_NODELIST",
"CR_DEVNODE_HAS_REQS",
"CR_DEVINST_HAS_REQS",
"CR_INVALID_RESOURCEID",
"CR_DLVXD_NOT_FOUND",  // WIN 95 ONLY
"CR_NO_SUCH_DEVNODE",
"CR_NO_SUCH_DEVINST",
"CR_NO_MORE_LOG_CONF",
"CR_NO_MORE_RES_DES",
"CR_ALREADY_SUCH_DEVNODE",
"CR_ALREADY_SUCH_DEVINST",
"CR_INVALID_RANGE_LIST",
"CR_INVALID_RANGE",
"CR_FAILURE",
"CR_NO_SUCH_LOGICAL_DEV",
"CR_CREATE_BLOCKED",
"CR_NOT_SYSTEM_VM", // WIN 95 ONLY
"CR_REMOVE_VETOED",
"CR_APM_VETOED",
"CR_INVALID_LOAD_TYPE",
"CR_BUFFER_SMALL",
"CR_NO_ARBITRATOR",
"CR_NO_REGISTRY_HANDLE",
"CR_REGISTRY_ERROR",
"CR_INVALID_DEVICE_ID",
"CR_INVALID_DATA",
"CR_INVALID_API",
"CR_DEVLOADER_NOT_READY",
"CR_NEED_RESTART",
"CR_NO_MORE_HW_PROFILES",
"CR_DEVICE_NOT_THERE",
"CR_NO_SUCH_VALUE",
"CR_WRONG_TYPE",
"CR_INVALID_PRIORITY",
"CR_NOT_DISABLEABLE",
"CR_FREE_RESOURCES",
"CR_QUERY_VETOED",
"CR_CANT_SHARE_IRQ",
"CR_NO_DEPENDENT",
"CR_SAME_RESOURCES",
"CR_NO_SUCH_REGISTRY_KEY",
"CR_INVALID_MACHINENAME", // NT ONLY
"CR_REMOTE_COMM_FAILURE", // NT ONLY
"CR_MACHINE_UNAVAILABLE", // NT ONLY
"CR_NO_CM_SERVICES",      // NT ONLY
"CR_ACCESS_DENIED",       // NT ONLY
"CR_CALL_NOT_IMPLEMENTED",
"CR_INVALID_PROPERTY",
"CR_DEVICE_INTERFACE_ACTIVE",
"CR_NO_SUCH_DEVICE_INTERFACE",
"CR_INVALID_REFERENCE_STRING",
"CR_INVALID_CONFLICT_LIST",
"CR_INVALID_INDEX",
"CR_INVALID_STRUCTURE_SIZE"
};

static	char cm_caps[][32]= {
	{ _T("Lockable")          },
	{ _T("Ejectable")         },
	{ _T("Removable")         },
	{ _T("Dock Device")       },
	{ _T("Has Unique ID")     },
	{ _T("Silent Install")    },
	{ _T("Raw Device")        },
	{ _T("Surprise Removal")  },
	{ _T("Hardware Disabled") },
	{ _T("Non-Dynamic")       },
	{ 0, NULL }
};

static char strTargetClass[32] = "USB";

static char lpszPwrData[][32] = 
{
	_T("D0 Supported"),
	_T("D1 Supported"),
	_T("D2 Supported"),
	_T("D3 Supported"),
	_T("Wake from D0 Supported"),
	_T("Wake from D1 Supported"),
	_T("Wake from D2 Supported"),
	_T("Wake from D3 Supported"),
	_T("Warm Eject Supported")
};


/***************************************************************/
#ifndef DIF_NEWDEVICEWIZARD_FINISHINSTALL
	#define DIF_NEWDEVICEWIZARD_FINISHINSTALL   0x0000001E
#endif

#define SIS_MEDIA_SOURCE_ID	1

FILE *g_pDebugFile=NULL;

// CInfInstallDlg message handlers


//================================================
// Get OriginalInfSourcePath %01% in inf
// Return value: 1: fail  0: success
//================================================  
int GetMediaRootDirectory(
    IN  HDEVINFO          DeviceInfoSet,  
    IN  PSP_DEVINFO_DATA  DeviceInfoData, 
    OUT LPTSTR           *MediaRootDirectory, 
    OUT LPTSTR           *MediaDiskName,
    OUT LPTSTR           *MediaTagFile,
    OUT LPTSTR           *MediaFileName)
{
    int nRet = 1;
    
    SP_DRVINFO_DATA DriverInfoData;
    PSP_DRVINFO_DETAIL_DATA DriverInfoDetailData = NULL;
    LPTSTR FileNamePart;
    TCHAR InfDirPath[MAX_PATH];
    HINF hInf = INVALID_HANDLE_VALUE;
    INFCONTEXT InfContext;
    DWORD PathLength;

    *MediaRootDirectory = NULL;
    *MediaDiskName = NULL;
    *MediaTagFile = NULL;
    *MediaFileName = NULL;

    // Get the full path of the INF being used to install this device.
	ZeroMemory(&DriverInfoData,sizeof(SP_DRVINFO_DATA));
    DriverInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
    if (!SetupDiGetSelectedDriver(DeviceInfoSet, DeviceInfoData, &DriverInfoData))  goto clean0;

    // Get the driver info details. 'DriverInfoDetailData' include InfFileName
    // We don't care about the id list at
    // the end, so we can just allocate a buffer for the fixed-size part...
    DriverInfoDetailData = (PSP_DRVINFO_DETAIL_DATA)GlobalAlloc(0, sizeof(SP_DRVINFO_DETAIL_DATA));
    if (!DriverInfoDetailData)  goto clean0;

    DriverInfoDetailData->cbSize = sizeof(SP_DRVINFO_DETAIL_DATA);
    if (!SetupDiGetDriverInfoDetail(DeviceInfoSet,
 									DeviceInfoData,
 									&DriverInfoData,
 									DriverInfoDetailData,
 									sizeof(SP_DRVINFO_DETAIL_DATA),
 									NULL)
		&& (GetLastError() != ERROR_INSUFFICIENT_BUFFER)) 
    {
        goto clean0;
    }

    *MediaRootDirectory = (LPTSTR)GlobalAlloc(0, MAX_PATH * sizeof(WCHAR));
    if (!*MediaRootDirectory) goto clean0;

    *MediaFileName = (LPTSTR)GlobalAlloc(0, _MAX_FNAME * sizeof(WCHAR));
    if (!*MediaFileName) goto clean0;

    // Strip the INF name off of the path.  (Resultant path will always end
    // with a path separator char ('\\').)
    PathLength = GetFullPathName(DriverInfoDetailData->InfFileName, 
                                 MAX_PATH, 
                                 *MediaRootDirectory, 
                                 &FileNamePart);
    if (!PathLength || (PathLength >= MAX_PATH))  goto clean0;

   	_tcscpy(*MediaFileName, FileNamePart);

    *FileNamePart = L'\0';

    // Check to see this INF is already in %windir%\Inf.
    PathLength = GetSystemWindowsDirectory(InfDirPath, MAX_PATH);
    if (!PathLength || (PathLength >= MAX_PATH))  goto clean0;

    // Append INF directory to path (making sure we don't end up with two path
    // separator chars).
    if ((InfDirPath[PathLength-1] != L'\\') && (InfDirPath[PathLength-1] != L'/'))
        lstrcpyn(&(InfDirPath[PathLength]), (LPCSTR)L"\\Inf\\", MAX_PATH - PathLength);
	else
        lstrcpyn(&(InfDirPath[PathLength]), (LPCSTR)L"Inf\\", MAX_PATH - PathLength);

    if (lstrcmpi(*MediaRootDirectory, InfDirPath))
    {
        // The INF isn't in %windir%\Inf, so assume its location is the root of
        // the installation media.  (We don't bother to retrieve the disk name
        // or tagfile name in this case.)
        nRet = 0;
        goto clean0;
    }

    // Since the INF is already in %windir%\Inf, we need to find out where it
    // originally came from.  There is no direct way to ascertain an INF's
    // path of origin, but we can indirectly determine it by retrieving a field
    // from our INF that uses a string substitution of %1% (DIRID_SRCPATH).
    //
    hInf = SetupOpenInfFile(DriverInfoDetailData->InfFileName,
                            NULL,
                            INF_STYLE_WIN4,
                            NULL);
    if (hInf == INVALID_HANDLE_VALUE) goto clean0;

    //
    // Contained within our INF should be a [SiSCoInfo] section with the
    // following entry:
    //
    //     OriginalInfSourcePath = %01%
    //
    // If we retrieve the value (i.e., field 1) of this line, we'll get the
    // full path where the INF originally came from.
    //
    if(!SetupFindFirstLine(hInf, (PCTSTR)L"SiSCoInfo", (PCTSTR)L"OriginalInfSourcePath", &InfContext))  goto clean0;
    if (!SetupGetStringField(&InfContext, 1, *MediaRootDirectory, MAX_PATH, &PathLength) ||
		(PathLength <= 1))
        goto clean0;

    //
    // PathLength we get back includes the terminating null character. Subtract
    // one to get actual length of string.
    //
    PathLength--;

    //
    // Ensure the path we retrieved has a path separator character at the end.
    //
    if (((*MediaRootDirectory)[PathLength-1] != L'\\') && 
       ((*MediaRootDirectory)[PathLength-1] != L'/')) 
        lstrcpyn(*MediaRootDirectory+PathLength, (LPCSTR)L"\\", MAX_PATH - PathLength);

    //
    // Now retrieve the disk name and tagfile for our setup media.
    //
    *MediaDiskName = (LPTSTR)GlobalAlloc(0, LINE_LEN * sizeof(WCHAR));
    *MediaTagFile = (LPTSTR)GlobalAlloc(0, MAX_PATH * sizeof(WCHAR));

    if (!(*MediaDiskName && *MediaTagFile))  goto clean0;

    if (!SetupGetSourceInfo(hInf, 
                           SIS_MEDIA_SOURCE_ID,
                           SRCINFO_DESCRIPTION,
                           *MediaDiskName,
                           LINE_LEN,
                           NULL))
        goto clean0;

    if (!SetupGetSourceInfo(hInf, 
                           SIS_MEDIA_SOURCE_ID,
                           SRCINFO_TAGFILE,
                           *MediaTagFile,
                           MAX_PATH,
                           NULL))
        goto clean0;

    nRet = 0;

clean0:
    
    if (hInf != INVALID_HANDLE_VALUE)
        SetupCloseInfFile(hInf);

    if (DriverInfoDetailData)
        GlobalFree(DriverInfoDetailData);

    if (nRet) //fail
    {
        if (*MediaRootDirectory)
        {
            GlobalFree(*MediaRootDirectory);
            *MediaRootDirectory = NULL;
        }

        if (*MediaDiskName)
        {
            GlobalFree(*MediaDiskName);
            *MediaDiskName = NULL;
        }

        if(*MediaTagFile)
        {
            GlobalFree(*MediaTagFile);
            *MediaTagFile = NULL;
        }

        if(*MediaFileName)
        {
            GlobalFree(*MediaFileName);
            *MediaFileName = NULL;
        }
    }

    return nRet;
}


BOOL GetInfDir(HDEVINFO DeviceInfoSet, PSP_DEVINFO_DATA DeviceInfoData, LPTSTR lpszInfDir, LPTSTR lpszInfName)
{
	int nRet=0;
	TCHAR *pszDir;
	TCHAR *pszDiskName;
	TCHAR *pszTagFile;
	TCHAR *pszFileName;

	// 0: success; 1: fail
	nRet=GetMediaRootDirectory(DeviceInfoSet, DeviceInfoData, (LPTSTR*)&pszDir, (LPTSTR*)&pszDiskName, (LPTSTR*)&pszTagFile, (LPTSTR*)&pszFileName);
	if (nRet) return FALSE;
	if (!pszDir || !pszFileName) return FALSE;
	fprintf(g_pDebugFile, "\t pszDir=%s\n", pszDir);
	fprintf(g_pDebugFile, "\t pszFileName=%s\n", pszFileName);
	if (_tcsstr(pszDir, "driverstore")) return FALSE;

	_tcscpy(lpszInfDir, pszDir);
	_tcscpy(lpszInfName, pszFileName);
	return TRUE;
}

/***************************************************************/

CDevMonDlg::CDevMonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevMonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hDevInfo = NULL;
	m_pCurrentDevice = NULL;
	m_pMachine = NULL;
	m_hDevInfo = NULL;
}

CDevMonDlg::~CDevMonDlg()
{
	DeleteAllRemnants();
	UnregisterDeviceNotification(m_hNotify);
}

void CDevMonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctlTree);
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CDevMonDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DEVICECHANGE,&CDevMonDlg::OnDeviceChange)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDevMonDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDevMonDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDevMonDlg message handlers

void CDevMonDlg::CreateInfSearchFolder(char *FolderName)
{  
	HKEY hOVTKey = NULL;  
	DWORD dwResult;  
	DWORD dwSize;
	char* nIndex;
	TCHAR szSysPath[2048];  
	
	dwResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
       TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion"),
       0,
       KEY_ALL_ACCESS,
       &hOVTKey
       );
 
	if(dwResult == ERROR_SUCCESS)
	{
		dwResult = RegQueryValueEx(hOVTKey,TEXT("DevicePath"),
			NULL,
			NULL,
			(LPBYTE) szSysPath,
			&dwSize);
  
		dwSize = strlen(szSysPath);
		if(dwSize !=0)
		{
			nIndex = strstr(szSysPath,FolderName);
			
			if(!nIndex) 
			{
				strcat(szSysPath, ";");
				strcat(szSysPath, FolderName);
				dwResult = RegSetValueEx(hOVTKey,
					TEXT("DevicePath"),
					0,
					REG_EXPAND_SZ,
					(LPBYTE) szSysPath,
					strlen(szSysPath)+1);
			}
		}
		else
		{
			strcpy(szSysPath, "%SystemRoot%\\");
			strcat(szSysPath, FolderName);
			dwResult = RegSetValueEx(hOVTKey,
				TEXT("DevicePath"),
				0,
				REG_EXPAND_SZ,
				(LPBYTE) szSysPath,
				strlen(szSysPath)+1);
		}
		RegCloseKey(hOVTKey);
	}
}

BOOL CDevMonDlg::OnInitDialog()
{
	CString str;

	CreateInfSearchFolder("C:\\Drivers");

// get path of executable
	char strEXEPath[MAX_PATH];
	VERIFY(::GetModuleFileName(::AfxGetInstanceHandle(), strEXEPath, MAX_PATH));

	LPTSTR lpszExt = _tcsrchr(strEXEPath, '\\');
	ASSERT(lpszExt != NULL);
	ASSERT(*lpszExt == '\\');
	*lpszExt = 0;       // no suffix

	
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ctlList.SetHorizontalExtent(1000);
	RefreshEntireTree();
/*
		//Obtain the system images for each class of device...
	m_pImages.cbSize = sizeof(SP_CLASSIMAGELIST_DATA);
	BOOL bRet = SetupDiGetClassImageList(&m_pImages);
	m_pImageList.Attach(m_pImages.ImageList);
	m_pImageList.SetBkColor(RGB(255,255,255));

	// Set the ROOT of the tree's to be the computer name + type...
	char buf[MAX_PATH];
	DWORD dwLen=MAX_PATH;
	::GetComputerName(buf,&dwLen);
	str.Format("%s(%s)",buf,"Devices");
	
	// Set the initial nodes of the trees...
	HICON hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEVICE_ICON));
	int nRootImgIndx = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GHOST));
	m_nGhostIndex = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_REGEDIT_ICON));
	m_nRegIndex = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	m_hDeviceRoot = m_ctlTree.InsertItem(str,nRootImgIndx,nRootImgIndx);

	//Fill the tree with DeviceInformation...
	BuildDeviceInfoTree(m_hDeviceRoot);

	// Now fill in the other tree with Node information...
	// Get the root node...
	DEVNODE dnRoot=NULL;
	CM_Locate_DevNode(&dnRoot,NULL, CM_LOCATE_DEVNODE_PHANTOM);
	DEVNODE dnFirst;
	CM_Get_Child(&dnFirst, dnRoot,0);

	m_pMachine = new CMachine();
	m_pMachine->Create(NULL);
	m_pMachine->m_hItem = m_hDeviceRoot;

	// Pretty up and sort...
	m_ctlTree.SortChildren(m_hDeviceRoot);
	m_ctlTree.Expand(m_hDeviceRoot,TVE_EXPAND);
*/	
    GUID ClassGuid = GUID_DEVCLASS_USB;
	DoRegisterDeviceInterface(ClassGuid,&m_hNotify);

	m_bPNPActive=FALSE;
	SetTimer(PNP_TIMER,1000,NULL);

	m_bDialogCreated = TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDevMonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDevMonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDevMonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDevMonDlg::RefreshEntireTree(void)
{
	CString str;

	DeleteAllRemnants();

		//Obtain the system images for each class of device...
	m_pImages.cbSize = sizeof(SP_CLASSIMAGELIST_DATA);
	BOOL bRet = SetupDiGetClassImageList(&m_pImages);
	m_pImageList.Attach(m_pImages.ImageList);
	m_pImageList.SetBkColor(RGB(255,255,255));

	// Set the ROOT of the tree's to be the computer name + type...
	char buf[MAX_PATH];
	DWORD dwLen=MAX_PATH;
	::GetComputerName(buf,&dwLen);
	str.Format("%s(%s)",buf,"Devices");
	
	// Set the initial nodes of the trees...
	HICON hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_DEVICE_ICON));
	int nRootImgIndx = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GHOST));
	m_nGhostIndex = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	hIcon = LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_REGEDIT_ICON));
	m_nRegIndex = ImageList_AddIcon(m_pImages.ImageList, hIcon);
	DeleteObject(hIcon);

	m_hDeviceRoot = m_ctlTree.InsertItem(str,nRootImgIndx,nRootImgIndx);

	//Fill the tree with DeviceInformation...
	BuildDeviceInfoTree(m_hDeviceRoot);

	// Now fill in the other tree with Node information...
	// Get the root node...
	DEVNODE dnRoot=NULL;
	CM_Locate_DevNode(&dnRoot,NULL, CM_LOCATE_DEVNODE_PHANTOM);
	DEVNODE dnFirst;
	CM_Get_Child(&dnFirst, dnRoot,0);

	m_pMachine = new CMachine();
	m_pMachine->Create(NULL);
	m_pMachine->m_hItem = m_hDeviceRoot;

	// Pretty up and sort...
	m_ctlTree.SortChildren(m_hDeviceRoot);
	m_ctlTree.Expand(m_hDeviceRoot,TVE_EXPAND);

	if(m_ctlTree.ItemHasChildren(m_hDeviceRoot))
	{
		HTREEITEM hChild = m_ctlTree.GetChildItem(m_hDeviceRoot);
		m_ctlTree.Expand(hChild,TVE_EXPAND);
	}

}

void CDevMonDlg::DeleteAllRemnants(void)
{
    if(m_hDevInfo) 
	{
		SetupDiDeleteDeviceInfo(m_hDevInfo,&m_DeviceInfoData);
		SetupDiDestroyDeviceInfoList(m_hDevInfo);
	}
	m_pImageList.DeleteImageList();

	//delete m_pMachine;

	POSITION pos = m_arAdditionalInfo.GetStartPosition();
	DWORD dwKey;
	LONG lReq;
	CAdditionalInfo* pInfo=NULL;

	while(pos)
	{
		m_arAdditionalInfo.GetNextAssoc(pos,dwKey,(void*&)pInfo);
		if(AfxIsMemoryBlock(pInfo,sizeof(CAdditionalInfo),&lReq))
		{
			delete pInfo;
		}
	}
	m_arAdditionalInfo.RemoveAll();

	m_arClassMap.RemoveAll();

	if(m_ctlTree.m_hWnd) m_ctlTree.DeleteAllItems();
}

void CDevMonDlg::BuildDeviceInfoTree(HTREEITEM m_hAddToNode)
{
    DWORD i;
	int j=0;
	int nIndex;
	LPGUID pClassGuid=NULL;
	DWORD dwNeededSize;
	DWORD dwError = CR_SUCCESS;
	GUID ClassGuid = GUID_DEVCLASS_USB;//GUID_DEVINTERFACE_USB_DEVICE;
	CString str;
	BOOL bNoNode = FALSE;
	CAdditionalInfo* pInfo;

	// Only clear the list upon building... leave the m_hDevInfo handle
	// around for later processing...

    if(m_hDevInfo) SetupDiDestroyDeviceInfoList(m_hDevInfo);

	// For a specific type of class, change the following...
	 m_hDevInfo = SetupDiGetClassDevs(NULL,//&ClassGuid, // See above
	 0, // Enumeratorb
     0,
     DIGCF_ALLCLASSES | DIGCF_PRESENT);//DIGCF_DEVICEINTERFACE); 
	
	if (m_hDevInfo == INVALID_HANDLE_VALUE)
    {
        // Insert error handling here.
		return;
    }
    
	//Obtain the system images for each class of device...
	m_ctlTree.SetImageList(&m_pImageList,TVSIL_NORMAL);

				// The main device enumeration loop...

	ZeroMemory(&m_DeviceInfoData,sizeof(SP_DEVINFO_DATA));
    m_DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	
	SP_DEVICE_INTERFACE_DATA m_InterfaceData;
	ZeroMemory(&m_InterfaceData,sizeof(m_InterfaceData));
	m_InterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	// Enumerate through all devices in Set.
    for (i=0;SetupDiEnumDeviceInfo(m_hDevInfo,i,&m_DeviceInfoData);i++)
    {
		ULONG lStatus=0;
		ULONG lProblem=0;
		bNoNode = FALSE;
		CONFIGRET cRet=CR_SUCCESS;
		DEVINST dnThis = m_DeviceInfoData.DevInst;
		DEVINST dnChild,dnSibling;
		SP_DRVINFO_DATA data;
		char InfDir[255];
		char InfName[255];

		GetInfDir(m_hDevInfo,&m_DeviceInfoData,&InfDir[0],&InfName[0]);

		ZeroMemory(&data,sizeof(SP_DRVINFO_DATA));
		data.cbSize = sizeof(SP_DRVINFO_DATA);
		if(SetupDiGetSelectedDriver(m_hDevInfo,&m_DeviceInfoData,&data))
		{
			int abc = 1;
		}

		Sleep(0);
		cRet = CM_Get_DevInst_Status(&lStatus,&lProblem,dnThis,0);
		if(IsPhantomDN(lProblem,lStatus,cRet)) 
		{
			if(cRet!=CR_INVALID_RESOURCEID) bNoNode = TRUE;
		}

		DEVINST dnParent=-1;

		// Get the parent node for this item and add it (and it's children) to the
		// m_arChildren element of CNodeInfo of the Parent CNodeInfo item...

		dwError = CM_Get_Parent(&dnParent,dnThis,0);
		if(dwError!=CR_SUCCESS)
		{
			int abc = 1;
		}
		
		// Based upon the the CLASS, fill in the tree...
		if(GetDevInfo(SPDRP_CLASS))
		{
			HTREEITEM pValue=NULL;
			HTREEITEM hNode,hChild;
			TVINSERTSTRUCT tviItem;
				
			if(_stricmp(m_strDevInfo,strTargetClass)) continue;
			
			DWORD dwIndex=0;
			for(int J=0;SetupDiEnumDeviceInterfaces(m_hDevInfo,NULL,&ClassGuid,dwIndex,&m_InterfaceData);J++)
			{
				DWORD dwSize=0;
				PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetail=NULL;
				SP_DEVINFO_DATA InterfaceData;

				InterfaceData.cbSize = sizeof(SP_DEVINFO_DATA);

				HKEY hKey = SetupDiOpenDeviceInterfaceRegKey(
					m_hDevInfo,
					&m_InterfaceData,
					0,
					KEY_ALL_ACCESS);

				if(hKey!=INVALID_HANDLE_VALUE)
				{

					RegCloseKey(hKey);
				}

				SetupDiGetDeviceInterfaceDetail(
					m_hDevInfo,&m_InterfaceData,NULL,0,&dwSize,NULL);

				pInterfaceDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR,dwSize);
				pInterfaceDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

				SetupDiGetDeviceInterfaceDetail(
					m_hDevInfo,&m_InterfaceData,pInterfaceDetail,dwSize,NULL,&InterfaceData);
         
				dwIndex++;
				LocalFree(pInterfaceDetail);
			}

			tviItem.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_STATE | TVIF_SELECTEDIMAGE;

			// Using our ID/String table, associate the data with a class(m_strDevInfo)...
			if(!m_arClassMap.Lookup(m_strDevInfo,(void*&)pValue))
			{
				pClassGuid = new GUID;
					
				BOOL bRet = SetupDiClassGuidsFromName(m_strDevInfo,pClassGuid,1,&dwNeededSize);
				// Get the image...
				bRet = SetupDiGetClassImageIndex(&m_pImages,pClassGuid,&nIndex);
				str.Format("%s",m_strDevInfo);
				hNode = m_ctlTree.InsertItem(str,nIndex,nIndex,m_hAddToNode,TVI_SORT);
				m_ctlTree.SetItemData(hNode,NULL);
				m_arClassMap.SetAt(m_strDevInfo,hNode);
					
				// Special case, disk drives have a device description of
				// "disk drive", not very usefull.  Use the FRIENDLYNAME instead.
				if(!GetDevInfo(SPDRP_DEVICEDESC)) m_strDevInfo = "Unknown";
				if(m_strDevInfo=="Disk drive") if(!GetDevInfo(SPDRP_FRIENDLYNAME)) m_strDevInfo = "Unknown";
				str.Format("%s [%04X]",m_strDevInfo,dnThis);
				if(bNoNode) nIndex = m_nGhostIndex;
				hChild = m_ctlTree.InsertItem(str,nIndex,nIndex,hNode,TVI_SORT);
				m_ctlTree.SetItemData(hChild,dnThis);
				pInfo = GetAdditionalInfo(dnThis);
				InsertProperties(hChild,dnThis,pInfo);

				HTREEITEM hCh;

				if(CM_Get_Child(&dnChild,dnThis,0)==CR_SUCCESS)
				{
					CAdditionalInfo* pInfo=NULL;
					pInfo = GetAdditionalInfo(dnChild);
					if(pInfo) m_strDevInfo = pInfo->m_pDevice->m_strDisplayName + " [Child]";
					hCh = m_ctlTree.InsertItem(m_strDevInfo,nIndex,nIndex,hChild,TVI_SORT);
					InsertProperties(hCh,dnChild,pInfo);
					m_ctlTree.SetItemData(hCh,dnChild);
				}
				dnSibling = dnChild;
				
				while(CM_Get_Sibling(&dnChild,dnSibling,0)==CR_SUCCESS)
				{
					CAdditionalInfo* pInfo=NULL;
					pInfo = GetAdditionalInfo(dnChild);
					if(pInfo) m_strDevInfo = pInfo->m_pDevice->m_strDisplayName + " [Sibling]";
					hCh = m_ctlTree.InsertItem(m_strDevInfo,nIndex,nIndex,hChild,TVI_SORT);
					InsertProperties(hCh,dnChild,pInfo);
					m_ctlTree.SetItemData(hCh,dnChild);
					dnSibling = dnChild;
				}
				delete pClassGuid;
			}
			else 
			{
				pClassGuid = new GUID;
					
				BOOL bRet = SetupDiClassGuidsFromName(m_strDevInfo,pClassGuid,1,&dwNeededSize);
				// Get the image...
				bRet = SetupDiGetClassImageIndex(&m_pImages,pClassGuid,&nIndex);
				if(!GetDevInfo(SPDRP_DEVICEDESC)) m_strDevInfo = "Unknown";
				if(m_strDevInfo=="Disk drive") if(!GetDevInfo(SPDRP_FRIENDLYNAME)) m_strDevInfo = "Unknown";
				str.Format("%s [%04X]",m_strDevInfo,dnThis);
				if(bNoNode) nIndex = m_nGhostIndex;
				hChild = m_ctlTree.InsertItem(str,nIndex,nIndex,pValue,TVI_SORT);
				m_ctlTree.SetItemData(hChild,dnThis);
				pInfo = GetAdditionalInfo(dnThis);
				InsertProperties(hChild,dnThis,pInfo);


				HTREEITEM hCh;

				if(CM_Get_Child(&dnChild,dnThis,0)==CR_SUCCESS)
				{
					CAdditionalInfo* pInfo=NULL;
					pInfo = GetAdditionalInfo(dnChild);
					if(pInfo) m_strDevInfo = pInfo->m_pDevice->m_strDisplayName + " [Child]";
					hCh = m_ctlTree.InsertItem(m_strDevInfo,nIndex,nIndex,hChild,TVI_SORT);
					InsertProperties(hCh,dnChild,pInfo);
					m_ctlTree.SetItemData(hCh,dnChild);
				}
				dnSibling = dnChild;

				while(CM_Get_Sibling(&dnChild,dnSibling,0)==CR_SUCCESS)
				{
					CAdditionalInfo* pInfo=NULL;
					pInfo = GetAdditionalInfo(dnChild);
					if(pInfo) m_strDevInfo = pInfo->m_pDevice->m_strDisplayName + " [Sibling]";
					hCh = m_ctlTree.InsertItem(m_strDevInfo,nIndex,nIndex,hChild,TVI_SORT);
					InsertProperties(hCh,dnChild,pInfo);
					m_ctlTree.SetItemData(hCh,dnChild);
					dnSibling = dnChild;
				}

				delete pClassGuid;
			}
		}
	}

      if ( GetLastError()!=NO_ERROR && GetLastError()!=ERROR_NO_MORE_ITEMS )
      {
		// Insert error handling here.
        return;
      }
}

// This function obtains some specific "driver" keys from the registry...

CAdditionalInfo* CDevMonDlg::GetAdditionalInfo(DEVNODE dnThis)
{
	HKEY hKey=NULL;
	DWORD dwType,dwCount;
	BYTE dbData[MAX_PATH];
	CString strINF,strProvider;
	CAdditionalInfo* pInfo=NULL;

	hKey = SetupDiOpenDevRegKey(m_hDevInfo,&m_DeviceInfoData,DICS_FLAG_GLOBAL,0,DIREG_DRV,KEY_READ);
	if(hKey==INVALID_HANDLE_VALUE) return NULL;
	
	pInfo = new CAdditionalInfo();

	dwCount = MAX_PATH;
	if(RegQueryValueEx(hKey,"InfPath",NULL,&dwType,dbData,&dwCount)==ERROR_SUCCESS)
	{
		pInfo->m_strINF.Format("%s",dbData);
	}
	dwCount = MAX_PATH;
	if(RegQueryValueEx(hKey,"ProviderName",NULL,&dwType,dbData,&dwCount)==ERROR_SUCCESS)
	{
		pInfo->m_strProvider.Format("%s",dbData);
	}
	dwCount = MAX_PATH;
	if(RegQueryValueEx(hKey,"DriverVersion",NULL,&dwType,dbData,&dwCount)==ERROR_SUCCESS)
	{
		pInfo->m_strVersion.Format("%s",dbData);
	}
	dwCount = MAX_PATH;
	if(RegQueryValueEx(hKey,"DriverDate",NULL,&dwType,dbData,&dwCount)==ERROR_SUCCESS)
	{
		pInfo->m_strDate.Format("%s",dbData);
	}
	GetSymbolicName(pInfo->m_strSymbolicName);
	
	RegCloseKey(hKey);
	hKey = NULL;

	CDevice* pDevice = new CDevice();
	pDevice->Create(NULL,dnThis);
	pInfo->m_pDevice = pDevice;
	CAttribute* pAtt;
	pDevice->GetAttribute(CM_DRP_SERVICE,&pAtt);

	strINF.Format("%s%s","SYSTEM\\CURRENTCONTROLSET\\SERVICES\\",pAtt->GetValue());
	
	RegOpenKey(HKEY_LOCAL_MACHINE,strINF,&hKey);
	if(hKey)
	{
		dwCount = MAX_PATH;
		if(RegQueryValueEx(hKey,"ImagePath",NULL,&dwType,dbData,&dwCount)==ERROR_SUCCESS)
		{
			pInfo->m_strImagePath.Format("%s",dbData);
		}
	}
	RegCloseKey(hKey);

	m_arAdditionalInfo.SetAt(dnThis,pInfo);
	return pInfo;
}

// Little utility to obtain some registry related details from the currently
// enumerating device...

BOOL CDevMonDlg::GetDevInfo(int nDevIndex)
{
	DWORD DataT;
    LPTSTR buffer = NULL;
    DWORD buffersize = 0;
 
	m_strDevInfo.Empty();

	// based upon the SPDRP ID, obtain it's value...
	while (!SetupDiGetDeviceRegistryProperty(
		m_hDevInfo,
		&m_DeviceInfoData,
		nDevIndex,
		&DataT,
		(PBYTE)buffer,
		buffersize,
		&buffersize))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			// Change the buffer size.
			if (buffer) LocalFree(buffer);
			buffer = (LPSTR) LocalAlloc(LPTR,buffersize);
		}
		else
		{
			// Insert error handling here.
			break;
		}
	}
           
	if(buffer)
	{
		if(nDevIndex == CM_DRP_LEGACYBUSTYPE)
		{
			int abc=1;
		}
		if(*buffer)
		{
			// Make sure we know the type of data we want to copy...
			switch(DataT)
			{
				case REG_SZ:
					m_strDevInfo = buffer;
					break;
				case REG_MULTI_SZ:
					m_strDevInfo = buffer;
					break;
				case REG_DWORD_LITTLE_ENDIAN:
					{
						DWORD dw;
						dw = atol(buffer);
						m_strDevInfo.Format("%X",dw);
					}
					break;
				case REG_BINARY:
					break;
				default:
					int x = 1;
					break;
			}
		}
		LocalFree(buffer);
		return TRUE;
	}
	return FALSE;
}

// For the currently enumerating device, grab the symbolic name (if any)...

BOOL CDevMonDlg::GetSymbolicName(CString& strSymbolicName)
{
	HKEY  hDeviceKey;
	DWORD dwBufferSize, dwError;
	char szBuffer[MAX_PATH];
	HANDLE hMyDevice = INVALID_HANDLE_VALUE;
	CString szMyInfo;
	PCHAR sFullDeviceName;

	//
	// Open the device key for the source device instance, and retrieve its
	// "SymbolicName" value.
	//
	hDeviceKey = SetupDiOpenDevRegKey(m_hDevInfo,
                                  &m_DeviceInfoData,
                                  DICS_FLAG_GLOBAL,
                                  0,
                                  DIREG_DEV,
                                  KEY_ALL_ACCESS);

	if (INVALID_HANDLE_VALUE == hDeviceKey) 
	{
		goto GetDeviceNameError;
	}

	dwBufferSize = sizeof(szBuffer);
	dwError = RegQueryValueEx(hDeviceKey,
                          _T("SymbolicName"),
                          NULL,
                          NULL,
                          (PBYTE)szBuffer,
                          &dwBufferSize);

	if(ERROR_SUCCESS != dwError) 
	{
		goto GetDeviceNameError;
	}
	strSymbolicName = szBuffer;
	RegCloseKey(hDeviceKey);

	strSymbolicName = strSymbolicName.Right(strSymbolicName.GetLength()-4);
	sFullDeviceName = (LPSTR)LocalAlloc(LPTR,strlen(strSymbolicName)+sizeof("\\\\.\\"));

	strcpy(sFullDeviceName,"\\\\.\\");
	strcpy(sFullDeviceName+sizeof("\\\\.\\")-1,strSymbolicName);
	strSymbolicName=sFullDeviceName;

	// Test the link...
	LocalFree(sFullDeviceName);

	hMyDevice = CreateFile(_T(strSymbolicName),
					GENERIC_READ|GENERIC_WRITE,
					FILE_SHARE_READ,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);		
	if(hMyDevice==INVALID_HANDLE_VALUE)
	{
		szMyInfo.Format("Error: CreateFile returns %0x. for: %s",
			GetLastError(),strSymbolicName);
		m_ctlList.AddString(szMyInfo);
		CloseHandle(hMyDevice);
	}
	else
	{
		szMyInfo.Format("Device opened with success: %s",
			strSymbolicName);
		m_ctlList.AddString(szMyInfo);
		CloseHandle(hMyDevice);
	}


	return TRUE;
GetDeviceNameError:
	if (hDeviceKey != INVALID_HANDLE_VALUE) 
	{
	RegCloseKey(hDeviceKey);
	}
	return FALSE;
}

BOOL CDevMonDlg::IsPhantomDN(UINT p, UINT s, UINT c)
{
	return (
		   ( ((s) & DN_HAS_PROBLEM) && ((CM_PROB_DEVICE_NOT_THERE == (p)) || (CM_PROB_PHANTOM == (p)))) ||
		   ((CR_NO_SUCH_DEVNODE == (c)) || (CR_DEVICE_NOT_THERE == (c)) || (CR_NO_SUCH_VALUE == (c)))
		   );
}

// This is the main NODE enumerating function...  Build relationships
// between children/siblings and parents... NOTE:  The DEVNODE will be the
// same as the DEVINST in the other tree...

BOOL CDevMonDlg::CreateSubtree(CDevice* pParent,CDevice* pSibling,DEVNODE  dnThis)
{
	HTREEITEM hItem;
	DEVNODE dnSibling, dnChild;
	CString str;
	do
    {
		Sleep(0);
		if (CR_SUCCESS != CM_Get_Sibling(&dnSibling, dnThis, 0)) dnSibling = NULL;

		CAdditionalInfo* pInfo=NULL;
		m_arAdditionalInfo.Lookup(dnThis,(void*&)pInfo);
		
		if(!pInfo) 
		{
			pInfo = GetAdditionalInfo(dnThis);
		}
		pInfo->m_pDevice->SetParent(pParent);

		if (pSibling)pSibling->SetSibling(pInfo->m_pDevice);
		else if (pParent)pParent->SetChild(pInfo->m_pDevice);

		LPGUID pClassGuid;
		CString strClass;
		CAttribute* pAtt;
		DWORD dwNeededSize=0;
		int nIndex;

		// The attributes, collected in the create method of CDevice,
		// is a collection of available registry entries about this node...

		for(int j=0;j<pInfo->m_pDevice->NumberOfAttributes();j++)
		{
			pInfo->m_pDevice->EnumerateAttribute(j,&pAtt);
			if(pAtt->m_lProperty==CM_DRP_CLASS)
			{
				strClass = pAtt->GetValue();
				break;
			}
		}

		if(!_stricmp(strClass,strTargetClass))
		{
			pClassGuid = new GUID;
			BOOL bRet = SetupDiClassGuidsFromName(strClass,pClassGuid,1,&dwNeededSize);
			// Get the image...
			bRet = SetupDiGetClassImageIndex(&m_pImages,pClassGuid,&nIndex);
		
			str.Format("%s [%04X]",pInfo->m_pDevice->GetDisplayName(),dnThis);
			hItem = m_ctlTree.InsertItem(str,nIndex,nIndex,pParent->m_hItem);
			m_ctlTree.SetItemData(hItem,(DWORD_PTR)pInfo->m_pDevice);
			pInfo->m_pDevice->m_hItem = hItem;

			delete pClassGuid;
		}

		if (CR_SUCCESS == CM_Get_Child(&dnChild, dnThis, 0))
		{
			CreateSubtree(pInfo->m_pDevice, NULL, dnChild);
		}
		dnThis = dnSibling;
		pSibling = pInfo->m_pDevice;
    } while (NULL != dnThis);

    return TRUE;
}

const PTSTR lpszLogConf[]= {_T("Basic Log Config"), _T("Filtered Log Config"), _T("Alloc Log Config"), _T("Boot Log Config"), _T("Forced Log Config"), _T("OverRide Log Config") };

LRESULT CDevMonDlg::InsertProperties(HTREEITEM hItem, DEVINST dnNode,CAdditionalInfo* pInfo)
{
	int nCount=0;
	int nListPosition=1;
	DWORD dwTest=1;
	DWORD dwValue=1;
	BOOL bShow = TRUE;
	CAttribute* pAtt;
	CString str;
	CString strAtt;
	CString strValue;
	DEVNODE dn = (DEVNODE)dnNode;
	int nIndex = 0;

	ULONG lStatus,lProblem;
	lProblem=lStatus=0;
	int	cRet = CM_Get_DevInst_Status(&lStatus,&lProblem,(DEVINST)dn,0);
	if(cRet)
	{
		str.Format("Problem: %s",strCRStatus[cRet]);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
	}

	if(!pInfo) return(0);

	if(pInfo->m_pDevice)
	{
		DisplayAttribute(hItem,CM_DRP_DEVICEDESC,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_HARDWAREID,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_COMPATIBLEIDS,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_SERVICE,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_CLASS,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_CLASSGUID,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_DRIVER,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_UPPERFILTERS,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_LOWERFILTERS,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_PHYSICAL_DEVICE_OBJECT_NAME,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_ENUMERATOR_NAME,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_HARDWAREDESC,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_INSTALL_STATE_PROBLEM,pInfo->m_pDevice);
		DisplayAttribute(hItem,CM_DRP_INSTALL_STATE,pInfo->m_pDevice);
	}

	if(pInfo)
	{
		str.Format("Provider: %s",pInfo->m_strProvider);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);

		str.Format("INF File: %s",pInfo->m_strINF);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);

		str.Format("Version: %s",pInfo->m_strVersion);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
		
		str.Format("Date: %s", pInfo->m_strDate);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
		
		str.Format("SymbolicName: %s",pInfo->m_strSymbolicName);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);

		str.Format("ImagePath: %s",pInfo->m_strImagePath);
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
	}

	if(!pInfo->m_pDevice) return 0;

	HTREEITEM hDevCaps = m_ctlTree.InsertItem("Device Capabilities",m_nRegIndex,m_nRegIndex,hItem);
	DisplayAttribute(hDevCaps,CM_DRP_CAPABILITIES,pInfo->m_pDevice);

	HTREEITEM hPower = m_ctlTree.InsertItem("Power Information",m_nRegIndex,m_nRegIndex,hItem);
	DisplayAttribute(hPower, CM_DRP_DEVICE_POWER_DATA,pInfo->m_pDevice);
	DisplayAttribute(hPower, CM_DRP_REMOVAL_POLICY,pInfo->m_pDevice);

	HTREEITEM hResources = m_ctlTree.InsertItem("Resources",m_nRegIndex,m_nRegIndex,hItem);

	ULONG status = 0;
	ULONG problem = 0;
	LOG_CONF config = 0;
	BOOL haveConfig = FALSE;
	UINT lc;
//	TCHAR *p, *s;

	if (CR_SUCCESS == CM_Get_DevNode_Status_Ex(&status,&problem, dn,0, NULL) )
	{
		//
		// see if the device is running and what resources it might be using
		//
		if(!(status & DN_HAS_PROBLEM)) {
			//
			// If this device is running, does this devinst have a ALLOC log config?
			//
			if (CM_Get_First_Log_Conf_Ex(&config,
										 dn,
										 ALLOC_LOG_CONF,
										 NULL) == CR_SUCCESS) {
				haveConfig = TRUE;
				lc = ALLOC_LOG_CONF;
			}
		}
		if(!haveConfig) {
			//
			// If no config so far, does it have a FORCED log config?
			// (note that technically these resources might be used by another device
			// but is useful info to show)
			//
			if (CM_Get_First_Log_Conf_Ex(&config,
										 dn,
										 FORCED_LOG_CONF,
										 NULL) == CR_SUCCESS) {
				haveConfig = TRUE;
				lc = FORCED_LOG_CONF;
			}
		}

		if(!haveConfig) {
			//
			// if there's a hardware-disabled problem, boot-config isn't valid
			// otherwise use this if we don't have anything else
			//
			if(!(status & DN_HAS_PROBLEM) || (problem != CM_PROB_HARDWARE_DISABLED)) {
				//
				// Does it have a BOOT log config?
				//
				if (CM_Get_First_Log_Conf_Ex(&config,
											 dn,
											 BOOT_LOG_CONF,
											 NULL) == CR_SUCCESS) {
					haveConfig = TRUE;
					lc = BOOT_LOG_CONF;
				}
			}
		}
	}

//	ctlList.InsertItem(nRet,"Resources",-1);
	if ( haveConfig) 
	{
		haveConfig = FALSE;
		m_ctlTree.InsertItem(lpszLogConf[lc],m_nRegIndex,m_nRegIndex,hResources);

		RES_DES rd, rdPrev = 0;
		RESOURCEID ResId;
		ULONG dsize;
		BYTE *resDesData;
		
		rdPrev = config;
		while( CR_SUCCESS == CM_Get_Next_Res_Des_Ex(&rd, rdPrev, ResType_All, &ResId, 0, NULL) )
		{
			CM_Get_Res_Des_Data_Size_Ex(&dsize, rd, 0, NULL);

			if( dsize )
			{
				resDesData = (BYTE*)malloc(dsize);
				if(resDesData )
				{
					if( CR_SUCCESS == CM_Get_Res_Des_Data_Ex(rd, resDesData, dsize,  0, NULL) )
					{
						switch(ResId)
						{
							case ResType_Mem: {
								PMEM_RESOURCE  pMemData = (PMEM_RESOURCE)resDesData;
								if(pMemData->MEM_Header.MD_Alloc_End - pMemData->MEM_Header.MD_Alloc_Base + 1)
								{
									haveConfig = TRUE;
									strValue.Format("Mem : [%08I64X - %08I64X]",pMemData->MEM_Header.MD_Alloc_Base,pMemData->MEM_Header.MD_Alloc_End);
									m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hResources);
								}
								break;
							}

							case ResType_IO: {
								haveConfig = TRUE;
								PIO_RESOURCE   pIoData = (PIO_RESOURCE)resDesData;
								if(pIoData->IO_Header.IOD_Alloc_End - pIoData->IO_Header.IOD_Alloc_Base + 1)
								{
									strValue.Format("IO    : [%04I64X - %04I64X]",pIoData->IO_Header.IOD_Alloc_Base,pIoData->IO_Header.IOD_Alloc_End);
									m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hResources);
								}
								break;
							}

							case ResType_DMA: {
								haveConfig = TRUE;
								PDMA_RESOURCE  pDmaData = (PDMA_RESOURCE)resDesData;
								if (pDmaData->DMA_Header.DD_Alloc_Chan)
								{
									strValue.Format("DMA : %u",pDmaData->DMA_Header.DD_Alloc_Chan);
									m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hResources);
								}
								break;
							}

							case ResType_IRQ: {
								haveConfig = TRUE;
								PIRQ_RESOURCE  pIrqData = (PIRQ_RESOURCE)resDesData;
								strValue.Format("IRQ : %u",pIrqData->IRQ_Header.IRQD_Alloc_Num);
								m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hResources);
								break;
							}

							case 0x43: {
								haveConfig = TRUE;
								strValue.Format("0x43 : %02X", (BYTE *)resDesData);
								m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hResources);
								break;
							}
						}
					}
					free(resDesData);
				}
			}
			CM_Free_Res_Des_Handle(rdPrev);
			rdPrev = rd;
		}

		CM_Free_Res_Des_Handle(rd);
		CM_Free_Log_Conf_Handle(config);
	}

	if ( !haveConfig)
	{
		m_ctlTree.InsertItem("Not Used",m_nRegIndex,m_nRegIndex,hResources);
	}

	return 0;

	for(int i=0;i<pInfo->m_pDevice->NumberOfAttributes();i++)
	{
		pInfo->m_pDevice->EnumerateAttribute(i,&pAtt);
		strValue = pAtt->GetValue();
		DWORD dwType = pAtt->GetType();

		switch(dwType)
		{
			case CM_DRP_FRIENDLYNAME:
				str.Format("FriendlyName: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_MFG:
				str.Format("Manufacturer: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_UPPERFILTERS:
				str.Format("Upper Filters: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_LOWERFILTERS:
				str.Format("Lower Filters: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_BUSTYPEGUID:
				str.Format("Bus Type GUID: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_LEGACYBUSTYPE:
				str.Format("UI Number: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_UI_NUMBER:
				str.Format("UI Number:%s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_LOCATION_INFORMATION:
				str.Format("Location Info: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_BUSNUMBER:
				str.Format("Bus Number: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_CONFIGFLAGS:
				str.Format("ConfigFlags: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			case CM_DRP_CAPABILITIES:
				str.Format("Capabilities: %s",strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
			default:
				str.Format("Unknown: %X - %s",dwType,strValue);
				m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				break;
		}

	}

	return 0;
}

void CDevMonDlg::DisplayAttribute(HTREEITEM hItem, int nProperty,CDevice* pDevice)
{
	CString strLabel,str,str2;
	CAttribute* pAtt=NULL;
	DWORD dwValue;
	DWORD dwTest = 1;
	int nProblem;

	TCHAR pUnSpecified[] = _T("UnSpecified");

	pDevice->GetAttribute(nProperty,&pAtt);
	if(pAtt==NULL) return;
	CString	strValue = pAtt->GetValue();

	switch(nProperty)
	{
		case CM_DRP_DEVICEDESC:
		case CM_DRP_HARDWAREDESC:
			strLabel = pAtt->m_bHardwareDesc ? "HardwareDesc" : "DeviceDesc";
			break;
		case CM_DRP_HARDWAREID:
			strLabel = "HardwareID(s)";
			break;
		case CM_DRP_LOWERFILTERS:
			strLabel = "Lower Filters";
			break;
		case CM_DRP_UPPERFILTERS:
			strLabel = "Upper Filters";
			break;
		case CM_DRP_SERVICE:
			strLabel = "Service";
			break;
		case CM_DRP_CLASS:
			strLabel = "Device Class";
			break;
		case CM_DRP_COMPATIBLEIDS:
			strLabel = "CompatibleID(s)";
			break;
		case CM_DRP_CLASSGUID:
			strLabel = "Class GUID";
			break;
		case CM_DRP_DRIVER:
			strLabel = "Driver Key";
			break;
		case CM_DRP_PHYSICAL_DEVICE_OBJECT_NAME:
			strLabel = "PDO Name";
			break;
		case CM_DRP_ENUMERATOR_NAME:
			strLabel = "Enumerator";
			break;
		case CM_DRP_DEVICE_POWER_DATA:
			dwValue = pAtt->m_PowerData.PD_Capabilities;
			pAtt->m_strStrList.RemoveAll();
			if (pAtt->m_PowerData.PD_MostRecentPowerState) /// PowerDeviceD3
				strValue.Format("Current Pwr State: D%d", pAtt->m_PowerData.PD_MostRecentPowerState - PowerDeviceD0);
			m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hItem);

			for(int nCount=0;nCount<9;nCount++)
			{
				if(dwValue&dwTest) 
				{
					m_ctlTree.InsertItem(lpszPwrData[nCount],m_nRegIndex,m_nRegIndex,hItem);
				}
				dwTest<<=1;
			}
			for (int j = PowerSystemWorking; j <= PowerSystemShutdown; j++ ) 
			{
				TCHAR unsp[3] = {'D', 0, 0}, *pu;

				if ( (pAtt->m_PowerData.PD_PowerStateMapping[j] == PowerDeviceUnspecified) ||
				 (pAtt->m_PowerData.PD_PowerStateMapping[j] > PowerDeviceD3) )
				  pu = pUnSpecified;
				else {
					unsp[1] = '0' + pAtt->m_PowerData.PD_PowerStateMapping[j] - PowerDeviceD0;
					pu = unsp;
				}
				strValue.Format("S%d -> %s", j - PowerSystemWorking, pu);
				m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hItem);
			} // for(j = PowerS....

			break;
		case CM_DRP_REMOVAL_POLICY:
			dwValue = pAtt->m_dwValue;
			pAtt->m_strStrList.RemoveAll();
			strValue.Format("0x%08X",dwValue);
			str.Format("Removal Policy: [%s] - %s",strValue,strValue);
			m_ctlTree.InsertItem(str,hItem);
			if(dwValue==CM_REMOVAL_POLICY_EXPECT_NO_REMOVAL) strValue = "Expect No Removal";
			if(dwValue==CM_REMOVAL_POLICY_EXPECT_ORDERLY_REMOVAL) strValue = "Expect Orderly Removal";
			if(dwValue==CM_REMOVAL_POLICY_EXPECT_SURPRISE_REMOVAL) strValue = "Expect Surpise Removal";
			str2.Format("%s %s",str,strValue);
			m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hItem);
			break;
		case CM_DRP_CAPABILITIES:
			dwValue = pAtt->m_dwValue;
			pAtt->m_strStrList.RemoveAll();
			strValue.Format("0x%08X",dwValue);

			for(int nCount=0;nCount<9;nCount++)
			{
				if(dwValue&dwTest) 
				{
					str.Format("%s %s",strValue,cm_caps[nCount]);
					m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
				}
				dwTest<<=1;
			}
			break;

		case CM_DRP_INSTALL_STATE_PROBLEM:
			strLabel = "Problem";
			nProblem = atoi(strValue);
			if(!nProblem)
			{
				pAtt->m_strStrList.RemoveAll();
				pAtt->m_strStrList.Add("The device is working properly");
			}
			break;
		case CM_DRP_INSTALL_STATE:
			strLabel = "Status";
			dwValue = pAtt->m_dwValue;
			if(dwValue)
			{
				str.Format(pAtt->m_bProblem ? "Problem" : "Status (0x%X)",dwValue);

				if(!pAtt->m_bProblem)
				{
					for(int nCount=0;nCount<32;nCount++)
					{
						if(dwValue&dwTest) 
						{
							strValue.Format("%s %s", str,strDNStatus[nCount]);
							m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hItem);
						}
						dwTest<<=1;
					}
					return;
				}
				else
				{
					m_ctlTree.InsertItem(strValue,m_nRegIndex,m_nRegIndex,hItem);
				}
			} 
			break;
	}

	int nCount = (int)pAtt->m_strStrList.GetCount();

	while(nCount)
	{
		str.Format("%s: %s",strLabel,pAtt->m_strStrList.GetAt(nCount-1));
		m_ctlTree.InsertItem(str,m_nRegIndex,m_nRegIndex,hItem);
		strLabel.Empty();
		--nCount;
	}
}

LRESULT CDevMonDlg::OnDeviceChange(WPARAM wParam,LPARAM lParam)
{
	CString str;
	DWORD mask,i;
	char Path[16];
	PDEV_BROADCAST_DEVICEINTERFACE hdrInfo = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
    DEV_BROADCAST_VOLUME *dbv;

	switch(wParam)
	{	
		case DBT_DEVICEARRIVAL:
			switch(hdrInfo->dbcc_devicetype)
			{
				case DBT_DEVTYP_VOLUME:
					dbv = (DEV_BROADCAST_VOLUME*)lParam;
					Path[1] = ':';
					Path[2] = '\\';
					Path[3] = 0;
					Path[4] = 0;
					for (i=0,mask=dbv->dbcv_unitmask; i<26; i++) 
					{
						if (mask&1) 
						{
							Path[0] = ('A' + (char)i);
							Path[3] = 0;
							str.Format("Drive %s arrived",Path);
							m_ctlList.InsertString(0,str);
						}
						mask = mask >> 1;
					}
					break;
				case DBT_DEVTYP_DEVICEINTERFACE:
					str.Format("DeviceArrived: %s",hdrInfo->dbcc_name);
					m_ctlList.InsertString(0,str);
					RefreshEntireTree();
					break;
			}
			break;

		case DBT_DEVICEREMOVECOMPLETE:
			switch(hdrInfo->dbcc_devicetype)
			{
				case DBT_DEVTYP_VOLUME:
					dbv = (DEV_BROADCAST_VOLUME*)lParam;
					Path[1] = ':';
					Path[2] = '\\';
					Path[3] = 0;
					Path[4] = 0;
					for (i=0,mask=dbv->dbcv_unitmask; i<26; i++) 
					{
						if (mask&1) 
						{
							Path[0] = ('A' + (char)i);
							Path[3] = 0;
							str.Format("Drive %s removed",Path);
							m_ctlList.InsertString(0,str);
						}
						mask = mask >> 1;
					}
					break;
				case DBT_DEVTYP_DEVICEINTERFACE:
					str.Format("DeviceRemoved: %s",hdrInfo->dbcc_name);
					m_ctlList.InsertString(0,str);
					RefreshEntireTree();
					break;
			}
	}

	return TRUE;
}

BOOL CDevMonDlg::DoRegisterDeviceInterface( 
    GUID InterfaceClassGuid, 
    HDEVNOTIFY *hDevNotify 
)
/*
Routine Description:
    Registers for notification of changes in the device interfaces for
    the specified interface class GUID. 

Parameters:
    InterfaceClassGuid - The interface class GUID for the device 
        interfaces. 

    hDevNotify - Receives the device notification handle. On failure, 
        this value is NULL.

Return Value:
    If the function succeeds, the return value is TRUE.

    If the function fails, the return value is FALSE.
*/
{
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
    DWORD Err;

    ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotificationFilter.dbcc_classguid = InterfaceClassGuid;

	*hDevNotify = RegisterDeviceNotification( this->m_hWnd, 
        &NotificationFilter,
        DEVICE_NOTIFY_WINDOW_HANDLE|0x04//DEVICE_NOTIFY_ALL_INTERFACE_CLASSES
    );

    if(!*hDevNotify) 
    {
        Err = GetLastError();
        printf( "RegisterDeviceNotification failed: %lx.\n", Err);
        return FALSE;
    }

    return TRUE;
}


void CDevMonDlg::OnTimer(UINT_PTR nIDEvent)
{
DWORD dwRet;

	switch(nIDEvent)
	{
		case PNP_TIMER:
			KillTimer(PNP_TIMER);
			dwRet = CMP_WaitNoPendingInstallEvents(0);

			switch(dwRet)
			{
				case WAIT_OBJECT_0:
					if(m_bPNPActive)
					{
						m_ctlList.InsertString(0,"PNP Complete");
						m_bPNPActive = FALSE;
					}
					break;
				case WAIT_TIMEOUT:
					if(!m_bPNPActive) m_ctlList.InsertString(0,"PNP Installing, please wait...");
					m_bPNPActive = TRUE;
					break;
				case WAIT_FAILED:
					m_ctlList.InsertString(0,"Wait Failed");
					break;
			}
			SetTimer(PNP_TIMER,1000,NULL);
			return;
	}

	CDialog::OnTimer(nIDEvent);
}


void CDevMonDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_ctlTree.m_hWnd)
	{
		CRect rc,rc2;
		GetClientRect(&rc); // main app window...

		m_ctlTree.SetWindowPos(&wndTop,rc.left+5,rc.top,rc.Width()-5,rc.Height()/2,SWP_SHOWWINDOW);
		m_ctlTree.RedrawWindow();
		m_ctlTree.GetClientRect(&rc2);

		m_ctlList.SetWindowPos(&wndTop,rc.left+5,rc.top+rc2.bottom+15,rc.Width()-5,(rc.Height()/2)-55,SWP_SHOWWINDOW);
		m_ctlList.RedrawWindow();

		m_btnOK.SetWindowPos(&wndTop,rc.Width()/2 - 60, rc.bottom-35,50,25,SWP_SHOWWINDOW);
		m_btnCancel.SetWindowPos(&wndTop,rc.Width()/2 + 60,rc.bottom-35,50,25,SWP_SHOWWINDOW);
		//Invalidate();
	}
}

void CDevMonDlg::OnBnClickedOk()
{
	DeleteAllRemnants();
	CDialog::OnOK();
}


void CDevMonDlg::OnBnClickedCancel()
{
	DeleteAllRemnants();
	CDialog::OnCancel();
}


void CDevMonDlg::OnClose()
{
	DeleteAllRemnants();
	CDialog::OnClose();
}
