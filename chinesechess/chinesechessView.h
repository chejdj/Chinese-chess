
// chinesechessView.h : CchinesechessView ��Ľӿ�
//

#pragma once

#include "Chess.h"
class CchinesechessView : public CView
{
protected: // �������л�����
	CchinesechessView();
	DECLARE_DYNCREATE(CchinesechessView)

// ����
public:
	CchinesechessDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CchinesechessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void DrawStar(int x, int y, CDC* pdc);//������
	void DrawChessbord(CDC * pdc);//��������Ϸ�ı���
	CDC chessall;//���ڴ����ֲ�ͼƬ�Ļ���
	CDC temp;//���ڴ������岼�ֵĻ���
	CBitmap tempbitmap;//�տ�ʼ��������610*620���ڴ�С
	CBitmap m_background;//���ڴ��汳��ͼƬ
	CBitmap m_chessbord;//���ڴ�������ͼƬ
	CBitmap m_chess;//���ڴ�������ͼƬ
	CBitmap m_mask;//���ڴ�������Բ��ͼƬ
	CBitmap m_choose;//���ڴ���ѡ���ͼƬ
	void DrawChoose(int x, int y, CDC * pdc);//��ѡ��Ŀ��
	void DrawChess(Chess ch, CDC* pdc);//������
	bool start;
	void PrintAll(void);//���»�������ϵ�����
	int SelectNum(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int num1;//num1����ƶ�����һ��λ�õ��ƶ���ʶ
	int num2;//num2 Ϊ�ɶ���ʶ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32772();//menu�˵��� ��ʼ��Ϸ�¼�
	afx_msg void On32773();//���¿�ʼ���¼�
	afx_msg void On32783();// menu�˵��� �������ֿ�ʼ�¼�
	afx_msg void On32784();//menu�˵��� ��������ֹͣ�¼�
	afx_msg void On32785();//menu �˵��� ���������¼�
	afx_msg void On32786();// menu�˵��� ���������¼������������̵��Ϸ����Ǻ�ɫ���Ƿ���
	afx_msg void On32787();//menu �˵��� ���������¼�
	afx_msg void On32788();//menu�˵���  ���������¼�
};

#ifndef _DEBUG  // chinesechessView.cpp �еĵ��԰汾
inline CchinesechessDoc* CchinesechessView::GetDocument() const
   { return reinterpret_cast<CchinesechessDoc*>(m_pDocument); }
#endif

