

#include"Tool.h"
Tool* r = new Tool();

int main()
{
	initgraph(Width, High,1);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();
	setbkmode(TRANSPARENT);//����ģʽΪ͸��ģʽ
	ExMessage msg;

	while (1)
	{
		r->show();
		while (peekmessage(&msg))
		{

			cleardevice();
			Menu();//�˵�
			keydown(msg);
			FlushBatchDraw();
		}
		
	}


	EndBatchDraw();
	closegraph();
}