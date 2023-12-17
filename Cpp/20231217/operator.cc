#include <iostream>
#include <string>
#include<string.h>
#include <stdio.h>
//运算符重载
//先来回顾一下赋值运算符重载
using namespace std;
class Student
{
public:
    //new表达式申请数组空间不加括号不会进行初始化
    Student(int id,const char*name)
        :_id(id)
         ,_name(new char[strlen(name)+1]())
    {
        strcpy(_name,name);
    }
    
    //赋值运算符：类名 &operator=(cosnt 类名&);
    Student & operator=(const Student &rhs)
    {
        //判断是否是自复制
        if(this != &rhs)//判断地址
        {
            //进到这里表示不是自复制
            //先清除原空间
            delete[] _name;
            //进行深拷贝
            _name=new char[strlen(rhs._name)+1]();
            strcpy(_name,rhs._name);
            this->_id=rhs._id;
        }
        return *this;//返回*this
    }
    void print()
    {
        cout<<_id<<"\t"<<_name<<endl;
    }
    ~Student()
    {
        if(_name)
        {
            delete[] _name;
            _name = nullptr;
        }
    }
private:
    int _id;
    char*_name;
};
void test()
{
    Student s1(1,"l1");
    Student s2(2,"l2");
    cout<<"赋值前"<<endl;
    s1.print();
    s2.print();
    s1=s2;
    cout<<"赋值后"<<endl;
    s1.print();
    s2.print();
}
int main()
{
    test();
    return 0;
}

