#include <iostream>
#include <string>
#include <stdio.h>
#define MAX 10
const int N=10;
using namespace std;

void test()
{
    cout<<N<<endl;
    cout<<MAX<<endl;
    cout<<sizeof(N)<<endl
        <<sizeof(MAX)<<endl;
}
int main()
{
    test();
    return 0;
}

