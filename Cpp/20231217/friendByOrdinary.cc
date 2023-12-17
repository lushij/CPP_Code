#include <iostream>
#include <string>
#include <stdio.h>
#include<math.h>
using namespace std;
//友元是不会受public/private/protect 的限制的
class Point
{
    //友元的第一种形式：以普通函数存在
    friend float distance(const Point & lhs,const Point &rhs);
public:
    Point(int x,int y)
        :_x(x)
         ,_y(y)
    {

    }
    void print()
    {
        cout<<"("<<_x<<","<<_y<<")";
    }
    ~Point()
    {

    }
private:
    int _x;
    int _y;
};
//并且在外面不需要类的作用域，并且可以访问类的私有成员
float distance(const Point &lhs,const Point &rhs)
{
    return hypot(lhs._x-rhs._x,lhs._y-rhs._y);
}
void test()
{
    Point p1(1,2);
    Point p2(5,5);
    p1.print();
    cout<<"-->";
    p2.print();
    cout<<" distance is "<<distance(p1,p2)<<endl;
}
int main()
{
    test();
    return 0;
}

