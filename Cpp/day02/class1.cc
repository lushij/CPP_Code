#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Stu
{
    //行业代码风格：public在上，private在下
public:
    //函数（方法）声明
    void print();
    void print1();
    void print2();
private:
    int _age;
    int _id;

};

void Stu::print()
{
    cout<<"print()"<<endl;
}
void Stu::print2()
{
    cout<<"print1()"<<endl;
}
void test()
{
    Stu s;
    s.print();
}
int main()
{
    test();
    return 0;
}

