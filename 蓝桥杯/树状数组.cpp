//Ê÷×´Êý×é
#include<iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int,int>mp;
const int N = 5*1e5;
int tr[N],nums[N];
int mx,n;

int lowbit(int i) 
{
    return i & -i;
}
void add(int i,int v)
{
    for(;i<mx;i+=lowbit(i)) tr[i]+=v;
}
int query(int i)
{
    int ret = 0;
    for(;i>0;i-=lowbit(i)) ret+=tr[i];
    return ret;
}
int main()
{
    cin >> n;
    int ret=0;
    for(int i=0;i<n;i++) cin >> nums[i];
    vector<int>bk(nums,nums+n);
    sort(bk.begin(),bk.end());
    bk.erase(unique(bk.begin(),bk.end()),bk.end());
    int len = bk.size();
    mx = bk[len-1]+10;
    for(int i=0;i<len;i++) mp[bk[i]]=i+1; 
    for(int i=n-1;i>=0;i--)
    {
        ret += query(mp[nums[i]] - 1);
        add(mp[nums[i]],1);
    }
    cout<<ret<<endl;
    return 0;
}
