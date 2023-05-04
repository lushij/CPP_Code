#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
面向对象的多态的作用：
1.什么是多态：
	同一个操作作用于不同的对象，可以有不同的解释，会产生不同的效果，这就是多态
2.多态有什么用
	1.可以解决项目中的紧耦合问题,提供程序的可扩展性
	2.应用程序不必为每一个子类的功能调用编写代码，只需要对抽象的父类进行处理
3.多态发生的三个条件	
	1.有继承。2.重写父类的虚函数。3.父类指针指向子类对象
1.依赖倒转
	业务层依赖抽象层，实现层依赖抽象层
4.抽象类
	1.有纯虚函数的类叫抽象类，不能实例化对象
*/



class Maker
{
public:
	//纯虚构
	virtual void speak() = 0;
};

class Mclass :public Maker
{
public:
	Mclass(string name,int age)
	{
		this->name = name;
		this->age = age;
	}
	//重写虚函数
	virtual void speak()
	{
		cout <<"王者荣耀区" << " " << name << " " << age << "岁" << endl;
	}
private:
	string name;
	int age;
};




class Mclass2 :public Maker
{
public:
	//纯虚构
	virtual void speak()
	{
		cout << "完美世界区 " << name << " " << skill << endl;
	}
	Mclass2(string name, string skill)
	{
		this->name = name;
		this->skill = skill;
	}
private:
	string name;
	string skill;
};
//班级
class Class
{
public:
	Class()
	{
		mCapity = 50;
		mSize = 0;
		this->p = new  Maker*[mCapity];
	}

	//增加人员
	void AddMaker(Maker* ma)
	{
		if (mSize == mCapity)
		{
			return;
		}

		this->p[mSize] = ma;
		mSize++;
	}
	//展示技能
	void show()
	{
		int i = 0;
		for (i = 0; i < mSize; i++)
		{
			p[i]->speak();
		}
	}
	~Class()
	{
		int i = 0;
		for (i = 0; i < mSize; i++)
		{
			delete p[i];
			p[i] = NULL;
		}
		delete[]p;
		p = NULL;
	}
private:
	Maker* *p;//存放人员指针的数组指针
	int mCapity;//容量
	int mSize;//实时大小
};

int main()
{
	Class* p = new Class;
	p->AddMaker(new Mclass("诸葛亮", 19));
	p->AddMaker(new Mclass("李白", 16));
	p->AddMaker(new Mclass2("荒天帝", "龙王破"));
	p->AddMaker(new Mclass2("公主", "月光宝盒"));

	p->show();

	return 0;
}