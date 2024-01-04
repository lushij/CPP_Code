#include <iostream>
#include <string>
#include <stdio.h>
#include<fstream>
#include<sstream>
using namespace std;

void test()
{
    ifstream ifs("data.txt");
    string word;
    while(ifs>>word)
    {
        cout<<word<<endl;
        word.clear();
    }
    ifs.close();
}
int main()
{
    test();
    return 0;
}

