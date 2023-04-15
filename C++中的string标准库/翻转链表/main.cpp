#define _CRT_SECURE_NO_WARNINGS 1
#include<cstdio>
#include<cstdlib>
#include<iostream>
typedef struct Lnode {
	int data;
	struct Lnode* next;
}LNode, * Linklist;

class Solution {
public:
	LNode* reverseList(LNode* pHead) {
		if (pHead == NULL)
			return NULL;
		LNode* cur = pHead;
		LNode* pre = NULL;
		while (cur != NULL) {
			//�Ͽ�����Ҫ��¼����һ�� fast-template
			LNode* temp = cur->next;
			//��ǰ��nextָ��ǰһ��
			cur->next = pre;
			//ǰһ������Ϊ��ǰ
			pre = cur;
			//��ǰ����Ϊ�ոռ�¼�ĺ�һ��
			cur = temp;
		}
		return pre;
	}
};

//ͷ�巨
void add_LinkList(LNode*& pHeader)
{
	//ͷ���
	pHeader = (Linklist)malloc(sizeof(LNode));
	pHeader->next = NULL;
	LNode* newNode = NULL;
	printf("��������Ҫ��������ݣ�����0Ϊ����\n");
	int num = 0;
	scanf("%d", &num);
	while (num)
	{
		newNode = (Linklist)malloc(sizeof(LNode));
		newNode->data = num;
		newNode->next = pHeader->next;
		pHeader->next = newNode;
		scanf("%d", &num);
	}
}




//��������
void print_list(LNode* pHeader)
{
	pHeader = pHeader->next;
	while (pHeader)
	{
		printf("%d ", pHeader->data);
		pHeader = pHeader->next;
	}
	printf("\n");
}

void print_list1(LNode* pHeader)
{
	while (pHeader)
	{
		printf("%d ", pHeader->data);
		pHeader = pHeader->next;
	}
	printf("\n");
}

int main()
{
	LNode* pHeader = NULL;
	//ͷ�巨��ʼ������
	add_LinkList(pHeader);
	//��������
	print_list(pHeader);

	Solution s;
	//����ͷ���ķ�ת
	pHeader=s.reverseList(pHeader->next);
	//��������
	print_list1(pHeader);
	return 0;
}