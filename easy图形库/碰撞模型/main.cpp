#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>
#include<conio.h>
#include<graphics.h>


//����һ��Բ�Ľṹ����з�װ����
typedef struct role {
	int x;
	int y;
	int r;
	int speed;
}Role;

//��ʼ��Բ
void initcirCle(Role*& cirCle)
{
	cirCle->x = 200;
	cirCle->y = 300;
	cirCle->r = 5;
	cirCle->speed = 50;
}

//���Ʒ���
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
	initgraph(500, 500);//��ʼ������
	outtextxy(1, 2, "���������");//�мǰ������ֽڸ�ʽ��Ϊ���ֽ�
	initcirCle(cirCle);
	while (1)
	{
		changeKey(cirCle);
		cleardevice();
		circle(cirCle->x, cirCle->y, cirCle->r);//Բ�����꣬�뾶
		Sleep(10);
	}
	closegraph();
	return 0;
}