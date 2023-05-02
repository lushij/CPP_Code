#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*
1.首先构造大顶堆，找到第一个非叶子节点即最后一个父亲节点，从后往前构建大顶堆
2.把堆顶元素和无序元素der最后一个元素交换，无序区的长度减一
3.把无序区重新调整为大顶堆
4.重复2,3的操作直到无需区域的长度为1
*/
void heapify(int*a, int f, int len)
{
	
	while (f<len)
	{
		int maxIdx = f;
		int leftChild = 2 * f + 1;
		int rightChild = 2 * f + 2;
		if (leftChild<len && a[leftChild]>a[maxIdx])
		{
			maxIdx = leftChild;
		}
		if (rightChild<len && a[rightChild]>a[maxIdx])
		{
			maxIdx = rightChild;
		}
		
		if (maxIdx == f)
		{
			break;
		}
		//若父亲节点的值max节点的值，就交换
		swap(a[f], a[maxIdx]);
		f = maxIdx;

	}
}

void bulidMax(int *a,int  len)
{
	int i = len / 2 - 1;
	for (i; i >= 0; i--)
	{
		heapify(a, i, len);
	}
}
void heapSort(int *a, int len)
{
	bulidMax(a, len);
	while (len > 1)
	{
		//数组长度与下标的关系注意别搞乱
		swap(a[len-1], a[0]);
		len--;
		// 把无序区重新调整成大顶堆
		heapify(a, 0, len);
	}
}
//遍历数组
void printArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main()
{
	int a[] = { 1,2,3,4,6,5,7,9,8566,10 };
	int sz = sizeof(a) / sizeof(a[0]);
	heapSort(a, sz);
	printArray(a, sz);
	return 0;
}