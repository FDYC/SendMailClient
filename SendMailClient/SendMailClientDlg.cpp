
// SendMailClientDlg.cpp : 实现文件
//

//#include <winsock2.h>
//#pragma comment(lib,"ws2_32.lib")
//#include <WS2tcpip.h>
#include "stdafx.h"
#include "SendMailClient.h"
#include "SendMailClientDlg.h"
#include "afxdialogex.h"
#include "Setup.h"
#include "string"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSendMailClientDlg 对话框




CSendMailClientDlg::CSendMailClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendMailClientDlg::IDD, pParent)
	, m_strFrom(_T(""))
	, m_strTo(_T(""))
	, m_strSubject(_T(""))
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSendMailClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM, m_strFrom);
	DDX_Text(pDX, IDC_EDIT_TO, m_strTo);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_Content, m_strMsg);
}

BEGIN_MESSAGE_MAP(CSendMailClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &CSendMailClientDlg::OnBnClickedButtonSetup)
	ON_BN_CLICKED(IDOK, &CSendMailClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSendMailClientDlg 消息处理程序

BOOL CSendMailClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSendMailClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSendMailClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSendMailClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSendMailClientDlg::OnBnClickedButtonSetup()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetup dlg;
//	dlg.DoModal(); 					//弹出服务器设置对话框
	dlg.m_strServer = m_strSmtpSrvName;
	dlg.m_strPort = m_strPort;
	dlg.m_strUser = m_szUser;
	dlg.m_strPwd = m_szPwd;
	if (dlg.DoModal() == IDOK)   	//单击确定
	{
		strcpy_s(m_strSmtpSrvName, dlg.m_strServer.GetBuffer());
		strcpy_s(m_strPort , dlg.m_strPort.GetBuffer());
		strcpy_s(m_szUser,  dlg.m_strUser.GetBuffer());
		strcpy_s(m_szPwd,  dlg.m_strPwd.GetBuffer());
	}

}

int CSendMailClientDlg::Talk(SOCKET sockid, const char *OkCode, char *pSend)
{     
          const int buflen = 256;
          char buf[buflen];
          ZeroMemory(buf, buflen);
          if (recv(sockid, buf, buflen, 0) == SOCKET_ERROR) 	//接收返回信息
          {      
               MessageBox("recv() error !");
               return 1;
          }
          if (strlen(pSend)) 				//发送命令
          {       
               ZeroMemory(buf, buflen);
               sprintf_s(buf, "%s\r\n", pSend);
               if (send(sockid, buf, lstrlen(buf), 0) == SOCKET_ERROR)
               {      
                    MessageBox("send() error ");
                    return 1;
               }
      }
      return 0;
}


void CSendMailClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 	 		//获取用户输入
	const int buflen = 256;
	char buf[buflen];
	WSADATA wsadata;  				//初始化网络环境
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		MessageBox((LPCTSTR)"WSAStartup Error!");
		return;
	}
	SOCKET sockid;  				//创建套接字
	if ((sockid = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		MessageBox((LPCTSTR)"Sockid Error!");
		WSACleanup();
		return;
	}
	//解析IP地址
	struct addrinfo *answer, hint;
	ZeroMemory(&hint, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	int ret = getaddrinfo(m_strSmtpSrvName, "smtp", &hint, &answer);
//使用getaddrinfo，需要#include <ws2tcpip.h>
	struct sockaddr_in addr;
	addr.sin_addr = ((struct sockaddr_in *)(answer->ai_addr))->sin_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(m_strPort));
	ZeroMemory(&addr.sin_zero, 8);

//连接服务器
	if (connect(sockid, (struct sockaddr *)&addr, sizeof(struct sockaddr_in))== SOCKET_ERROR)
	{
		MessageBox((LPCTSTR)"connect() error !");
		goto STOP;
	}
	//命令交互开始
	if (Talk(sockid, "220", "HELO asdf"))     	goto STOP;
	if (Talk(sockid, "250", "AUTH LOGIN"))   goto STOP;
	ZeroMemory(buf, buflen);
	Base64(m_szUser, buf);
	if (Talk(sockid, "334", buf))	  			goto STOP; 	//发送Base64用户名
	ZeroMemory(buf, buflen);
	Base64(m_szPwd, buf);
	if (Talk(sockid, "334", buf)) 			goto STOP; 		//发送Base64密码  
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "MAIL FROM:<%s>", m_strFrom);        			//发信人
	if (Talk(sockid, "235", buf))   			goto STOP;
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "RCPT TO:<%s>", m_strTo);              		//收信人
	if (Talk(sockid, "250", buf))    			goto STOP;
	if (Talk(sockid, "250", "DATA"))  		goto STOP;   		//数据
	ZeroMemory(buf, buflen);
	sprintf_s(buf, "TO: %s\r\nFROM: %s\r\nSUBJECT: %s\r\n%s\r\n\r\n.",
		m_strTo, m_strFrom, m_strSubject, m_strMsg);
	if (Talk(sockid, "354", buf))  			goto STOP;
	if (Talk(sockid, "250", "QUIT"))  		goto STOP;   		//结束命令
	if (Talk(sockid, "221", ""))     			goto STOP;
STOP:
	shutdown(sockid, SD_BOTH);
	closesocket(sockid);
	WSACleanup();
	return;
}

void CSendMailClientDlg::Base64(const char* Data, char* chuue)
{
	//编码表
	const char EncodeTable[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string strEncode;
	int DataByte = strlen((char*)Data);
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	for (int i = 0; i<(int)(DataByte / 3); i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
		if (LineLength += 4, LineLength == 76) 
{ strEncode += "\r\n"; LineLength = 0; }
	}
	//对剩余数据进行编码
	int Mod = DataByte % 3;
	if (Mod == 1)
	{
		Tmp[1] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode += "==";
	}
	else if (Mod == 2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode += "=";
	}
	int n = strlen(strEncode.c_str()) + 1;
	strcpy_s(chuue, n, strEncode.c_str());
}

