#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
/*
remove_if()������ʹ�÷���
begin  end  p: һ��ν�ʣ�UnaryPredicate���������ж���ЩԪ��Ӧ�ñ�ɾ����
ע�⣺remove_if()ֻ�ǰѷ��������������Ƶ����һ���������Ҫ���erase��������ɾ������

*/
void test()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6 };
	v.erase(v.begin(), v.end(), [&](int x) {return x % 2 != 0});

}

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5, 6 };

	// ʹ�� lambda ���ʽ��Ϊν�ʺ���
	auto is_even = [](int x) { return x % 2 == 0; };

	// ���� remove_if() ����
	auto new_end = std::remove_if(v.begin(), v.end(), is_even);

	// ʹ�� erase() ��������ɾ��Ԫ��
	v.erase(new_end, v.end());

	// ������
	for (auto elem : v) {
		std::cout << elem << " ";
	}

	return 0;
}