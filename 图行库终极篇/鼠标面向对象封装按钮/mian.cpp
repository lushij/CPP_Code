#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<graphics.h>

using namespace std;

class Button 
{
private:
	//按钮的左上角
	int x;
	int y;
	//按钮的宽和高
	int w;
	int h;
	unsigned long outColor;			//不在按钮中颜色
	unsigned long inColor;			//在按钮中颜色
	char* str;						//带有的文字
	unsigned long textColor;		//文字颜色
	char* changeTxt;//更改的文字
public:
	void setNum(int r,int m,int W,int H,COLORREF color, COLORREF c, const char*s,COLORREF c2)
	{
		x = r;
		y = m;
		w = W;
		h = H;
		outColor = color;
		inColor = c;
		str = (char*)malloc(strlen(s) + 1);
		strcpy(str, s);
		textColor = c2;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getW()
	{
		return w;
	}
	int getH()
	{
		return h;
	}
	COLORREF getOutColor()
	{
		return outColor;
	}
	COLORREF getInColor()
	{
		return inColor;
	}
	char* getStr()
	{
		return str;
	}
	COLORREF getTxtColor()
	{
		return textColor;
	}

	//绘制按钮
	void DrawButton()
	{
		solidrectangle(getX(), getY(), getX() + getW(), getY() + getH());
		setbkmode(TRANSPARENT);
		settextcolor(getTxtColor());
		//调整文字显示居中
		int height = textheight(getStr());
		int width = textwidth(getStr());
		int x = getX() + (getW() - width) / 2;
		int y = getY() + (getH() - height) / 2;
		outtextxy(x,y,getStr());
	}
	//判断鼠标是否在按钮区域中
	bool mouseInButton(Button pB, struct MOUSEMSG m)
	{
		
		if ( pB.getX()<= m.x && m.x <= pB.getX() + pB.getW() &&
			pB.getY() <= m.y && m.y <= pB.getY() + pB.getH())
		{
			//若在区域中，背景颜色更改
			setfillcolor(pB.getInColor());
			return 1;
		}
		setfillcolor(pB.getOutColor());
		return 0;
	}

	//若在区域中，文字更改等操作效果
	void setTxt(const char*s)
	{
		str = (char*)malloc(strlen(s) + 1);
		strcpy(str, s);
	}
};
int main()
{
	initgraph(800, 600);
	Button pButton;
	pButton.setNum(0, 0, 100, 25, RGB(204, 213, 240), RGB(236, 244, 255),
		"开始", BLACK);
	Button endButton;
	endButton.setNum(200, 0, 100, 25, RGB(204, 213, 240), RGB(236, 244, 255),
		"结束", BLACK);
	//详情
	Button deTailButton;
	deTailButton.setNum(100, 0, 100, 25, RGB(204, 213, 240), RGB(236, 244, 255),
		"详情", BLACK);

	BeginBatchDraw();
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();
		if (pButton.mouseInButton(pButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			pButton.setTxt("保存中");
		}
		pButton.DrawButton();

	
		if (deTailButton.mouseInButton(deTailButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			deTailButton.setTxt("详情");
		}
		deTailButton.DrawButton();

		if (endButton.mouseInButton(endButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			endButton.setTxt("保存中");
			break;
		}
		endButton.DrawButton();
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}