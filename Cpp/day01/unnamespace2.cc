#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

extern int g_num;
extern int _num;
extern int g_num2;
void test()
{
    /* cout<<_num<<endl;//error_type */
    cout<<g_num<<endl;//
    /* cout<<g_num2<<endl;//erro */
}
int main()
{
    test();
    return 0;
}

