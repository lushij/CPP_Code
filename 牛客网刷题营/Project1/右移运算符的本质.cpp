#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int a = 2;
	int b = 6;
	int mid = a + b >> 1;//�����a��b�ĺͳ���2
	//1000   8 ������
	//>>1    0100   4 ��������
	cout << mid << endl;

	return 0;
}