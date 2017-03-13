// Setup.cpp : 实现文件
//

#include "stdafx.h"
#include "SendMailClient.h"
#include "Setup.h"
#include "afxdialogex.h"


// CSetup 对话框

IMPLEMENT_DYNAMIC(CSetup, CDialog)

CSetup::CSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CSetup::IDD, pParent)
	, m_strServer(_T(""))
	, m_strPort(_T(""))
	, m_strUser(_T(""))
	, m_strPwd(_T(""))
{

}

CSetup::~CSetup()
{
}

void CSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CSetup, CDialog)
	ON_BN_CLICKED(IDOK, &CSetup::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetup 消息处理程序


void CSetup::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
          UpdateData(TRUE);    		//保存控件中的输入信息到变量中
          OnOK();
//	CDialog::OnOK();
}
