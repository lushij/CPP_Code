#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Complety {
public:
	//´¿Ðéº¯Êý
	virtual void Content() = 0;
};

class Mouse :public Complety {
private:
	string name;
	string price;
	string cpu;
public:
	Mouse(string name, string price, string cpu)
	{
		this->cpu = cpu;
		this->name = name;
		this->price = price;
	}
	void Content()
	{
		cout << name << " " << price << " " << cpu << endl;
	}
};
class Jianpan :public Complety {
private:
	string name;
	string price;
	string cpu;
public:
	Jianpan(string name, string price, string cpu)
	{
		this->cpu = cpu;
		this->name = name;
		this->price = price;
	}
	void Content()
	{
		cout << name << " " << price << " " << cpu << endl;
	}
};

int main()
{
	Complety* cp=new Mouse("leishe","169","3060");
	cp->Content();
	Complety* cp2 = new Jianpan("leishe", "169", "3060");
	cp2->Content();
	return 0;
}