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
	//����
	virtual void Jianp() = 0;
	//���
	virtual void Mouse() = 0;
	//��ʾ��
	virtual void View() = 0;
	//wifi�ȼ�
	virtual void Wifi() = 0;
	//Ʒ��
	virtual void Name() = 0;
	//��װ˳��
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
	//�ع����麯��ʱvirtual���Բ�д��Ҳ����д
	//cpu
	 void Cpu()
	{
		cout << "13��i9�����ܴ�����" << endl;
	}
	//����
	 void Jianp()
	{
		cout << "��е����" << endl;
	}
	//���
	 void Mouse()
	{
		cout << "��Ϸ���" << endl;
	}
	//��ʾ��
	 void View()
	{
		cout << "4k����ʾ" << endl;
	}
	//wifi�ȼ�
	 void Wifi()
	{
		cout << "wifi6plus" << endl;
	}
	//Ʒ��
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
		cout << "13��i9�����ܴ�����4090" << endl;
	}
	//����
	virtual void Jianp()
	{
		cout << "��е����" << endl;
	}
	//���
	virtual void Mouse()
	{
		cout << "��Ϸ���" << endl;
	}
	//��ʾ��
	virtual void View()
	{
		cout << "4k����ʾ" << endl;
	}
	//wifi�ȼ�
	virtual void Wifi()
	{
		cout << "wifi6plus" << endl;
	}
	//Ʒ��
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