#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
class Point
{
public:
    Point(int x,int y)
        :_x(x)
         ,_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }
    /*拷贝构造形式： 类名(const 类名 &); */
    Point(const Point & rhs)
        :_x(rhs._x)
         ,_y(rhs._y)
    {
         cout<<"Point(const Point & rhs)"<<endl;
    }
    void print()
    {
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

    //像这样的没有申请内存的可以直接用默认析构函数
private:
    int _x;
    int _y;
};
void test()
{
    Point p(1,2);
    p.print();
    Point p2(p);//拷贝构造
    p2.print();
}
int main()
{
    test();
    return 0;
}

