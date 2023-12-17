#include <iostream>
#include <string>
#include <stdio.h>
#include<fstream>
using namespace std;

void test()
{
    ifstream ifs("1.txt");
    if(!ifs)
    {
        std::cerr<<"open 1.txt fail"<<endl;
        return;
    }
    char word;
    while(ifs>>word)
    {
        cout<<word<<endl;
    }
    ifs.close();
}
int main()
{
    test();
    return 0;
}

