#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
�������Ķ�̬�����ã�
1.ʲô�Ƕ�̬��
	ͬһ�����������ڲ�ͬ�Ķ��󣬿����в�ͬ�Ľ��ͣ��������ͬ��Ч��������Ƕ�̬
2.��̬��ʲô��
	1.���Խ����Ŀ�еĽ��������,�ṩ����Ŀ���չ��
	2.Ӧ�ó��򲻱�Ϊÿһ������Ĺ��ܵ��ñ�д���룬ֻ��Ҫ�Գ���ĸ�����д���
3.��̬��������������	
	1.�м̳С�2.��д������麯����3.����ָ��ָ���������
1.������ת
	ҵ�����������㣬ʵ�ֲ����������
4.������
	1.�д��麯������г����࣬����ʵ��������
*/



class Maker
{
public:
	//���鹹
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
	//��д�麯��
	virtual void speak()
	{
		cout <<"������ҫ��" << " " << name << " " << age << "��" << endl;
	}
private:
	string name;
	int age;
};




class Mclass2 :public Maker
{
public:
	//���鹹
	virtual void speak()
	{
		cout << "���������� " << name << " " << skill << endl;
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
//�༶
class Class
{
public:
	Class()
	{
		mCapity = 50;
		mSize = 0;
		this->p = new  Maker*[mCapity];
	}

	//������Ա
	void AddMaker(Maker* ma)
	{
		if (mSize == mCapity)
		{
			return;
		}

		this->p[mSize] = ma;
		mSize++;
	}
	//չʾ����
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
	Maker* *p;//�����Աָ�������ָ��
	int mCapity;//����
	int mSize;//ʵʱ��С
};

int main()
{
	Class* p = new Class;
	p->AddMaker(new Mclass("�����", 19));
	p->AddMaker(new Mclass("���", 16));
	p->AddMaker(new Mclass2("�����", "������"));
	p->AddMaker(new Mclass2("����", "�¹ⱦ��"));

	p->show();

	return 0;
}