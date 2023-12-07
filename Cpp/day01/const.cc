#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

void test()
{
    const int num=10;
    /* const int n; *///必须赋值且不能改变
    /* num=11;//ero */
}
void test1()
{
    int num=10;
    int cnt=1;
    const int *p=&num;
    /* *p=20;//const 在*左边称为常量指针：就是不能修改指针所指向空间的值 */
    p=&cnt;// erro                     但是可以改变指针指向的空间
}
void test2()
{
    int num=10;
    int cnt=1;
    int * const p=&num;//const在*右边称为指针常量：就是不能修改指针所指向的空间
    /* p=&cnt;//erro                                  但是可以修改指针指向空间的值 */
    *p=20;
}
void test3()
{
    int num=10;
    int cnt=1;
    const int * const p=&num;//const即在*左边又在*右边称为双层const：哪一个个也不能修改
    /* p=&cnt;//er */
    /* *p=20;//er */
}
int main()
{
    test();
    test1();
    test2();
    return 0;
}

