#include <iostream>

using namespace std;

//单例模式
//1.该对象不能是一个栈对象，全局/静态对象
//2.该对象只能是堆对象
//步骤：
//     1.将构造函数私有化
//     

class SingleTon
{
public:
    //只有第一次调用getInstance时，才创建对象
    //之后所有的调用，都直接返回第一次创建的对象
    static SingleTon*getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance=new SingleTon();
        }
        return _pInstance;
    }

    static void destory()
    {
        if(_pInstance)
        {
            //在类内部执行delete表达式
            delete _pInstance;
        }
    }

private:
    SingleTon(){cout<<"SingleTon()"<<endl;}
    ~SingleTon(){cout<<"~SingleTon()"<<endl;}
    static SingleTon * _pInstance;


};

//static 变量要放在类外进行初始化
//且必须加上作用域
SingleTon * SingleTon :: _pInstance=nullptr;

void test()
{
//    SingleTon s;error_code
//    因为new表达式子啊执行过程中一定会调用构造函数
    /* SingleTon *pst1=new SingleTon(); *///error_type
    SingleTon *pst = SingleTon::getInstance();
    SingleTon *pst1=SingleTon::getInstance();
    cout<<"pst:"<<pst<<endl;
    cout<<"pst1:"<<pst1<<endl;
    //这样打来的地址一样的
    //pst:0x5557abc65e70
    //pst1:0x5557abc65e70

    //手动调用析构函数
    SingleTon::destory();

}

int main()
{
    test();
    return 0;
}

