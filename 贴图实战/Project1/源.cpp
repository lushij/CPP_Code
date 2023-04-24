#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

int main()
{
    int a[5][5] = {
      1,3,2,5,6,
      5,6,9,2,7,
      6,38,88,39,9,
      1,3,6,9,58,
      1,2,23,6,7
    };
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (a[i][j] == 66 || a[i][j] == 88)
            {
                break;
            }
        }
        if (a[i][j] == 66 || a[i][j] == 88)
        {
            break;
        }
    }
    return 0;
}