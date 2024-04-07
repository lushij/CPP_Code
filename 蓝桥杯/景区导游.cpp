#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+20;
typedef pair<int,int> PII;
vector<PII>g[N];
int fa[N],sz[N],top[N],son[N],dep[N];
int a[N],dis[N];
int n,m;

void dfs1(int u)
{
	sz[u]=1;
	dep[u] = dep[fa[u]] + 1;
	for(auto &val:g[u])
	{
		int v=val.first;
		if(v != fa[u])
		{
			fa[v] = u;
			dfs1(v);
			sz[u] += sz[v];
			if(sz[v] > sz[son[u]]) son[u] = v;
		}
	}
}

void dfs2(int u, int tp)
{
	top[u] = tp;
	if(son[u])
	{
		dfs2(son[u],tp);
	}
	for(auto &val:g[u])
	{
		int v = val.first;
		if(v != fa[u] && v != son[u])
		{
			dfs2(v,v);
		}
	}
}

int lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] > dep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

//图的前缀和 
void calSum(int u)
{
	for(int i=0;i < g[u].size();++i)
	{
		int n = g[u][i].first;
		if(n != fa[u])
		{
		    int w = g[u][i].second;
		    dis[n] = dis[u] + w;
		  //  printf("dis[%lld] = dis[%lld] + %lld = %lld ,dis[%lld] = %lld\n",n,u,w,dis[n],u,dis[u]);
			calSum(n);
		}
	}
}

int path(int x,int y)
{
	if(!x || !y) return 0;
	return dis[x] + dis[y] - 2*dis[lca(x,y)]; 
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i = 1; i < n; i++)
	{
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	dfs1(1);dfs2(1,1);calSum(1);
// 	for(int i=1;i<=2*m;i++) 
// 	{
// 	    if(fa[i] != 0) 
// 	        printf("fa[%lld] = %lld\n",i,fa[i]);
// 	}
//  	for(int i = 1;i <=n;++i) cout<<dis[i]<<' ';
// 	puts("");
	int ans = 0;
	for(int i=1;i <= m; ++ i)
	{
		scanf("%lld",&a[i]);
// 		cout<<path(a[i-1],a[i])<<endl;
		ans += path(a[i-1],a[i]);//总路径的和 
	} 
// 	cout << ans<<endl;
	for(int i=1;i<=m;i++)
	{
		int tmp = ans;
		if(i == 1)	printf("%lld ",ans - path(a[i],a[i+1]));
		else if(i == m) printf("%lld ",ans - path(a[i-1],a[i]));
		else printf("%lld ",ans - path(a[i-1],a[i]) - path(a[i],a[i+1]) + path(a[i-1],a[i+1]));
	} 
	return 0;
}
