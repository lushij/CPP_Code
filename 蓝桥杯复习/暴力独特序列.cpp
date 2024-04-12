#include <bits/stdc++.h>
#define int long long 
using namespace std;
int mod = 1e9 + 7;
const int N = 1e5+20;
int a[N];
int  n;
int ret;
bool check[N];

void dfs(int pos)
{
  for(int i = pos + 1 ;i < n; ++ i)
  {
    if(a[i] != a[pos])
    {
      dfs(i);
    }
  }
  ret++;
  ret %= mod;
}
signed main()
{
  cin >> n;
  for(int i = 0;i < n; ++ i) cin >> a[i];
  sort(a,a+n);
  for(int i = 0;i < n;++ i)
  {
    dfs(i);
  }
  cout<<ret%mod<<endl;
  return 0;
}
