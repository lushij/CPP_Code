#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
using namespace std;
void test()
{
    // 定义一个二维向量 matrix
    vector<vector<int>> matrix = {
        {1, 2, 3},   // 第一行，包含3个元素
        {4, 5, 6},   // 第二行，包含3个元素
        {7, 8, 9}    // 第三行，包含3个元素
    };
    // 计算行数
    int numRows = matrix.size();
    // 计算列数，需要选取一个一维向量的大小作为列数，这里选择第一个一维向量
    int numCols = matrix[0].size();
    cout << "行数：" << numRows << endl;
    cout << "列数：" << numCols << endl;
}

void test1()
{
// 示例：使用范围-based for 循环遍历二维数组
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // 使用范围-based for 循环遍历二维数组
    for (const auto& row : matrix) {//行数
        for (const auto& elem : row) {//列数
            cout << elem << " ";
        }
    cout << endl;
    }
}
int main()
{
	vector<int>num({ 1,2,3,5,6,7,8,9,10 });
	for (auto x : num)//和string容器一样
	{
		cout << x << " ";
	}
	return 0;
}