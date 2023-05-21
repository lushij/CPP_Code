#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<graphics.h>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
//结构体封装
 struct Star {
	int x;
	int y;
	int r;
	int speed;
};//流星和星星区分开来
Star s[500];
IMAGE imgWelcome[2];//主页和背景
IMAGE imgMeter[2];//流星
void loadResource()
{
	//L或在系统里设置多字节设置
	loadimage(imgWelcome, L"welcome.png", getwidth(), getheight());
	loadimage(imgWelcome+1, L"bk.jpg", getwidth(), getheight());
	loadimage(imgMeter, L"1.jpg", 50,50);
	loadimage(imgMeter +1, L"2.jpg",50, 50);
}

void initWeclomeView()
{
	putimage(0, 0, imgWelcome);
}
void initTxt()//文字部分
{
	
	settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	outtextxy(300, 100, L"有缘自会相见");
	outtextxy(270,150, L"各自努力，顶峰相见");
	outtextxy(270,200, L"你若安好，便是晴天");
	outtextxy(230,250, L"两情若是久长时,又岂在朝朝暮暮");
	outtextxy(230,300, L"长相思兮长相忆,短相思兮无穷极");
	outtextxy(390,350, L"作者：鲁");
	for (int i = 0; i < 10; i++)
	{
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(rand() % getwidth(), rand() % getheight(), rand()%2? _T("♥") :_T("❤"));
	}
	Sleep(200);
}

void initStar(Star *s, int x, int y, int r, int speed)
{
	s->x = x;
	s->y = y;
	s->r = r;
	s->speed = speed;
}
void starDraw(Star* s)
{
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256, ));
	fillcircle(s->x, s->y, s->r);
}

void init()
{
	for (int i = 0; i < 500; i++)
	{
		int x = rand() % 1200;
		int y = rand()%800;
		initStar(s+i, x, y, 1, rand() % 5+1);
	}

}
void Draw()
{
	
	for (int i = 0; i < 500; i++)
	{
		starDraw(s + i);
	}
}

Star m[100];

void init(Star*m,int x,int y,int speed)
{
	m->x = x;
	m->y = y;
	m->speed = speed;
}

/***********************************************/
//流星  坐标 速度
struct Meteor
{
	int x;
	int y;
	int speed;	//速度
};
void meteor_init(Meteor* pthis, int x, int y, int speed)
{
	pthis->x = x;
	pthis->y = y;
	pthis->speed = speed;
}
void meteor_draw(Meteor* pthis)
{
	putimage(pthis->x, pthis->y, imgMeter + rand() % 2, SRCPAINT);
}
void meteor_update(Meteor* pthis)
{
	pthis->x += pthis->speed;
	pthis->y += pthis->speed;

	if (pthis->y > 800)
	{
		pthis->x = rand() % 1200 - 300;	
		pthis->y = rand() % 1200 - 300;	
	}
}

/***********************************************/
int main()
{
	srand((unsigned int)time(NULL));
	initgraph(1200, 800);
	//播放音乐 media control interface send string
	mciSendString(L"open 浪漫空气.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	//设置背景模式
	settextstyle(26, 0, _T("宋体")); // 设置文字大小和字体
	setbkmode(TRANSPARENT);//透明模式
	while (!_kbhit())
	{
		loadResource();
		initWeclomeView();
		initTxt();//文字部分
		FlushBatchDraw();
	}

	/************/
	Meteor meteors[100];
	for (int i = 0; i < 100; i++)
	{
		int x = rand() % 1500 - 300;	//[-300,800]
		int y = rand() % 1200 - 300;	//[-300,540]
		meteor_init(meteors + i, x, y, rand() % 2 + 1);
	}
	while (true)
	{
		//方式闪屏:双缓冲
		BeginBatchDraw();
		putimage(0, 0, imgWelcome  + 1);
		for (int i = 0; i < 100; i++)
		{
			meteor_draw(meteors + i);
			meteor_update(meteors + i);
		}
		EndBatchDraw();
		Sleep(10);
	}

	/************/

	EndBatchDraw();
	closegraph();
	return 0;
}