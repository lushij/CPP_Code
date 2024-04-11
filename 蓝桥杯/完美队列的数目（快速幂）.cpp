#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+20;
int n,m;
int a[N];
int MOD = 1e9 + 7;

int quickPow(int a,int q)
{
  int res=1;
  while(q)
  {
    if(q&1)
    {
      res=res*a%MOD;
    }
    q>>=1;
    a=a*a%MOD;
  }
  return res;
}
signed main()
{
  int ret = 0;
  scanf("%lld%lld",&n,&m);
  for(int i=0;i<n;i++) scanf("%lld",&a[i]);
  sort(a,a+n);
  int l = 0,r = n - 1;
  while(l <= r)
  {
    if(a[l] + a[r] <= m)
    {
      ret = (ret + quickPow(2,r - l)) ;
      ret %=MOD;
      l++;
    }
    else
    {
      r--;
    }
  } 
  cout<<ret<<endl;

  return 0;
}
