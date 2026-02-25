#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main()
{
    string s;
    int cnt = 100;
    while (cin >> s && cnt > 0)
    {
        --cnt;
        int sz = s.size();
        string str;
        int flag = 1;
        long long num;
        for (int i = 0; i < sz; ++i)
        {
            if (s[i] != '.') str += s[i];
            if (s[i] == '.')
            {
                num = stoll(str);
                // cout<<num<<endl;
                str = "";
                if (num > 255 || num < 0)
                {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 1)
        {
            num = stoll(str);
            // cout<<num<<endl;
            str = "";
            if (num > 255 || num < 0)
            {
                flag = 0;
            }
        }
        if (flag == 1)
            cout << "Yes!" << endl;
        else
            cout << "No!" << endl;
    }
    return 0;
}