#include <iostream>
using namespace std;
const int N = 1e5+20;
int n;
int a[N];
int main()
{
  // 请在此输入您的代码
  cin >> n ;
  for(int i = 0;i < n; ++ i) cin >> a[i];
  int l = 0,r = n-1;
  while(l < r && n --)
  {
    if(a[l] > a[r]) swap(a[l],a[r]);
    ++l,--r;
  }
  int flag = 0;
  for(int i=1;i<n;i++)
  {
    if(a[i] < a[i-1]) 
    {
      flag = 1;
      break; 
    }
  }
  cout<<(flag == 1 ? "NO" : "YES")<<endl;
  return 0;
}
