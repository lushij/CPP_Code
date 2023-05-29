#include "Tool.h"
extern Tool *r;
bool status[8] = { false,false,false, false, false, false, false, false };//开关，false，默认
void setColor(int x,int y,int mx,int my)
{
	setfillcolor(RGB(245, 246, 247));
	setlinecolor(RGB(218, 219, 220));
	setlinestyle(PS_SOLID, 2);
	fillrectangle(x, 0, mx,my);
}

void setClickColor(int x, int y, int mx, int my)
{
	setlinecolor(RGB(201, 224, 247));
	setlinestyle(PS_SOLID, 2);
	setfillcolor(RGB(201, 224, 247));
	fillrectangle(x, 0, mx, my);
}

void Menu()
{
	
	settextcolor(BLACK);
	settextstyle(30,0,"微软雅黑");
	int w = 100;
	int h = 100;
	select(status);
	brush(status);
	revoke(status);
	rectangle(status);
	circle(status);
	color(status);
	thickness(status);
	filling(status);
}
void select(bool *stadus)
{
	if (!status[0])
	{
		//默认
		setColor(0, 0, 100, MHigh);
		char txt[56] = "选择";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((100 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(0, 0, 100, MHigh);
		char txt[56] = "选择";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((100 - w) / 2, (100 - h) / 2, txt);
	}
	
}
void brush(bool *status)
{
	if (!status[1])
	{
		//默认
		setColor(100, 0, 200, MHigh);
		char txt[56] = "画笔";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((300 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(100, 0, 200, MHigh);
		char txt[56] = "画笔";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((300 - w) / 2, (100 - h) / 2, txt);
	}
}
void revoke(bool *status)
{
	if (!status[2])
	{
		//默认
		setColor(200, 0, 300, MHigh);
		char txt[56] = "撤销";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((500 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(200, 0, 300, MHigh);
		char txt[56] = "撤销";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((500 - w) / 2, (100 - h) / 2, txt);
	}
}

void rectangle(bool *status)
{
	if (!status[3])
	{
		//默认
		setColor(300, 0, 400, MHigh);
		char txt[56] = "矩形";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((700 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(300, 0, 400, MHigh);
		char txt[56] = "矩形";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((700 - w) / 2, (100 - h) / 2, txt);
	}
	
}

void circle(bool *status)
{
	if (!status[4])
	{
		//默认
		setColor(400, 0, 500, MHigh);
		char txt[56] = "圆形";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((900 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(400, 0, 500, MHigh);
		char txt[56] = "圆形";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((900 - w) / 2, (100 - h) / 2, txt);
	}
	
}

void color(bool *status)
{
	if (!status[5])
	{
		//默认
		setColor(500, 0, 600, MHigh);
		char txt[56] = "颜色";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1100 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(500, 0, 600, MHigh);
		char txt[56] = "颜色";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1100 - w) / 2, (100 - h) / 2, txt);
	}
	
}
void thickness(bool *status)
{
	if (!status[6])
	{
		//默认
		setColor(600, 0, 700, MHigh);
		char txt[56] = "粗细";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1300 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(600, 0, 700, MHigh);
		char txt[56] = "粗细";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1300 - w) / 2, (100 - h) / 2, txt);
	}
	
}

void filling(bool *status)
{
	if (!status[7])
	{
		//默认
		setColor(700, 0, 800, MHigh);
		char txt[56] = "填充";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1500 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(700, 0, 800, MHigh);
		char txt[56] = "填充";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((1500 - w) / 2, (100 - h) / 2, txt);
	}
	
}

void clear(int x,int y,int mx,int my)
{
	if (!status[1])
	{
		//默认
		setColor(0, 0, 100, MHigh);
		char txt[56] = "选择";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((100 - w) / 2, (100 - h) / 2, txt);
	}
	else
	{
		setClickColor(0, 0, 100, MHigh);
		char txt[56] = "选择";
		int w = textwidth(txt);
		int h = textheight(txt);
		outtextxy((100 - w) / 2, (100 - h) / 2, txt);
	}
}

void keydown(ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		if (msg.x >= 0 && msg.x <= 100 && msg.y >= 0 && msg.y <= 100)
		{
			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 0)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 100 && msg.x <= 200 && msg.y >= 0 && msg.y <= 100)
		{
			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 1)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 200 && msg.x <= 300 && msg.y >= 0 && msg.y <= 100)
		{

			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 2)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 300 && msg.x <= 400 && msg.y >= 0 && msg.y <= 100)
		{

			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 3)
				{
					status[i] = true;
				}
			}
			Rectangle(msg);//矩形实现
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 400 && msg.x <= 500 && msg.y >= 0 && msg.y <= 100)
		{

			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 4)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 500 && msg.x <= 600 && msg.y >= 0 && msg.y <= 100)
		{
			
			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 5)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		if (msg.x > 600 && msg.x <= 700 && msg.y >= 0 && msg.y <= 100)
		{

			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 6)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
		
		if (msg.x > 700 && msg.x <= 800 && msg.y >= 0 && msg.y <= 100)
		{
			for (int i = 0; i < 8; i++)
			{
				status[i] = false;
				if (i == 7)
				{
					status[i] = true;
				}
			}
			/*cout << msg.x << " " << msg.y << endl;*/
		}
	}
}

void Rectangle(ExMessage&msg)//矩形实现
{
	if (isRange(msg))
	{
		while (peekmessage(&msg))
		{
			r->event(msg);
		}
	}
	
}

bool isRange(ExMessage& msg)
{
	if (msg.x >= 0 && msg.x <= Width && msg.y >= MHigh && msg.y <= High)
	{
		return true;
	}
	return false;
}

