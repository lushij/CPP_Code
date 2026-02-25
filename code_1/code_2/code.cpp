#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>


using namespace std;


int n, p, m;
int main()
{	
	while (cin >> n >> p >> m)
	{
		queue<int>q;
		queue<int>res;
		if (n == 0 && p == 0 && m == 0)break;
		int i = 1;
		for (i; i <= n; ++i)
		{
			q.push(i);
		}
		int cnt = 0;
		int num = 0;
		while (!q.empty())
		{
			++cnt;
			if (cnt < p)
			{
				int tmp = q.front();
				q.pop();
				q.push(tmp);
			}
			if (cnt >= p)
			{
				++num;
				if (num == m)
				{
					res.push(q.front());
					q.pop();
					num = 0;
				}
				else
				{
					int tmp = q.front();
					q.pop();
					q.push(tmp);
				}
			}	
		}
		// 输出结果：逗号分隔，最后一个无逗号
		while (!res.empty()) {
			cout << res.front();
			res.pop();
			if (!res.empty()) cout << ",";
		}
		cout << endl;
	
	}
	return 0;
}