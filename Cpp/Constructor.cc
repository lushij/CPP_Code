#include <iostream>
#include<string.h>
using namespace std;

class Constructor
{
public :
    //有时候默认拷贝构造函数可能不能完成我们的参数()
    //自己实现构造函数
    //                因为c++语法严格，传入的参数是字符串常量，所以需要const
    Constructor(int id,const char*name)
        :_id(id)
         ,_name(new char[strlen(name)+1]())
    {
        stpcpy(_name,name);
        cout<<"Constructor(int,char*)"<<endl;
    }

    //拷贝构造固定格式： 类名（const 类名&名字）
    //就需要自己写一个拷贝构造函数
    Constructor(const Constructor &rhs)
        :_id(rhs._id)
         ,_name(new char[strlen(rhs._name)+1]())
    { 
        strcpy(_name,rhs._name);
        cout<<"拷贝构造"<<endl;
    }

    void print()
    {
        cout<<"id:"<<_id<<"name:"<<_name<<endl;
    }

    ~Constructor()
    {
        cout<<"~Constructor()"<<endl;
        if(_name)
        {
            delete []_name;
            _name=nullptr;
        }
    }
private:
    int _id;
    char* _name;
};

void test()
{
    //调用构造函数
    Constructor s1(1,"Rock");
    s1.print();
    cout<<endl;
    //调用拷贝构造
    Constructor s2(s1);
    s2.print();
}

int main()
{
    test();
    return 0;
}

