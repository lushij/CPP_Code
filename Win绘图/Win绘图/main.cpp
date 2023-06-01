#include"Global.h"

void ribbon()
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	fillrectangle(650, 15, 750, 80);
	for (int i = 0; i < 3; i++)
	{
		int x = 650 + i * 30;
		int y = 40;
		setfillcolor(color[i]);
		
		fillrectangle(x+i*2, 15, x + 30, y);
	}
}


void menu()
{
	setfillcolor(RGB(245, 246, 247));
	setlinecolor(RGB(218, 219, 220));
	setlinestyle(PS_SOLID, 2);
	fillrectangle(0, 0, Width, WHigh);
	ribbon();
}


int main()
{
	initgraph(Width, High);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	while (1)
	{
		menu();
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}