
// SendMailClientDlg.h : 头文件
//

#pragma once


// CSendMailClientDlg 对话框
class CSendMailClientDlg : public CDialogEx
{
// 构造
public:
	CSendMailClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SENDMAILCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	char m_strSmtpSrvName[32];
    char m_strPort[8];
    char m_szUser[32];
    char m_szPwd[32];
	void Base64(const char* Data, char* chuue);
	int Talk(SOCKET sockid, const char *OkCode, char *pSend);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSetup();
	CString m_strFrom;
	CString m_strTo;
	CString m_strSubject;
	CString m_strMsg;
	afx_msg void OnBnClickedOk();
};
