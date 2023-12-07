#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
int g_num=2;//全局变量可以跨模块使用
static int g_num2=10;//静态变量只能在本模块使用
namespace 
{
int _num=10;//匿名空间实体只能在本模块使用
void print()
{
    cout<<_num<<endl;
}
}//end of namespace


