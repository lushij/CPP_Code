#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
/*�ı��ֽ���ʽ*/
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
#define Width 800//���ڿ��
#define High 600//���ڸ߶�
#define MHigh 100//�˵��߶�

void Menu();
void select();//ѡ������
void brush();//��������