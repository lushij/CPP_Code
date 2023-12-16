#include <iostream>
#include <string>
#include <stdio.h>
#include<unordered_map>
using namespace std;

void test()
{
    unordered_map<string,int>word;
    word.insert(make_pair("a",1));//用make_pair插入键值对
    for(auto &x:word)
    {
        cout<<x.first<<x.second<<endl;
    }
}
int main()
{
    test();
    return 0;
}

