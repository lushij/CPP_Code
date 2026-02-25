#define _CRT_SECURE_NO_WARNINGS 1
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
using namespace std;

int main() {
    map<char, int>priorty = {
        {'\0', 0},
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };

    string str;
    while (cin >> str)
    {
        stack<char>ops;
        stack<double>nums;
        string numstr = "";
        for (auto& c : str)
        {
            if (c >= '0' && c <= '9')
            {
                numstr += c;
            }
            else
            {
                nums.push(stod(numstr));
                numstr = "";
                while(!ops.empty()  && priorty[c] <= priorty[ops.top()])
                {
                    // 表明这是要进行操作数操作了
                    double r = nums.top();
                    nums.pop();
                    double l = nums.top();
                    nums.pop();
                    // 检测对应操作
                    if (ops.top() == '+')
                    {
                        nums.push(l + r);
                    }
                    if (ops.top() == '-')
                    {
                        nums.push(l - r);
                    }
                    if (ops.top() == '*')
                    {
                        nums.push(l * r);
                    }
                    if (ops.top() == '/')
                    {
                        nums.push(l / r);
                    }
                    ops.pop();
                }
                ops.push(c);
            }
           
        }
        if (!numstr.empty())
        {
            nums.push(stod(numstr));
        }
        while (!ops.empty())
        {
            // 表明这是要进行操作数操作了
            double r = nums.top();
            nums.pop();
            double l = nums.top();
            nums.pop();
            // 检测对应操作
            if (ops.top() == '+')
            {
                nums.push(l + r);
            }
            if (ops.top() == '-')
            {
                nums.push(l - r);
            }
            if (ops.top() == '*')
            {
                nums.push(l * r);
            }
            if (ops.top() == '/')
            {
                nums.push(l / r);
            }
            ops.pop();
        }
        cout << nums.top() << endl;

    }

    return 0;
}
