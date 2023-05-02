#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*
1.���ȹ���󶥶ѣ��ҵ���һ����Ҷ�ӽڵ㼴���һ�����׽ڵ㣬�Ӻ���ǰ�����󶥶�
2.�ѶѶ�Ԫ�غ�����Ԫ��der���һ��Ԫ�ؽ������������ĳ��ȼ�һ
3.�����������µ���Ϊ�󶥶�
4.�ظ�2,3�Ĳ���ֱ����������ĳ���Ϊ1
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
		//�����׽ڵ��ֵmax�ڵ��ֵ���ͽ���
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
		//���鳤�����±�Ĺ�ϵע������
		swap(a[len-1], a[0]);
		len--;
		// �����������µ����ɴ󶥶�
		heapify(a, 0, len);
	}
}
//��������
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