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
			//断开链表，要记录后续一个 fast-template
			LNode* temp = cur->next;
			//当前的next指向前一个
			cur->next = pre;
			//前一个更新为当前
			pre = cur;
			//当前更新为刚刚记录的后一个
			cur = temp;
		}
		return pre;
	}
};

//头插法
void add_LinkList(LNode*& pHeader)
{
	//头结点
	pHeader = (Linklist)malloc(sizeof(LNode));
	pHeader->next = NULL;
	LNode* newNode = NULL;
	printf("请输入你要输入的数据，输入0为结束\n");
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




//遍历链表
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
	//头插法初始化链表
	add_LinkList(pHeader);
	//遍历链表
	print_list(pHeader);

	Solution s;
	//不带头结点的翻转
	pHeader=s.reverseList(pHeader->next);
	//遍历链表
	print_list1(pHeader);
	return 0;
}