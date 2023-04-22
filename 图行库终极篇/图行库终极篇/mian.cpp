#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <stdio.h>
/*
	//鼠标信息是一些系列的值，需要保存到特定的结构体中
	//1.创建鼠标消息的变量
		MOUSEMSG  m
	//2.GetMouseMsg();
	//3.坐标: 访问鼠标结构体的x和y成员
	//4.分类讨论
		m.uMsg 这个值去分辨当前鼠标操作的类型
		windows:窗口  message:消息  mouse:鼠标 move:移动
		R:right
		L:left
		BUTTON: 按钮
		WM_MOUSEMOVE:  鼠标移动
		WM_LBUTTONDOWN: 左键按下
		WM_RBUTTONDOWN: 右键按下
		WM_LBUTTONUP:   左键弹起
		WM_RBUTTONUP:	右键弹起
*/

int main()
{
	initgraph(400, 400);
	struct MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();			//获取鼠标消息
		printf("%d,%d\n", m.x, m.y);
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			//printf("鼠标移动!\n");
			putpixel(m.x, m.y, RED);
			break;
		case WM_LBUTTONDOWN:
			setfillcolor(WHITE);
			fillcircle(m.x, m.y, 10);
			//printf("左键按下\n");
		case WM_RBUTTONDOWN:
			setfillcolor(WHITE);
			fillrectangle(m.x, m.y, m.x - 5, m.y - 5);
			//printf("右键按下\n");
			break;
		case WM_MBUTTONDOWN:
			setfillcolor(RED);
			fillcircle(m.x, m.y, 10);
			break;
		}
	}
	closegraph();
	return 0;
}