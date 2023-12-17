#include <iostream>
#include <string>
#include<string.h>
#include <stdio.h>
using namespace std;
class Complex
{

public:
    Complex(int x)
        :_x(x)
    {

    }
    //第一种方式类内实现
    Complex operator+(const Complex &rhs)
    {
        return  Complex(_x+rhs._x);//临时对象，生命周期只在这一行
    }
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

