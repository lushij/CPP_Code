#pragma once
#include"Point.h"
class Rect
{
public:
	Rect(int x = 0, int y = 0, int mx = 0, int my = 0);
	void setX(int x);
	void setY(int y);
	void setMx(int mx);
	void setMy(int my);
	int getX();
	int getY();
	int getMx();
	int getMy();
private:
	int x;
	int y;
	int mx;
	int my;
};

