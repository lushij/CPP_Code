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
    int k = 0;
    for (i = 0; i < 10; i++)
    {
        cin >> a[i];
    }
    while (l < r)
    {
        while (l < r && a[r] % 2 == 0)//ż��
        {
            r--;
        }
        while (l < r && a[l] % 2 != 0)//����
        {
            l++;
        }
        swap(a[l], a[r]);//����
    }
    while (a[k] % 2 != 0)
    {
        k++;//���м������ֽ��
    }
    int count = k;
    for (i = 0; i < k; i++)
    {
        for (int j = 0; j < k - i - 1; j++)
        {
            if (a[j] < a[j+1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
   
    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    cout << endl;

    return 0;
}