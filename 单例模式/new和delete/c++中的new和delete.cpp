#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Lnode {
	int a;
	int b;
};

int main()
{
	int* pInt = new int[10];
	char* pChar = new char[10];
	Lnode* pLnode = new Lnode[2];
	for (int i = 0; i < 10; i++)
	{
		pInt[i] = i + 1;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << pInt[i] << " ";
	}

	delete[]pInt;//delete时new有括号，delete也有括号

	return 0;
}