#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
//单例模式框架介绍
//步骤：
//1.构造函数私有化
//2.定义一个静态的指向本类型的指针
//3.在public区域定义一个静态成员的函数
class Single
{
public:
    static Single*getPst()
    {
        if(_pst == nullptr)
        {
            _pst=new Single();
        }
        return _pst;
    }
    static void destroy()
    {
        if(_pst != nullptr)
        {
            delete _pst;
            _pst=nullptr;
        }
    }
private:
   static  Single *_pst;//静态成员变量必须放在类外初始化
   Single(){cout<<"Single()"<<endl;}
   ~Single(){cout<<"~Single()"<<endl;}
};
Single*Single::_pst=nullptr;
void test()
{
    //Single s;//err
    //必须手动调用
    Single*pst=Single::getPst();
    Single*pst1=Single::getPst();
    //这个是指向对象的地址(我们平时关注的是指针执向对象的地址)
    cout<<"Address of object pointed by pst:"<<endl;
    cout<<pst<<endl;
    cout<<pst1<<endl;
    //这个是指向指针本身在内存的地址
    cout<<"Address of pst pointer:"<<endl;
    cout<<&pst<<endl;
    cout<<&pst1<<endl;
    //而且手动调用析构函数
    Single::destroy();
    
}
int main()
{
    test();
    return 0;
}

