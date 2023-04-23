#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include <conio.h>
#include<time.h>
const int ROW = 7;//行数
const int COL = 8;//列数

/*
IMAGE img;
getimage(&img, 0, 0, 100, 100);
putimage(200, 200, &img);

void loadimage(
	IMAGE* pDstImg,			// 保存图像的 IMAGE 对象指针
	LPCTSTR pImgFile,		// 图片文件名
	int nWidth = 0,			// 图片的拉伸宽度
	int nHeight = 0,		// 图片的拉伸高度
	bool bResize = false	// 是否调整 IMAGE 的大小以适应图片
);
*/
/*
0代表空地
1代表墙
2代表箱子
3代表目的地
5箱子到达目的地
6人
9人站在目的地显示人
*/
//二维数组初始化地图
int map[ROW][COL] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 3, 2, 0, 0, 2, 3, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 0, 6, 0, 0, 0, 1,
	1, 3, 2, 0, 0, 2, 3, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

//批量处理数据
//----------------------------------------
//加载资源---->变量的初始化
//不同的变量有不同的初始化方式
//loadimage 初始化IMAGE 变量
//批量处理数据
//----------------------------------------
IMAGE img[6];
int imgIndex[6] = { 0,1,2,3,5,6 };
void loadResour()
{
	for (int i = 0; i < 6; i++)
	{
		char filename[20] = "";
		sprintf_s(filename, "%d.bmp", imgIndex[i]);
		loadimage(img + i, filename);//把图片名字按照格式保存在img数组里
	}
	
}

void drawmap()
{
	int x, y;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//贴出平面需要x，y坐标
			x = 64 * j;
			y = 64 * i;
			//游戏状态的分析，游戏组成
			/*
			0代表空地
			1代表墙
			2代表箱子
			3代表目的地
			5箱子到达目的地
			6人
			9人站在目的地显示人
			int imgIndex[6] = { 0,1,2,3,5,6 };
			*/
			switch (map[i][j])
			{
			case 0:
				putimage(x, y, img + 0);
				break;
			case 1:
				putimage(x, y, img + 1);
				break;
			case 2:
				putimage(x, y, img + 2);
				break;
			case 3:
				putimage(x, y, img + 3);
				break;
			case 6:
			case 9:		//人站目的上 显示人
				putimage(x, y, img + 5);
				break;
			case 5:		//箱子到达目的地
				putimage(x, y, img + 4);
				break;
			}
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(64 * COL, 64 * ROW);
	loadResour();
	drawmap();
	getchar();
	closegraph();
	return 0;
}