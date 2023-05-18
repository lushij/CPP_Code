#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>


int main()
{
	int a[6] = { 1,2,3,4,5,6 };
	int index = 0;//ÔÝ´æÏÂ±ê
	int n = 2;
	for (int i = index; i < 6; i += n)
	{
		a[i] = 0;
	}
	for (int i = index; i < 6; i++)
	{
		if (a[i] != 0)
		{
			index = i;
		}
	}
	for (int i = index; i < 6; i++)
	{
		if (a[i] != 0)
		{
			printf("%d\n", a[i]);
		}
	}
	

	return 0;
}