#include "React.h"

React::React(int x, int y, int mx, int my)
{
	this->x = x;
	this->y = y;
	this->my = my;
	this->mx = mx;
}

void React::setX(int& x)
{
	this->x = x;
}

void React::setY(int& y)
{
	this->y = y;
}

void React::setMx(int& mx)
{
	this->mx = mx;
}

void React::setMy(int& my)
{
	this->my = my;
}

int React::getX()
{
	return x;
}

int React::getY()
{
	return y;
}

int React::getMx()
{
	return mx;
}

int React::getMy()
{
	return my;
}

void React::setReact(int& x, int& y, int& mx, int& my)
{

}


