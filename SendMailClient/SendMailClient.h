
// SendMailClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSendMailClientApp:
// �йش����ʵ�֣������ SendMailClient.cpp
//

class CSendMailClientApp : public CWinApp
{
public:
	CSendMailClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSendMailClientApp theApp;