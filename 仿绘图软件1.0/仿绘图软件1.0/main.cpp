

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
		cleardevice(); 
		Menu();//�˵�
		while (peekmessage(&msg))
		{
			keydown(msg);
			Realize_function(msg);//����ʵ��
			FlushBatchDraw();
		}
		
	}
	EndBatchDraw();
	closegraph();
}