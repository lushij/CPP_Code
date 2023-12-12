#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int ROW = 3;
const int COL = 3;
IMAGE W, B, M;

void loadResource()
{
	loadimage(&W, "����.png",100,100);
	loadimage(&B, "����.png", 100, 100);
	loadimage(&M, "��ͼ.png", 100, 100);
}


int map[ROW][COL] = 
{ 
	0,0,0,
	0,0,0,
	0,0,0
};

void drawMap()
{
	int i = 0;
	int j = 0;
	for(i=0;i<ROW;i++)
	{
		for (j = 0; j < COL; j++)
		{
			int x = j * 100;//���������й�ϵ
			int y = i * 100;
			//cout << i << " " << j <<" " <<x << " " << y << endl;
			if(map[i][j]==0)
			{
				putimage(x,y,&M);
			}
			if (map[i][j] == 1)
			{
				putimage(x, y, &W);//����
			}
			if (map[i][j] == 2)
			{
				putimage(x, y, &B);//����
			}
		}

	}
}

void comPlay()
{
	
	while (1)
	{
		int a = rand() % ROW;
		int b = rand() % COL;
		if (map[a][b] == 0)
		{
			map[a][b] = 2;
			//cout << "��������" << a << " " << b << endl;
			break;
		}
	}
}

int winGame()
{
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
	{
		if (map[i][0] == map[i][1] && map[i][1] == map[i][2] && map[i][1] != 0)
		{
			return map[i][1];
		}
	}

	//�ж�����
	for (i = 0; i < COL; i++)
	{
		if (map[0][i] == map[1][i] && map[1][i] == map[2][i] && map[2][i] != 0)
		{
			return map[1][i];
		}
	}
	//�ж϶Խ���
	if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[1][1] != 0)
		return map[1][1];
	if (map[0][2] == map[1][1] && map[1][1] == map[2][0] && map[1][1] != 0)
		return map[1][1];
}

int keyDown(HWND hwnd)
{
	
	int ret = 0;
	while (1)
	{
		drawMap();
		ret = winGame();
		if (ret == 1)
		{
			
			MessageBox(hwnd, "���Ӯ", "gameover", MB_OK);
			return 1;
		}
		else if (ret == 2)
		{
			MessageBox(hwnd, "����Ӯ", "gameover", MB_OK);
			return 1;
		}
		else
		{
			//�ж�ƽ��
			int count = 0;
			for (int n = 0; n < ROW; n++)
			{
				for (int k = 0; k < COL; k++)
				{
					if (map[n][k] == 0)
					{
						count++;
					}
				}
			}
			if (count == 1)
			{
				MessageBox(hwnd, "ƽ��", "gameover", MB_OK);
				
				//MessageBox(hwnd, "ƽ��", "gameover", MB_YESNO);
				return 1;
			}
			
		}
		
		//�����
		MOUSEMSG m = GetMouseMsg();
		int i = m.y / 100;//ͨ����������˳������±�  ��  --->���y�������ÿһ��ĸ߶�
		int j = m.x / 100;//������
		
		switch (m.uMsg)
		{
			//��
			case WM_LBUTTONDOWN:
				map[i][j] = 1;
				//cout <<"�������"<< i << " " << j << endl;
				//����
				comPlay();
				/*��������
				for (int n = 0; n < ROW; n++)
				{
					for (int k = 0; k < COL; k++)
					{
						if (map[n][k] == 0)
							cout << "��������" << n << " " << k << "";
					}

				}
				cout << endl;*/
				break;
		}	
		
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	loadResource();
	HWND hwnd=initgraph(300, 300);
	//drawMap();
	keyDown(hwnd);
	closegraph();
	return 0;
}