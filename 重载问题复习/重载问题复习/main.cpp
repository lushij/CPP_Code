#include "MyArray.h"
void printMarray(MyArray&arr)
{
	int i = 0;
	for (i = 0; i <arr.Size(); i++)
	{
		cout << arr.Get(i) << " ";
	}
	cout << endl;
}

void test(MyArray& arr)
{
	//���Ԫ��
	for (int i = 0; i < 10; i++)
	{
		//β��
		arr.PushBack(i + 10);
	}
	//for (int i = 0; i < 9; i++)
	//{
	//	//ͷ��
	//	arr.PushFront(i + 20);
	//}
	// 
	printMarray(arr);
	//ͷɾ

	arr.PopFront();
	//βɾ
	arr.PopBack();
}

int main()
{
	//����
	MyArray m;
	test(m);
	MyArray m2(m);
	printMarray(m);
	printMarray(m2);


	return 0;
}