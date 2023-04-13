#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>
using namespace std;

int Tmp(int*arr, int left,int  right)
{
	int tmp = arr[left];//先暂定边界就是左边的值
	while (left < right)
	{
		//先把右边不符合的移到左边
		while (left < right && arr[right] >= tmp)
		{
			--right;
		}
		arr[left] = arr[right];//把右边的小于边界值的数全都移到左边部分
		//再把左边不符合的移到右边
		while (left < right && arr[left] <= tmp)
		{
			++left;
		}
		arr[right] = arr[left];//把左边大于边界值的数全都移到右边
	}
	arr[left] = tmp;
	return left;

}

void quick_sort(int *arr,int left,int right)
{
	//采用递归思想
	if (left < right)
	{
		int tmp = Tmp(arr,left,right);//分隔值确定，最为关键
		quick_sort(arr, left, tmp-1);//先排序左边与边界的部分
		quick_sort(arr, tmp+1, right);//再排序边界与右边的部分
	}
}

int main()
{
	int arr[10] = { 64,94,95,79,69,84,18,22,12,78 };
	int left = 0;
	int right = (int)(sizeof(arr) / sizeof(arr[0]) - 1);
	quick_sort(arr,left,right);
	for (int i = 0; i <= right; i++)
	{
		cout << arr[i] << " ";
	}
	return 0;
}