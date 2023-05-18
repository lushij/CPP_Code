#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
using namespace std;

/*
容器内部函数
.sizeof()求函数的长度
.begin()求数组的第一个元素的下标
.end()最后一个元素下标

*/
void print(vector<int>&arr)
{
	for (auto x: arr)
	{
		cout << x<<" ";
	}
	cout << endl;
}
void print(vector<char>& arr)
{
	for (auto x : arr)
	{
		cout << x << " ";
	}
	cout << endl;
}

void test01()
{
	vector<int>v;
	vector<char>v1 = {'c','h','i','n','a'};
	//迭代器使用
	vector<char>::iterator begin = v1.begin();
	vector<char>::iterator end = v1.end();
	//​cout << begin << endl;
	//v1.push_back('c');//插入字符
	//v.push_back(1);//插入数据
	////cout << v.size() << endl;
	//print(v1);
}
int main()
{
	vector<int>a = {1,2,3,4,5,6,6};//一维数组类型
	//二维数组嵌套形式
	vector<vector<int>>arr = {
		{1,2},{2,3}
	};
	//for ( auto x:a)
	//{
	//	cout << x << " ";
	//}
	//cout << endl;

	////遍历二维数组
	//for (auto row :arr)
	//{
	//	for (auto col : row)
	//	{
	//		col = col + 1;
	//		cout << col << " ";
	//	}
	//	cout << endl;
	//}

	test01();
	return 0;
}