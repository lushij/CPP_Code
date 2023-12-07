#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void dispaly(int *p)
{
    cout<<p<<endl;
}
void test()
{
    int *p=static_cast<int*>(malloc(sizeof(int)));
    dispaly(p);
    const int a=10;
    dispaly(const_cast<int*>(&a));//ok
    //但是个人感觉没必要，因为你都设置为常量属性了，肯定不会再改了吧
}
int main()
{
    test();
    return 0;
}

