
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
using namespace std;
bool user = false;//ע����Ϣ
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
	string name;//����
	int count;//����
	string IBSN;//���
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
			  cout << "������" << ;
		  }
	  }

private:
	vector<Book> B;
}



void menu()
{
	printf("--------------��ͼ�����ϵͳ��---------------\n");
	printf("\t\t0.�˳�ϵͳ\n");
	printf("\t\t1.����ͼ��\n");
	printf("\t\t2.��ʾͼ����Ϣ\n");
	printf("\t\t3.ɾ��ͼ��\n");
	printf("\t\t4.����ͼ��\n");
	printf("\t\t5.����ͼ��\n");
	printf("\t\t6.�黹ͼ��\n");
	printf("--------------------------------------------\n");
	printf("��������ѡ��(0-5):");
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
		cout << "������ͼ����Ϣ��������������"<<endl;
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
		cout << "�㻹δע�ᣬ�Ƿ�ע��" << endl;
		cout << "�ظ� �� �� �� " << endl;
		string select;
		cin >> select;
		if (select == "��")
		{
			cout << "ע��ɹ�" << endl;
			user = true;
			system("pause");
			system("cls");

		}
		else
		{
			cout << "δע�ᣬ����ʧ��" << endl;
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