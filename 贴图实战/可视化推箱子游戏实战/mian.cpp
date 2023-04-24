#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include <conio.h>
#include<time.h>
const int ROW = 7;//����
const int COL = 8;//����

/*
IMAGE img;
getimage(&img, 0, 0, 100, 100);
putimage(200, 200, &img);

void loadimage(
	IMAGE* pDstImg,			// ����ͼ��� IMAGE ����ָ��
	LPCTSTR pImgFile,		// ͼƬ�ļ���
	int nWidth = 0,			// ͼƬ��������
	int nHeight = 0,		// ͼƬ������߶�
	bool bResize = false	// �Ƿ���� IMAGE �Ĵ�С����ӦͼƬ
);
*/
/*
0����յ�
1����ǽ
2��������
3����Ŀ�ĵ�
5���ӵ���Ŀ�ĵ�
6��
9��վ��Ŀ�ĵ���ʾ��
*/
//��ά�����ʼ����ͼ
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

//������������
//----------------------------------------
//������Դ---->�����ĳ�ʼ��
//��ͬ�ı����в�ͬ�ĳ�ʼ����ʽ
//loadimage ��ʼ��IMAGE ����
//������������
//----------------------------------------
IMAGE img[6];
int imgIndex[6] = { 0, 1, 3, 4, 5, 7 };
void loadResour()
{
	for (int i = 0; i < 6; i++)
	{
		char filename[20] = "";
		sprintf_s(filename, "%d.bmp", imgIndex[i]);
		loadimage(img + i, filename);//��ͼƬ���ְ��ո�ʽ������img������
	}
	
}



void drawmap()
{
	int x, y;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//����ƽ����Ҫx��y����
			x = 64 * j;
			y = 64 * i;
			//��Ϸ״̬�ķ�������Ϸ���
			/*
			0����յ�
			1����ǽ
			4��������
			3����Ŀ�ĵ�
			7���ӵ���Ŀ�ĵ�
			5��
			8��վ��Ŀ�ĵ���ʾ��
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
			case 8:		//��վĿ���� ��ʾ��
				putimage(x, y, img + 4);
				break;
			case 7:		//���ӵ���Ŀ�ĵ�
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
	//����������
	char userKey = _getch();  //���ɼ�����
	//С���� 72 80 75 77
	switch (userKey)
	{
	case 'w':
	case 'W':
	case 72:
		//��һ����������Ա��ǿյػ���Ŀ��
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
		{
			map[i][j] -= 5;
			map[i - 1][j] += 5;
		}
		//�ڶ�����������Ա�������
		//����������״̬
		else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
		{
			//�ж������Ա������� �յغ�Ŀ�ĵ�
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
		//�ڶ�����������Ա�������
		//����������״̬
		else if (map[i + 1][j] == 4 || map[i + 1][j] == 7)
		{
			//�ж������Ա������� �յغ�Ŀ�ĵ�
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
		//�ڶ�����������Ա�������
		//����������״̬
		else if (map[i][j - 1] == 4 || map[i][j - 1] == 7)
		{
			//�ж������Ա������� �յغ�Ŀ�ĵ�
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
		//�ڶ�����������Ա�������
		//����������״̬
		else if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
		{
			//�ж������Ա������� �յغ�Ŀ�ĵ�
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
			MessageBox(hwnd, "��Ϸ����", "wind game", MB_OK);
			break;
		}
	}
	
	closegraph();
	return 0;
}