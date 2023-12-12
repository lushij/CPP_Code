#include <iostream>
#include <string>
#include <stdio.h>
#define mub(x,y) x*y  //宏函数不安全，只是进行简单的字符串替换
using namespace std;

void test()
{
    int x=1;
    int y=2;
    int z=3;
    int t=2;
    int ret=mub(1,2);
    cout<<"mub(1,2)"<<ret<<endl;//2
    ret=mub(x+y,z+t);//实际是2
    cout<<"mub(x+y,z+t)"<<ret<<endl;//理想是3*5=15但是现实是9（x+y*z+t)
    ret=mub(x,2+z);//因此不安全
    cout<<"mub(x,z+2)"<<ret<<endl;//1*5
}
int main()
{
    test();
    return 0;
}

