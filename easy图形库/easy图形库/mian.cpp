#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>//ͼ�ο�ͷ�ļ�
//����Ϊcpp��׺

//��ʽ�����ຯ��
void test2()
{
	//��ɫ����
	//set+color
	/*
		���ñ�����ɫsetbkcolor
		ע�⣺һ��Ҫˢ��  cleardevice();
		������������ɫsetlinecolor
		��ɫ�꣨��Ӧ��ɫ�Ĵ�д���ʣ�
		���� setlinecolor(RED);
		RGBģʽsetlinecolor(RGB�� �� �� ��);
		����������ɫ
		setfillcolor();
	*/

	/*
	��ʽ����
	�����ߵ���ʽ
	settextstyle(���� ����ϸ)��
	ע�⣻��Щָʾ������������ο��ĵ�api
	*/

	/*
	�������
	ֻ֧���ַ������
	ע�⣺outtextxy(int x,int y,const char*str)������Ҫ���ֽڸ�ʽ��Ϊ���ֽ�
	����--���߼�--���ַ���--�����ֽ��ַ���
	���־��б�����Ҫȥ������ setbkmode(TRANSPARENT);
	������ʽ settextstyle(int h,int w,"����");
	ע�⣺�߶���0���߿����0 ��������Ӧ ϵͳ�Լ��жϱ���
	������ɫ
	settextcolor();

	ע��������������������
	��Ҫ�Լ��ӹ���װһ������
	����
	void outtextxy(int x,int y,int score)
	{
		char str[20]="";
		sprintf(str,"����Ϊ%d",score);
		outtextxy(x,y,str);
	}



	*/
	
}


void test()
{
//	//��������
//	line(0, 0, 200, 200);
//	//��������
//
//	for (int i = 0; i <= 200; i+=50)
//	{
//		line(0, i, 200, i);
//		line(i, 0, i, 200);
//	}

//����ͼ��
 rectangle(100, 100, 200, 200);//���Ͻ����꣬���½�����
 //Բ��ͼ��
 circle(100, 100, 50);//Բ�����꣬�뾶

 //���fill+��״����  û�б߽���
 fillcircle(80, 80, 20);
 //���solid+��״����   �б߽���
 solidcircle(120, 120, 20);

 //��ʽ�����ຯ��
 test2();
}
int main()
{
	//��ʼ������
	//initgraph(200, 200);//����ʾ����̨
	initgraph(200, 200,1);//��ʾ����̨��Ҫ����һ������1
	//�����qt����һ������
	/*
	* ������ʽ
	0------------x
	|
	|
	|
	|
	y
	
	*/

	test();
	while (1);

	closegraph();//�رմ���

	return 0;
}