#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
#define lc k<<1    //左孩子下标2k
#define rc k<<1|1  //右孩子下标2k+1
const int N=100010;
int a[N];
//线段树
struct node{
    int l,r,mx;//l,r表示区间左右端点，mx表示区间l,r的最值
}tre[4*N];

void build(int k,int l,int r)
{
    //创建线段树
    tre[k].l=l;
    tre[k].r=r;
    if(l==r)
    {
        //叶子节点
        tre[k].mx=a[l];
        return ;
    }
    int mid=(l + r)/2;
    build(lc,l,mid);//左子树
    build(rc,mid+1,r);//右子树
    tre[k].mx=max(tre[lc].mx,tre[rc].mx);//更新节点的最值
}

//点更新,将a[i]修改为v
void update(int k,int i,int v)
{   
    if(tre[k].l == tre[k].r && tre[k].l == i)
    {
        tre[k].mx=v;
        return;
    }
    int mid=(tre[k].l + tre[k].r) / 2;
    if(i <= mid) update(lc,i,v);
    else update(rc,i,v);
    tre[k].mx=max(tre[lc].mx,tre[rc].mx);//回归更新节点的最值
}
//区间查询
int query(int k,int l,int r)
{
    if(tre[k].l == l && tre[k].r == r) return tre[k].mx;
    int mid=(tre[k].l + tre[k].r) / 2;
    if(r <= mid) return query(lc,l,r);
    else if(l > mid) return query(rc,l,r);
    else return max(query(lc,l,r),query(rc,l,r));
}
int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    build(1,1,n);
    int ret=query(1,1,4);
    cout<<ret<<endl;
}
