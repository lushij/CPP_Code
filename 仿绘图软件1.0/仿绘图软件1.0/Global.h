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




void setColor(int x, int y, int mx, int my);//Ĭ�ϱ�����ɫ
void setClickColor(int x, int y, int mx, int my);
void Menu();
void select(bool *status);//ѡ������
void brush(bool *status);//��������
void revoke(bool *status);//��������
void rectangle(bool *status);//��������
void circle(bool *status);//Բ����
void color(bool *status);//��ɫ����
void thickness(bool *status);
void filling(bool *status);
void clear(int x,int y,int mx,int my=0);
void keydown(ExMessage& msg);

void Rectangle(ExMessage& msg);//����ʵ��
bool isRange(ExMessage& msg);//ȷ����Χ�Ƿ��ڲ�����