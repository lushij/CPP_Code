#include <bits/stdc++.h>
using namespace std;
const  int N = 1e5+20;
vector<int>dp(15);//Ö»¹ØÐÄ£¨0~9£©
int n;
int main()
{
  cin >> n;
  int ret=0;
  for(int i=1;i<=n;++i)
  {
    string str;
    cin >> str;
    int len = str.size();
    int x=str[0]-'0';
    int y=str[len - 1] - '0';
    dp[y]=max(dp[x]+1,dp[y]);
    ret=max(ret,dp[y]);
  }
  cout<<n-ret<<endl;
  return 0;
}
