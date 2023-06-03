#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include<vector>
#include<map>
#include<deque>
#include<string>
#include <algorithm>
#include"Speaker.h"
using namespace std;
class speekManger
{
public:
	//构造函数
	speekManger();
	//初始化菜单
	void initMenu();
	//开始比赛
	void startSystem();
	//初始化创建12名选手
	void createSpeaker();












	//退出系统
	void exitSystem();
	//析构函数
	~speekManger();

public:
	//比赛选手 容器 12人
	vector<int>v1;
	//第一轮晋级容器 6人
	vector<int>v2;
	//胜利前三名容器 3人
	vector<int>vVictory;
	//存放编号 以及对应的 具体选手 容器
	map<int, Speaker> m_Speaker;
	int m_Index;
};

	