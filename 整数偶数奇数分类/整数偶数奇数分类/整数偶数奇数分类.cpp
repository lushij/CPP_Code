#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>
using namespace std;

int main()
{
    int i = 0;
    int a[10] = { 0 };
    int l = 0;
    int r = 9;
    for (i = 0; i < 10; i++)
    {
        cin >> a[i];
    }
    while (l < r)
    {
        while (l < r && a[r] % 2 == 0)//Å¼Êý
        {
            r--;
        }
        while (l < r && a[l] % 2 != 0)
        {
            l++;
        }
        swap(a[l], a[r]);
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    cout << endl;

    return 0;
}