#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#pragma comment(lib,"winmm.lib")//启动多线程库
using namespace std;
const int NUM = 46;
//添加音乐
DWORD WINAPI playMusic(LPVOID pvoid)
{
	mciSendString("open 11.mp3", 0, 0, 0);
	mciSendString("play 11.mp3 wait", 0, 0, 0);
	mciSendString("close 11.mp3", 0, 0, 0);
	return 0;
}
//爱心的坐标，最笨的方法
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

//文字,采用二维数组
char buff[NUM][50] = {
		"一封信",
		"两年未都",
		"没动笔",
		"三个字",
		"过了",
		"几个四季",
		"你是有",
		"多想逃避",
		"来不及",
		"问问你",
		"我已经",
		"错过",
		"相爱",
		"的日期",
		"那天你",
		"消失在",
		"人海里",
		"你的背影",
		"沉默的",
		"让人恐惧",
		"你说的",
		"那些问题",
		"我回答得",
		"很坚定",
		"偏偏",
		"那个时候",
		"我最想你",
		"我不曾",
		"爱过你",
		"我自己",
		"骗自己",
		"已经给你",
		"写了信",
		"又被我",
		"丢进海里",
		"我不曾",
		"爱过你",
		"我自己",
		"骗自己",
		"明明觉得",
		"自己",
		"很冷静",
		"却还",
		"掉入",
		"我自己",
		"的陷阱"
};

//图片
IMAGE img[10];
char txt[56] = "0";
void loadResource()
{
	for (int i = 0; i < 10; i++)
	{
		sprintf(txt, "memory\\%d.jpg", i + 1);//组装函数
		loadimage(&img[i],txt,240,240);
	}
}

void initMap()
{
	int n = 0;
	//音乐开始
	CreateThread(NULL, NULL, playMusic, NULL, NULL, NULL);
	for (int i = 0; i < NUM; i++)
	{
		Sleep(100);//第一次为了效果明显
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256, ));
		outtextxy(arr[i].x, arr[i].y, buff[i+n%NUM]);
	}
	
	while (1)
	{
		cleardevice();
		for (int i = 0; i < NUM; i++)
		{
			//这个部分主要为了彰显图的变换
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