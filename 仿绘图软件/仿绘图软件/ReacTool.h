#pragma once
#include "Global.h"
#include "React.h"
#include "Point.h"
//��ͼʵ���붨��Ҫ���뿪����ʵ�ֳ�����ʵ�ַ���

class ReacTool//��ͼ����ʵ��
{
public:
	ReacTool();
	void show();
	bool isDraeR(ExMessage& msg);
	void event(ExMessage& msg);

protected:
	vector<React> rect;//������л��Ƶľ���
	Point begin;//Ԥ���ľ������
	Point end;//Ԥ�����ε��յ�
	bool preview;//Ԥ���ı��
	bool isDown;//�ж�����Ƿ���
};

