#pragma once
#include "Chess.h"
class Managers
{
public:
	Managers(void);
	~Managers(void);
	int map[9][10];//棋盘信息 0表示无子，１表示有白子，２表示有黑子   [][]中表示棋子的坐标，从[0][0]到[8][9]
	int game_state;//游戏状态，0表示ｐｌａｙ１走，１表示ｐｌａｙ２走，２表示汉方胜利，３表示楚方胜利，4表示和棋
	Chess* search(int x, int y);
	void gamestart(void);
	Chess nChessinfo[32];
	bool DoMsg(int x, int y, int action);
	Chess* PointCh;
	bool Moveto(int x, int y, bool isgo);
	void updata(void);
};

