#include <iostream>
#include <string>
#include <stdio.h>
//内联函数发生在编译阶段，更加安全
//为了降低犯错误的效率，尽量使用内联函数代替宏函数
//在inline函数没有函数调用的开销，且在效率上与宏函数保持一致
using namespace std;

inline
int divide(int x,int y)
{  return x/y ;   }

void test()
{
    int ret = divide(2,1);
    cout<<ret<<endl;
}
int main()
{
    test();
    return 0;
}

