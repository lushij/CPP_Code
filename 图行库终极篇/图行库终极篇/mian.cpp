#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <stdio.h>
/*
	//�����Ϣ��һЩϵ�е�ֵ����Ҫ���浽�ض��Ľṹ����
	//1.���������Ϣ�ı���
		MOUSEMSG  m
	//2.GetMouseMsg();
	//3.����: �������ṹ���x��y��Ա
	//4.��������
		m.uMsg ���ֵȥ�ֱ浱ǰ������������
		windows:����  message:��Ϣ  mouse:��� move:�ƶ�
		R:right
		L:left
		BUTTON: ��ť
		WM_MOUSEMOVE:  ����ƶ�
		WM_LBUTTONDOWN: �������
		WM_RBUTTONDOWN: �Ҽ�����
		WM_LBUTTONUP:   �������
		WM_RBUTTONUP:	�Ҽ�����
*/

int main()
{
	initgraph(400, 400);
	struct MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();			//��ȡ�����Ϣ
		printf("%d,%d\n", m.x, m.y);
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			//printf("����ƶ�!\n");
			putpixel(m.x, m.y, RED);
			break;
		case WM_LBUTTONDOWN:
			setfillcolor(WHITE);
			fillcircle(m.x, m.y, 10);
			//printf("�������\n");
		case WM_RBUTTONDOWN:
			setfillcolor(WHITE);
			fillrectangle(m.x, m.y, m.x - 5, m.y - 5);
			//printf("�Ҽ�����\n");
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