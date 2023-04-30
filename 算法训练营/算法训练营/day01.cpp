#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

void twoPrint(int a)
{
	int i = 31;
	for (i = 31; i >= 0; i--)
	{
		//在c++中语法较严格 三目操作符返回的是地址，需要转换
		cout << (int)((a & (1 << i)) == 0 ? 0 : 1);
		/*if ((a & (1 << i)) == 0)
		{
			cout << 0;
		}
		else
		{
			cout << 1;
		}*/
	}
	cout << endl;
}
int main()
{
	// &  有0为0  按位与
	// |  有1为1  按位或
	// ^  同0非1  按位异或
	//twoPrint(1);
	int a = 1;
	int b = ~a + 1;//相反数的底层逻辑
	cout << a << " " << b << endl;
	return 0;
}