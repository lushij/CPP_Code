#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main1()
{
    int hour=0, monten=0;
    int count = 0;
    scanf("%d", &count);
    if (count >= 60)
    {
        hour=count/60;
        monten = count % 60;
    }
    printf("%d���ӵ���%dСʱ%d����\n", count, hour, monten);
    return 0;
}