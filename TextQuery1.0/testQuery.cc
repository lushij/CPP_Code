#include "TextQuery.h"
#include<signal.h>

void func(int sig)
{
    exit(0);
}

void test()
{
    TextQuery test;
    string filename="china_daily.txt";
    test.readFile(filename);
    string word;
    cout<<"please cin your word # ";
    while(cin>>word)
    {
        test.query(word);
        cout<<endl;
        cout<<"please cin your word # ";
    }
}
int main()
{
    signal(2,func);
    test();
    return 0;
}

