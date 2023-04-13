#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


int lcm(int a, int b)
{
    int tmp = 0;
    tmp = a > b ? a : b;
    for (tmp;; tmp++)
    {
        if (tmp % a == 0 && tmp % b == 0)
        {
            return tmp;
        }
    }
}
int main1()
{
    int a = 0, b = 0;
    int min_num = 0;
    cin >> a >> b;
    min_num = lcm(a, b);
    cout << min_num << endl;
    return 0;
}