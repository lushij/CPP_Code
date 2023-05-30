
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
using namespace std;
bool user = false;//注册信息
class Book
{
public:
	Book(string name,int count)
	{
		this->name = name;
		this->count = count;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setCount(int count)
	{
		this->count = count;
	}
	string getName()
	{
		return name;
	}
	int getCount()
	{
		return count;
	}
	void setIbsn(string&ibsn)
	{
		this->IBSN = ibsn;
	}
	string getIbsn()
	{
		return IBSN;
	}

private:
	string name;//书名
	int count;//数量
	string IBSN;//编号
};

class Library
{
public: 
	void addBook(const Book& book)
	{
		B.push_back(book);
	}

	void removeBookByName(const string& ibsn)
	{
		for (auto &v:B)
		{
			if (v.getIbsn() == ibsn)
			{
				B.erase(remove_if(B.begin(), B.end(),
					[&]( Book& book) { return book.getIbsn() == ibsn; }),
					B.end());
			}

		}
	}

	  void listBooks() const 
	  {
		  for (auto &b : B)
		  {
			  cout << "书名：" << ;
		  }
	  }

private:
	vector<Book> B;
}



void menu()
{
	printf("--------------【图书管理系统】---------------\n");
	printf("\t\t0.退出系统\n");
	printf("\t\t1.增加图书\n");
	printf("\t\t2.显示图书信息\n");
	printf("\t\t3.删除图书\n");
	printf("\t\t4.查找图书\n");
	printf("\t\t5.借阅图书\n");
	printf("\t\t6.归还图书\n");
	printf("--------------------------------------------\n");
	printf("请输入你选择(0-5):");
}

void addBook()
{
	string ch;
	int num;
	cin >> ch >> num;
	book.push_back(&num,&ch);
}
void keyDown()
{
	int select = 0;
	cin >> select;
	switch (select)
	{
	case 0:
		exit(0);
		break;
	case 1:
		cout << "请输入图书信息（书名，数量）"<<endl;
		addBook();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;

	}
}

void Register()
{
	if (user == false)
	{
		cout << "你还未注册，是否注册" << endl;
		cout << "回复 是 或 否 " << endl;
		string select;
		cin >> select;
		if (select == "是")
		{
			cout << "注册成功" << endl;
			user = true;
			system("pause");
			system("cls");

		}
		else
		{
			cout << "未注册，进入失败" << endl;
			exit(0);

		}
	}
}
int main()
{
	
	Register();
	if (user == true)
	{
		menu();
		while (1)
		{
			keyDown();
			system("pause");
			system("cls");
		}
	}
	
	

	return 0;
}