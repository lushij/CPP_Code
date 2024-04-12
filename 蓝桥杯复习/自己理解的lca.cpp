#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5+20;
typedef pair<ll,ll> PLL;
vector<int>g[N];
ll fa[N],son[N],sz[N],top[N],dep[N];


int n, m, root;

void dfs1(int u)
{
	//sz fa son dep
	sz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for(auto &v : g[u])
	{
		if(v != fa[u])
		{
			fa[v] = u;
			dfs1(v);
			sz[u] += sz[v];
			if(sz[v] > sz[son[u]])
				son[u] = v;
		}
	}
}

void dfs2(int u ,int tp)
{
	top[u] = tp;
	//ÏÈÖØºóÇá
	if(son[u])
		dfs2(son[u],tp);
	for(auto &v:g[u])
	{
		if(v != fa[u] && v != son[u])
		{
			dfs2(v,v);
		}
	 } 
}

ll lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] > dep[top[y]])
			x = fa[top[x]];
		else
			y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

int main()
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
