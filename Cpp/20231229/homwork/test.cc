#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test()
{
    int a=0;
    cout<<a++<<a++<<a++<<endl;
    int b[5]={1,2,3,4,5};
    int *p=&b[3];
    *p=100;
    cout<<*p++<<endl<<*p--<<endl<<*--p<<endl;
}
int main()
{
    test();
    return 0;
}

