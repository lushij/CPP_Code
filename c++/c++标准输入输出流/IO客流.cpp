#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
using namespace std;


//��׼������
/*
*	cin.get() //һ��ֻ�ܶ�ȡһ���ַ�
	cin.get(һ������) //��һ���ַ�
	cin.get(��������) //���Զ��ַ���
	cin.getline()//ȡһ�У����з�����
	cin.ignore()//����
	cin.peek()//͵��
	cin.putback()//�Ż�
*/
void in()
{
	//char num=0;
	//cin.get(num);//һ��һ���ַ���ȡ
	//cout << num;
	
	//��
	char buf[1024] = {0};
	cin.getline(buf, 1024);
	cout << buf << endl;
	/*string s;
	getline(cin, s);*/
}


int main()
{
	in();
	return 0;
}