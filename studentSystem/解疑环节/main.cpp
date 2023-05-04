#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	char name[20] = { 0 };
	scanf("%s", name);
	//scanf_s("%s", name,20);
	printf("%s\n", name);

	return 0;
}