#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;


int j = 0;
int b[5] = { 0 };
int prv(int a[], int l, int r)
{
    int idx = a[l];
    b[j++] = idx;
    while (l < r)
    {
        while (l < r && a[r] >= idx)
        {
            --r;
        }
        a[l] = a[r];
        while (l < r && a[l] <= idx)
        {
            ++l;
        }
        a[r] = a[l];
    }
    a[l] = idx;
    return l;
}

void quick_sort(int a[], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int idx = prv(a, l, r);
    quick_sort(a, l, idx - 1);
    quick_sort(a, idx + 1, r);

}
int main()
{
    int i = 0;
    int N = 0;
    int a[100] = { 0 };
    cin >> N;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    a[i] = 0;
    int left = 0;
    int right = N-1;
    quick_sort(a, left, right);
    for (int i = 0; i <= right; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < j; i++)
    {
        cout << b[i] << " ";
    }
    return 0;
}