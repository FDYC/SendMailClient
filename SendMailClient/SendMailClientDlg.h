
// SendMailClientDlg.h : ͷ�ļ�
//

#pragma once


// CSendMailClientDlg �Ի���
class CSendMailClientDlg : public CDialogEx
{
// ����
public:
	CSendMailClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SENDMAILCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	char m_strSmtpSrvName[32];
    char m_strPort[8];
    char m_szUser[32];
    char m_szPwd[32];
	void Base64(const char* Data, char* chuue);
	int Talk(SOCKET sockid, const char *OkCode, char *pSend);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
