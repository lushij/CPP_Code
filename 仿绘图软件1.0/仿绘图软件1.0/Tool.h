#pragma once
#include"Rect.h"

class Tool
{
public:
	Tool();
	void show();
	bool event(ExMessage& msg);
	void achieve_rvoke(ExMessage& msg);
private:
	vector <Rect> rect;//�洢���εĵ�
	Point begin;
	Point end;
	bool preview;
	bool isDown;//�ж�����Ƿ���
};

