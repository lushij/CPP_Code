#include <iostream>
#include <string>
#include <stdio.h>
#include "default.hpp"
using namespace std;
int add(int x,int y=10,int z=0)
{
    return x+y+z;
}
int sub(int x,int y)
{
    return x-y;
}
int main()
{
    cout<<sub(1)<<endl;
    cout<<add(1)<<endl;
}
