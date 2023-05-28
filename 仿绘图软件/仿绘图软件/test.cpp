#include"ReacTool.h"
void initDrawMenu()
{
	setfillcolor(RGB(245, 246, 247));
	setlinecolor(RGB(218, 219, 220));
	setlinestyle(PS_SOLID, 2);//设置线的形式
	fillrectangle(0, 0, WIDTH, MHIGH);
}

int main()
{
	ReacTool* pRect = new ReacTool;
	initgraph(WIDTH, HIGH,1);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	while (1)
	{
		initDrawMenu();
		pRect->show();
		ExMessage msg;
		while (peekmessage(&msg))
		{
			pRect->event(msg);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}