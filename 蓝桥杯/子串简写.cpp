#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
int k;
string str;
char st,ed;
int main()
{
	ll cnt = 0;
	ll ret = 0;
	scanf("%d",&k);
	cin >> str >> st >> ed;
	ll l=0,r=k-1;
	int n=str.size();
	while(r<=n)
	{
		if(str[l] == st) cnt ++;
		if(str[r] == ed) ret+=cnt;
		l++;
		r++; 
	}
	cout<<ret<<endl;
}
