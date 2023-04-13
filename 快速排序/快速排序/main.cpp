#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>
using namespace std;

int Tmp(int*arr, int left,int  right)
{
	int tmp = arr[left];//���ݶ��߽������ߵ�ֵ
	while (left < right)
	{
		//�Ȱ��ұ߲����ϵ��Ƶ����
		while (left < right && arr[right] >= tmp)
		{
			--right;
		}
		arr[left] = arr[right];//���ұߵ�С�ڱ߽�ֵ����ȫ���Ƶ���߲���
		//�ٰ���߲����ϵ��Ƶ��ұ�
		while (left < right && arr[left] <= tmp)
		{
			++left;
		}
		arr[right] = arr[left];//����ߴ��ڱ߽�ֵ����ȫ���Ƶ��ұ�
	}
	arr[left] = tmp;
	return left;

}

void quick_sort(int *arr,int left,int right)
{
	//���õݹ�˼��
	if (left < right)
	{
		int tmp = Tmp(arr,left,right);//�ָ�ֵȷ������Ϊ�ؼ�
		quick_sort(arr, left, tmp-1);//�����������߽�Ĳ���
		quick_sort(arr, tmp+1, right);//������߽����ұߵĲ���
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