#include "Tool.h"



Tool::Tool()
{
	this->preview = false;
	this->isDown = false;
}

void Tool::show()
{
    for (auto v : rect)
    {
        setlinecolor(BLACK);
        rectangle(v.getX(), v.getY(), v.getMx(), v.getMy());
    }
    if (preview)
    {
        setlinecolor(BLACK);
        rectangle(begin.getX(), begin.getY(), end.getX(), end.getY());
    }
}



bool Tool::event(ExMessage& msg)
{
    if (isRange(msg))
    {
		if (msg.message == WM_LBUTTONDOWN)
		{
			isDown = true;
			begin = { msg.x,msg.y };
			cout << "左上";
			cout << msg.x << " " << msg.y << endl;
		}
		if (msg.message == WM_LBUTTONUP)
		{
			isDown = false;
			end = { msg.x,msg.y };
			cout << "右下";
			cout << msg.x << " " << msg.y << endl;
			Rect temp = { begin.getX(),begin.getY(),end.getX(),
				end.getY() };
			rect.push_back(temp);
			preview = false;
		}
		if (msg.message == WM_RBUTTONDOWN)
		{
			if (!rect.empty())
			{
				rect.pop_back();			//从存储数组中删除掉已经绘制的矩形
			}
		}
		
		if (isDown == true && msg.message == WM_MOUSEMOVE)
		{
			end = { msg.x,msg.y };
			preview = true;
		}
    }
	return false;
}



