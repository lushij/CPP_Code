#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
using namespace std;
void test()
{
    // ����һ����ά���� matrix
    vector<vector<int>> matrix = {
        {1, 2, 3},   // ��һ�У�����3��Ԫ��
        {4, 5, 6},   // �ڶ��У�����3��Ԫ��
        {7, 8, 9}    // �����У�����3��Ԫ��
    };
    // ��������
    int numRows = matrix.size();
    // ������������Ҫѡȡһ��һά�����Ĵ�С��Ϊ����������ѡ���һ��һά����
    int numCols = matrix[0].size();
    cout << "������" << numRows << endl;
    cout << "������" << numCols << endl;
}

void test1()
{
// ʾ����ʹ�÷�Χ-based for ѭ��������ά����
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // ʹ�÷�Χ-based for ѭ��������ά����
    for (const auto& row : matrix) {//����
        for (const auto& elem : row) {//����
            cout << elem << " ";
        }
    cout << endl;
    }
}
int main()
{
	vector<int>num({ 1,2,3,5,6,7,8,9,10 });
	for (auto x : num)//��string����һ��
	{
		cout << x << " ";
	}
	return 0;
}