#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;

//联系人
struct PeopleTel {
	char name[20];
	char Phone[12];
	char Address[20];
};

//链表
struct list {
	struct PeopleTel data;
	struct list* next;
};

//创建头结点
list* createHeadList()
{
	list *HeadList = NULL;
	HeadList = new list;
	HeadList->next = NULL;
	return HeadList;
}

//创建节点
list* createNode(PeopleTel data)
{
	list* newNode = new list;
	newNode->data= data;
	newNode->next = NULL;
	return newNode;
}

//添加联系人
void insertList(list* &Head,  PeopleTel data)
{
	list* newList = createNode(data);
	newList->next = Head->next;
	Head->next = newList;
}


//遍历
void insearch(list*Head)
{
	list* Move = Head->next;
	while (Move != NULL)
	{
		cout << Move->data.name << "\t" 
			<< Move->data.Phone << "\t"
			<< Move->data.Address << endl;
		Move = Move->next;
	}
}

//链表读取文件操作
void readFile(list* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if(fp==NULL)
	{
		fp = fopen(fileURL, "w");
		fclose(fp);
		return;
	}
	PeopleTel tmp ;
	while (fscanf(fp, "%s\t%s\t%s\n", tmp.name, tmp.Phone, tmp.Address) != EOF)
	{
		insertList(headNode, tmp);
	}
	fclose(fp);
}

//链表写文件
void saveFile(list* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "w");
	list* Move = headNode->next;
	while (Move)
	{
		fprintf(fp, "%s\t%s\t%s\n",
			Move->data.name,
			Move->data.Phone,
			Move->data.Address);
		Move = Move->next;
	}
	fclose(fp);
}

//菜单
void menu()
{
	cout << "************************" << endl;
	cout << "***** 1.添加联系人 *****" << endl;
	cout << "***** 2.删除联系人 *****" << endl;
	cout << "***** 3.显示联系人 *****" << endl;
	cout << "***** 4.查找联系人 *****" << endl;
	cout << "***** 5.修改联系人 *****" << endl;
	cout << "***** 6.清空联系人 *****" << endl;
	cout << "***** 0.退出系统   *****" << endl;
	cout << "************************" << endl;
}


//用户交互按键封装
void keyDown(list* &Headlist)
{
	PeopleTel Peo;
	int userKey = 0;
	cout << "请输入你的选择(0-6)：";
	cin >> userKey;
	switch (userKey)
	{
	case 0:
		cout << "退出成功" << endl;
		exit(0);
		break;
	case 1://1.添加联系人
		cout << "请输入信息：姓名 电话 联系地址" << endl;
		cin >> Peo.name >> Peo.Phone >> Peo.Address;
		insertList(Headlist, Peo);
		saveFile(Headlist, "通讯录文件.txt");
		cout << "添加成功" << endl;
		break;
	case 2://2.删除联系人
		saveFile(Headlist, "通讯录文件.txt");
		break;
	case 3://3.显示联系人
	
		insearch(Headlist);

		break;
	case 4://4.查找联系人
		break;
	case 5://5.修改联系人
		saveFile(Headlist, "通讯录文件.txt");
		break;
	case 6://6.清空联系人
		saveFile(Headlist, "通讯录文件.txt");
		break;
	}
}

int main()
{
	list* Headlist = createHeadList();
	readFile(Headlist, "通讯录文件.txt");
	while (1)
	{
		menu();
		keyDown(Headlist);
		system("pause");
		system("cls");
	}
	

	return 0;
}