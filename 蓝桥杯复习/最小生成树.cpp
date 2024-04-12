#include<bits/stdc++.h>
using namespace std;
//��С�������� ��Ȩ��ͨ����ͼ�У�������������Ȩֵ֮����С�������� 
#define int long long
const int N = 200001;
int fa[2*N];
int n,m;
int ans;
struct Edge
{
	int a,b,w;
	bool operator< (const Edge & W) const 
	{
		return w < W.w;
	}
}e[N];

int find(int x)
{
	if(x != fa[x])
	{
		fa[x] = find(fa[x]);
	}
	return fa[x];
}
signed main()
{
	cin >> n >> m;
	int cnt = 0;
	for(int i=1;i<=n;i++) fa[i] = i;
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		e[i] = {a,b,c}; 
	}
	sort(e,e+m);
	for(int i=0;i<m;i++)
	{
		int a = e[i].a,b = e[i].b,w = e[i].w;
		a= find(a),b = find(b);
		if(a != b) 
		{
			fa[a]=b;
			ans += w;
			cnt++;//������ǵ�ǰ�ߵ����� 
		}
	}
	if(cnt < n- 1) puts("orz");//������С�ڵ���-1����ʾ����ͨ ����Ϊ������ == ����-1���ǹ�����С������ 
	else cout<<ans<<endl;
	return 0;
} 
