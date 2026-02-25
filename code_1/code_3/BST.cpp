#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

struct Tree {
    int data;
    Tree* lc;
    Tree* rc;
};

void InsertBst(Tree*& root, int data)
{
    Tree* p = new Tree;
    p->data = data;
    p->lc = NULL;
    p->rc = NULL;
    if (root == NULL)
    {
        root = p;
        printf("-1\n");
        return;
    }

    Tree* pre = NULL;
    Tree* cur = root;
    while (cur)
    {
        if (cur->data > data)
        {
            //×ó×ÓÊ÷
            pre = cur;
            cur = cur->lc;
            if (cur == NULL)
            {
                pre->lc = p;
                printf("%d\n", pre->data);
                break;
            }
        }
        else
        {
            //ÓÒ×ÓÊ÷
            pre = cur;
            cur = cur->rc;
            if (cur == NULL)
            {
                pre->rc = p;
                printf("%d\n", pre->data);
                break;
            }
        }


    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    Tree* root = NULL;
    for (int i = 0; i < n; ++i)
    {
        int m;
        scanf("%d", &m);
        // printf("%d\n",m);
        InsertBst(root, m);
    }
    return 0;
}

