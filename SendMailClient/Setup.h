#pragma once


// CSetup 对话框

class CSetup : public CDialog
{
	DECLARE_DYNAMIC(CSetup)

public:
	CSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetup();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERVERSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strServer;
	CString m_strPort;
	CString m_strUser;
	CString m_strPwd;
	afx_msg void OnBnClickedOk();
};
