#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>
#include<conio.h>
#include<graphics.h>


//定义一个圆的结构体进行封装函数
typedef struct role {
	int x;
	int y;
	int r;
	int speed;
}Role;

//初始化圆
void initcirCle(Role*& cirCle)
{
	cirCle->x = 200;
	cirCle->y = 300;
	cirCle->r = 5;
	cirCle->speed = 50;
}

//控制方向
void changeKey(Role *& cirCle)
{
	int userkey = _getch();
	switch (userkey)
	{
	case 'W':
	case 'w':
	case 72:
		cirCle->y -= cirCle->speed;
		break;
	case 's':
	case 'S':
	case 80:
		cirCle->y += cirCle->speed;
		break;
	case 'A':
	case 'a':
	case 75:
		cirCle->x -= cirCle->speed;
		break;
	case 'd':
	case 'D':
	case 77:
		cirCle->x += cirCle->speed;
		break;
	}
}
int main()
{
	Role* cirCle = (Role*)malloc(sizeof(Role));
	initgraph(500, 500);//初始化窗口
	outtextxy(1, 2, "任意键继续");//切记把属性字节格式换为多字节
	initcirCle(cirCle);
	while (1)
	{
		changeKey(cirCle);
		cleardevice();
		circle(cirCle->x, cirCle->y, cirCle->r);//圆心坐标，半径
		Sleep(10);
	}
	closegraph();
	return 0;
}