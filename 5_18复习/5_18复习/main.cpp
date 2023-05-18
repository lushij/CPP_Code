#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	//区别注意
	const char* ch[] = { "n","哈" };//只能存储一个字
	char ch[][6] = { "你好","nihao" };//这样才可以存储字符串集合，并且需要能够存储包括’\0‘;
	return 0;
}