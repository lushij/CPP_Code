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
	//���캯��
	speekManger();
	//��ʼ���˵�
	void initMenu();
	//��ʼ����
	void startSystem();
	//��ʼ������12��ѡ��
	void createSpeaker();












	//�˳�ϵͳ
	void exitSystem();
	//��������
	~speekManger();

public:
	//����ѡ�� ���� 12��
	vector<int>v1;
	//��һ�ֽ������� 6��
	vector<int>v2;
	//ʤ��ǰ�������� 3��
	vector<int>vVictory;
	//��ű�� �Լ���Ӧ�� ����ѡ�� ����
	map<int, Speaker> m_Speaker;
	int m_Index;
};

	