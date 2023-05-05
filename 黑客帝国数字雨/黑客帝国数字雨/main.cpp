#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>	


#define RAIN_NUM 128 //�ַ�������
#define STR_NUM 20	 //ÿ���������ַ�����
#define SIZE 15		 //�ַ����
#define SCREEN_TICKS_PER_FRAME (1000/60.0)	//ÿ����Ļ���� 16.666666

//������ṹ��
struct Rain
{
	int x;
	int y;
	int speed;			//�����ٶ�
	char str[STR_NUM];	//ÿһ����������ַ�
};
struct Rain rains[RAIN_NUM];

//��������ַ�
char createChar()
{
	int flag = rand() % 3;	//0 1 2
	if (flag == 0)
	{
		//���������ַ�
		return rand() % 10 + '0';
	}
	else if (flag == 1)
	{
		//������ĸ
		return rand() % 26 + 'A';
	}
	else
	{
		return rand() % 26 + 'a';
	}
}
//��ʼ��������
void rainInit()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].x = i * SIZE;		//�Ⱦ�
		rains[i].y = rand() % getheight();
		rains[i].speed = rand() % 3 + 1;	//1 2 3
		for (int k = 0; k < STR_NUM; k++)
		{
			rains[i].str[k] = createChar();
		}
	}
}
//����������
void rainDraw()
{
	//printf("hello ����");
	//error C2665:  2 ��������û��һ������ת�����в�������  �ַ�������
	//outtextxy(0, 0, "hello ����");

	for (int i = 0; i < RAIN_NUM; i++)
	{
		for (int k = 0; k < STR_NUM; k++)
		{
			//����������ɫ
			settextcolor(RGB(0, 255 - k * 13, 0));
			outtextxy(rains[i].x, rains[i].y - k * 15, rains[i].str[k]);
		}
	}
}
//�漴�ı��ַ�
void rainChangChar()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].str[rand() % STR_NUM] = createChar();
	}
}
//����
void raining()
{
	for (int i = 0; i < RAIN_NUM; i++)
	{
		rains[i].y += rains[i].speed;
		//������������ȥ��֮���ִ���������
		if (rains[i].y - STR_NUM * SIZE > getheight())
		{
			rains[i].y = 0;
		}
	}
}




int main()
{
	//����ͼ�δ���
	initgraph(960, 640);
	//���ñ���ģʽ
	setbkmode(TRANSPARENT);
	//�������������
	srand(time(NULL));
	rainInit();
	//fps 60 ��ο���֡��
	while (true)
	{
		//��ȡÿһ��ѭ����ʼ��ʱ��
		int startTime = clock();	//��ȡ�������е�����clock�����������ĺ�����

		//˫����
		BeginBatchDraw();
		//����
		cleardevice();

		rainDraw();
		rainChangChar();
		raining();
		FlushBatchDraw();
		//����һ����һ֡�����˶��ٺ���
		int frameTime = clock() - startTime;
		//�ж��Ƿ���ǰ��� 16ms 6 -> 10ms
		if (frameTime < SCREEN_TICKS_PER_FRAME)
		{
			Sleep(SCREEN_TICKS_PER_FRAME - frameTime);
		}
	}
	EndBatchDraw();	//�������е�ͼ���Ƶ�������
	closegraph();
	//getchar();
	return 0;
}