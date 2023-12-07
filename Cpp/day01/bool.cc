#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void test()
{
    bool res=true;
    cout<<"bool true is "<<res<<endl
        <<"bool size is "<<sizeof(res)<<endl;
}
int main()
{
    test();
    return 0;
}

