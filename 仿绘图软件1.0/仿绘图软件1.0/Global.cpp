#include "Global.h"

void Menu()
{
	setfillcolor(RGB(245, 246, 247));
	setlinecolor(RGB(218, 219, 220));
	setlinestyle(PS_SOLID, 2);
	fillrectangle(0, 0, Width, MHigh);
	settextcolor(BLACK);
	settextstyle(30,0,"Î¢ÈíÑÅºÚ");
	int w = 100;
	int h = 100;
	for (int i = 0; i < 8; i++)
	{
		fillrectangle(i * 100, 0, i * 100 + w, h);
	}
	select();
	brush();
}
void select()
{
	char txt[56] = "Ñ¡Ôñ";
	int w= textwidth(txt);
	int h = textheight(txt);
	
	outtextxy((100 - w) / 2, (100-h) / 2,txt);
}
void brush()
{
	char txt[56] = "»­±Ê";
	int w = textwidth(txt);
	int h = textheight(txt);
	outtextxy((300 - w) / 2, (100 - h) / 2, txt);
}