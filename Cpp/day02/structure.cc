#include <iostream>
#include <string>
#include <stdio.h>
#include<string.h>
using namespace std;
class Point
{
public:
    Point(int id,const char*name)
    :_id(id)//初始化列表
     ,_name(new char[strlen(name)+1])
    {
        strcpy(_name,name);
        cout<<"Point(int,char*)"<<endl;
    }

    void print()
    {
        cout<<"id = "<<_id<<"\t"
            <<"name = "<<_name<<endl;
    }

    ~Point()
    {
        if(_name!=nullptr)
        {
            delete _name;//释放内存
            _name=nullptr;//置为空
            cout<<"~Point()"<<endl;
        }
    }

private:
    int _id;
    char*_name;
};


void test()
{
    Point p(1,"Lu");
    p.print();
}
int main()
{
    test();
    return 0;
}

