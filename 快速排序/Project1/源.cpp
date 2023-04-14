#define _CRT_SECURE_NO_WARNINGS 1
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>

typedef struct LNode {
	int data;
	struct LNode* next;
}Lnode, * Linklist;



void add_head_list(Linklist& newNode)
{
	newNode = NULL;
	newNode = (Linklist)malloc(sizeof(Lnode));
	newNode->next = NULL;
	int num = 0;
	scanf("%d", &num);
	newNode->data = num;

	while (scanf("%d", &num) != EOF)
	{
		Linklist p = (Linklist)malloc(sizeof(Lnode));
		p->data = num;
		p->next = newNode->next;
		newNode->next = p;
	}
}

void print(Linklist newNode)
{
	if (newNode == NULL)
	{
		printf(" \n");
		return;
	}
	while (newNode)
	{
		printf("%d ", newNode->data);
		newNode = newNode->next;
	}
}
int main()
{
	Linklist newNode = NULL;
	add_head_list(newNode);
	print(newNode);
	return 0;
}