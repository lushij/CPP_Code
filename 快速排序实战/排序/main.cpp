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
* 挖坑法原理
* 
* 
* 
* 
* 
*/

void intiNum(int*a)
{
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 100;
	}
}


//以左边为基准值
//int Partition(int*a, int low, int high)
//{
//	//相反规则，以左边为基准值，先看右边不符合的，相反反之
//	int pivot = a[low];
//	while (low < high)
//	{
//		while (low < high && a[high] >= pivot)
//		{
//			--high;//符合就--，不符合就跳出，交换
//		}
//		a[low] = a[high];
//		while (low < high && a[low] <= pivot)
//		{
//			++low;
//		}
//		a[high] = a[low];
//	}
//	a[low] = pivot;//以那边为基准值，跳出大循环就覆盖那边的
//	return low;
//
//}

//以右边为基准值
int Partition(int* a, int low, int high)
{
	//相反规则，以右边为基准值，先看左边边不符合的，相反反之
	int pivot = a[high];/***************************************************/
	while (low < high)
	{
		while (low < high && a[low] <= pivot)
		{
			++low;
		}
		a[high] = a[low];
		while (low < high && a[high] >= pivot)
		{
			--high;//符合就--，不符合就跳出，交换
		}
		a[low] = a[high];
	}
	a[high] = pivot;//以那边为基准值，跳出大循环就覆盖那边的  /******************/
	/*cout << "基准值的下标为：" << high << endl;*/
	return high;

}


void quickSort(int*a, int low,int  high)
{
	if (low < high)
	{
		//划分边界操作，存储变化的基准值的下标
		int pivotpos = Partition(a, low, high);//核心操作的
		quickSort(a, low, pivotpos-1);//前半部分即小于基准值的部分
		quickSort(a,  pivotpos+1,high);//后半部分即大于基准值的部分

	}
}

void printA(int*a)
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
	quickSort(a, low, high);
	printA(a);
	return 0;
}