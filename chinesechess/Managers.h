#pragma once
#include "Chess.h"
class Managers
{
public:
	Managers(void);
	~Managers(void);
	int map[9][10];//������Ϣ 0��ʾ���ӣ�����ʾ�а��ӣ�����ʾ�к���   [][]�б�ʾ���ӵ����꣬��[0][0]��[8][9]
	int game_state;//��Ϸ״̬��0��ʾ��������ߣ�����ʾ��������ߣ�����ʾ����ʤ��������ʾ����ʤ����4��ʾ����
	Chess* search(int x, int y);
	void gamestart(void);
	Chess nChessinfo[32];
	bool DoMsg(int x, int y, int action);
	Chess* PointCh;
	bool Moveto(int x, int y, bool isgo);
	void updata(void);
};

