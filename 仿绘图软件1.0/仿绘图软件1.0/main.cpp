#include"Global.h"



int main()
{
	initgraph(Width, High);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	setbkmode(TRANSPARENT);//背景模式为透明模式
	while (1)
	{
		Menu();//菜单
		FlushBatchDraw();
	}


	EndBatchDraw();
	closegraph();
}