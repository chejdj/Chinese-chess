
// chinesechessView.cpp : CchinesechessView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "chinesechess.h"
#endif
#include "mmsystem.h"
#include "chinesechessDoc.h"
#include "chinesechessView.h"
#include "Chess.h"
#include "Managers.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include<playsoundapi.h>
#include <mmsystem.h>
#include <MMSYSTEM.H>
#pragma comment(lib, "winmm.lib")//���ӿ�
extern Managers manager;
// CchinesechessView

IMPLEMENT_DYNCREATE(CchinesechessView, CView)

BEGIN_MESSAGE_MAP(CchinesechessView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32772, &CchinesechessView::On32772)
	ON_COMMAND(ID_32773, &CchinesechessView::On32773)
ON_COMMAND(ID_32783, &CchinesechessView::On32783)
ON_COMMAND(ID_32784, &CchinesechessView::On32784)
ON_COMMAND(ID_32785, &CchinesechessView::On32785)
ON_COMMAND(ID_32786, &CchinesechessView::On32786)
ON_COMMAND(ID_32787, &CchinesechessView::On32787)
ON_COMMAND(ID_32788, &CchinesechessView::On32788)
END_MESSAGE_MAP()

// CchinesechessView ����/����

CchinesechessView::CchinesechessView()
{
	// TODO: �ڴ˴���ӹ������
	start=true;
	num1 = 100;
	num2 = 100;//100��ʾ��ǰû��ѡ��ĳ������
}


CchinesechessView::~CchinesechessView()
{
}

BOOL CchinesechessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸ģ��������������ͼƬ
	m_chessbord.LoadBitmap(IDB_BITMAP1);
	m_chess.LoadBitmap(IDB_BITMAP7);
	m_mask.LoadBitmap(IDB_BITMAP8);
	m_choose.LoadBitmap(IDB_BITMAP9);
	return CView::PreCreateWindow(cs);
}



void CchinesechessView::OnDraw(CDC* pDC)
{
	CchinesechessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(start)
	{
		chessall.CreateCompatibleDC(pDC);//˫����ȥ������ 
		temp.CreateCompatibleDC(NULL);
		tempbitmap.CreateCompatibleBitmap(pDC,610,620);
		temp.SelectObject(&tempbitmap);
		temp.FillSolidRect(0,0,610,620,RGB(255,255,255));
		start=false;
		manager.gamestart();
	}
	PrintAll();
}



BOOL CchinesechessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CchinesechessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CchinesechessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

// CchinesechessView ���

#ifdef _DEBUG
void CchinesechessView::AssertValid() const
{
	CView::AssertValid();
}

void CchinesechessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CchinesechessDoc* CchinesechessView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CchinesechessDoc)));
	return (CchinesechessDoc*)m_pDocument;
}
#endif //_DEBUG


// CchinesechessView ��Ϣ�������


void CchinesechessView::DrawStar(int x, int y, CDC* pdc)//�滭�������ϵ�����
{
	
	int m;
	int	n;
	if(x>0&&x<8)
	{
		for(m=-1;m<2;)
		{
				for(n=-1;n<2;)
			{
				pdc->MoveTo(80+50*x+m*5,65+50*y+n*5);
				pdc->LineTo(80+50*x+m*15,65+50*y+n*5);
				pdc->MoveTo(80+50*x+m*5,65+50*y+n*5);
				pdc->LineTo(80+50*x+m*5,65+50*y+n*15);
				n+=2;
			}
				m+=2;
		}
	}
	else if(x==0)
	{
		for(m=-1;m<2;)
		{
			pdc->MoveTo(80+5,65+50*y+m*5);
			pdc->LineTo(80+5,65+50*y+m*20);
			pdc->MoveTo(80+5,65+50*y+m*5);
			pdc->LineTo(80+5+15,65+50*y+m*5);
			m+=2;
		}
	}
	else if(x==8)
	{
		for(m=-1;m<2;)
		{
			pdc->MoveTo(80+8*50-5,65+50*y+m*5);
			pdc->LineTo(80+8*50-5,65+50*y+m*20);
			pdc->MoveTo(80+8*50-5,65+50*y+m*5);
			pdc->LineTo(80+8*50-20,65+50*y+m*5);
			m+=2;
		}
	}
}
void CchinesechessView::DrawChessbord(CDC * pdc)//�滭���̣�
{
	CPen chessbord1,chessbord2;//��������
	chessbord1.CreatePen(0,1,RGB(0,0,0));
	chessbord2.CreatePen(0,3,RGB(0,0,0));
	int	i;
	int	k;

	for(i=0;i<2;i++)
	{	
		pdc->SelectObject(&chessbord1);
		for(k=1;k<=4;k++)
		{
			pdc->MoveTo(80,65+k*50+i*4*50);
			pdc->LineTo(80+50*8,65+k*50+i*4*50);
		}
		
		for(k=1;k<=7;k++)
		{	
			pdc->MoveTo(80+50*k,65+i*5*50);
			pdc->LineTo(80+50*k,65+4*50+i*5*50);
		}
		pdc->MoveTo(80+50*3,65+i*7*50);
		pdc->LineTo(80+50*5,65+2*50+i*7*50);
		pdc->MoveTo(80+50*3,65+2*50+i*7*50);
		pdc->LineTo(80+5*50,65+i*7*50);
		if(i==1)
			pdc->SelectObject(&chessbord2);
		pdc->MoveTo(80-i*10,65-i*10);
		pdc->LineTo(80-i*10,65+9*50+i*10);
		pdc->MoveTo(80-i*10,65-i*10);
		pdc->LineTo(80+8*50+i*10,65-i*10);
		pdc->MoveTo(80+8*50+i*10,65-i*10);
		pdc->LineTo(80+8*50+i*10,65+9*50+i*10);
		pdc->MoveTo(80+8*50+i*10,65+9*50+i*10);
		pdc->LineTo(80-i*10,65+9*50+i*10);
		pdc->SelectObject(&chessbord2);
		DrawStar(1,2+i*5,pdc);
		DrawStar(7,2+i*5,pdc);
		DrawStar(2,3+i*3,pdc);
		DrawStar(4,3+i*3,pdc);
		DrawStar(6,3+i*3,pdc);
		DrawStar(0,3+i*3,pdc);
		DrawStar(8,3+i*3,pdc);

	}

	ReleaseDC(pdc);
	chessbord1.DeleteObject();
	chessbord2.DeleteObject();
	
}


void CchinesechessView::DrawChoose(int x, int y, CDC * pdc)
{
	chessall.SelectObject(&m_choose);
	pdc->BitBlt(60+x*50,45+y*50,45,45,&chessall,0,0,MERGEPAINT);
	pdc->BitBlt(60+x*50,45+y*50,45,45,&chessall,45,0,SRCAND);
}
void CchinesechessView::DrawChess(Chess ch, CDC* pdc)
{
	if(!ch.color)//������ң���
	{
		chessall.SelectObject(m_mask);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,0,MERGEPAINT);
		chessall.SelectObject(m_chess);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,0, SRCAND);
	}
	else//������ң���
	{
		chessall.SelectObject(m_mask);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,45,MERGEPAINT);
		chessall.SelectObject(m_chess);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,45,SRCAND);
	}
}



int CchinesechessView::SelectNum(int x, int y)//ѡ������
{
	x = (x-60)/50;
	y = (y-45)/50;
	return	y*10+x;
}


void CchinesechessView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(manager.PointCh==NULL)
		return;
	int	mx=point.x;
	int	my=point.y;
	if(mx>=65&&my>=50&&mx<=490&&my<=525)//��������
	{
		int k;//һ��ʮλ���洢��ǰ����ֵ (x,y)��ʾΪ y*10+x
		k=SelectNum(mx,my);
		if(manager.game_state==0||manager.game_state==1)
		{
			if(manager.DoMsg(k%10,k/10,false))
			{
				num2=k;//��ʾ���ƶ�������
			}
			else
			{
				num2=100;//��ʾ�����ƶ�
			}
		}
	}
	PrintAll();
	CView::OnMouseMove(nFlags, point);
}


void CchinesechessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(manager.game_state==-1)
		return;
	int	mx=point.x;
	int	my=point.y;
	CDC *pdc=GetDC();
	int k;
	num1=100;
	if(mx>=65&&my>=50&&mx<=490&&my<=525)
	{
		k=SelectNum(mx,my);
		if(manager.PointCh==NULL)
		{
			if((manager.game_state+1)==manager.map[k%10][k/10])//�е�ǰ�ж��غ���ҵ���
			{
				manager.PointCh=manager.search(k%10,k/10);
			}
		}
		else//��ǰ����Ŀ��
		{
			if((manager.game_state+1)==manager.map[k%10][k/10])//���Լ�����������
			{

				manager.PointCh=manager.search(k%10,k/10);
			}
			else if(manager.DoMsg(k%10,k/10,true))//������Ծ͹�ȥ
			{
				num1=k;//num1��¼�߹��ĺۼ�
				manager.game_state=(manager.game_state==0);//in turns
				PlaySoundA("������.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_SYNC|SND_NOSTOP);
			}
			else//����ȥ
			{
				manager.PointCh=NULL;
			}
		}

	}
	ReleaseDC(pdc);
	PrintAll();
	CView::OnLButtonDown(nFlags, point);
}



void CchinesechessView::On32772()
{
	// TODO: �ڴ���������������
	manager.gamestart();
	PlaySoundA("������.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	PrintAll();
}


void CchinesechessView::On32773()
{
	// TODO: �ڴ���������������
	manager.gamestart();
	PlaySoundA("������.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	PrintAll();
}

void CchinesechessView::PrintAll(void)
{
	CDC *pdc = GetDC();
	chessall.SelectObject(&m_chessbord);//������
	temp.BitBlt(0, 0, 610, 620, &chessall, 0, 0, SRCCOPY);//˫����ȥ������
	DrawChessbord(&temp);//���ڻ����dc��   ÿ���ػ涼��ȫ������һ�ε����� �������ϵ���
	int	k = 0;
	//������������
	for (; k <= 31; k++)
	{
		if (manager.nChessinfo[k].type <= 7)
			DrawChess(manager.nChessinfo[k], &temp);
	}
	//����ѡ�е����ӵ�ѡ��
	if (manager.PointCh != NULL)
		DrawChoose(manager.PointCh->x, manager.PointCh->y, &temp);
	//�����������û��ѡ������
	if (num1<100)
		DrawChoose(num1 % 10, num1 / 10, &temp);
	if (num2<100)
		DrawChoose(num2 % 10, num2 / 10, &temp);

	pdc->BitBlt(0, 0, 800, 600, &temp, 0, 0, SRCCOPY);
}


void CchinesechessView::On32783()//��ʼ��������
{
	// TODO: �ڴ���������������
	PlaySoundA("��������.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
}


void CchinesechessView::On32784()
{
	// TODO: �ڴ���������������
   PlaySoundA(NULL, NULL, SND_FILENAME);
}


void CchinesechessView::On32785()//��������
{
	// TODO: �ڴ���������������
	PlaySoundA("5390.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	manager.game_state = 4;
	manager.updata();
}


void CchinesechessView::On32786()//��������
{
	// TODO: �ڴ���������������
	PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	int k;
	k = MessageBox(_T("�������������"), _T(""), MB_OKCANCEL);
	if (k == 1)
	{
		manager.game_state = 3;//game_state==3,����ʤ��
	}
	manager.updata();

}


void CchinesechessView::On32787()//��������
{
	// TODO: �ڴ���������������
	PlaySoundA("5390.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	manager.game_state = 4;
	manager.updata();
}


void CchinesechessView::On32788()   //��������
{
	// TODO: �ڴ���������������
	PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	//��ʱgame_state=1;
	int k;
	k = MessageBox(_T("�������������"), _T(""), MB_OKCANCEL);
	if (k == 1)
	{
		manager.game_state = 2;//game_state==2,����ʤ��
	}
	manager.updata();
}
