#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


typedef struct List {
    int data;
    struct List* next;
}LNode, * LinkList;


void insert_list(LinkList& Pheader)
{
    Pheader = (LinkList)malloc(sizeof(LNode));
    Pheader->next = NULL;
    LinkList newList;
    int num = 0;
    for (int i = 0; i < 3; i++)
    {
        
        cin >> num;
        newList = (LinkList)malloc(sizeof(LNode));
        newList->data = num;
        newList->next = Pheader->next;
        Pheader->next = newList;
    }
}
void print_list(LinkList Pheader)
{
    LinkList p = Pheader->next;
    if (Pheader == NULL)
    {
        return;
    }
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }

}
int main()
{
    LinkList Pheader = NULL;
    //插入数据采用头插法
    insert_list(Pheader);
    //遍历链表
    print_list(Pheader);
    return 0;
}