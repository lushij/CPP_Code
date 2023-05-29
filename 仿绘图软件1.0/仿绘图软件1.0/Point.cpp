#include "Point.h"

Point::Point(int x, int y,int r)
{
    this->x = x;
    this->y = y;
    this->r = r;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}

void Point::setR(int r)
{
    this->r = r;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

int Point::getR()
{
    return r;
}
