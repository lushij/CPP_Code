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
    // ָ�������λ�úʹ�С
    int x = 100, y = 100, w = 200, h = 100;
    bool clicked = false; // �Ƿ�����ָ������
    while (1)
    {
        while (peekmessage(&msg))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
                // ��ȡ��������
                int mx = msg.x, my = msg.y;

                // �ж�����Ƿ���ָ��������
                if (mx >= x && mx <= x + w && my >= y && my <= y + h)
                {
                    clicked = true; // �����ָ������
                    setfillcolor(YELLOW); // ���ñ���ɫ
                    solidrectangle(x, y, x + w, y + h); // ����������
                }
                else
                {
                    clicked = false; // ����˱������
                    setfillcolor(BLACK); // ���ñ���ɫ
                    solidrectangle(x, y, x + w, y + h); // ����������
                }

                //// ��������Ϣ
                //clearmouseclick(WM_LBUTTONDOWN);
            }

            if (clicked)
            {
                setbkcolor(YELLOW);
                outtextxy(x, y, "Hello, world!"); // ��������
            }

            Sleep(10); // ����CPUռ����
        }
   }
    closegraph();
	return 0;
}