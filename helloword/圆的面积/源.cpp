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
    printf("%d分钟等于%d小时%d分钟\n", count, hour, monten);
    return 0;
}