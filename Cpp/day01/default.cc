#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int add(int x,int y=0,int z=0)
{
    return x+y+z;
}
//err
/* int sub(int x=0,int y,int z)//erro 默认参数从右边往左边生效 */
/* { */
/* } */
void test()
{
    cout<<"add(int):"<<add(1)<<endl
        <<"add(int ,int):"<<add(1,2)<<endl
        <<"add(int,int,int):"<<add(1,2,3)<<endl;
}
int main()
{
    test();
    return 0;
}

