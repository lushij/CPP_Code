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
		//��c++���﷨���ϸ� ��Ŀ���������ص��ǵ�ַ����Ҫת��
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
	// &  ��0Ϊ0  ��λ��
	// |  ��1Ϊ1  ��λ��
	// ^  ͬ0��1  ��λ���
	//twoPrint(1);
	int a = 1;
	int b = ~a + 1;//�෴���ĵײ��߼�
	cout << a << " " << b << endl;
	return 0;
}