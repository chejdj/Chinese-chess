#pragma once
class Chess
{
public:
	Chess(void);
	int type;//1�� 2�� 3�� 4�� 5�� 6ʿ 7˧ ����7��ʾ������Ч//2��ʾ��3��ʾ�ڣ�5��������
	bool color;//false���棨������ң� true���棨������ң�
	int x,y;
	virtual ~Chess(void);
};

