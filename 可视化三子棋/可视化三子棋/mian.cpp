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
	loadimage(&W, "白棋.png",100,100);
	loadimage(&B, "黑棋.png", 100, 100);
	loadimage(&M, "地图.png", 100, 100);
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
			int x = j * 100;//坐标与行列关系
			int y = i * 100;
			//cout << i << " " << j <<" " <<x << " " << y << endl;
			if(map[i][j]==0)
			{
				putimage(x,y,&M);
			}
			if (map[i][j] == 1)
			{
				putimage(x, y, &W);//白旗
			}
			if (map[i][j] == 2)
			{
				putimage(x, y, &B);//白旗
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
			//cout << "电脑坐标" << a << " " << b << endl;
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

	//判断三列
	for (i = 0; i < COL; i++)
	{
		if (map[0][i] == map[1][i] && map[1][i] == map[2][i] && map[2][i] != 0)
		{
			return map[1][i];
		}
	}
	//判断对角线
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
			
			MessageBox(hwnd, "玩家赢", "gameover", MB_OK);
			return 1;
		}
		else if (ret == 2)
		{
			MessageBox(hwnd, "电脑赢", "gameover", MB_OK);
			return 1;
		}
		else
		{
			//判断平局
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
				MessageBox(hwnd, "平局", "gameover", MB_OK);
				
				//MessageBox(hwnd, "平局", "gameover", MB_YESNO);
				return 1;
			}
			
		}
		
		//玩家走
		MOUSEMSG m = GetMouseMsg();
		int i = m.y / 100;//通过鼠标坐标退出数组下标  行  --->鼠标y坐标除以每一块的高度
		int j = m.x / 100;//数组列
		
		switch (m.uMsg)
		{
			//人
			case WM_LBUTTONDOWN:
				map[i][j] = 1;
				//cout <<"玩家坐标"<< i << " " << j << endl;
				//电脑
				comPlay();
				/*测试数据
				for (int n = 0; n < ROW; n++)
				{
					for (int k = 0; k < COL; k++)
					{
						if (map[n][k] == 0)
							cout << "还有坐标" << n << " " << k << "";
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