#include <iostream>
#include <string>
#include <stdio.h>
#include<math.h>
using namespace std;
//注意使用友元的第二种方式：类内成员函数可能需要类的前向声明
class Point;//类的前向声明，否则可能会造成数据类型的不完整
//incomplete type 'Point' named in nested name specifier
//嵌套名称说明符中命名的不完全类型“行”
class Line
{
public:
    //注意：友元成员函数的声明要放在public
    //      而且实现函数要在类外实现，因为类型不完全
    //      还有友元具有单一性，不具有传递性
    //      友元函数重载需要分别单独实现
    float distance(const Point &a,const Point &b);

};
class Point
{
    friend float Line::distance(const Point &a,const Point &b);
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
//友元第二种实现方式：友元之类成员函数
float Line::distance(const Point &lhs,const Point &rhs)
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
    cout<<" distance is "<<Line().distance(p1,p2)<<endl;//这种写法是临时对象
}
int main()
{
    test();
    return 0;
}

