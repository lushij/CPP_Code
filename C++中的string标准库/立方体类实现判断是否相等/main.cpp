#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include<string>

using namespace std;

class Cube {
private://˽������
	int Long;
	int High;
	int Width;
public://��������
	//��ʼ��
	void init()
	{
		Long = 0;
		High = 0;
		Width = 0;
	}
    //��ȡ����
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
	//��ȡ����
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
	//���
	int Scube()
	{
		return 2 * Long * High + 2 * Long * Width + 2 * High * Width;
	}
	//���
	int Vcube()
	{
		return Long * High * Width;
	}
	//�Ƚ��ж�
	bool ComPareCube(Cube &cube)//Ϊɶ����һ��������
		//��Ϊ������ĳ�Ա�����Դ��Լ�������
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
		cout << "���" << endl;
	}
	else
	{
		cout << "�����" << endl;
	}*/
	//�������һģһ��
	if (c2.ComPareCube(c1))
	{
		cout << "���" << endl;
	}
	else
	{
		cout << "�����" << endl;
	}
	return 0;
}