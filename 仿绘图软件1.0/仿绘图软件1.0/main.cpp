

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
		cleardevice(); 
		Menu();//菜单
		while (peekmessage(&msg))
		{
			keydown(msg);
			Realize_function(msg);//功能实现
			FlushBatchDraw();
		}
		
	}
	EndBatchDraw();
	closegraph();
}