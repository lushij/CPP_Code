#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test()
{
    //注释牵扯到类和对象的知识，先了解
    string s("hello");//构造函数
    string s1="word";
    string s2=s+s1;
    string s3(s2);//拷贝构造
    cout<<"s is "<<s<<endl
        <<"s1 is "<<s1<<endl
        <<"s2 is "<<s2<<endl
        <<"s3 is "<<s3<<endl;
}
int main()
{
    test();
    return 0;
}

