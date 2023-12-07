#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#if 0
//错误示例
int & getId()
{
    int num=1;//
    return &num;
}
#endif

int & getIdx(int & val)
{
    val=10;
    cout<<"&val is"<<&val<<endl;
    return val;
}

void test()
{
    int num;
    cout<<"&num is"<<&num<<endl;
    int &idx=getIdx(num);
    cout<<idx<<endl;
    cout<<"&idx is"<<&idx<<endl;
}


int & heapVal()
{
    int *p=new int(1);
    return *p;
}

void testHeapVal()
{
    int &x=heapVal();
    cout<<x<<endl;
    delete &x;//若是返回的是堆空间的引用，切记手动回收空间，以免造成内存泄漏
}
int main()
{
    /* test(); */
    testHeapVal();
    return 0;
}

