#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>
#include<conio.h>
#include<graphics.h>

//����һ��Բ�Ľṹ����з�װ����
typedef struct role {
	int x;
	int y;
	int r;
	int dx;
	int dy;
}Role;

//��ʼ��Բ
void initcirCle(Role*& cirCle)
{
	cirCle->x = 200;
	cirCle->y = 300;
	cirCle->r = 5;
	cirCle->dx = 10;
	cirCle->dy = 10;
}
void drawCircle(Role*& cirCle)
{
	setfillcolor(RED);
	solidcircle(cirCle->x, cirCle->y, cirCle->r);
}

void moveCircle(Role*& cirCle)
{
	if (cirCle->x - cirCle->r <= 0 || cirCle->x + cirCle->r >= 900)
	{
		cirCle->dx = -cirCle->dx;
		cirCle->dy = -cirCle->dy;
	}
	if (cirCle->y - cirCle->r <= 0 || cirCle->y + cirCle->r >= 600)
	{
		cirCle->dy = -cirCle->dy;
	}
	cirCle->x += cirCle->dx;
	cirCle->y += cirCle->dy;
}

int main()
{
	Role* cirCle = (Role*)malloc(sizeof(Role));
	initgraph(900, 600);//��ʼ������
	setbkcolor(WHITE);
	cleardevice();
	initcirCle(cirCle);
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		drawCircle(cirCle);
		moveCircle(cirCle);
		Sleep(10);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}