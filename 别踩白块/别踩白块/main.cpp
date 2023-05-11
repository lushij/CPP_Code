#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")//�������߳̿�
const int GradW = 100;
const int GradH = 150;
using namespace std;

int flag[4];

void initFlag()
{
	for (int i = 0; i < 4; i++)
	{
		flag[i] = rand() % 4;
	}
}

void DrawMap()
{
	//����������ɫ
	setlinecolor(BLACK);
	//������������ʽ
	setlinestyle(PS_SOLID, 2);
	for (int i = 0; i < 4; i++)
	{
		line(i * GradW, 0, i * GradW, 600);//��������꣩--->���յ����꣩
		line(0, i * GradH, 400, i * GradH);
	}
	//���ƺڿ����
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(BLACK);
		solidrectangle(flag[i] * GradW, i * GradH, flag[i] * GradW + GradW, i * GradH + GradH);
	}
}

//��Ч����
DWORD WINAPI playMusic(LPVOID pvoid)
{
	mciSendString("open bgm.mp3", 0, 0, 0);
	mciSendString("play bgm.mp3 wait", 0, 0, 0);
	mciSendString("close bgm.mp3", 0, 0, 0);
	return 0;
}
void keyDown(HWND hwnd)
{
	MOUSEMSG m = GetMouseMsg();
	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
	
		//������һ�еĺڿ��ˢ��
		int x = flag[3] * GradW;
		int y = 3 * GradH;
		if (m.x >= x && m.y >= y && m.x <= x + GradW && m.y <= y + GradH)
		{
			for (int i = 3; i >= 1; i--)
			{
				flag[i] = flag[i - 1];
			}
			flag[0] = rand() % 4;
		}
		else
		{
			MessageBox(hwnd, "��Ϸ����", "gameover", MB_OK);
			exit(0);
		}
		break;
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	HWND hwnd=initgraph(400, 600);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();//˫����
	initFlag();
	
	while (1)
	{
		cleardevice();
		DrawMap();
		keyDown(hwnd);
		FlushBatchDraw();
	}
	
	EndBatchDraw();
	closegraph();
	return 0;
}