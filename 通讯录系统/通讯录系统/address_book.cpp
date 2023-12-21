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

void deleteContact(list*& Head, const char* nameToDelete) {
	list* current = Head->next;
	list* prev = Head;
	while (current != NULL) {
		if (strcmp(current->data.name, nameToDelete) == 0) {
			prev->next = current->next;
			delete current;
			cout << "��ϵ����ɾ��" << endl;
			return;
		}
		prev = current;
		current = current->next;
	}
	cout << "δ�ҵ�����ϵ��" << endl;
}

void searchContact(list* Head, const char* nameToSearch) {
	list* current = Head->next;
	while (current != NULL) {
		if (strcmp(current->data.name, nameToSearch) == 0) {
			cout << "��ϵ����Ϣ��" << endl;
			cout << current->data.name << "\t" << current->data.Phone << "\t" << current->data.Address << endl;
			return;
		}
		current = current->next;
	}
	cout << "δ�ҵ�����ϵ��" << endl;
}
void updateContact(list* Head, const char* nameToUpdate, const PeopleTel& newData) {
	list* current = Head->next;
	while (current != NULL) {
		if (strcmp(current->data.name, nameToUpdate) == 0) {
			current->data = newData;
			cout << "��ϵ����Ϣ�Ѹ���" << endl;
			return;
		}
		current = current->next;
	}
	cout << "δ�ҵ�����ϵ��" << endl;
}

void clearContacts(list*& Head) {
	list* current = Head->next;
	list* nextNode;
	while (current != NULL) {
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
	Head->next = NULL;
	cout << "������ϵ�������" << endl;
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
		cout << "������Ҫɾ������ϵ��������";
		cin >> Peo.name;
		deleteContact(Headlist, Peo.name);
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		break;
	case 3://3.��ʾ��ϵ��
		insearch(Headlist);
		break;
	case 4://4.������ϵ��
		cout << "������Ҫ���ҵ���ϵ��������";
		cin >> Peo.name;
		searchContact(Headlist, Peo.name);
		break;
	case 5://5.�޸���ϵ��
		cout << "������Ҫ�޸ĵ���ϵ��������";
		cin >> Peo.name;
		cout << "�������µ���ϵ����Ϣ������ �绰 ��ϵ��ַ" << endl;
		cin >> Peo.name >> Peo.Phone >> Peo.Address;
		updateContact(Headlist, Peo.name, Peo);
		saveFile(Headlist, "ͨѶ¼�ļ�.txt");
		break;
	case 6://6.�����ϵ��
		clearContacts(Headlist);
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