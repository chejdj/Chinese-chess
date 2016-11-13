#include "stdafx.h"
#include "Managers.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
Managers::Managers(void)
{
	//��ʼ������
	int i,j;
	for(i=0;i<32;i++)
		nChessinfo[i].type=8;
	for(i=0;i<9;i++)
		for(j=0;j<10;j++)
			map[i][j]=0;
	game_state=-1;//��ʼ������ǰΪ-1����ʼ�����̺�ֵ0��������ҿ�ʼ����
	PointCh=NULL;//��ǰѡ��Ϊ��
}


Managers::~Managers(void)
{
}


Chess* Managers::search(int x, int y)
{
	int i;
	for(i=0;i<32;i++)
		if(nChessinfo[i].x==x && nChessinfo[i].y==y && nChessinfo[i].type<=7)
			return nChessinfo+i;
	return NULL;
}


void Managers::gamestart(void)
{
	int i,j;
	//��ʼ���յ�����
	for(i=0;i<9;i++)
		for(j=0;j<10;j++)
			map[i][j]=0;
	for(i=0;i<16;i++)
		nChessinfo[i].color=true;//true���������·��ĳ���
	//
	for(i=16;i<32;i++)
		nChessinfo[i].color=false;
	for(i=0;i<5;i++)//[0]-[4]
	{
		map[i*2][6]=2;
		nChessinfo[i].type=1;
		nChessinfo[i].x=i*2;
		nChessinfo[i].y=6;
	}
	for(i=16;i<21;i++)//[16]-[20]
	{
		map[(i-16)*2][3]=1;
		nChessinfo[i].type=1;
		nChessinfo[i].x=(i-16)*2;
		nChessinfo[i].y=3;
	}
	map[1][7]=2;
	map[7][7]=2;
	nChessinfo[5].type=5;//��1
	nChessinfo[5].x=1;
	nChessinfo[5].y=7;
	nChessinfo[6].type=5;//��2
	nChessinfo[6].x=7;
	nChessinfo[6].y=7;

	for(i=7;i<16;i++)
		nChessinfo[i].y=9;
	nChessinfo[7].type=2;//��1
	nChessinfo[7].x=0;
	nChessinfo[8].type=2;//��2
	nChessinfo[8].x=8;

	nChessinfo[9].type=4;//��1
	nChessinfo[9].x=1;
	nChessinfo[10].type=4;//��2
	nChessinfo[10].x=7;

	nChessinfo[11].type=3;//��1
	nChessinfo[11].x=2;
	nChessinfo[12].type=3;//��2
	nChessinfo[12].x=6;

	nChessinfo[13].type=6;//ʿ1
	nChessinfo[13].x=3;
	nChessinfo[14].type=6;//ʿ2
	nChessinfo[14].x=5;
	nChessinfo[15].type=7;//˧1
	nChessinfo[15].x=4;

	for(i=0;i<9;i++)
	{
		map[i][0]=1;//�������һ���ǰ׷�
		map[i][9]=2;//������һ���Ǻڷ�
	}

	//�׷�˫��
	map[1][2]=1;
	map[7][2]=1;
	nChessinfo[21].type=5;//��3
	nChessinfo[21].x=1;
	nChessinfo[21].y=2;
	nChessinfo[22].type=5;//��4
	nChessinfo[22].x=7;
	nChessinfo[22].y=2;


	for(i=23;i<32;i++)
		nChessinfo[i].y=0;
	nChessinfo[23].type=2;//��3
	nChessinfo[23].x=0;
	nChessinfo[24].type=2;//��4
	nChessinfo[24].x=8;
	nChessinfo[25].type=4;//��3
	nChessinfo[25].x=1;
	nChessinfo[26].type=4;//��4
	nChessinfo[26].x=7;
	nChessinfo[27].type=3;//��3
	nChessinfo[27].x=2;
	nChessinfo[28].type=3;//��4
	nChessinfo[28].x=6;
	nChessinfo[29].type=6;//ʿ3
	nChessinfo[29].x=3;
	nChessinfo[30].type=6;//ʿ4
	nChessinfo[30].x=5;
	nChessinfo[31].type=7;//��2
	nChessinfo[31].x=4;
	PointCh=NULL;
	game_state=0;//������ĺ�������ʼ��
	
}


bool Managers::DoMsg(int x, int y, int action)
{
	if(PointCh==NULL)
	    return false;
	if(game_state>1)
		return false;
	if(PointCh->color==game_state)//�ߵ��ǵ�ǰ���ж�Ȩ�����
	{
		if(action==1)
		{
			if(PointCh->x==x && PointCh->y==y)//ȡ��ѡ��
			{
				PointCh=NULL;
				return true;
			}
			else if(Moveto(x,y,true))//��������ƶ��Ļ����ƶ�
			{
				//ɾ������ȥ������
				updata();
				return true;
			}
			else if(map[x][y]==game_state+1)//ѡ���˸���ҵ�����һ������
			{
				PointCh=search(x,y);// ���������ø����ӵ�ָ��
				return true;
			}
			else//ȡ��ѡ��
			{
				PointCh=NULL;
				return false;
			}
		}
		else if(action==0)
		{
			if(PointCh!=NULL)
			{
				if(Moveto(x,y,false))
				{
					return true;
					//��(x,y)��������ʾ
				}
			}
		}
	}

	return false;
}





bool Managers::Moveto(int x, int y, bool isgo)
{
	
	if (PointCh==NULL)
		return false;
	Chess &ch=*PointCh;
	if((map[x][y]==1 && !ch.color) ||(map[x][y]==2 && ch.color))//�ж�Ҫ�ߵ�λ�����Ƿ����б�������
		return false;
	if(ch.type==1)//��
	{
		if((abs(ch.x-x)==1 && ch.y==y) ||(abs(ch.y-y)==1 && ch.x==x))
		{
			if(!ch.color && ch.y<5 && ch.x!=x)//������� ��yС��5��ʱ���ǲ���ת���
				return false;
			if(ch.color && ch.y>4 && ch.x!=x)//ͬ��
				return false;
			if(!ch.color && y<ch.y)//���ܺ���
				return false;
			if(ch.color && y>ch.y)//���ܺ���
				return false;
			if(isgo)
			{
				map[ch.x][ch.y]=0;
				ch.x=x;
				ch.y=y;
				if(ch.color)//2���ߵ�
				{
					
					map[x][y]=2;
				}
				else
					map[x][y]=1;
				return true;
			}
			else//����ֻ��ʾ�������
				return true;
		}
		else
			return false;
	}
	else if(ch.type==5)//��
	{
		if((ch.x!=x && ch.y!=y) || (ch.x==x && ch.y==y))//ֻ����ʮ��ֱ������
			return false;
		int i=ch.x-x,j=ch.y-y;//�����������
		if(i>0)
			i--;
		else if(i<0)
			i++;
		if(j>0)
			j--;
		else if(j<0)
			j++;
		int num=0;
		while(i!=0 || j!=0)//������
		{
			if(map[ch.x-i][ch.y-j]!=0)
				num++;
			if(i>0)
				i--;
			else if(i<0)
				i++;
			if(j>0)
				j--;
			else if(j<0)
				j++;
		}
		if(map[x][y]!=0 && num!=1)//���Ǹ�ɽ�ڲ��ܳ���
			return false;
		if(map[x][y]==0 && num!=0)//������������
			return false;
		if(isgo)
		{
			map[ch.x][ch.y]=0;
			ch.x=x;
			ch.y=y;
			if(ch.color)
				map[x][y]=2;
			else
				map[x][y]=1;
			return true;
		}
		else
			return true;
	}
	else if(ch.type==2)//��
	{
		if((ch.x!=x && ch.y!=y) || (ch.x==x && ch.y==y))//ֻ����ֱ��
			return false;
		int i=ch.x-x,j=ch.y-y;
		if(i>0)
			i--;
		else if(i<0)
			i++;
		if(j>0)
			j--;
		else if(j<0)
			j++;
		while(i!=0 || j!=0)
		{
			if(map[ch.x-i][ch.y-j]!=0)//��⵽�ϰ���������
				return false;
			if(i>0)
				i--;
			else if(i<0)
				i++;
			if(j>0)
				j--;
			else if(j<0)
				j++;
		}
		if(isgo)
		{
			map[ch.x][ch.y]=0;
			ch.x=x;
			ch.y=y;
			if(ch.color)
				map[x][y]=2;
			else
				map[x][y]=1;
		
			return true;
		}
		else
			return true;
	}
	else if(ch.type==4)//4��
	{
		if((abs(ch.x-x)==1 && abs(ch.y-y)==2) ||(abs(ch.x-x)==2 && abs(ch.y-y)==1))
		{	
			int xi,yi;//����
			if(abs(ch.x-x)==1)
			{
				xi=ch.x;
				yi=(ch.y+y)/2;
			}
			else
			{
				yi=ch.y;
				xi=(ch.x+x)/2;
			}
			if(map[xi][yi]!=0)
				return false;
			if(isgo)
			{
				map[ch.x][ch.y]=0;
				ch.x=x;
				ch.y=y;
				if(ch.color)
					map[x][y]=2;
				else
					map[x][y]=1;
				
				return true;
			}
			else
				return true;
		}
		else
			return false;
	}
	else if(ch.type==3)// 5��
	{
		if(!ch.color && y>4)//�Ϸ���
			return false;
		if(ch.color && y<5)//�·���
			return false;
		if(abs(ch.x-x)==2 && abs(ch.y-y)==2 && map[(ch.x+x)/2][(ch.y+y)/2]==0)
		{
			if(isgo)
			{
				map[ch.x][ch.y]=0;
				ch.x=x;
				ch.y=y;
				if(ch.color)
					map[x][y]=2;
				else
					map[x][y]=1;
				
				return true;
			}
			else
				return true;
		}
		else
			return false;
	}
	else if(ch.type==6)// 6ʿ 
	{
		if(x<3 || x>5)
			return false;
		if(y>2 && y<7)
			return false;
		if(abs(ch.x-x)==1 && abs(ch.y-y)==1)
		{
			if(isgo)
			{

				map[ch.x][ch.y]=0;
				ch.x=x;
				ch.y=y;
				if(ch.color)
					map[x][y]=2;
				else
					map[x][y]=1;
				
				return true;
			}
			else
				return true;
		}
		else
			return false;
	}
	else if(ch.type==7)//7˧
	{
		if(x<3 || x>5)
			return false;
		if(y>2 && y<7)
			return false;
		if((abs(ch.x-x)==1 && ch.y==y) ||(ch.x==x && abs(ch.y-y)==1))
		{
			if(isgo)
			{
			
				map[ch.x][ch.y]=0;
				ch.x=x;
				ch.y=y;
				if(ch.color)
					map[x][y]=2;
				else
					map[x][y]=1;
				return true;
			}
			else
				return true;
		}
		else
			return false;
	}
	return false;
}


void Managers::updata(void)
{
	if (game_state == 4) {
		MessageBox(NULL, _T("����"), _T(""), IDOK);
	}
	if (game_state == 3) {
		MessageBox(NULL, _T("����ʤ��"), _T(""), IDOK);
	}
	if (game_state == 2) {
		MessageBox(NULL, _T("����ʤ��"), _T(""), IDOK);
	}
	for (int i = 0; i < 32; i++)
	{
		if(map[nChessinfo[i].x][nChessinfo[i].y]!=(nChessinfo[i].color+1))//�����ɫ��һ��
		{
			nChessinfo[i].type=8;
		}
	
	}	
	if(nChessinfo[15].type==8)
	{
		if(MessageBox(NULL,L"���2���ˣ��Ƿ����棿",L"gameover",MB_OKCANCEL)==IDOK)
			gamestart(),game_state=1;
		PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	}
	if(nChessinfo[31].type==8)
	{
		if(MessageBox(NULL,L"���1���ˣ��Ƿ����棿",L"gameover",MB_OKCANCEL)==IDOK)
			gamestart(),game_state=1;
		PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
	}

	if(nChessinfo[15].x==nChessinfo[31].x)//������ͬһֱ����
	{
		int count=0;
		//�����������ߴ��Ƿ�������
		for (int i = nChessinfo[31].y+1; i < nChessinfo[15].y; i++)
		{
			if(map[nChessinfo[31].x][i]!=0)
			{
				count++;
				break;//����
			}
		}

		if(count==0)//��һ�غ��ж����и�
		{
			if(game_state==0)
			{
				if(MessageBox(NULL,L"���1���ˣ��Ƿ����棿",L"gameover",MB_OKCANCEL)==IDOK)
					gamestart(),game_state=1;
				PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
			}
			else if(game_state==1)
			{
				if(MessageBox(NULL,L"���2���ˣ��Ƿ����棿",L"gameover",MB_OKCANCEL)==IDOK)
					gamestart(),game_state=1;
				PlaySoundA("����Ӯ��.wav", NULL, SND_FILENAME | SND_PURGE | SND_NODEFAULT | SND_ASYNC);
			}

		}

	}

}
