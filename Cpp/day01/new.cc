#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

void test()
{
    int *p=new int(1);//括号有数字就是初始化为你所要的数据
    int *num=new int();//括号没有数组就默认为0
    cout<<*p<<endl;
    cout<<*num<<endl;
    delete p;//按照申请顺序来delete空间
    delete num;
}
int main()
{
    test();
    return 0;
}

