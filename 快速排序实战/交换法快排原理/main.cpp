#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;


/*
*
*
*
*
* 交换法原理
* 此方法效率不高理解即可
*
*
*
*
*
*/

void intiNum(int* a)
{
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 100;
	}
}



void quick_sort(int a[], int low, int high)
{
	if (low < high)
	{
		int index = a[low];
		/*int i = low - 1;
		int j = high + 1;*/
		/*while (i < j)
		{
			do
			{
				i++;
			} while (a[i] < index);
			do
			{
				j--;
			} while (a[j] > index);
			if (i < j)
			{
				swap(a[i], a[j]);
			}
		}*/
		int i = low ;
		int j = high;
		while (i < j)
		{
			while (a[i] < index)
			{
				++i;
			}
			while (a[j] > index)
			{
				--j;
			}
			if (i < j)
			{
				swap(a[i], a[j]);
			}
		}
		/*quick_sort(a, low , j);
		quick_sort(a,j+ 1,high);*/
		/***************两种方法都可以**********************/
		quick_sort(a, low , i);
		quick_sort(a,i+ 1,high);
	}
}

void printA(int* a)
{
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));
	//int a[10] = { 1,3,2,4,6,0,8,7,5,66 };//入门好练思维
	int a[10];
	intiNum(a);
	int low = 0;
	int high = 9;
	quick_sort(a, low, high);
	printA(a);
	return 0;
}