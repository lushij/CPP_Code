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
	1, 3, 4, 0, 0, 4, 3, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 0, 5, 0, 0, 0, 1,
	1, 3, 4, 0, 0, 4, 3, 1,
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
int imgIndex[6] = { 0, 1, 3, 4, 5, 7 };
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
			4代表箱子
			3代表目的地
			7箱子到达目的地
			5人
			8人站在目的地显示人
			int imgIndex[6] = { 0, 1, 3, 4, 5, 7 };
			*/
			switch (map[i][j])
			{
			case 0:
				putimage(x, y, img + 0);
				break;
			case 1:
				putimage(x, y, img + 1);
				break;
			case 3:
				putimage(x, y, img + 2);
				break;
			case 4:
				putimage(x, y, img + 3);
				break;
			case 5:
			case 8:		//人站目的上 显示人
				putimage(x, y, img + 4);
				break;
			case 7:		//箱子到达目的地
				putimage(x, y, img + 5);
				break;
			}
		}
	}
}

void keyDown()
{
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
				goto NEXT;
		}
		
	}
	NEXT:
	//按键处理框架
	char userKey = _getch();  //不可见输入
	//小键盘 72 80 75 77
	switch (userKey)
	{
	case 'w':
	case 'W':
	case 72:
		//第一种情况：人旁边是空地或者目的
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
		{
			map[i][j] -= 5;
			map[i - 1][j] += 5;
		}
		//第二种情况：人旁边是箱子
		//箱子有两种状态
		else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
		{
			//判断箱子旁边能走吗？ 空地和目的地
			if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
			{
				map[i][j] -= 5;
				map[i - 1][j] += 1;
				map[i - 2][j] += 4;
			}

		}
		break;
	case 's':
	case 'S':
	case 80:
		if (map[i + 1][j] == 0 || map[i + 1][j] == 3)
		{
			map[i][j] -= 5;
			map[i + 1][j] += 5;
		}
		//第二种情况：人旁边是箱子
		//箱子有两种状态
		else if (map[i + 1][j] == 4 || map[i + 1][j] == 7)
		{
			//判断箱子旁边能走吗？ 空地和目的地
			if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
			{
				map[i][j] -= 5;
				map[i + 1][j] += 1;
				map[i + 2][j] += 4;
			}

		}
		break;
	case 'a':
	case 'A':
	case 75:
		if (map[i][j - 1] == 0 || map[i][j - 1] == 3)
		{
			map[i][j] -= 5;
			map[i][j - 1] += 5;
		}
		//第二种情况：人旁边是箱子
		//箱子有两种状态
		else if (map[i][j - 1] == 4 || map[i][j - 1] == 7)
		{
			//判断箱子旁边能走吗？ 空地和目的地
			if (map[i][j - 2] == 0 || map[i][j - 2] == 3)
			{
				map[i][j] -= 5;
				map[i][j - 1] += 1;
				map[i][j - 2] += 4;
			}

		}
		break;
	case 'D':
	case 'd':
	case 77:
		if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
		{
			map[i][j] -= 5;
			map[i][j + 1] += 5;
		}
		//第二种情况：人旁边是箱子
		//箱子有两种状态
		else if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
		{
			//判断箱子旁边能走吗？ 空地和目的地
			if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
			{
				map[i][j] -= 5;
				map[i][j + 1] += 1;
				map[i][j + 2] += 4;
			}

		}
		break;
	}
}


int WinGame()
{
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (map[i][j] == 4)
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	srand((unsigned int)time(NULL));
	HWND hwnd = initgraph(64 * COL, 64 * ROW);
	while (1)
	{
		loadResour();
		drawmap();
		keyDown();
		int ret = WinGame();
		if (ret)
		{
			MessageBox(hwnd, "游戏结束", "wind game", MB_OK);
			break;
		}
	}
	
	closegraph();
	return 0;
}