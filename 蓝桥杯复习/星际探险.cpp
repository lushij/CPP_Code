#include<bits/stdc++.h>
using namespace std;
#define int long long
using namespace std;
const int  N  = 520;
int a[N];
int mod = 1e9+7;
int n;
vector<int>fa(300010);
struct Edge
{
  int a,b,w;

  bool operator > (const Edge & rhs) const
  {
    return w>rhs.w;
  }
};
vector<Edge>e(300010);
int find(int x)
{
  if(x != fa[x])
  {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}
int qmi(int a,int k,int p)
{
  int res = 1;
  while(k)
  {
    if(k&1) res = res * a %p;
    k>>=1;
    a=a*a%p;
  }
  return res;
}

int ret;
signed main()
{
  scanf("%lld",&n);
  for(int i=0;i<n;i++) scanf("%lld",&a[i]);
  for(int i=1;i<=n;i++) fa[i] = i;
  for(int i=0;i<n;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      int w = max(qmi(a[i],a[j],mod),qmi(a[j],a[i],mod));
      e.push_back({i,j,w});
    }
  }
  sort(e.begin(),e.end(),greater<Edge>());
  for(auto &v:e)
  {
      int a = v.a,b=v.b,w=v.w;
      a=find(a),b=find(b);
      if(a != b)
      {
        fa[a]=b;
        ret += w;
        ret %= mod;
      }
  }
  printf("%lld\n",ret);
  return 0;
}



