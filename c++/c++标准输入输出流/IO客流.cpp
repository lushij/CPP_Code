#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
using namespace std;


//标准输入流
/*
*	cin.get() //一次只能读取一个字符
	cin.get(一个参数) //读一个字符
	cin.get(两个参数) //可以读字符串
	cin.getline()//取一行，换行符丢弃
	cin.ignore()//忽略
	cin.peek()//偷窥
	cin.putback()//放回
*/
void in()
{
	//char num=0;
	//cin.get(num);//一个一个字符读取
	//cout << num;
	
	//行
	char buf[1024] = {0};
	cin.getline(buf, 1024);
	cout << buf << endl;
	/*string s;
	getline(cin, s);*/
}


int main()
{
	in();
	return 0;
}