#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
#include<deque>
#include<ctime>
using namespace std;

//����ѧ����
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

//1����ѧ��
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
//2���д��
void setStuScore(vector<Student>& Stu)
{
	vector<int>Vstu;
	deque<int>Sscore;
	for (auto &V : Stu)
	{
		int score = 0;
		
		//10����ί���д�ֲ�ȥ����߷ֺ���ͷ�
		for (int i = 0; i < 10; i++)
		{
			score = rand() % 70 + 30;
			Sscore.push_back(score);
		}
		//ȥ����߷ֺ���ͷ�
		Sscore.pop_front();
		Sscore.pop_back();
		for (auto t : Sscore)
		{
			score += t;
		}
		//��ƽ����
		int avgScore = score / Sscore.size();
		V.score = avgScore;
 	}
}
//3��������
void sortStuScore(vector<Student>& Stu)
{
	sort(Stu.begin(), Stu.end(), compare);
	for (auto V : Stu)
	{
		cout << "������" << V.name << " ������" << V.score << endl;
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	vector<Student> Stu;
	//1����ѧ��
	createStudent(Stu);
	//2���д��
	setStuScore(Stu);
	//3��������
	sortStuScore(Stu);
	return 0;
}