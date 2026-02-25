#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include<algorithm>
using namespace std;

struct Tree {
	char c;
	Tree* lc;
	Tree* rc;
};

void insert(Tree* &root,string &s)
{

	for (auto& ch : s)
	{
		Tree* pre = NULL;
		Tree* cur = root;
		Tree* p = new Tree;
		p->c = ch;
		p->lc = NULL;
		p->rc = NULL;
		if (root == NULL)
		{
			root = p;
		}
		else
		{
			while (cur)
			{
				if (cur->c > ch)
				{
					pre = cur;
					cur = cur->lc;
					if (cur == NULL)
					{
						pre->lc = p;
					}
				}
				else
				{
					pre = cur;
					cur = cur->rc;
					if (cur == NULL)
					{
						pre->rc = p;
					}
				}
			}
		}
	}
}

string inprint(Tree*& r)
{
	if (r)
	{
		return r->c + inprint(r->lc) + inprint(r->rc);
	}
	else
	{
		return "";
	}
}
string ordprint(Tree*& r)
{
	if (r)
	{
		return ordprint(r->lc) + r->c + ordprint(r->rc);
	}
	else
	{
		return "";
	}
}

int main() 
{
	int n;
	// 【重点修改 1】处理多组测试用例，遇到 n=0 结束
	while (cin >> n && n != 0)
	{
		string base_s;
		cin >> base_s; // 【重点修改 2】先读取一个“基准序列”

		// 构造基准树并获取它的遍历结果
		Tree* base_root = NULL;
		insert(base_root, base_s);
		string base_pre = inprint(base_root);
		string base_in = ordprint(base_root);

		// 【重点修改 3】接下来的 n 行，每一个都与基准树进行比较
		for (int i = 0; i < n; ++i)
		{
			string test_s;
			cin >> test_s;

			Tree* test_root = NULL;
			insert(test_root, test_s);

			string test_pre = inprint(test_root);
			string test_in = ordprint(test_root);

			if (base_pre == test_pre && base_in == test_in)
			{
				printf("YES\n");
			}
			else
			{
				printf("NO\n");
			}
		}
	}
	return 0;
}
