#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e7 + 20, MOD = 1e9 + 7;
int dp[N];
int n;
signed main()
{
	scanf("%lld",&n);
	dp[1] = 1, dp[2] = 2 , dp[3] = 5;
	for(int i = 4; i <= n; ++ i)
	{
		dp[i]=2*dp[i-1] + dp[i-3];
		dp[i]%=MOD;
	}
	printf("%lld ",dp[n]%MOD) ;
	return 0;
}
