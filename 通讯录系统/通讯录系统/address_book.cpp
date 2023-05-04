#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;

//��ϵ��
struct PeopleTel {
	char name[20];
	char Phone[12];
	char Address[20];
};

//����
struct list {
	struct PeopleTel data;
	struct list* next;
};

//����ͷ���
list* createHeadList()
{
	list *HeadList = NULL;
	HeadList = new list;
	HeadList->next = NULL;
	return HeadList;
}

//�����ڵ�
list* createNode(PeopleTel data)
{
	list* newNode = new list;
	newNode->data= data;
	newNode->next = NULL;
	return newNode;
}

//�����ϵ��
void insertList(list* &Head,  PeopleTel data)
{
	list* newList = createNode(data);
	newList->next = Head->next;
	Head->next = newList;
}


//����
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

//�����ȡ�ļ�����
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

//����д�ļ�
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

//�˵�
void menu()
{
	cout << "************************" << endl;
	cout << "***** 1.�����ϵ�� *****" << endl;
	cout << "***** 2.ɾ����ϵ�� *****" << endl;
	cout << "***** 3.��ʾ��ϵ�� *****" << endl;
	cout << "***** 4.������ϵ�� *****" << endl;
	cout << "***** 5.�޸���ϵ�� *****" << endl;
	cout << "***** 6.�����ϵ�� *****" << endl;
	cout << "***** 0.�˳�ϵͳ   *****" << endl;
	cout << "************************" << endl;
}


//�û�����������װ
void keyDown(list* &Headlist)
{
	PeopleTel Peo;
	int userKey = 0;
	cout << "���������ѡ��(0-6)��";
	cin >> userKey;
	switch (userKey)
	{
	case 0:
		cout << "�˳��ɹ�" << endl;
		exit(0);
		break;
	case 1://1.�����ϵ��
		cout << "��������Ϣ������ �绰 ��ϵ��ַ" << endl;
		cin >> Peo.name >> Peo.Phone >> Peo.Address;
		insertList(Headlist, Peo);
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		cout << "��ӳɹ�" << endl;
		break;
	case 2://2.ɾ����ϵ��
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		break;
	case 3://3.��ʾ��ϵ��
	
		insearch(Headlist);

		break;
	case 4://4.������ϵ��
		break;
	case 5://5.�޸���ϵ��
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		break;
	case 6://6.�����ϵ��
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		break;
	}
}

int main()
{
	list* Headlist = createHeadList();
	readFile(Headlist, "ͨѶ¼�ļ�.txt");
	while (1)
	{
		menu();
		keyDown(Headlist);
		system("pause");
		system("cls");
	}
	

	return 0;
}