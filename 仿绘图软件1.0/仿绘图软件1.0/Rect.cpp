#include "Rect.h"

Rect::Rect(int x, int y, int mx, int my)
{
	this->x = x;
	this->y = y;
	this->mx = mx;
	this->my = my;
}

void Rect::setX(int x)
{
	this->x = x;
}

void Rect::setY(int y)
{
	this->y = y;
}

void Rect::setMx(int mx)
{
	this->mx = mx;
}

void Rect::setMy(int my)
{
	this->my = my;
}

int Rect::getX()
{
	return x;
}

int Rect::getY()
{
	return y;
}

int Rect::getMx()
{
	return mx;
}

int Rect::getMy()
{
	return my;
}
