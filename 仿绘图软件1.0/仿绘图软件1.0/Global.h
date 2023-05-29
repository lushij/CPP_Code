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




void setColor(int x, int y, int mx, int my);//默认背景颜色
void setClickColor(int x, int y, int mx, int my);
void Menu();
void select(bool *status);//选择区域
void brush(bool *status);//画笔区域
void revoke(bool *status);//撤销区域
void rectangle(bool *status);//矩形区域
void circle(bool *status);//圆区域
void color(bool *status);//颜色区域
void thickness(bool *status);
void filling(bool *status);
void clear(int x,int y,int mx,int my=0);
void keydown(ExMessage& msg);

void Rectangle(ExMessage& msg);//矩形实现
bool isRange(ExMessage& msg);//确定范围是否在操作区