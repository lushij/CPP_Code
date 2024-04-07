#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 500010;
int n, m, root;
vector<int> G[N];
ll fa[N], sz[N], son[N], top[N], dep[N];

void dfs1(int from)
{
	sz[from] = 1;
	dep[from] = dep[fa[from]] + 1;
	for (auto &to : G[from])
	{
		if (to != fa[from])
		{
			fa[to] = from;
			dfs1(to);
			sz[from] += sz[to];
			if (sz[to] > sz[son[from]])
				son[from] = to;
		}
	}
}

void dfs2(int from, int tp)
{
	//ÖØÁ´¶¥µã 
	top[from] = tp;
	if (son[from])
		dfs2(son[from], tp);
	for (auto &to : G[from])
	{
		if (to != fa[from] && to != son[from])
		{
			dfs2(to, to);
		}
	}
}

ll lca(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] > dep[top[y]])
			x = fa[top[x]];
		else
			y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

int main()
{
	cin >> n >> m >> root;
	for (int i = 1; i < n; i++)
	{
		ll from, to;
		cin >> from >> to;
		G[from].push_back(to);
		G[to].push_back(from);
	}
	dfs1(root);
	dfs2(root, root);
	while (m--)
	{
		int l, r;
		cin >> l >> r; 
		cout << lca(l, r) << endl;
	}
	return 0;
}

