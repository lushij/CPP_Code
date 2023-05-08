#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Maker
{
public:
	Maker()
	{
		cout << "无参构造" << endl;
	}
	void printMaker()
	{
		cout << "hello Maker" << endl;
	}
	~Maker()
	{
		cout << "析构函数" << endl;
	}
};

class SmartPoint
{
public:
	SmartPoint(Maker*m)
	{
		this->pMaker = m;
	}
	~SmartPoint()
	{
		if (this->pMaker != NULL)
		{
			delete this->pMaker;
			this->pMaker = NULL;
		}
	}
private:
	Maker* pMaker;

};

void test()
{
	Maker* p = new Maker;

	SmartPoint sm(p);//栈区，会调用析构函数
}
int main()
{
	test();
	return 0;
}