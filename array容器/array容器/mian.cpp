#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <array>

using namespace std;
/*
	array:��������
	1.array�Ļ�������
	2.array�����Զ�������
	3.��ģ��һ��array��ʵ��
*/
//1.��������
void testCreateArray()
{
	//��������ʼ��
	array<int, 3>  myArray;
	//�������б����ݳ�ʼ������{}
	array<string, 2> str = { "ILoveyou","IMiisyou" };
}
void userArray()
{
	array<string, 3> strData;
	//ֱ�ӵ�������ʹ��
	strData[0] = "ILoveyou";
	strData[1] = "Imiisyou";
	//strData[3] = "IMiis";   Խ��
	strData[2] = "IMiis";
	for (int i = 0; i < strData.size(); i++)
	{
		cout << strData[i] << "\t";
	}
	cout << endl;
	//�µ�forѭ��
	for (auto v : strData)
	{
		cout << v << "\t";
	}
	cout << endl;
	//���õ���������
	array<string, 3>::iterator iter;
	for (iter = strData.begin(); iter != strData.end(); iter++)
	{
		cout << *iter << "\t";
	}
	cout << endl;
	//at����
	for (int i = 0; i < strData.size(); i++)
	{
		cout << strData.at(i) << "\t";
	}
	cout << endl;
}
void arrayFunc()
{
	array<int, 3>  Num = { 1,2,3 };
	cout << Num.size() << endl;
	cout << Num.empty() << endl;
	cout << Num.front() << endl;
	cout << Num.at(0) << endl;
	cout << Num.back() << endl;
	int iNum[3] = { 1,2,3 };
	//�� c + + 11 ���ѹ�ʱ���滻Ϊ fill �� �滻����Ԫ�ء�
	array<int, 3> Data;
	Data.fill(3);
	for (auto v : Data)
	{
		cout << v << "\t";
	}
	cout << endl;
}
//�����  ����һ�����ݣ��������ݿ���������������
//������������
//������������ֵ
//����������ݳ�ԱҲ�ǿ���

	
int main()
{
	userArray();
	arrayFunc();
	return 0;
}