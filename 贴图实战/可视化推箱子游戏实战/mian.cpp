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
	1, 3, 2, 0, 0, 2, 3, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 0, 6, 0, 0, 0, 1,
	1, 3, 2, 0, 0, 2, 3, 1,
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
int imgIndex[6] = { 0,1,2,3,5,6 };
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
			2��������
			3����Ŀ�ĵ�
			5���ӵ���Ŀ�ĵ�
			6��
			9��վ��Ŀ�ĵ���ʾ��
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
			case 9:		//��վĿ���� ��ʾ��
				putimage(x, y, img + 5);
				break;
			case 5:		//���ӵ���Ŀ�ĵ�
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