#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
//第一步引入头文件
#include<fstream>

/*

注意：c++文件中不能string类型，会出现问题


*/
using namespace std;

//写文件
void ofs()
{
   //第二步定义流对象
	ofstream ofs;
	//打开文件
	ofs.open("text.txt", ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		//判断是否打开成功
		perror("打开失败");
	}
	//写数据
	ofs.write("香菜，红烧肉",16);

	ofs.close();//关闭文件 ​
}


//读文件
void ifs()
{
	ifstream ifs;
	ifs.open("text.txt",ios::in);
	if (!ifs.is_open())
	{
		//判断是否打开成功
		perror("打开失败");
	}
	char buf[1024] = " ";
	//按照一行一行读取
	while (ifs >> buf)
	{
		cout << buf;
	}
	/*cout << endl;*/

	ifs.close();

}

int main()
{	
    ifs();
	return 0;
}