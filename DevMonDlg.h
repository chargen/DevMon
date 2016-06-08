// DevMonDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "Device.h"
#include "MapDword.h"
#include "AdditionalInfo.h"

#include "DevGUID.h"
#include "dbt.h"
#include "afxwin.h"

//typedef  PVOID           HDEVNOTIFY;
//typedef  HDEVNOTIFY     *PHDEVNOTIFY;
//#define DBT_DEVTYP_DEVICEINTERFACE      0x00000005  // device interface class
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */


// CDevMonDlg dialog
class CDevMonDlg : public CDialog
{
// Construction
public:
	CDevMonDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CDevMonDlg();
	void CreateInfSearchFolder(char *FolderName);

// Dialog Data
	enum { IDD = IDD_DevMon_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void RefreshEntireTree(void);
	void DeleteAllRemnants(void);
	void BuildDeviceInfoTree(HTREEITEM m_hAddToNode);
	CAdditionalInfo* GetAdditionalInfo(DEVNODE dnThis);
	BOOL GetDevInfo(int nDevIndex);
	BOOL GetSymbolicName(CString& strSymbolicName);
	BOOL IsPhantomDN(UINT p, UINT s, UINT c);
	BOOL CreateSubtree(CDevice* pParent,CDevice* pSibling,DEVNODE  dnThis);
	LRESULT InsertProperties(HTREEITEM hItem, DEVINST dnNode,CAdditionalInfo* pInfo);
	void DisplayAttribute(HTREEITEM hItem, int nProperty,CDevice* pDevice);
	BOOL DoRegisterDeviceInterface(GUID InterfaceClassGuid,HDEVNOTIFY *hDevNotify);

// Implementation
protected:
	HICON m_hIcon;
	CDevice* m_pCurrentDevice;
	CMachine* m_pMachine;
	HTREEITEM m_hDeviceRoot;
	SP_CLASSIMAGELIST_DATA m_pImages;
	CImageList m_pImageList;
	int m_nGhostIndex;
	int m_nRegIndex;
	BOOL m_bPNPActive;
	CMapDWordToPtr m_arAdditionalInfo;
	SP_DEVINFO_DATA m_DeviceInfoData;
	HDEVINFO m_hDevInfo;
	CMapStringToPtr m_arClassMap;
  	CString m_strDevInfo;
	HDEVNOTIFY m_hNotify;
	BOOL m_bDialogCreated;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnDeviceChange(WPARAM wParam,LPARAM lParam);	

public:
	CTreeCtrl m_ctlTree;
	
	CListBox m_ctlList;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_btnOK;
	CButton m_btnCancel;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
