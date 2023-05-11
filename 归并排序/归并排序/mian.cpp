#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
const int N = 9;


void merge(int*a, int low,int mid, int high)//核心操作
{
	int i, j, k;
	static int b[N];
	for (i = 0; i < N; i++)
	{
		b[i] = a[i];//把a里面当然数据拷贝到b数组里面
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
	{
		if (b[i] <= b[j])
		{
			a[k] = b[i++];
		}
		else
		{
			a[k] = b[j++];
		}
	}

	//检查剩余的表中是否有漏的数据
	//两个循环只会进入一个
	while (i <= mid)
	{
		a[k++] = b[i++];
	}
	while (j <= high)
	{
		a[k++] = b[j++];
	}
}

void mergesort(int*a, int low,int  high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;//划分两个区域
		mergesort(a,low, mid );//把左侧归并排序
		mergesort(a,mid + 1, high);//右侧
		merge(a,low,mid,high);//核心操作
	}
}


void printA(int* a)
{
	for (int i = 0; i < N; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void initA(int* a)
{
	for (int i = 0; i <N ; i++)
	{
		a[i] = rand() % 100;
	}
}



int main()
{
	srand((unsigned int)time(NULL));
	//int a[N] = { 1,999,6,8,66,99 };
	int a[N];
	initA(a);
	int low = 0;
	int high = N - 1;
	
	//cout << mid;
	mergesort(a, low,high);
	printA(a);
	return 0;
}