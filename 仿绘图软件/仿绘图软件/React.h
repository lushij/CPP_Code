#pragma once
#include"Point.h"
class React
{
public:
	React(int x = 0, int y = 0, int mx = 0, int my = 0);
	void setX(int &x);
	void setY(int &y);
	void setMx(int &mx);
	void setMy(int &my);
	int getX();
	int getY();
	int getMx();
	int getMy();
	void setReact(int& x, int& y, int& mx, int& my);
private:
	int x;//左上
	int y;//左上
	int mx;//右下
	int my;//右下
};

