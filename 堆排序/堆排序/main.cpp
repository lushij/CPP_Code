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

//核心操作  f父亲节点
void heapify(int arr[], int f, int len)
{
	while (f < len)
	{
		/*
		先左节点的值与父亲节点的值比较，然后先暂存值大的节点，再与右节点的值比较，最后，看是否需要交换值		
		*/
		int liftChild = 2 * f + 1;//左节点
		int rightChild = 2 * f + 2;//右节点
		int MaxIdx = f;//暂存相较于最大值的节点
		if (liftChild<len && arr[liftChild]>arr[MaxIdx])
		{
			MaxIdx = liftChild;
		}
		if (rightChild<len && arr[rightChild]>arr[MaxIdx])
		{
			MaxIdx = rightChild;
		}
		if (MaxIdx == f)
		{
			//表示父节点和最大值节点一样，不需要交换
			break;
		}
		//若父亲节点的值max节点的值，就交换
		swap(arr[f], arr[MaxIdx]);
		f = MaxIdx;
	}
}


void buildMax(int arr[], int len)
{
	//找到第一个非叶子节点即最后一个父亲节点，从后往前构建大顶堆
	int i = len / 2 - 1;
	for (i; i >= 0; i--)
	{
		heapify(arr, i, len);
	}
}


void heapSort(int arr[], int len)
{
	//1.首先构造大顶堆
	buildMax(arr, len);
	while (len > 1)
	{
		//把堆顶元素和无序元素der最后一个元素交换
		swap(arr[0],arr[len-1]);
		//无序区的长度减一
		len--;
		// 把无序区重新调整成大顶堆
		heapify(arr, 0, len);
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
	int arr[10] = { 1,2,999,4,5,6,7,89,50,10};
	heapSort(arr, 10);
	printArray(arr, 10);
	return 0;
}