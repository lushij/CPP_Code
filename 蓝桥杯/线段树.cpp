#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
#define lc k<<1    //�����±�2k
#define rc k<<1|1  //�Һ����±�2k+1
const int N=100010;
int a[N];
//�߶���
struct node{
    int l,r,mx;//l,r��ʾ�������Ҷ˵㣬mx��ʾ����l,r����ֵ
}tre[4*N];

void build(int k,int l,int r)
{
    //�����߶���
    tre[k].l=l;
    tre[k].r=r;
    if(l==r)
    {
        //Ҷ�ӽڵ�
        tre[k].mx=a[l];
        return ;
    }
    int mid=(l + r)/2;
    build(lc,l,mid);//������
    build(rc,mid+1,r);//������
    tre[k].mx=max(tre[lc].mx,tre[rc].mx);//���½ڵ����ֵ
}

//�����,��a[i]�޸�Ϊv
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
    tre[k].mx=max(tre[lc].mx,tre[rc].mx);//�ع���½ڵ����ֵ
}
//�����ѯ
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
