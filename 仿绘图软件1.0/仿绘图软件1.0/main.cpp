#include"Global.h"



int main()
{
	initgraph(Width, High);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	setbkmode(TRANSPARENT);//����ģʽΪ͸��ģʽ
	while (1)
	{
		Menu();//�˵�
		FlushBatchDraw();
	}


	EndBatchDraw();
	closegraph();
}