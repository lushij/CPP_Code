#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
int _id=19;
namespace Lu
{
int _id=1;
int _age=18;
void printInfo()
{
    cout<<_id<<endl
        <<_age<<endl;
}
}//end of Lu



void test()
{
    Lu::printInfo();
    /* cout<<"Lu::_id = "<<Lu::_id<<endl; */
}
int main()
{
    test();
    return 0;
}

