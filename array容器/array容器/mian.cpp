#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <array>

using namespace std;
/*
	array:定长数组
	1.array的基本操作
	2.array操作自定义类型
	3.简单模拟一下array的实现
*/
//1.基本操作
void testCreateArray()
{
	//创建不初始化
	array<int, 3>  myArray;
	//创建用列表数据初始化数组{}
	array<string, 2> str = { "ILoveyou","IMiisyou" };
}
void userArray()
{
	array<string, 3> strData;
	//直接当做数组使用
	strData[0] = "ILoveyou";
	strData[1] = "Imiisyou";
	//strData[3] = "IMiis";   越界
	strData[2] = "IMiis";
	for (int i = 0; i < strData.size(); i++)
	{
		cout << strData[i] << "\t";
	}
	cout << endl;
	//新的for循环
	for (auto v : strData)
	{
		cout << v << "\t";
	}
	cout << endl;
	//内置迭代器遍历
	array<string, 3>::iterator iter;
	for (iter = strData.begin(); iter != strData.end(); iter++)
	{
		cout << *iter << "\t";
	}
	cout << endl;
	//at方法
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
	//在 c + + 11 中已过时，替换为 fill 。 替换所有元素。
	array<int, 3> Data;
	Data.fill(3);
	for (auto v : Data)
	{
		cout << v << "\t";
	}
	cout << endl;
}
//类对象  就是一个数据，所以数据可以做的它都可以
//当做函数参数
//当做函数返回值
//当做类的数据成员也是可以

	
int main()
{
	userArray();
	arrayFunc();
	return 0;
}