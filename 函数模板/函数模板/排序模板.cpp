#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//排序函数模板
//类型打印数组数据
template<class T>
void mySort(T a[], int len)
{

	for (int i = 0; i <len ; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//类型打印数组数据
template<class T>
void print(T a,int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}



int main()
{/*
	int a[5] = { 0,2,1,3,45 };
	double b[5] = { 0.1,2.3,2.5,5.6,20.6 };
	mySort(a,5);
	mySort(b,5);
	print(a,5);
	print(b,5);*/

	char ch[] = "hello world";
	int chlen = strlen(ch);
	int len = sizeof(ch) / sizeof(ch[0]);
	mySort(ch, len);
	print(ch, len);
	return 0;
}