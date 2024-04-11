#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n;

signed main()
{
	scanf("%lld",&n);
	while(n --)
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		double tmp = 1.0*x / 2;
    if(tmp <= y) cout<<"YES"<<endl;
    else cout<<"NO"<<endl; 
	}
	return 0; 
}

