#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5+20;
int fa[N],son[N],dep[N],top[N],sz[N];

vector<int>g[N];
int n,m,root;

void dfs1(int u)
{
	sz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for(auto &v:g[u])
	{
		if(v != fa[u])
		{
			fa[v]= u;
			dfs1(v);
			sz[u] += sz[v];
			if(sz[v] > sz[son[u]]) son[u] = v;
		}
	}
}
void dfs2(int u,int tp)
{
	top[u] = tp;
	if(son[u]) dfs2(son[u],tp);
	for(auto &v:g[u])
		if(v != fa[u] && v!=son[u]) dfs2(v,v);
}

int lca(int x ,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] > dep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];  
	}
	return dep[x] < dep[y] ? x : y;
}

signed main()
{
	cin >> n >> m >> root;
	for(int i = 1; i < n ; ++ i)
	{
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(root);
	dfs2(root,root);
	while(m -- )
	{
		int x,y;
		cin >> x >> y;
		cout<<lca(x,y)<<endl;
	}
	return 0;
}
