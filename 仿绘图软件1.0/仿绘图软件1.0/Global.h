#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
/*改变字节形式*/
#ifdef UNICODE
#undef UNICODE
#endif

#include<iostream>
#include <cstring>
#include <algorithm>
#include<graphics.h>
#include<vector>
#include<conio.h>
using namespace std;
#define Width 800//窗口宽度
#define High 600//窗口高度
#define MHigh 100//菜单高度

void Menu();
void select();//选择区域
void brush();//画笔区域