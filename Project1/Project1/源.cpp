#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<graphics.h>
#include<conio.h>
using namespace std;

int main()
{
    initgraph(500, 300);
    ExMessage msg;
    // 指定区域的位置和大小
    int x = 100, y = 100, w = 200, h = 100;
    bool clicked = false; // 是否点击了指定区域
    while (1)
    {
        while (peekmessage(&msg))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
                // 获取鼠标的坐标
                int mx = msg.x, my = msg.y;

                // 判断鼠标是否在指定区域内
                if (mx >= x && mx <= x + w && my >= y && my <= y + h)
                {
                    clicked = true; // 点击了指定区域
                    setfillcolor(YELLOW); // 设置背景色
                    solidrectangle(x, y, x + w, y + h); // 绘制填充矩形
                }
                else
                {
                    clicked = false; // 点击了别的区域
                    setfillcolor(BLACK); // 设置背景色
                    solidrectangle(x, y, x + w, y + h); // 绘制填充矩形
                }

                //// 清除鼠标消息
                //clearmouseclick(WM_LBUTTONDOWN);
            }

            if (clicked)
            {
                setbkcolor(YELLOW);
                outtextxy(x, y, "Hello, world!"); // 绘制文字
            }

            Sleep(10); // 降低CPU占用率
        }
   }
    closegraph();
	return 0;
}