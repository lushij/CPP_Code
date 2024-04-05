#include<bits/stdc++.h>
using namespace std;

const int N = 50;
int d[N],a[N];
int n,m;
int main()
{
	cin >> n >> m;
	for(int i = 1 ; i <= n; i++)
	{
		cin >> a[i];
		//版本一，把原数组当做一个一次插入的数据 
		d[i]+=a[i];
		d[i+1]-=a[i];
	}
	
	while( m -- )
	{
		int l,r,v;
		cin >> l >> r >> v;
		d[l]+=v;
		d[r+1]-=v;	
	}	
	for(int i=1;i<=n;i++)
	{
		d[i]+=d[i-1];
		cout << d[i]<<" ";
	}
	puts(""); 
	
	return 0; 
}
