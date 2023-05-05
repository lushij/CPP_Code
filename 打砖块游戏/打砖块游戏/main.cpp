#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<graphics.h>
#include<ctime>
using namespace std;
const int Row = 3;//行数
const int Col = 5;
int a[Row][Col];
//初始化地图
void initMap()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < Row; i++)
	{
		for (j = 0; j < Col; j++)
		{
			a[i][j] = rand() % 3 + 1;
		}
	}
}

//绘制地图
void drawMap()
{
	int i = 0;
	int j = 0;
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	for (i = 0; i < Row; i++)
	{
		for (j = 0; j <Col ; j++)
		{
			printf("(%d %d)\n", i, j);
			int x = j * 100;
			int y = i * 25;
			printf("(%d %d)\n", x, y);
			switch (a[i][j])
			{
			case 0:
				break;
			case 1:
				setfillcolor(RED);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setfillcolor(GREEN);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setfillcolor(LIGHTBLUE);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
	}
}




//板块
struct Board {
	int x;
	int y;
	int w;
	int h;
	int speed;
	COLORREF color;
};
Board boards;
void creatBoard(int X,int Y,int W, int H, COLORREF Color,int S)
{
	boards.x = X;
	boards.y = Y;
	boards.speed = S;
	boards.w = W;
	boards.h = H;
	boards.color = Color;
}
//按键控制
void keyDown()
{
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT) && boards.x >= 0)
	{
		//左移  VK_LEFT小键盘左方向键
		boards.x -= boards.speed;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT) && boards.x+boards.w <= 800)
	{
		//右移
		boards.x += boards.speed;
	}
}
//绘制板块
void drawBoard()
{
	setfillcolor(boards.color);
	fillrectangle(boards.x, boards.y, boards.x + boards.w, boards.y+boards.h);
}


struct Ball {
	int x;
	int y;
	int r;
	COLORREF color;
	int dx;
	int dy;
};

//小球部分
Ball ball;
void creatBall(int X,int Y,int R, COLORREF Color,int Dx,int Dy)
{
	ball.x = X;
	ball.y = Y;
	ball.r = R;
	ball.color = Color;
	ball.dx = Dx;
	ball.dy = Dy;
	
}

//击打板块
int hitBoard()
{
	if (ball.y + ball.r == boards.y)
	{
		if (ball.x >= boards.x && ball.x <= boards.x + boards.w)
		{
			return 1;
		}
		
	}
	return 0;
}

//击打砖块
int hitMap()
{
	//横排数列 row行 col列  3行5列
	int col =ball.x / 100;//圆心x坐标 列数
	int row = (ball.y-ball.r) / 25;//圆心纵坐标-半径 行
	/*printf("(%d %d)\n", ball.x, ball.y);
	printf("(%d %d)\n", row, col);*/
	if (row < Row && col < Col && a[row][col] != 0 )
	{
		/*printf("(%d %d)\n", row, col);*/
		a[row][col] = 0;
		return 1;
	}
	return 0;
}


void drawBall()
{
	setfillcolor(ball.color);
	fillcircle(ball.x, ball.y, ball.r);
}
void moveBall()
{
	if (ball.x+ball.r >= 500 || ball.x - ball.r <= 0)
	{
		ball.dx = -ball.dx;
		
	}
	if ( ball.y - ball.r <= 0 || hitBoard() || hitMap())
	{
		ball.dy = -ball.dy;
	}
	ball.x += ball.dx;
	ball.y += ball.dy;
}
int  gameOver()
{
	if (ball.y + ball.r > boards.y)
	{
		return 1;
	}
	return 0;
}

int winGame()
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (a[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	//句柄 HWND
	HWND hwnd = initgraph(500, 500,1);
	
	
	
	while (1)
	{
		initMap();
		creatBoard(0, 500 - 25, 500, 25, WHITE, 3);
		creatBall(100, 300, 15, YELLOW, 1, -1);
		srand((unsigned int)time(NULL));
		while (1)
		{
			
			cleardevice();
			BeginBatchDraw();
			drawMap();
			if (winGame())
			{
				MessageBox(hwnd, "游戏结束", "wind game", MB_OK);
				break;
			}
			drawBoard();
			keyDown();
			drawBall();
			moveBall();
			if (gameOver())
			{
				//对话框: MessagBox
				MessageBox(hwnd, "是否继续", "lose game", MB_OK);
				break;
			}

			
			FlushBatchDraw();
		}
		
		EndBatchDraw();
	}
	closegraph();
	return 0;
}