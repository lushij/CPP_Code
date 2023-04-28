#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<graphics.h>
#include<iostream>
#pragma comment(lib,"winmm.lib")//启动多线程库
using namespace std;
const int IMAGEW = 600;//图片自定义缩放的宽
const int IMAGEH = 600;//图片自定义缩放的高
const int ROW = 4;//行数
const int COL = 4;//列数
const int BlockW = IMAGEW / COL;//切割每小块的宽
const int BlockH = IMAGEH / ROW;//切割每小块的高

IMAGE mm, white;
int map[ROW][COL] =
{
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,15,13,14
};
//定义map[i][j]==15为白块即替换的图片

//加载资源
void loadResource()
{
	loadimage(&mm, "1.png", IMAGEW, IMAGEH);
	loadimage(&white, "white.jpg",BlockW, BlockH);
}

void drawMap()
{
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			int x = j * BlockW;
			int y = i * BlockH;
			if (map[i][j] == 15)
			{
				putimage(x, y, &white);
			}
			else
			{
				int row = map[i][j] / COL;
				int col = map[i][j] % COL;
			/*	printf("(r,c)=(%d,%d)\n", row, col);
				cout << col * BlockH << " " << row * BlockW << endl;*/
				putimage(x, y,BlockW,BlockH, &mm,  col * BlockW, row * BlockH);
			}
		}
	}
}

typedef struct WiMAG {
	int i;
	int j;
}WM;

WiMAG wm;

//鼠标操作需要通过子函数来遍历，否则会改变值
WM search()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == 15)
			{
				wm.i = i;
				wm.j = j;
				return wm;
			}
		}
	}
	return wm;
}

int winGame()
{
	int count = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (count++ != map[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
DWORD WINAPI playMusic(LPVOID pvoid)
{
	mciSendString("open 鼠标.mp3", 0,0,0);
	mciSendString("play 鼠标.mp3 wait", 0,0,0);
	mciSendString("close 鼠标.mp3", 0,0,0);
	return 0;
}

void keyDown()
{
	while (1)
	{
		//先画出地图
		drawMap();
		if (winGame())
		{
			break;
		}
		MOUSEMSG m = GetMouseMsg();
		int i = m.y / BlockH;//通过鼠标坐标退出数组下标  行  --->鼠标y坐标除以每一块的高度
		int j = m.x / BlockW;//数组列
		int wi = search().i;//白块的坐标
		int wj = search().j;
		//通过控制台进行调试
		/*cout <<"数组下标" << i << " " << j << endl;
		cout << "白块坐标" << wi << " " << wj << endl;*/
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			CreateThread(NULL, NULL, playMusic,NULL, NULL, NULL);

			if (i == wi && j == wj - 1)
			{
				
				/*swap(map[wi][wj], map[i][j]);*/
				map[wi][wj] = map[i][j];
				map[i][j] = 15;
			}
			else if (i == wi && j == wj + 1)
			{
				
				map[wi][wj] = map[i][j];
				map[i][j] = 15;
			}
			else if (i == wi-1 && j == wj )
			{
				
				map[wi][wj] = map[i][j];
				map[i][j] = 15;
			}
			else if (i == wi+1 && j == wj)
			{
				
				map[wi][wj] = map[i][j];
				map[i][j] = 15;
			}
			break;
		}
	}
	
}

int main()
{
	loadResource();
	HWND hwnd=initgraph(IMAGEW, IMAGEH);//句柄
	keyDown();
	/*Sleep(10);*/
	MessageBox(hwnd, "游戏结束", "gameover", MB_OK);
	closegraph();
	return 0;
}