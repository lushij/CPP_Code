#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>		//getch();
#include <stdlib.h>		//system函数
int main()
{
	//printf("✔☐☒✘♥♠♤♂♀★☆※卍卐■□◆◇▲△▂▃▄▅▆▇█●○◎⊕⊙㊣\n");
	//???????♂♀★☆※卍卐■□◆◇▲△▂▃▄▅▆▇█●○◎⊕⊙㊣
	//1 墙:■
	//0 路:空格(两个)
	//3 目的地: ☆
	//4 箱子:   ★
	//3+4-->7 箱子推到目的地上:⊙
	//5:人: ♀  人站在目的上也是人8
	//多关卡制作: ctr+f  map替换为 map[cas]
	int cas = 0;
	int map[3][8][8] =
	{
		1,1,1,1,1,1,1,1,
		1,3,4,0,0,0,0,1,
		1,0,1,0,1,1,0,1,
		1,0,1,3,5,0,0,1,
		1,0,0,4,0,0,0,1,
		1,0,1,0,0,1,0,1,
		1,0,0,0,0,4,3,1,
		1,1,1,1,1,1,1,1,

		0,0,0,1,1,1,1,1,
		0,0,0,1,0,0,0,1,
		1,1,1,0,1,1,0,1,
		1,0,1,3,5,0,0,1,
		1,0,0,4,0,0,0,1,
		1,0,1,0,0,1,0,1,
		1,0,0,0,0,4,3,1,
		1,1,1,1,1,1,1,1,

		1,1,1,1,1,1,1,1,
		1,3,4,0,0,4,3,1,
		1,0,1,0,1,1,0,1,
		1,0,1,3,5,0,0,1,
		1,0,0,4,0,0,0,1,
		1,0,1,0,0,1,0,1,
		1,3,4,0,0,4,3,1,
		1,1,1,1,1,1,1,1
	};
	int i = 0;
	int j = 0;
	while (1)
	{
		printf("欢迎来到第 【%d】 关\n", cas + 1);		//数组计数从0
		//画地图
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				switch (map[cas][i][j])
				{
				case 0:
					printf("  ");		//；两个空格
					break;
				case 1:
					printf("■");
					break;
				case 3:
					printf("☆");
					break;
				case 4:
					printf("★");
					break;
				case 5:
				case 8: //当改变人的位置的后，人站在目的上的时候8
					printf("♀");
					break;
				case 7:
					printf("⊙");
					break;
				}
			}
			printf("\n");
		}
		//游戏是否结束:判断游戏地图上是否存在箱子
		int flag = 0;
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				if (map[cas][i][j] == 4)		//如果存在箱子
				{
					flag = 1;			//把标记置为1
					goto DOWN;
				}
			}
		}
	DOWN:
		if (flag == 0)
		{
			//当第一次没有箱子的时候，不应该跳出游戏主循环，应该切换关卡
			cas++;		//0 map[0][i][j]  1 map[1][i][j]
			//什么时候才是真正的游戏结束关卡等于3
			if (cas == 3)
				break;   //break语句只能跳出switch语句和循环语句
		}
		//玩游戏
		//1.找到人在哪里
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				if (map[cas][i][j] == 5 || map[cas][i][j] == 8)
					break;
				//goto next;
			}
			if (map[cas][i][j] == 5 || map[cas][i][j] == 8)
				break;
		}
		//next:
			//此时i和j代表人在数组中行列
			//选择结构中讲过的那个按键框架拿过来
			//VC CB dev turbo 不需要写下划线 
			//直接用getch()
		int userKey = _getch();			//接受用户按键
		switch (userKey)
		{
			//上
		case 'w':
		case 'W':
		case 72:
			//改变两格：要去的地方是空地或者目的地
			if (map[cas][i - 1][j] == 0 || map[cas][i - 1][j] == 3)
			{
				map[cas][i - 1][j] += 5;
				map[cas][i][j] -= 5;
			}
			//改变三格：要去的地方是箱子，
			if (map[cas][i - 1][j] == 4 || map[cas][i - 1][j] == 7)
			{
				//箱子旁边是空地或者目的地
				if (map[cas][i - 2][j] == 0 || map[cas][i - 2][j] == 3)
				{
					map[cas][i][j] -= 5;
					map[cas][i - 1][j] += 1;
					map[cas][i - 2][j] += 4;
				}
			}
			break;
			//下
		case 's':
		case 'S':
		case 80:
			if (map[cas][i + 1][j] == 0 || map[cas][i + 1][j] == 3)
			{
				map[cas][i + 1][j] += 5;
				map[cas][i][j] -= 5;
			}
			if (map[cas][i + 1][j] == 4 || map[cas][i + 1][j] == 7)
			{
				if (map[cas][i + 2][j] == 0 || map[cas][i + 2][j] == 3)
				{
					map[cas][i][j] -= 5;
					map[cas][i + 1][j] += 1;
					map[cas][i + 2][j] += 4;
				}
			}

			break;
			//左边
		case 'a':
		case 'A':
		case 75:
			if (map[cas][i][j - 1] == 0 || map[cas][i][j - 1] == 3)
			{
				map[cas][i][j - 1] += 5;
				map[cas][i][j] -= 5;
			}
			if (map[cas][i][j - 1] == 4 || map[cas][i][j - 1] == 7)
			{
				if (map[cas][i][j - 2] == 0 || map[cas][i][j - 2] == 3)
				{
					map[cas][i][j] -= 5;
					map[cas][i][j - 1] += 1;
					map[cas][i][j - 2] += 4;
				}
			}

			break;
			//右边
		case 'd':
		case 'D':
		case 77:
			if (map[cas][i][j + 1] == 0 || map[cas][i][j + 1] == 3)
			{
				map[cas][i][j + 1] += 5;
				map[cas][i][j] -= 5;
			}
			if (map[cas][i][j + 1] == 4 || map[cas][i][j + 1] == 7)
			{
				if (map[cas][i][j + 2] == 0 || map[cas][i][j + 2] == 3)
				{
					map[cas][i][j] -= 5;
					map[cas][i][j + 1] += 1;
					map[cas][i][j + 2] += 4;
				}
			}
			break;
		}
		
		system("cls");
	}
	printf("GameOver!\n");
	return 0;
}

