#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
int g_num=10;//全局变量i
static int s_num=1;//静态变量
const int N=1;//文字常量区

//test()本身就在代码区
void test()
{
    const  int cnt=0;//栈区
    int arr[10]={0};//数组也在栈上
    int *p=new int (1);//堆区
    static int st=0;//静态变量区/全局变量区
    const char*pstr="hello";//字符串在位于文字常量区
    //pstr位于栈区
    printf("&pstr位于栈区 %p\n",&pstr);//栈区
    cout<<"堆区"<<p<<endl
        <<"全局变量区"<<&g_num<<endl
        <<"静态变量区"<<&s_num<<endl
        <<"文字常量区"<<&N<<endl
        <<"全局变量区"<<&st<<endl;
        delete  p;
    printf("pstr %p\n",pstr);//文字常量区
    printf("&test() %p\n",&test);//代码区
}
int main()
{
    test();
    return 0;
}

