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

//���Ĳ���  f���׽ڵ�
void heapify(int arr[], int f, int len)
{
	while (f < len)
	{
		/*
		����ڵ��ֵ�븸�׽ڵ��ֵ�Ƚϣ�Ȼ�����ݴ�ֵ��Ľڵ㣬�����ҽڵ��ֵ�Ƚϣ���󣬿��Ƿ���Ҫ����ֵ		
		*/
		int liftChild = 2 * f + 1;//��ڵ�
		int rightChild = 2 * f + 2;//�ҽڵ�
		int MaxIdx = f;//�ݴ���������ֵ�Ľڵ�
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
			//��ʾ���ڵ�����ֵ�ڵ�һ��������Ҫ����
			break;
		}
		//�����׽ڵ��ֵmax�ڵ��ֵ���ͽ���
		swap(arr[f], arr[MaxIdx]);
		f = MaxIdx;
	}
}


void buildMax(int arr[], int len)
{
	//�ҵ���һ����Ҷ�ӽڵ㼴���һ�����׽ڵ㣬�Ӻ���ǰ�����󶥶�
	int i = len / 2 - 1;
	for (i; i >= 0; i--)
	{
		heapify(arr, i, len);
	}
}


void heapSort(int arr[], int len)
{
	//1.���ȹ���󶥶�
	buildMax(arr, len);
	while (len > 1)
	{
		//�ѶѶ�Ԫ�غ�����Ԫ��der���һ��Ԫ�ؽ���
		swap(arr[0],arr[len-1]);
		//�������ĳ��ȼ�һ
		len--;
		// �����������µ����ɴ󶥶�
		heapify(arr, 0, len);
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
	int arr[10] = { 1,2,999,4,5,6,7,89,50,10};
	heapSort(arr, 10);
	printArray(arr, 10);
	return 0;
}