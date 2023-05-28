#pragma once
#include"Global.h"
class Point
{
public:
	Point(int x = 0, int y = 0);
	void setX(int &x);
	void setY(int &y);
	int getX();
	int getY();
	void setPoint(int &x,int &y);
private:
	int x;
	int y;
};

