#include "speekManger.h"

speekManger::speekManger()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
}

void speekManger::initMenu()
{
	cout <<"***********************************************" << endl;
	cout <<"************* 欢迎参加演讲比赛 ****************" << endl;
	cout <<"************* 1.开始演讲比赛 ******************" << endl;
	cout <<"************* 2.查看往届记录 ******************" << endl;
	cout <<"************* 3.清空比赛记录 ******************" << endl;
	cout <<"************* 0.退出比赛程序 ******************" << endl;
	cout <<"***********************************************" << endl;
	cout << endl;
}

void speekManger::startSystem()
{
}

void speekManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.Score[i] = 0;
		}
		//12名选手编号
		this->v1.push_back(i + 10001);
		//选手编号 以及对应的选手 存放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void speekManger::exitSystem()
{
	cout << "退出成功" << endl;
	cout << "欢迎下次使用" << endl;
	exit(0);
}

speekManger::~speekManger()
{
}
