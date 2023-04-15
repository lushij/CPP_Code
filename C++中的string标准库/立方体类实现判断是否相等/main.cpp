#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<string>

using namespace std;

class Cube {
private://私有属性
	int Long;
	int High;
	int Width;
public://公有属性
	//初始化
	void init()
	{
		Long = 0;
		High = 0;
		Width = 0;
	}
    //获取数据
	void getL(int L)
	{
		Long = L;
	}
	void getW(int w)
	{
		Width = w;
	}
	void getH(int h)
	{
		High = h;
	}
	//读取数据
	int getL()
	{
		return Long;
	}
	int	getW()
	{
		return Width;
	}
	int	getH()
	{
		return High;
	}
	//面积
	int Scube()
	{
		return 2 * Long * High + 2 * Long * Width + 2 * High * Width;
	}
	//体积
	int Vcube()
	{
		return Long * High * Width;
	}
	//比较判断
	bool ComPareCube(Cube &cube)//为啥传入一个变量类
		//因为自身类的成员方法自带自己的属性
	{
		if (getL() == cube.getL() && getW() == cube.getW() && getH() == cube.getH())
		{
			return true;
		}
		return false;
	}
};	


int main()
{
	Cube c1, c2;
	c1.getH(10);
	c1.getW(10);
	c1.getL(10);
	c2.getH(10);
	c2.getW(20);
	c2.getL(10);
	/*if (c1.ComPareCube(c2))
	{
		cout << "相等" << endl;
	}
	else
	{
		cout << "不相等" << endl;
	}*/
	//和上面的一模一样
	if (c2.ComPareCube(c1))
	{
		cout << "相等" << endl;
	}
	else
	{
		cout << "不相等" << endl;
	}
	return 0;
}