#pragma once
#include"Global.h"
class Point
{
public:
	Point(int x = 0, int y = 0,int r = 0);
	void setX(int x);
	void setY(int y);
	void setR(int r);
	int getX();
	int getY();
	int getR();
private:
	int x;
	int y;
	int r;
};

