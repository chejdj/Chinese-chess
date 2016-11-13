
// chinesechessView.h : CchinesechessView 类的接口
//

#pragma once

#include "Chess.h"
class CchinesechessView : public CView
{
protected: // 仅从序列化创建
	CchinesechessView();
	DECLARE_DYNCREATE(CchinesechessView)

// 特性
public:
	CchinesechessDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CchinesechessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawStar(int x, int y, CDC* pdc);//画棋盘
	void DrawChessbord(CDC * pdc);//画象棋游戏的背景
	CDC chessall;//用于创建局部图片的画板
	CDC temp;//用于创建总体布局的画板
	CBitmap tempbitmap;//刚开始用来创建610*620窗口大小
	CBitmap m_background;//用于储存背景图片
	CBitmap m_chessbord;//用于储存棋盘图片
	CBitmap m_chess;//用于储存棋子图片
	CBitmap m_mask;//用于储存棋子圆形图片
	CBitmap m_choose;//用于储存选择框图片
	void DrawChoose(int x, int y, CDC * pdc);//画选择的框框
	void DrawChess(Chess ch, CDC* pdc);//画棋子
	bool start;
	void PrintAll(void);//重新绘制棋局上的所有
	int SelectNum(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int num1;//num1点击移动后上一个位置的移动标识
	int num2;//num2 为可动标识
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32772();//menu菜单中 开始游戏事件
	afx_msg void On32773();//重新开始的事件
	afx_msg void On32783();// menu菜单中 播放音乐开始事件
	afx_msg void On32784();//menu菜单中 播放音乐停止事件
	afx_msg void On32785();//menu 菜单中 汉方和棋事件
	afx_msg void On32786();// menu菜单中 汉方认输事件（汉代表棋盘的上方就是红色的那方）
	afx_msg void On32787();//menu 菜单中 楚方和棋事件
	afx_msg void On32788();//menu菜单中  楚方认输事件
};

#ifndef _DEBUG  // chinesechessView.cpp 中的调试版本
inline CchinesechessDoc* CchinesechessView::GetDocument() const
   { return reinterpret_cast<CchinesechessDoc*>(m_pDocument); }
#endif

