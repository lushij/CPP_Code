#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;


//������ģ��
class MyArray
{
public:
	MyArray();
	MyArray(const MyArray& arr);
	~MyArray();

	//ͷ��
	void PushFront(int val);
	//β��
	void PushBack(int val);
	//ͷɾ
	void PopFront();
	//βɾ
	void PopBack();
	//��ȡ����Ԫ�ظ���
	int Size();
	//��ȡ��������
	int Capacity();
	//ָ��λ�ò���Ԫ��
	void Insert(int pos, int val);
	//��ȡָ���±��ֵ
	int& Get(int pos);
	//��ָ��λ���޸�ֵ
	void Set(int pos, int val);

private:
	int* pArray;//ָ������ռ䣬�洢����
	int mSize;//Ԫ�ظ���
	int mCapacity;//����
};

