#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test()
{
    int a=0;
    int b=0;
    int c=0;
    int x=35;
    cout<<"a="<<a<<endl;
    cout<<"(!a)=";
    cout<<(!a)<<endl;
    int y=1;//真的
    cout<<"y="<<y<<"and ~y ="<<~y<<endl;
    if(!a)
    {
        x--;
    }
    else if(b){}
    if(c)
    {
        x=3;
    }
    else
    {
        x=4;
    }
    cout<<x<<endl;
}
int main()
{
    test();
    return 0;
}

