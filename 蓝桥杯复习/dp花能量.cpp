#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+20;
int n;
int a[N],dp[N];
int mx = INT_MIN;
int main()
{
  // 请在此输入您的代码
  cin >> n ;
  for(int i=0;i<n;i++) 
    cin >> a[i],dp[i]=a[i];
  for(int i = 1; i < n;++ i)
  {
    for(int j = 0;j < i; ++ j)
    {
      if(a[i] > a[j])
      {
        dp[i] = max(dp[j] + a[i],dp[i]);
      }
    }
    mx = max (mx,dp[i]);
  }
  cout<<mx<<endl;
  return 0;
}
