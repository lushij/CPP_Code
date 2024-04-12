#incude <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5+20;
vectro<ll>g[N];//无向图，邻接表表示法
ll fa[N],sz[N],son[N],top[N],dep[N];//父节点  子树大小 重儿子(子树大的那一个节点) 重链的顶点 深度
int n,m,root;

void dfs1(int from)
{
	//子树大小，重儿子 深度 
	sz[from] = 1;//表示当前节点自身 
	//子节点的深度 = 父节点的深度 + 1 
	dep[from] = dep[fa[from]] + 1;
	for(auto &to :g[from]) 
	{
		//from -> to的对应节点
		if(to != fa[from]) 
		{
			//防止死循环
			fa[to] = from;
			dfs1(to);
			sz[from] += sz[to];
			if(sz[to] > sz[son[from]]) son[from] = to; 
		}
	}
	
}
//更新树链顶点
void dfs2(int from ,int tp)
{
	//son[from]表示from的儿子 
	top[from] = tp;//更新向上的重链顶点，在一条重链上继续更新 
	if(son[from]) dfs2(son[from],tp);//先dfs重儿子，重儿子的顶点都一样 
	for(auto &to : g[from])//再dfs轻边 
	{
		//from的父亲           from的儿子 
		if(to != fa[from] && to != son[from])
		{
			dfs2(to,to);
		}
	 } 
} 

int LCA(int x,int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] > dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x] < dep[y] ? x : y;
}
int main()
{
	cin >> n >> m >> root;
	for(int i=1; i<=n;i++)
	{
		int from,to;
		cin >> from >> to;
		g[from].push_back(to);
		g[to].push_back(from);//无向图 
	}
	dfs1(root);//根节点
	dfs2(root,root);
	 
} 
 
