#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>
#include<time.h>
#include<conio.h>

void DrawTxt()
{
	int x = 220;
	int y = 160;
	const char* str[8] = { "若","想","登","顶","必","要","先","苦" };
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
	//按键交互
	//文字闪烁效果
	
	settextstyle(32, 0, "黑体");
	while (1)
	{
		//_kbhit()函数用于检查是否按键已被按下，如果按键被按下，则返回一个非零值，否则返回零。
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//先设置颜色，在设置文字
		outtextxy(30,200, "既然有缘，便赠与先生几句箴言");
		Sleep(10);
		settextcolor(WHITE);
		outtextxy(120, 300, "任意键进行下一页");
		if (_kbhit())
		{
			char useKey = _getch();
			break;
		}
	}
	
}



int main()
{
	initgraph(500, 500);//初始化窗口
	srand((unsigned int)time(NULL));
	test();
	cleardevice();
	DrawTxt();
	
	while (1);
	closegraph();
	return 0;
}