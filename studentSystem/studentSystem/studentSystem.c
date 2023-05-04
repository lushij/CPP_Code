#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <assert.h>		//���ԣ��ж�ָ���Ƿ��
#include <stdlib.h>
//��װ�Լ���Ҫ����ʽ�ṹ�洢������
struct MM 
{
	char name[20];
	int age;
	int num;
	char tel[12];
	//.....
	//.....
	//.....
};
//�ṹ��
struct Node 
{
	//int data;
	struct MM data;
	struct Node* next;
};
struct Node* list = NULL;
//������ǽṹ������ͽṹ������һ��
//ָ����α�ɱ���ȥʹ�ã�
//1.��ָ��ָ�����
//2.��̬�ڴ����룬ָ������ı���
struct Node* createHead() 
{
	//����ı�ͷ�����컯����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}
//�����ڵ�(���û������ݱ�ɽṹ�����)
struct Node* createNode(struct MM data) 
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	/*
	//����������������ã��������Ա��
		if(newNode==NULL)
			return NULL;
	*/
	//NULL->data=data; ����
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//����
void insertByHead(struct Node* headNode, struct MM data) 
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
//ɾ���� ָ��λ��ɾ��
void deleteByName(struct Node* headNode,const char* name) 
{
	struct Node* preNode = headNode;
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name ,name)) 
	{
		preNode = posNode;
		posNode = preNode->next;
	}
	if (posNode != NULL) 
	{
		preNode->next = posNode->next;
		free(posNode);
		printf("ɾ���ɹ�!!!\n");
	}
}
struct Node* searchByNum(struct Node* headNode, int posData) 
{
	struct Node* pMove = headNode->next;
	while (pMove != NULL && pMove->data.num != posData) 
	{
		pMove = pMove->next;
	}
	return pMove;
}
//����
void printList(struct Node* headNode) 
{
	struct Node* pMove = headNode->next;
	printf("����\t����\t���\t�ֻ�\n");
	while (pMove != NULL) 
	{
		//printf("%d\t", pMove->data);
		printf("%s\t%d\t%d\t%s\n",
			pMove->data.name, 
			pMove->data.age, 
			pMove->data.num
			, pMove->data.tel);
		pMove = pMove->next;
	}

}
//���������ļ�������
void readFile(struct Node* headNode, const char* fileURL) 
{
	//C�����ļ��������ǵ��ú���
	FILE* fp = fopen(fileURL, "r");   //��һ���д�ʧ�� r:�����д�������
	if (fp == NULL) 
	{
		fp = fopen(fileURL, "w+");	  //w��ʽ���д����ļ�����
		fclose(fp);
		return;
	}
	struct MM data;
	//��ȡ��ͷ
	int result=fscanf(fp, "%s\t%s\t%s\t%s\n", data.name, data.name, data.name, data.name);
	while (fscanf(fp, "%s\t%d\t%d\t%s\n", data.name, &data.age, &data.num, data.tel) != EOF) 
	{
		insertByHead(list, data);
	}
	fclose(fp);
}

//����������ļ�д����
void saveFile(struct Node* headNode, const char* fileURL) 
{
	FILE* fp = fopen(fileURL, "w");
	struct Node* pMove = headNode->next;
	//д���ͷ
	fprintf(fp, "%s\t%s\t%s\t%s\n", "����", "����", "���", "�绰");
	while (pMove != NULL) 
	{
		fprintf(fp, "%s\t%d\t%d\t%s\n", pMove->data.name,
			pMove->data.age,
			pMove->data.num,
			pMove->data.tel);
		pMove = pMove->next;
	}
	fclose(fp);
}


//�û�����
void makeMenu() 
{
	printf("--------------��MM����ϵͳ��---------------\n");
	printf("\t\t0.�˳�ϵͳ\n");
	printf("\t\t1.¼����Ϣ\n");
	printf("\t\t2.�����Ϣ\n");
	printf("\t\t3.ɾ����Ϣ\n");
	printf("\t\t4.������Ϣ\n");
	printf("\t\t5.�޸���Ϣ\n");
	printf("--------------------------------------------\n");
	printf("��������ѡ��(0-5):");
}
void keyDown() 
{
	struct MM data;
	struct Node* result = NULL;
	int userKey = 0;
	scanf_s("%d", &userKey);   //��ǿ�汾��scanf
	switch (userKey) 
	{
	case 0:
		printf("�˳��ɹ�!\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("��������Ů��Ϣ(name,age,num,tel):");
		scanf("%s%d%d%s", data.name, &data.age, &data.num, data.tel);
		insertByHead(list, data);
		printf("¼��ɹ�!...\n");
		//���浽�ļ�
		saveFile(list, "newMM.xls");
		break;
	case 2:
		printList(list);
		break;
	case 3:
		printf("������Ҫɾ������Ů������:");
		scanf_s("%s", data.name, 20);
		deleteByName(list, data.name);
		//���浽�ļ�
		saveFile(list, "newMM.xls");
		break;
	case 4:
		printf("������Ҫ������Ů�ı��:");
		scanf("%d", &data.num);
		result = searchByNum(list, data.num);
		if (result != NULL) 
		{
			printf("����\t����\t���\t�ֻ�\n");
			printf("%s\t%d\t%d\t%s\n",
				result->data.name,
				result->data.age,
				result->data.num, 
				result->data.tel);
		}
		else 
		{
			printf("δ�ҵ������Ϣ!\n");
		}
		break;
	case 5:
		printf("������Ҫ�޸�С��Ů�ı��:");
		scanf("%d", &data.num);
		result = searchByNum(list, data.num);
		if (result != NULL)
		{
			printf("��������Ů�µ���Ϣ(name,age,num,tel):");
			scanf("%s%d%d%s",
				result->data.name,
				&result->data.age,
				&result->data.num,
				result->data.tel);
			//%s ���׵�ַ��ʼ ��\0
			//������: ������׵�ַ
			//char array[10]; array: &array[0]
			printf("�޸ĳɹ���\n");
			//���浽�ļ�
			saveFile(list, "newMM.xls");
		}
		else
		{
			printf("δ�ҵ������Ϣ!�޷��޸�\n");
		}
		break;
	default:
		printf("�������!..����������\n");
		break;
	}
}
int main() 
{
	list = createHead();
	//���е�ʱ�����Ҫ���ļ�
	readFile(list, "newMM.xls");
	while (1) 
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");
	}
	return 0;
}