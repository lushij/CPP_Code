#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<graphics.h>

using namespace std;

class Button 
{
private:
	//��ť�����Ͻ�
	int x;
	int y;
	//��ť�Ŀ�͸�
	int w;
	int h;
	unsigned long outColor;			//���ڰ�ť����ɫ
	unsigned long inColor;			//�ڰ�ť����ɫ
	char* str;						//���е�����
	unsigned long textColor;		//������ɫ
	char* changeTxt;//���ĵ�����
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

	//���ư�ť
	void DrawButton()
	{
		solidrectangle(getX(), getY(), getX() + getW(), getY() + getH());
		setbkmode(TRANSPARENT);
		settextcolor(getTxtColor());
		//����������ʾ����
		int height = textheight(getStr());
		int width = textwidth(getStr());
		int x = getX() + (getW() - width) / 2;
		int y = getY() + (getH() - height) / 2;
		outtextxy(x,y,getStr());
	}
	//�ж�����Ƿ��ڰ�ť������
	bool mouseInButton(Button pB, struct MOUSEMSG m)
	{
		
		if ( pB.getX()<= m.x && m.x <= pB.getX() + pB.getW() &&
			pB.getY() <= m.y && m.y <= pB.getY() + pB.getH())
		{
			//���������У�������ɫ����
			setfillcolor(pB.getInColor());
			return 1;
		}
		setfillcolor(pB.getOutColor());
		return 0;
	}

	//���������У����ָ��ĵȲ���Ч��
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
		"��ʼ", BLACK);
	Button endButton;
	endButton.setNum(200, 0, 100, 25, RGB(204, 213, 240), RGB(236, 244, 255),
		"����", BLACK);
	//����
	Button deTailButton;
	deTailButton.setNum(100, 0, 100, 25, RGB(204, 213, 240), RGB(236, 244, 255),
		"����", BLACK);

	BeginBatchDraw();
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();
		if (pButton.mouseInButton(pButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			pButton.setTxt("������");
		}
		pButton.DrawButton();

	
		if (deTailButton.mouseInButton(deTailButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			deTailButton.setTxt("����");
		}
		deTailButton.DrawButton();

		if (endButton.mouseInButton(endButton, m) && m.uMsg == WM_LBUTTONDOWN)
		{
			endButton.setTxt("������");
			break;
		}
		endButton.DrawButton();
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}