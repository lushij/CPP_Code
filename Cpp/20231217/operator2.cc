#include <iostream>
#include <string>
#include<string.h>
#include <stdio.h>
using namespace std;
class Complex
{
#if 1
    //第二种 友元函数
    friend Complex operator+(const Complex &lhs,const Complex &rhs);
#endif
public:
    Complex(int x)
        :_x(x)
    {

    }
#if 0
    //第一种方式类内实现
    Complex operator+(const Complex &rhs)
    {
        return  Complex(_x+rhs._x);//临时对象，生命周期只在这一行
    }
#endif
    void print()const
    {
        cout<<_x<<endl;

    }
    ~Complex()
    {

    }
private:
    int _x;
};
//第二种 友元
Complex operator+(const Complex &lhs ,const Complex &rhs)
{
    return Complex(rhs._x+lhs._x);
}
void test()
{
    Complex c1(1);
    Complex c2(2);
    Complex c3=c1+c2;
    c1.print();
    c2.print();
    c3.print();

}
int main()
{
    test();
    return 0;
}

