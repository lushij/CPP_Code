#pragma once
#include "Global.h"
#include "React.h"
#include "Point.h"
//绘图实现与定义要分离开来，实现抽象与实现分离

class ReacTool//绘图操作实现
{
public:
	ReacTool();
	void show();
	bool isDraeR(ExMessage& msg);
	void event(ExMessage& msg);

protected:
	vector<React> rect;//存放所有绘制的矩形
	Point begin;//预览的矩形起点
	Point end;//预览矩形的终点
	bool preview;//预览的标记
	bool isDown;//判定鼠标是否按下
};

