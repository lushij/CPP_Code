#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6;
int fa[N];
int n,m;

struct Edge
{
	int a, b,w;
	bool operator<(const Edge & rhs) const
	{
		return w < rhs.w;
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
	int ret = 0,cnt = 0;
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<m;i++)
	{
		int a,b,w;
		scanf("%lld%lld%lld",&a,&b,&w);
		e[i]={a,b,w};
	}
	sort(e,e+m);
	for(int i=1;i <= n;i++) fa[i] = i;
	for(int i=0;i<m;i++)
	{
		int a = e[i].a,b=e[i].b,w=e[i].w;
		a = find(a),b = find(b);
		if(a != b)
		{
			fa[a] = b;
			ret += w;
			cnt++;
		}
	}
	if(cnt < n-1) puts("orz");
	else cout<<ret<<endl;
	return 0;
}
