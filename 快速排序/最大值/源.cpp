#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int max = (a > b ? a : b) > c ? (a > b ? a : b) : c;
    cout << max << " eh o maior" << endl;
    return 0;
}