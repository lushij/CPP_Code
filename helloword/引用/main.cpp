#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

int main1()
{
	//���õı��ʾ�����c++�ڲ�ʵ����һ����ָ��
	int a = 0;
	int &b = a;
	b = 20;
	cout << b << endl;
	cout << a << endl;

	return 0;
}

int main()
{
	int a = 0;
	int hour = 0;
	cin >> a;
	if (a >= 60)
	{
		hour=a/60;
	}
	cout << hour << endl;
	return 0;
}