

#include"Tool.h"
Tool* r = new Tool();

int main()
{
	initgraph(Width, High,1);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	setbkmode(TRANSPARENT);//背景模式为透明模式
	ExMessage msg;

	while (1)
	{
		r->show();
		while (peekmessage(&msg))
		{

			cleardevice();
			Menu();//菜单
			keydown(msg);
			FlushBatchDraw();
		}
		
	}


	EndBatchDraw();
	closegraph();
}