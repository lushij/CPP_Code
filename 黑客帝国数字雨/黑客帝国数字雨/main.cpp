#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>	


#define RAIN_NUM 128 //字符雨条数
#define STR_NUM 20	 //每串数字雨字符个数
#define SIZE 15		 //字符间距
#define SCREEN_TICKS_PER_FRAME (1000/60.0)	//每秒屏幕节拍 16.666666

//数字雨结构体
struct Rain
{
	int x;
	int y;
	int speed;			//下落速度
	char str[STR_NUM];	//每一串数字雨的字符
};
struct Rain rains[RAIN_NUM];

//随机生成字符
char createChar()
{
	int flag = rand() % 3;	//0 1 2
	if (flag == 0)
	{
		//生成数字字符
		return rand() % 10 + '0';
	}
	else if (flag == 1)
	{
		//生成字母
		return rand() % 26 + 'A';
	}
	else
	{
		return rand() % 26 + 'a';
	}
}
//初始化数字雨
void rainInit()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].x = i * SIZE;		//等距
		rains[i].y = rand() % getheight();
		rains[i].speed = rand() % 3 + 1;	//1 2 3
		for (int k = 0; k < STR_NUM; k++)
		{
			rains[i].str[k] = createChar();
		}
	}
}
//绘制数字雨
void rainDraw()
{
	//printf("hello 歪你");
	//error C2665:  2 个重载中没有一个可以转换所有参数类型  字符集问题
	//outtextxy(0, 0, "hello 歪你");

	for (int i = 0; i < RAIN_NUM; i++)
	{
		for (int k = 0; k < STR_NUM; k++)
		{
			//设置文字颜色
			settextcolor(RGB(0, 255 - k * 13, 0));
			outtextxy(rains[i].x, rains[i].y - k * 15, rains[i].str[k]);
		}
	}
}
//随即改变字符
void rainChangChar()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].str[rand() % STR_NUM] = createChar();
	}
}
//下雨
void raining()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].y += rains[i].speed;
		//让数字雨落下去了之后，又从上往下落
		if (rains[i].y - STR_NUM * SIZE > getheight())
		{
			rains[i].y = 0;
		}
	}
}




int main()
{
	//创建图形窗口
	initgraph(960, 640);
	//设置背景模式
	setbkmode(TRANSPARENT);
	//设置随机数种子
	srand(time(NULL));
	rainInit();
	//fps 60 如何控制帧率
	while (true)
	{
		//获取每一次循环开始的时间
		int startTime = clock();	//获取程序运行到调用clock函数所经过的毫秒数

		//双缓冲
		BeginBatchDraw();
		//清屏
		cleardevice();

		rainDraw();
		rainChangChar();
		raining();
		FlushBatchDraw();
		//计算一下这一帧经过了多少毫秒
		int frameTime = clock() - startTime;
		//判断是否提前完成 16ms 6 -> 10ms
		if (frameTime < SCREEN_TICKS_PER_FRAME)
		{
			Sleep(SCREEN_TICKS_PER_FRAME - frameTime);
		}
	}
	EndBatchDraw();	//把内容中的图绘制到窗口上
	closegraph();
	//getchar();
	return 0;
}