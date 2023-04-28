#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<graphics.h>
#include<iostream>
#pragma comment(lib,"winmm.lib")//�������߳̿�
using namespace std;
const int IMAGEW = 600;//ͼƬ�Զ������ŵĿ�
const int IMAGEH = 600;//ͼƬ�Զ������ŵĸ�
const int ROW = 4;//����
const int COL = 4;//����
const int BlockW = IMAGEW / COL;//�и�ÿС��Ŀ�
const int BlockH = IMAGEH / ROW;//�и�ÿС��ĸ�

IMAGE mm, white;
int map[ROW][COL] =
{
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,15,13,14
};
//����map[i][j]==15Ϊ�׿鼴�滻��ͼƬ

//������Դ
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

//��������Ҫͨ���Ӻ����������������ı�ֵ
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
	mciSendString("open ���.mp3", 0,0,0);
	mciSendString("play ���.mp3 wait", 0,0,0);
	mciSendString("close ���.mp3", 0,0,0);
	return 0;
}

void keyDown()
{
	while (1)
	{
		//�Ȼ�����ͼ
		drawMap();
		if (winGame())
		{
			break;
		}
		MOUSEMSG m = GetMouseMsg();
		int i = m.y / BlockH;//ͨ����������˳������±�  ��  --->���y�������ÿһ��ĸ߶�
		int j = m.x / BlockW;//������
		int wi = search().i;//�׿������
		int wj = search().j;
		//ͨ������̨���е���
		/*cout <<"�����±�" << i << " " << j << endl;
		cout << "�׿�����" << wi << " " << wj << endl;*/
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
	HWND hwnd=initgraph(IMAGEW, IMAGEH);//���
	keyDown();
	/*Sleep(10);*/
	MessageBox(hwnd, "��Ϸ����", "gameover", MB_OK);
	closegraph();
	return 0;
}