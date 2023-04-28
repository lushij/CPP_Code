#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*单列模式顺序方法
	1.把无参构造函数和拷贝构造函数私有化

​	2.定义一个类内的静态成员指针

​	3.在类外初始化时，new一个对象

​	4.把指针的权限设置为私有，然后提供一个静态成员函数让外面获取这个指针
*/

class Printer 
{
	//1.把无参构造函数和拷贝构造函数私有化
private:
	Printer()
	{
		count = 0;
	}
	Printer(const Printer& p)
	{

	}
public:
	//4.把指针的权限设置为私有，然后提供一个静态成员函数让外面获取这个指针
	static Printer* getP()
	{
		return p;
	}
	void printP()
	{
		cout << "打印" << endl;
		count++;
	}
	int getCount()
	{
		return count;
	}
private:
	int count;//记录打印机打印的次数
	//2.定义一个类内的静态成员指针
	static Printer* p;
};

//3.在类外初始化时，new一个对象
Printer* Printer::p = new Printer;


int main()
{
	Printer* p1 = Printer::getP();
	p1->printP();
	Printer* p2 = Printer::getP();
	p2->printP();
	Printer* p3 = Printer::getP();
	p3->printP();

	
	Printer* p = Printer::getP();
	cout << p->getCount() << endl;

	
	return 0;
}