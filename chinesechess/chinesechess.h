
// chinesechess.h : chinesechess Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CchinesechessApp:
// �йش����ʵ�֣������ chinesechess.cpp
//

class CchinesechessApp : public CWinAppEx
{
public:
	CchinesechessApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CchinesechessApp theApp;
