#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+20;
int n;
int a[N];
int mx = INT_MIN;
void dfs(int pos,int ret)
{
 
  for(int i = pos + 1;i<=n;i++)
  {
    if(a[i] > a[pos])
    {
      dfs(i,ret+a[i]);
    }
  }
  mx = max(ret,mx);
}
int main()
{
  // 请在此输入您的代码
  cin >> n ;
  //暴力
  for(int i=1;i<=n;i++) cin >> a[i];
  for(int i=1;i<=n;i++)
  {
    dfs(i,a[i]);
  }
  cout<<mx<<endl;
  return 0;
}
