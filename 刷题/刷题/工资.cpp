#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main2()
{
    int a, b;
    float c;
    cin >> a >> b >> c;
    cout << "NUMBER = " << a << endl;
    printf("SALARY = U$ %.2f\n", b * c);
    return 0;
}