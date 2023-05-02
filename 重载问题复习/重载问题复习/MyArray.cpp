#include "MyArray.h"

//����
MyArray::MyArray()
{
	this->mSize = 0;
	this->mCapacity = 20;
	this->pArray = new int[this->mCapacity];//����ռ�new
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->pArray[i] = 0;
	}

}
//��������
MyArray::MyArray(const MyArray& arr)
{
	this->mCapacity = arr.mCapacity;
	this->mSize = arr.mSize;
	//�����¿ռ�
	//1.����ռ�
	this->pArray = new int[arr.mCapacity];
	//2.��������
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->pArray[i] = arr.pArray[i];
	}
}


MyArray::~MyArray()
{
	if (this->pArray != NULL)
	{
		delete[] this->pArray;//����ʱ�����ţ�ɾ��ʱҲҪ������
		this->pArray = NULL;
	}
}

//ͷ��
void MyArray::PushFront(int val)
{
	//�ж������Ƿ���
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	for (int i = this->mSize - 1; i >= 0; i--)
	{
		this->pArray[i+1] = this->pArray[i];
	}
	this->pArray[0] = val;
		//����
	this->mSize++;
}
//β��
void MyArray::PushBack(int val)
{
	//�ж������Ƿ���
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	this->pArray[this->mSize] = val;
	this->mSize++;
}
//ͷɾ
void MyArray::PopFront()
{
	//�ж��Ƿ�Ϊ��
	if (mSize == 0)
	{
		return;
	}
	for (int i = 0; i < this->mSize-1; i++)
	{
		this->pArray[i] = this->pArray[i + 1];

	}
	this->mSize--;
}
//βɾ
void MyArray::PopBack()
{
	this->mSize--;
}
//��ȡ����Ԫ�ظ���
int MyArray::Size()
{
	return this->mSize;
}
//��ȡ��������
int MyArray::Capacity()
{
	return this->mCapacity;
}
//ָ��λ�ò���yuans 
void MyArray::Insert(int pos, int val)
{

	//�ж������Ƿ���
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	for (int i = this->mSize; i >= pos; i--)
	{
		this->pArray[i] = this->pArray[i - 1];
	}
	this->pArray[pos - 1] = val;
	this->mSize++;
}
//��ȡָ���±��ֵ
int& MyArray::Get(int pos)
{
	return this->pArray[pos];
}
//��ָ��λ���޸�ֵ
void MyArray::Set(int pos, int val)
{
	this->pArray[pos-1] = val;
}

