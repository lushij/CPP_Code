#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
class Point
{
public:
    Point(int _x,int _y)
        :_x(_x)
         ,_y(_y){}
    void setX(int x)
    {
        this->_x=x;
        cout<<"this->_x is "<<this->_x<<endl;
    }

private:
    int _x;
    int _y;
};
void test()
{
    Point p(1,2);
    p.setX(3);

}
int main()
{
    test();
    return 0;
}

