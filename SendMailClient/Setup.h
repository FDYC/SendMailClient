#pragma once


// CSetup �Ի���

class CSetup : public CDialog
{
	DECLARE_DYNAMIC(CSetup)

public:
	CSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERVERSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strServer;
	CString m_strPort;
	CString m_strUser;
	CString m_strPwd;
	afx_msg void OnBnClickedOk();
};
