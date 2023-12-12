#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Stu
{
    //行业代码风格：public在上，private在下
public:
    void print()
    {
        cout<<"age = "<<_age<<endl
            <<"id = "<<_id<<endl;
    }
    void ptint1()
    {
        cout<<"age = "<<_age<<endl;
    }
private:
    int _age;
    int _id;

};
void test()
{
    Stu s;
    s.print();
}
int main()
{
    test();
    return 0;
}

