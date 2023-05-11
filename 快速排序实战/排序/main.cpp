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
* �ڿӷ�ԭ��
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


//�����Ϊ��׼ֵ
//int Partition(int*a, int low, int high)
//{
//	//�෴���������Ϊ��׼ֵ���ȿ��ұ߲����ϵģ��෴��֮
//	int pivot = a[low];
//	while (low < high)
//	{
//		while (low < high && a[high] >= pivot)
//		{
//			--high;//���Ͼ�--�������Ͼ�����������
//		}
//		a[low] = a[high];
//		while (low < high && a[low] <= pivot)
//		{
//			++low;
//		}
//		a[high] = a[low];
//	}
//	a[low] = pivot;//���Ǳ�Ϊ��׼ֵ��������ѭ���͸����Ǳߵ�
//	return low;
//
//}

//���ұ�Ϊ��׼ֵ
int Partition(int* a, int low, int high)
{
	//�෴�������ұ�Ϊ��׼ֵ���ȿ���߲߱����ϵģ��෴��֮
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
			--high;//���Ͼ�--�������Ͼ�����������
		}
		a[low] = a[high];
	}
	a[high] = pivot;//���Ǳ�Ϊ��׼ֵ��������ѭ���͸����Ǳߵ�  /******************/
	/*cout << "��׼ֵ���±�Ϊ��" << high << endl;*/
	return high;

}


void quickSort(int*a, int low,int  high)
{
	if (low < high)
	{
		//���ֱ߽�������洢�仯�Ļ�׼ֵ���±�
		int pivotpos = Partition(a, low, high);//���Ĳ�����
		quickSort(a, low, pivotpos-1);//ǰ�벿�ּ�С�ڻ�׼ֵ�Ĳ���
		quickSort(a,  pivotpos+1,high);//��벿�ּ����ڻ�׼ֵ�Ĳ���

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
	//int a[10] = { 1,3,2,4,6,0,8,7,5,66 };//���ź���˼ά
	int a[10];
	intiNum(a);
	int low = 0;
	int high = 9;
	quickSort(a, low, high);
	printA(a);
	return 0;
}