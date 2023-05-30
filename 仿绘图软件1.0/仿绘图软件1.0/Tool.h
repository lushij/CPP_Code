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
	vector <Rect> rect;//存储矩形的点
	Point begin;
	Point end;
	bool preview;
	bool isDown;//判定鼠标是否按下
};

