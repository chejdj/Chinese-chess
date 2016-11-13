#pragma once
class Chess
{
public:
	Chess(void);
	int type;//1兵 2炮 3车 4马 5象 6士 7帅 大于7表示棋子无效//2表示象，3表示炮，5代表车！！
	bool color;//false上面（汉方玩家） true下面（楚方玩家）
	int x,y;
	virtual ~Chess(void);
};

