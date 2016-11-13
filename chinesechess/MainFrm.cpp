
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	WORD  wVersionRequested;
	WSADATA  wsadata;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsadata);
	if (err != 0)
	{
		CString iA("������ϣ�");
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
	//����ͼ��
	SetIcon(hIcon, FALSE);
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style = WS_CAPTION | FWS_ADDTOTITLE| WS_SYSMENU | WS_MINIMIZEBOX;
	cs.x=100;
	cs.y=50;
	cs.cx=610;
	cs.cy=620;
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: �ڴ����ר�ô����/����û���
	CString csAppName;
	csAppName.Format(AFX_IDS_APP_TITLE);
	SetWindowText(csAppName);
}
