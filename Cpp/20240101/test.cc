#include <iostream>
#include <string>
#include <stdio.h>
#include <functional>
#include<vector>
using namespace std;

int dfs(vector<int>&a,int l,int r,int val);
void dfs(vector<int>&a,int val)
{
    int idx=dfs(a,0,a.size()-1,val);
    if(idx==-1)
    {
        cout<<"没找到"<<endl;
    }
    else
    {
        cout<<"找到了，下标为："<<idx<<endl;
    }
}

int dfs(vector<int>&a,int l,int r,int val)
{
    int mid = (l+r)/2;
    if(l>r) return -1;//递归结束条件
    if(a[mid]<val)
    {
        return dfs(a,mid+1,r,val);
    }
    else if(a[mid]==val)
    {
        return mid;
    }
    else
    {
        return dfs(a,l,mid-1,val);
    }
}
void test()
{
    vector<int>a;
    for(int i=0;i<10;++i)
    {
        a.push_back(i);
    }
    int val=3;
    dfs(a,val);
    for(auto &x:a)
    {
        cout<<x<<" ";
    }
    cout<<endl;
}
int main()
{
    test();
    return 0;
}

