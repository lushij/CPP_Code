#define _CRT_SECURE_NO_WARNINGS 1
#include<easyx.h>//图形库头文件
//必须为cpp后缀

//格式控制类函数
void test2()
{
	//颜色控制
	//set+color
	/*
		设置背景颜色setbkcolor
		注意：一定要刷新  cleardevice();
		设置线条的颜色setlinecolor
		颜色宏（相应颜色的大写单词）
		例如 setlinecolor(RED);
		RGB模式setlinecolor(RGB（ ， ， ）);
		设置填种颜色
		setfillcolor();
	*/

	/*
	样式函数
	设置线的样式
	settextstyle(类型 ，粗细)；
	注意；这些指示基础，更多请参考文档api
	*/

	/*
	文字输出
	只支持字符串输出
	注意：outtextxy(int x,int y,const char*str)并且需要把字节格式改为多字节
	属性--》高级--》字符集--》多字节字符集
	文字具有背景需要去除背景 setbkmode(TRANSPARENT);
	文字样式 settextstyle(int h,int w,"字体");
	注意：高度是0或者宽度是0 采用自适应 系统自己判断比例
	文字颜色
	settextcolor();

	注意输出别的文字例如数字
	需要自己加工封装一个函数
	例如
	void outtextxy(int x,int y,int score)
	{
		char str[20]="";
		sprintf(str,"分数为%d",score);
		outtextxy(x,y,str);
	}



	*/
	
}


void test()
{
//	//基本函数
//	line(0, 0, 200, 200);
//	//画个棋盘
//
//	for (int i = 0; i <= 200; i+=50)
//	{
//		line(0, i, 200, i);
//		line(i, 0, i, 200);
//	}

//矩形图形
 rectangle(100, 100, 200, 200);//左上角坐标，右下角坐标
 //圆形图像
 circle(100, 100, 50);//圆心坐标，半径

 //填充fill+形状（）  没有边界线
 fillcircle(80, 80, 20);
 //填充solid+形状（）   有边界线
 solidcircle(120, 120, 20);

 //格式控制类函数
 test2();
}
int main()
{
	//初始化窗口
	//initgraph(200, 200);//不显示控制台
	initgraph(200, 200,1);//显示控制台需要加入一个参数1
	//坐标和qt界面一样都是
	/*
	* 坐标形式
	0------------x
	|
	|
	|
	|
	y
	
	*/

	test();
	while (1);

	closegraph();//关闭窗口

	return 0;
}