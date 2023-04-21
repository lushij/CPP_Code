#define _CRT_SECURE_NO_WARNINGS 1
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string name[5]={"’‘","¿÷¿÷"};
	for (auto x : name)
	{
		cout << x<<endl;
	}
	cout << endl;
	return 0;
}