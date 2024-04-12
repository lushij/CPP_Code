#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,k,p;
//快速幂模板 
//结果就是a^k%p 
int qmi(int a,int k,int p)
{
	int res = 1;
	while(k)
	{
		if(k & 1) res = res * a % p;
		k >>= 1;//用过的就右移出去 
		a = a * a % p; 
	}
	return res;
}
signed main()
{
	char s[256]={0};
	scanf("%lld%lld%lld",&a,&k,&p);
	sprintf(s,"%lld^%lld mod %lld=%lld",a,k,p,qmi(a,k,p));
	cout<<s<<endl;
	return 0;
 } 
