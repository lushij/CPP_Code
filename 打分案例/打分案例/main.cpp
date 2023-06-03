#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
#include<deque>
#include<ctime>
using namespace std;

//抽象学生类
class Student 
{
public:
	string name;
	int score;
};
bool compare(Student &s1,Student &s2)
{
	return s1.score > s2.score;
}

//1创建学生
void createStudent(vector<Student>& v)
{
	string name[6] = { "A","B","C" ,"D","E","V"};
	
	for (int i=0;i<6;i++)
	{
		Student stu;
		stu.name = name[i];
		stu.score = 0;
		v.push_back(stu);
	}
}
//2进行打分
void setStuScore(vector<Student>& Stu)
{
	vector<int>Vstu;
	deque<int>Sscore;
	for (auto &V : Stu)
	{
		int score = 0;
		
		//10个评委进行打分并去掉最高分和最低分
		for (int i = 0; i < 10; i++)
		{
			score = rand() % 70 + 30;
			Sscore.push_back(score);
		}
		//去掉最高分和最低分
		Sscore.pop_front();
		Sscore.pop_back();
		for (auto t : Sscore)
		{
			score += t;
		}
		//求平均分
		int avgScore = score / Sscore.size();
		V.score = avgScore;
 	}
}
//3进行排序
void sortStuScore(vector<Student>& Stu)
{
	sort(Stu.begin(), Stu.end(), compare);
	for (auto V : Stu)
	{
		cout << "姓名：" << V.name << " 分数：" << V.score << endl;
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	vector<Student> Stu;
	//1创建学生
	createStudent(Stu);
	//2进行打分
	setStuScore(Stu);
	//3进行排序
	sortStuScore(Stu);
	return 0;
}