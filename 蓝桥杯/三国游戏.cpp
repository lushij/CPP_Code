#include <bits/stdc++.h>
using namespace std;
//Ì°ÐÄ 
#define int long long
const int N = 1e5+10;
int a[N],b[N],c[N],w[N];
int n;

int work(int *x,int *y,int *z)
{
    int ret = -1;
    for(int i=0;i<n;i++)
    {
        w[i] = x[i] - y[i] -z[i];
    }
    sort(w,w+n,greater<int>());
    int sum = 0;
    for(int i=0;i<n;i++)
    {
        sum += w[i];
        if(sum > 0) ret = i + 1;
        else break;
    }
    return ret;
}
signed main()
{
    scanf("%lld",&n);
    for(int i=0;i<n;++i) scanf("%lld", &a[i]);
    for(int i=0;i<n;++i) scanf("%lld", &b[i]);
    for(int i=0;i<n;++i) scanf("%lld", &c[i]);
    
    cout<< max({work(a,b,c),work(b,c,a),work(c,a,b)});
    return 0;
}

