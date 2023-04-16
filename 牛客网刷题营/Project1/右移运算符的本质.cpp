#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int a = 2;
	int b = 6;
	int mid = a + b >> 1;//代表把a和b的和除以2
	//1000   8 二进制
	//>>1    0100   4 本质作用
	cout << mid << endl;

	return 0;
}