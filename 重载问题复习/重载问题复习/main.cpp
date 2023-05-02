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
	//Ìí¼ÓÔªËØ
	for (int i = 0; i < 10; i++)
	{
		//Î²²å
		arr.PushBack(i + 10);
	}
	//for (int i = 0; i < 9; i++)
	//{
	//	//Í·²å
	//	arr.PushFront(i + 20);
	//}
	// 
	printMarray(arr);
	//Í·É¾

	arr.PopFront();
	//Î²É¾
	arr.PopBack();
}

int main()
{
	//²âÊÔ
	MyArray m;
	test(m);
	MyArray m2(m);
	printMarray(m);
	printMarray(m2);


	return 0;
}