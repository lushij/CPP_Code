#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

//效率高
void test01()
{
    string s;
    getline(cin, s);
    for (char& c : s)//c++中的 效率高
    {
        if (c >= 'a' && c <= 'z')
        {
            c = (c + 1 - 'a') % 26 + 'a';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c = (c + 1 - 'A') % 26 + 'A';
        }
    }
    cout << s << " ";
}
void test02()
{
        string s;
        getline(cin, s);
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                s[i] = (s[i] + 1 - 'a') % 26 + 'a';
            }
            else if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[i] = (s[i] + 1 - 'A') % 26 + 'A';
            }
        }
        cout << s << " ";
     
}

void test03()
{
    string s;
    getline(cin, s);
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = (s[i] + 1 - 'a') % 26 + 'a';
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = (s[i] + 1 - 'A') % 26 + 'A';
        }
    }
    cout << s << " ";
}
int main()
{
    return 0;
}