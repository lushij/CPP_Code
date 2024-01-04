#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
class String
{
public:
    String()
        :_pstr(nullptr)
    {}

    
    ~String()
    {
        if(_pstr)
        {
            delete []_pstr;
            _pstr=nullptr;
        }
    }

private:
    char*_pstr;
};
void test()
{

}
int main()
{
    test();
    return 0;
}

