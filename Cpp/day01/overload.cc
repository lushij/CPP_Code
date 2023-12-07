#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int add(int x,int y)
{
    return x+y;
}

double add(double x,double y)
{
    return x+y;
}
int add(double x,int y)
{
    return x+y;
}
double add(int x,double y)
{
    return x+y;
}
int add(int x,int y,int z)
{
    return x+y+z;
}


void test()
{
    int a=10;
    int b=10;
    int c=10;
    double x=10.1;
    double y=12.1;
    int res;
    double ret;
    res = add(a,b);
    cout<<"add(int,int)"<<res<<endl;

}
int main()
{
    test();
    return 0;
}

