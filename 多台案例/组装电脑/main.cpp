#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class AceCop
{
public:
	//cpu
	virtual void Cpu() = 0;
	//键盘
	virtual void Jianp() = 0;
	//鼠标
	virtual void Mouse() = 0;
	//显示率
	virtual void View() = 0;
	//wifi等级
	virtual void Wifi() = 0;
	//品牌
	virtual void Name() = 0;
	//组装顺序
	void Make()
	{
		Name();
		Cpu();
		Wifi();
		View();
		Jianp();
	}
};

class Xiaomi:public AceCop
{
	//重构纯虚函数时virtual可以不写，也可以写
	//cpu
	 void Cpu()
	{
		cout << "13代i9高性能处理器" << endl;
	}
	//键盘
	 void Jianp()
	{
		cout << "机械键盘" << endl;
	}
	//鼠标
	 void Mouse()
	{
		cout << "游戏鼠标" << endl;
	}
	//显示率
	 void View()
	{
		cout << "4k高显示" << endl;
	}
	//wifi等级
	 void Wifi()
	{
		cout << "wifi6plus" << endl;
	}
	//品牌
	 void Name()
	{
		cout << "xioami" << endl;
	}
};



class Leven :public AceCop
{
	
	//cpu
	virtual void Cpu()
	{
		cout << "13代i9高性能处理器4090" << endl;
	}
	//键盘
	virtual void Jianp()
	{
		cout << "机械键盘" << endl;
	}
	//鼠标
	virtual void Mouse()
	{
		cout << "游戏鼠标" << endl;
	}
	//显示率
	virtual void View()
	{
		cout << "4k高显示" << endl;
	}
	//wifi等级
	virtual void Wifi()
	{
		cout << "wifi6plus" << endl;
	}
	//品牌
	virtual void Name()
	{
		cout << "Leven" << endl;
	}
};

int main()
{
	AceCop* abs = new Xiaomi;
	abs->Make();
	AceCop* ace = new Leven;
	ace->Make();
	return 0;
}