#include <iostream>
#include <string>
#include <stdio.h>
#include<string.h>
using namespace std;

void test()
{
    //new 申请数组类型
    int *arr = new int[10];
    /* int *arr1 = new int[10](1); *///erro 不能这样申请数组还赋值 是错误的
    /* delete arr;//虽然不报错，但是不建议 */
    delete []arr;//正确用法
}
/**************************************************/
struct Stu_s{
    int _age;
    char _name[256];
    Stu_s()
        :_age(0)
    {
        bzero(_name,sizeof(_name));
    }
    Stu_s(int age,const char*name)
        :_age(age)
    {
        bzero(_name,sizeof(_name));
        strcpy(_name,name);
        cout<<"Stu_s(int,char*)"<<endl;
    }
};

void test1()
{
    //new 申请结构体类型
    Stu_s *stu=new Stu_s; //调用的是默认构造函数
    cout<<stu->_age<<endl
        <<stu->_name<<endl;
    delete stu;

    //申请结构体数组
    Stu_s * StuArr=new Stu_s[10];
    delete []StuArr;
    
    //调用有参构造
    Stu_s * stu1 = new Stu_s(10,"lu");
    cout<<stu->_age<<endl
        <<stu->_name<<endl;
    delete stu1;
}
int main()
{
    /* test(); */
    test1();
    return 0;
}

