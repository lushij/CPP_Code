#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//斐波那契数列
class Solution {
public:
    int Fibonacci(int n) 
    {
        int a = 0, b = 1;
        while (n--)
        {
            int c = a + b;
            a = b, b = c;
        }
        return a;
    }
};

//递归思想
int Fibonacci(int n)
{
    if (n == 0) return 0;
    if (n>=1 && n <= 2) return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}
int main()
{
    //方法一
    Solution s;
    cout << s.Fibonacci(5) << endl;
    //方法二
    Fibonacci(5);
    cout << Fibonacci(0) << endl;
	return 0;
}