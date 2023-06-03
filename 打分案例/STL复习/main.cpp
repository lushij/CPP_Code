#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
/*
remove_if()函数的使用方法
begin  end  p: 一个谓词（UnaryPredicate），用于判断哪些元素应该被删除。
注意：remove_if()只是把符合条件的数据移到最后一个，因此需要配合erase函数进行删除数据

*/
void test()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6 };
	v.erase(v.begin(), v.end(), [&](int x) {return x % 2 != 0});

}

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5, 6 };

	// 使用 lambda 表达式作为谓词函数
	auto is_even = [](int x) { return x % 2 == 0; };

	// 调用 remove_if() 函数
	auto new_end = std::remove_if(v.begin(), v.end(), is_even);

	// 使用 erase() 函数真正删除元素
	v.erase(new_end, v.end());

	// 输出结果
	for (auto elem : v) {
		std::cout << elem << " ";
	}

	return 0;
}