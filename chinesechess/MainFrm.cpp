
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "chinesechess.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	WORD  wVersionRequested;
	WSADATA  wsadata;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsadata);
	if (err != 0)
	{
		CString iA("网络故障！");
		MessageBox(iA);
		return;
	}
}

CMainFrame::~CMainFrame()
{ 
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON3);
	//设置图标
	SetIcon(hIcon, FALSE);
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style = WS_CAPTION | FWS_ADDTOTITLE| WS_SYSMENU | WS_MINIMIZEBOX;
	cs.x=100;
	cs.y=50;
	cs.cx=610;
	cs.cy=620;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString csAppName;
	csAppName.Format(AFX_IDS_APP_TITLE);
	SetWindowText(csAppName);
}
