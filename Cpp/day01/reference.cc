#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test()
{
    int number=10;
    int &num=number;//引用的形式就是如此
    num=100;
    cout<<"number is "<<number<<endl
        <<"num is "<<num<<endl;
    number=1000;
    cout<<"number is "<<number<<endl
        <<"num is "<<num<<endl;
}
void test1()
{
    int num=10;
    int n=11;
    int *p=&num;
   // p=&n;
    int &rfe=num;//引用进项绑定必须是已经存在的变量,且一旦绑定后就不可更改
   // &rfe=n;//erro
    cout<<"&num："<<&num<<endl
        <<"指针p："<<p<<endl
        <<"引用 rfe："<<&rfe<<endl;
}
int main()
{
    /* test(); */
    test1();
    return 0;
}

