#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
class Base
{
public:
    Base(long base)
        :_base(base)
    {}
    /* virtual */
        void print()
        {

        }
    ~Base()
    {}
private:
    long _base;
};
class Drived
:virtual public Base//虚继承
{
public:
    Drived(long base,long drived)
        :Base(base)
        ,_drived(drived)
    {}
    virtual//虚函数
        void print()
        {

        }
    ~Drived()
    {}
private:
    long _drived;
};
void test()
{
    cout<<"sizeof(Base) = "<<sizeof(Base)<<endl;
    cout<<"sizeof(Drived) = "<<sizeof(Drived)<<endl;
}
int main()
{
    test();
    return 0;
}

