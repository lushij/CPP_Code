#include <iostream>
#include <string>

using namespace std;

namespace Student 
{
int _id;
string _name;
void setId(int id)
{
   _id=id;
}
void setName(string name)
{
    _name=name;
}
int getId()
{
    return _id;
}
string getName()
{
    return _name;
}
}
void test()
{
    Student::setId(1);
    int res= Student::getId();
    cout<<res<<endl;
     
}
int main()
{
    test();
    return 0;
}

