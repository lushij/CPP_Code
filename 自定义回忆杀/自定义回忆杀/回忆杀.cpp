#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#pragma comment(lib,"winmm.lib")//�������߳̿�
using namespace std;
const int NUM = 46;
//�������
DWORD WINAPI playMusic(LPVOID pvoid)
{
	mciSendString("open 11.mp3", 0, 0, 0);
	mciSendString("play 11.mp3 wait", 0, 0, 0);
	mciSendString("close 11.mp3", 0, 0, 0);
	return 0;
}
//���ĵ����꣬��ķ���
struct point {
	int x;
	int y;
};
point arr[NUM] = {
		{ 395,268 },
		{ 406,222 },
		{ 416,193 },
		{ 441,162 },
		{ 468,133 },
		{ 500,117 },
		{ 537,105 },
		{ 577,107 },
		{ 617,120 },
		{ 649,146 },
		{ 666,173 },
		{ 680,211 },
		{ 683,247 },
		{ 680,293 },
		{ 675,338 },
		{ 660,385 },
		{ 640,440 },
		{ 616,484 },
		{ 588,529 },
		{ 557,573 },
		{ 530,610 },
		{ 493,645 },
		{ 460,675 },
		{ 422,696 },
		{ 381,676 },
		{ 350,654 },
		{ 320,626 },
		{ 292,606 },
		{ 257,570 },
		{ 230,540 },
		{ 200,500 },
		{ 180,470 },
		{ 160,430 },
		{ 140,390 },
		{ 126,342 },
		{ 117,293 },
		{ 120,250 },
		{ 133,203 },
		{ 160,170 },
		{ 200,140 },
		{ 240,130 },
		{ 280,135 },
		{ 312,146 },
		{ 340,170 },
		{ 360,195 },
		{ 375,230 }
};

//����,���ö�ά����
char buff[NUM][50] = {
		"һ����",
		"����δ��",
		"û����",
		"������",
		"����",
		"�����ļ�",
		"������",
		"�����ӱ�",
		"������",
		"������",
		"���Ѿ�",
		"���",
		"�మ",
		"������",
		"������",
		"��ʧ��",
		"�˺���",
		"��ı�Ӱ",
		"��Ĭ��",
		"���˿־�",
		"��˵��",
		"��Щ����",
		"�һش��",
		"�ܼᶨ",
		"ƫƫ",
		"�Ǹ�ʱ��",
		"��������",
		"�Ҳ���",
		"������",
		"���Լ�",
		"ƭ�Լ�",
		"�Ѿ�����",
		"д����",
		"�ֱ���",
		"��������",
		"�Ҳ���",
		"������",
		"���Լ�",
		"ƭ�Լ�",
		"��������",
		"�Լ�",
		"���侲",
		"ȴ��",
		"����",
		"���Լ�",
		"������"
};

//ͼƬ
IMAGE img[10];
char txt[56] = "0";
void loadResource()
{
	for (int i = 0; i < 10; i++)
	{
		sprintf(txt, "memory\\%d.jpg", i + 1);//��װ����
		loadimage(&img[i],txt,240,240);
	}
}

void initMap()
{
	int n = 0;
	//���ֿ�ʼ
	CreateThread(NULL, NULL, playMusic, NULL, NULL, NULL);
	for (int i = 0; i < NUM; i++)
	{
		Sleep(100);//��һ��Ϊ��Ч������
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256, ));
		outtextxy(arr[i].x, arr[i].y, buff[i+n%NUM]);
	}
	
	while (1)
	{
		cleardevice();
		for (int i = 0; i < NUM; i++)
		{
			//���������ҪΪ������ͼ�ı任
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256, ));
			outtextxy(arr[i].x, arr[i].y, buff[i]);
		}
		putimage(320, 290, &img[n%10]);
		n++;
		if (n >= 10)n = 0;
		Sleep(200);
	}
	
}

int main()
{
	srand((unsigned int )time(NULL));
	initgraph(900, 800);
	loadResource();	
	
	initMap();
	closegraph();
	return 0;
}