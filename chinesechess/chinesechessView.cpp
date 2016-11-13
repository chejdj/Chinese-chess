
// chinesechessView.cpp : CchinesechessView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
#pragma comment(lib, "winmm.lib")//链接库
extern Managers manager;
// CchinesechessView

IMPLEMENT_DYNCREATE(CchinesechessView, CView)

BEGIN_MESSAGE_MAP(CchinesechessView, CView)
	// 标准打印命令
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

// CchinesechessView 构造/析构

CchinesechessView::CchinesechessView()
{
	// TODO: 在此处添加构造代码
	start=true;
	num1 = 100;
	num2 = 100;//100表示当前没有选中某个坐标
}


CchinesechessView::~CchinesechessView()
{
}

BOOL CchinesechessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改，给个个对象插入图片
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
		chessall.CreateCompatibleDC(pDC);//双缓存去闪机制 
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
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CchinesechessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CchinesechessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

// CchinesechessView 诊断

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


// CchinesechessView 消息处理程序


void CchinesechessView::DrawStar(int x, int y, CDC* pdc)//绘画出棋盘上的星型
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
void CchinesechessView::DrawChessbord(CDC * pdc)//绘画棋盘！
{
	CPen chessbord1,chessbord2;//创建画笔
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
	if(!ch.color)//上面玩家（白
	{
		chessall.SelectObject(m_mask);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,0,MERGEPAINT);
		chessall.SelectObject(m_chess);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,0, SRCAND);
	}
	else//下面玩家（黑
	{
		chessall.SelectObject(m_mask);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,45,MERGEPAINT);
		chessall.SelectObject(m_chess);
		pdc->BitBlt(60+ch.x*50,45+ch.y*50,45,45,&chessall,(7-ch.type)*45,45,SRCAND);
	}
}



int CchinesechessView::SelectNum(int x, int y)//选择数据
{
	x = (x-60)/50;
	y = (y-45)/50;
	return	y*10+x;
}


void CchinesechessView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(manager.PointCh==NULL)
		return;
	int	mx=point.x;
	int	my=point.y;
	if(mx>=65&&my>=50&&mx<=490&&my<=525)//在棋盘内
	{
		int k;//一个十位数存储当前坐标值 (x,y)表示为 y*10+x
		k=SelectNum(mx,my);
		if(manager.game_state==0||manager.game_state==1)
		{
			if(manager.DoMsg(k%10,k/10,false))
			{
				num2=k;//显示可移动的区域
			}
			else
			{
				num2=100;//表示不可移动
			}
		}
	}
	PrintAll();
	CView::OnMouseMove(nFlags, point);
}


void CchinesechessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
			if((manager.game_state+1)==manager.map[k%10][k/10])//有当前行动回合玩家的子
			{
				manager.PointCh=manager.search(k%10,k/10);
			}
		}
		else//当前已有目标
		{
			if((manager.game_state+1)==manager.map[k%10][k/10])//是自己的其他棋子
			{

				manager.PointCh=manager.search(k%10,k/10);
			}
			else if(manager.DoMsg(k%10,k/10,true))//如果可以就过去
			{
				num1=k;//num1记录走过的痕迹
				manager.game_state=(manager.game_state==0);//in turns
				PlaySoundA("落子声.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_SYNC|SND_NOSTOP);
			}
			else//过不去
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
	// TODO: 在此添加命令处理程序代码
	manager.gamestart();
	PlaySoundA("开局声.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	PrintAll();
}


void CchinesechessView::On32773()
{
	// TODO: 在此添加命令处理程序代码
	manager.gamestart();
	PlaySoundA("开局声.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	PrintAll();
}

void CchinesechessView::PrintAll(void)
{
	CDC *pdc = GetDC();
	chessall.SelectObject(&m_chessbord);//画背景
	temp.BitBlt(0, 0, 610, 620, &chessall, 0, 0, SRCCOPY);//双缓存去闪机制
	DrawChessbord(&temp);//画在缓存的dc中   每次重绘都完全覆盖上一次的内容 画棋盘上的线
	int	k = 0;
	//画出所有棋子
	for (; k <= 31; k++)
	{
		if (manager.nChessinfo[k].type <= 7)
			DrawChess(manager.nChessinfo[k], &temp);
	}
	//画出选中的棋子的选框
	if (manager.PointCh != NULL)
		DrawChoose(manager.PointCh->x, manager.PointCh->y, &temp);
	//如果不可走则没有选中区域
	if (num1<100)
		DrawChoose(num1 % 10, num1 / 10, &temp);
	if (num2<100)
		DrawChoose(num2 % 10, num2 / 10, &temp);

	pdc->BitBlt(0, 0, 800, 600, &temp, 0, 0, SRCCOPY);
}


void CchinesechessView::On32783()//开始播放音乐
{
	// TODO: 在此添加命令处理程序代码
	PlaySoundA("背景音乐.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
}


void CchinesechessView::On32784()
{
	// TODO: 在此添加命令处理程序代码
   PlaySoundA(NULL, NULL, SND_FILENAME);
}


void CchinesechessView::On32785()//汉方和棋
{
	// TODO: 在此添加命令处理程序代码
	PlaySoundA("5390.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	manager.game_state = 4;
	manager.updata();
}


void CchinesechessView::On32786()//汉方认输
{
	// TODO: 在此添加命令处理程序代码
	PlaySoundA("己方赢声.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	int k;
	k = MessageBox(_T("你真的想认输吗？"), _T(""), MB_OKCANCEL);
	if (k == 1)
	{
		manager.game_state = 3;//game_state==3,楚方胜利
	}
	manager.updata();

}


void CchinesechessView::On32787()//楚方和棋
{
	// TODO: 在此添加命令处理程序代码
	PlaySoundA("5390.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	manager.game_state = 4;
	manager.updata();
}


void CchinesechessView::On32788()   //楚方认输
{
	// TODO: 在此添加命令处理程序代码
	PlaySoundA("己方赢声.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	//此时game_state=1;
	int k;
	k = MessageBox(_T("你真的想认输吗？"), _T(""), MB_OKCANCEL);
	if (k == 1)
	{
		manager.game_state = 2;//game_state==2,汉方胜利
	}
	manager.updata();
}
