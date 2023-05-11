#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
const int N = 9;


void merge(int*a, int low,int mid, int high)//���Ĳ���
{
	int i, j, k;
	static int b[N];
	for (i = 0; i < N; i++)
	{
		b[i] = a[i];//��a���浱Ȼ���ݿ�����b��������
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

	//���ʣ��ı����Ƿ���©������
	//����ѭ��ֻ�����һ��
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
		int mid = (low + high) / 2;//������������
		mergesort(a,low, mid );//�����鲢����
		mergesort(a,mid + 1, high);//�Ҳ�
		merge(a,low,mid,high);//���Ĳ���
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