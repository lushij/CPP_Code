#incude <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5+20;
vectro<ll>g[N];//����ͼ���ڽӱ��ʾ��
ll fa[N],sz[N],son[N],top[N],dep[N];//���ڵ�  ������С �ض���(���������һ���ڵ�) �����Ķ��� ���
int n,m,root;

void dfs1(int from)
{
	//������С���ض��� ��� 
	sz[from] = 1;//��ʾ��ǰ�ڵ����� 
	//�ӽڵ����� = ���ڵ����� + 1 
	dep[from] = dep[fa[from]] + 1;
	for(auto &to :g[from]) 
	{
		//from -> to�Ķ�Ӧ�ڵ�
		if(to != fa[from]) 
		{
			//��ֹ��ѭ��
			fa[to] = from;
			dfs1(to);
			sz[from] += sz[to];
			if(sz[to] > sz[son[from]]) son[from] = to; 
		}
	}
	
}
//������������
void dfs2(int from ,int tp)
{
	//son[from]��ʾfrom�Ķ��� 
	top[from] = tp;//�������ϵ��������㣬��һ�������ϼ������� 
	if(son[from]) dfs2(son[from],tp);//��dfs�ض��ӣ��ض��ӵĶ��㶼һ�� 
	for(auto &to : g[from])//��dfs��� 
	{
		//from�ĸ���           from�Ķ��� 
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
		g[to].push_back(from);//����ͼ 
	}
	dfs1(root);//���ڵ�
	dfs2(root,root);
	 
} 
 
