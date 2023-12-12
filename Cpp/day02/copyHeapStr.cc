#include <iostream>
#include <string>
#include <stdio.h>
#include<string.h>
using namespace std;
class Computer
{
public:
    Computer(int price,const char*name)
        :_price(price)
         ,_name(new char[strlen(name)+1]){}

    
    Computer(const Computer &rhs)
        :_price(rhs._price)
         ,_name(new char[strlen(rhs._name)+1]){
             strcpy(_name,rhs._name);
         }
    
    ~Computer()
    {
        if(_name != nullptr)
        {
            delete _name;
            _name = nullptr;
        }
    }
private:
    int _price;
    char *_name;
};
void test()
{
    Computer xiaomi(7999,"xiaomi book");
    Computer huawei(8999,"huawei mate");
    Computer xiaomi2(xiaomi);
}
int main()
{
    test();
    return 0;
}

