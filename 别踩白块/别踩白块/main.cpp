#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<graphics.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#pragma comment(lib,"winmm.lib")//启动多线程库
const int GradW = 100;
const int GradH = 150;
using namespace std;
time_t t;
string name;
struct Info {
	string name;
	time_t t;
};

bool cmp(const Info& a, const Info& b)
{
	return a.t > b.t;
}

vector<Info>_info;

time_t startTime;
int flag[4];

void initFlag()
{
	for (int i = 0; i < 4; i++)
	{
		flag[i] = rand() % 4;
	}
}

void DrawMap()
{
	//设置线条颜色
	setlinecolor(BLACK);
	//设置线条的样式
	setlinestyle(PS_SOLID, 2);
	for (int i = 0; i < 4; i++)
	{
		line(i * GradW, 0, i * GradW, 600);//（起点坐标）--->（终点坐标）
		line(0, i * GradH, 400, i * GradH);
	}
	//绘制黑块格子
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(BLACK);
		solidrectangle(flag[i] * GradW, i * GradH, flag[i] * GradW + GradW, i * GradH + GradH);
	}
}

//音效加载
DWORD WINAPI playMusic(LPVOID pvoid)
{
	mciSendString("open bgm.mp3", 0, 0, 0);
	mciSendString("play bgm.mp3 wait", 0, 0, 0);
	mciSendString("close bgm.mp3", 0, 0, 0);
	return 0;
}
void readFile(string filename)
{
	ifstream ifs(filename);
	if (!ifs)
	{
		return;
	}
	string line;
	while (getline(ifs, line))
	{
		string name;
		time_t t;
		istringstream iss(line);
		iss >> name >> t;
		Info i = {name,t};
		_info.push_back(i);
	}
	sort(_info.begin(), _info.end(), cmp);
	ifs.close();
}
void show(const char* str, int color,int t)
{
	while (1)
	{
		cleardevice();
		setbkmode(TRANSPARENT);  // 设置文字背景透明
		BeginBatchDraw();//双缓冲
		readFile("save.txt");
		int centerX = getwidth() / 2;  // 计算窗口中心横坐标
		//上面的区域都是该背景大概400*200（0,200）
		setbkcolor(LIGHTBLUE);
		settextcolor(BLACK);
		solidrectangle(0, 0, getwidth(), 200);  // 上面的矩形区域
		setfillcolor(LIGHTBLUE);
		char buf[526] = { 0 };
		sprintf(buf, "用户名 ：%s", _info.front().name.c_str());
		settextstyle(16, 16, _T("宋体"));  // 设置字体样式
		outtextxy(centerX-100, 60, buf);
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "最好记录：%lf", (double)_info.front().t);
		outtextxy(centerX-140, 100, buf);
		//下面整块都是下面的背景400*400（200,600）
		settextcolor(WHITE);
		setbkcolor(color);
		solidrectangle(0, 200, getwidth(), getheight()-400); 
		settextstyle(50, 50, _T("宋体"));  // 设置字体样式
		outtextxy(centerX-100, 350, str);
		FlushBatchDraw();
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			return;
		}
	}
	EndBatchDraw();
}
void showFlag(int flag,int t)
{
	if (flag == 1)
	{
		//表示成功
		show("成功", GREEN,t);
		
	}
	else
	{
		//表示失败
		show("失败", RED,t);
	}
}
void saveFile(const char*str)
{
	ofstream ofs(str, std::ios::app);
	if (!ofs)
	{
		return;
	}
	ofs << name << "\t" << t << endl;
	ofs.close();
}
void keyDown(HWND hwnd)
{
	MOUSEMSG m = GetMouseMsg();
	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
	
		//点击最后一列的黑快就刷新
		int x = flag[3] * GradW;
		int y = 3 * GradH;
		if (m.x >= x && m.y >= y && m.x <= x + GradW && m.y <= y + GradH)
		{
			for (int i = 3; i >= 1; i--)
			{
				flag[i] = flag[i - 1];
			}
			flag[0] = rand() % 4;
		}
		else
		{
			time_t endTime=time(NULL);
			cout << endTime << endl;
			t = endTime - startTime;//玩游戏的时间
			cout << t << endl;
			int flag = -1;
			char names[256] = { 0 };
			InputBox(names, 39, "请输入您的名字：");
			name=string(names);
			saveFile("save.txt");
			if (t > 30)
			{
				flag = 1;//表示成功
			}
			else
			{
				flag = 0;//表示失败
			}
			MessageBox(hwnd, "游戏结束", "gameover", MB_OK);
			showFlag(flag,t);
			exit(0);
		}
		
		break;
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	HWND hwnd=initgraph(400, 600);
	setbkcolor(WHITE);
	cleardevice();
	BeginBatchDraw();//双缓冲
	initFlag();
	startTime = time(NULL);
	cout << startTime << endl;
	while (1)
	{
		cleardevice();
		//setbkcolor(WHITE);
		DrawMap();
		keyDown(hwnd);
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}