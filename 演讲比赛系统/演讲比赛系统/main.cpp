#include"speekManger.h"
int main()
{
	speekManger sm;
	
	int choice = 0; //用来存储用户的选项
	while (true)
	{
		sm.initMenu();
		cout << "请输入您的选择： " << endl;
		cin >> choice; // 接受用户的选项
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSystem();
			break;
		case 2: //查看记录
			break;
		case 3: //清空记录
			break;
		case 0: //退出系统
			sm.exitSystem();
			break;
		}
	}
	system("pause");
	return 0;
}
