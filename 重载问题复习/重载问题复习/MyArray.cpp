#include "MyArray.h"

//构造
MyArray::MyArray()
{
	this->mSize = 0;
	this->mCapacity = 20;
	this->pArray = new int[this->mCapacity];//申请空间new
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->pArray[i] = 0;
	}

}
//拷贝构造
MyArray::MyArray(const MyArray& arr)
{
	this->mCapacity = arr.mCapacity;
	this->mSize = arr.mSize;
	//申请新空间
	//1.申请空间
	this->pArray = new int[arr.mCapacity];
	//2.拷贝数据
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->pArray[i] = arr.pArray[i];
	}
}


MyArray::~MyArray()
{
	if (this->pArray != NULL)
	{
		delete[] this->pArray;//申请时有括号，删除时也要有括号
		this->pArray = NULL;
	}
}

//头插
void MyArray::PushFront(int val)
{
	//判断容量是否满
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	for (int i = this->mSize - 1; i >= 0; i--)
	{
		this->pArray[i+1] = this->pArray[i];
	}
	this->pArray[0] = val;
		//更新
	this->mSize++;
}
//尾插
void MyArray::PushBack(int val)
{
	//判断容量是否满
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	this->pArray[this->mSize] = val;
	this->mSize++;
}
//头删
void MyArray::PopFront()
{
	//判断是否为空
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
//尾删
void MyArray::PopBack()
{
	this->mSize--;
}
//获取数组元素个数
int MyArray::Size()
{
	return this->mSize;
}
//获取数组容量
int MyArray::Capacity()
{
	return this->mCapacity;
}
//指定位置插入yuans 
void MyArray::Insert(int pos, int val)
{

	//判断容量是否满
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
//获取指定下标的值
int& MyArray::Get(int pos)
{
	return this->pArray[pos];
}
//在指定位置修改值
void MyArray::Set(int pos, int val)
{
	this->pArray[pos-1] = val;
}

