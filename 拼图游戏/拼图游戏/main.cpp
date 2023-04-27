#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<graphics.h>
#include<ctime>
#include<cstdlib>
const int ROW = 4;//��
const int COL = 4;//��
const int IMAGEW = 500;//ͼƬ���
const int IMAGEH = 552;//ͼƬ�߶�
const int BlockW = IMAGEW / COL;//ÿһС��Ŀ�
const int BlockH = IMAGEH / ROW;//ÿһС��ĸ�

IMAGE mm, White;
using namespace std;


int map[ROW][COL] =
{
	0,1,2,3,
	4,5,6,7,
	8,9,10,15,
	12,13,14,11
};

void loadRsoure()
{
	loadimage(&mm, "mm.jpg", IMAGEW, IMAGEH);
	loadimage(&White, "white.jpg", BlockW, BlockH);
}

void drawMap()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int x = i * BlockW;//ÿһС������� 
			int y = j * BlockH;
			cout << x << " " << y << endl;
			if (map[i][j] == 15)
			{
				putimage(x, y, &White);
			}
			else
			{
				/*cout << "-----------------" << endl;*/

				int row = map[i][j] / COL;
				int col = map[i][j] % COL;
				//cout << row << " " << col << endl;
				putimage(x, y, BlockW, BlockH, &mm, col * BlockW, row * BlockH);
			}

		}
	}
}




int main()
{
	loadRsoure();
	initgraph(IMAGEW, IMAGEH,1);
	drawMap();
	while (1);
	//keyDown();
	closegraph();
	return 0;
}