#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>
#include<time.h>
#include<conio.h>

void DrawTxt()
{
	int x = 220;
	int y = 160;
	const char* str[8] = { "��","��","��","��","��","Ҫ","��","��" };
	for (int i = 0; i < 4; i++)
	{
		outtextxy(x, y + i * 50, str[i]);
		Sleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		outtextxy(x + 50, y + i * 50, str[i+4]);
		Sleep(100);
	}

}

void test()
{
	//��������
	//������˸Ч��
	
	settextstyle(32, 0, "����");
	while (1)
	{
		//_kbhit()�������ڼ���Ƿ񰴼��ѱ����£�������������£��򷵻�һ������ֵ�����򷵻��㡣
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//��������ɫ������������
		outtextxy(30,200, "��Ȼ��Ե��������������������");
		Sleep(10);
		settextcolor(WHITE);
		outtextxy(120, 300, "�����������һҳ");
		if (_kbhit())
		{
			char useKey = _getch();
			break;
		}
	}
	
}



int main()
{
	initgraph(500, 500);//��ʼ������
	srand((unsigned int)time(NULL));
	test();
	cleardevice();
	DrawTxt();
	
	while (1);
	closegraph();
	return 0;
}