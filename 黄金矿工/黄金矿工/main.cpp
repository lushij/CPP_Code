#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<gui/Gui.h>
#include<graphics.h>
using namespace std;
#define Width 800
#define High  600

IMAGE img;
IMAGE oldMan[2];
//Ã¶¾Ù
enum State
{
	Nomal,Long,Short
};

class Tool
{
public:
	double x;
	double y;
	double endx;
	double endy;
	double speed;
	State state;
public:
	Tool()
	{
		this->x = 0;
		this->y = 0;
		this->endx = 0;
		this->endy = 0;
		this->speed = 5;
		this->state = Nomal;//Õý³£
	}

};
void loadResource()
{
	loadimage(oldMan + 0, "./Resource/images/oldMan-up.png" );
	loadimage(oldMan + 1, "./Resource/images/oldMan-down.png");
}

void initT()
{
	BeginBatchDraw();
	cleardevice();
	loadResource();
	setfillcolor(RGB(221, 180, 118));
	fillrectangle(0, 0, Width, 100);
	loadimage(&img, "./Resource/images/bk.jpg");
	putimage(0, 100, &img);
	for (int i = 0; i < 2; i++)
	{
		/*cleardevice();*/
		drawTexture((getwidth() - (oldMan + 0)->getwidth()) / 2, 0, oldMan + i);
	}
	
	FlushBatchDraw();

}
int main()
{
	
	initgraph(Width, High);
	setbkmode(TRANSPARENT);
	while (1)
	{
		initT();

	}



	EndBatchDraw();
	closegraph();
	return 0;
}