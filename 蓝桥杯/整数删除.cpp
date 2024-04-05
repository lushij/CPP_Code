#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct _st
{
  ll v;
  int idx;
  bool operator<(const _st & rhs) const
  {
      return v==rhs.v?idx<rhs.idx:v<rhs.v;
  }
};
const int N = 5e5+20;
ll nums[N];
int n,k;
int l[N],r[N];
set<_st>st;

int main()
{
    memset(l, -1, sizeof l);
    memset(r, -1, sizeof l);
    cin >> n >> k;
    for(int i=1;i<=n;i++)
    {
        cin >> nums[i];
        st.insert({nums[i],i});
        l[i]=i-1;
        r[i]=i+1;
    }
    while (k)
    {
        ll t = st.begin()->v;
        int pos = st.begin()->idx;//数组中的下标
       // cout<<"t = "<<t<<" pos = "<<pos<<endl;
        st.erase(st.begin());
        if(nums[pos] != t) continue;//表示这个数据已经过时
        else k--;
        if(l[pos] > 0)
        {
            nums[l[pos]]+=t;
            st.insert({nums[l[pos]],l[pos]});
        }
        if(r[pos] <= n)
        {
            nums[r[pos]]+=t;
            st.insert({nums[r[pos]],r[pos]});
        }
        l[r[pos]]=l[pos];
        r[l[pos]]=r[pos];
        l[pos]=r[pos]=-1;
    }
    for(int i=1;i<=n;i++)
    {
      if(r[i] != -1 && l[i] != -1) 
         cout<<nums[i]<<" ";
    }
    return 0;
}

