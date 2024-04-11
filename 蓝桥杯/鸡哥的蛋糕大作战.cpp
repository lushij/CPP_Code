#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int>PII;
set<PII>st;
int n,m;
int mx = INT_MIN;
int main()
{
  cin >> n >> m;
  for(int i=n;i<=m;i++)
  {
    string s = to_string(i);
    int cnt=0;
    for(auto &ch :s)
    {
      if(ch == '0' || ch == '6' || ch == '9') cnt++;
      if(ch == '8') cnt += 2; 
    }
    mx = max(mx,cnt);
    st.insert({mx,i});
  }
  for(auto &v:st)
  {
    if(v.first == mx)
    { cout<<v.second<<endl;
      break;
    }
  }

  return 0;
}
