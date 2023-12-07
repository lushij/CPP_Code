#include <iostream>
using namespace std;
class Point
{
public:
    Point(int ix,int iy)
    :_ix(ix)
     ,_iy(iy)
    {
        cout<<"Point()"<<endl;
    }
    Point(const Point & rhs)
        :_ix(rhs._ix)
         ,_iy(rhs._iy)
    {

    }
    
    void print()
    {
        cout<<"("<<_ix<<","<<_iy<<")";
    }
private:
    int _ix;
    int _iy;
};

class Line
{
public:
    //显示调用对应的构造函数
    Line(int x1,int y1,int x2,int y2)
        :_p1(x1,y1)
         ,_p2(x2,y2)
    {
        cout<<"Line(int,int,int,int)"<<endl;
    }

    void printLine()
    {
        _p1.print();
        cout<<"-->";
        _p2.print();
        cout<<endl;
    }
private:
    //类中还可以定义其他的类
    Point _p1;
    Point _p2;
};
void test()
{
    Line l(1,2,3,4);
    l.printLine();
}
int main()
{
    test();
    return 0;
}

