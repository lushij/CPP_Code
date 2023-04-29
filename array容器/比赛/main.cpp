#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

//原理解析
void test()
{
    char n,c;
    cin >> n;
    c = (n - 'a' + 1) % 26 + 'a';
    printf("%c\n", (n - 'a' + 1) % 26 + 'a');
    cout << c ;//根据简单输出数据，若有精度或格式用C语言的输出函数即可
}

void test1()
{
    int n = 0;
    string m;
    cin >> n;
    getchar();
    getline(cin, m);
    for (char& c : m)
    {
        //我们将其转化为相对于字母表顺序中的位置（即减去 'a'），加上移动位数 n，然后再对 26 取余数，最后再加上 'a' 来得到新的字符；
        c = (c - 'a' + n) % 26 + 'a';//根据当前字母减去a得出对应的
        cout << c;
    }
    cout << endl;
}


void test2()
{

    int n = 0;
    cin >> n;
    int num[10000];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    num[i] = 0;
    for (i = 0; i < n; i++)
    {
        int a = 2 * num[i] - 1;
        cout << ((num[i] * (1 + a)) / 2) % 10000 << endl;
    }
}
//题目
int main()
{
    //test();
    //test1();
    test2();
    return 0;
}

