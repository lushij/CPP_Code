#include <iostream>
using namespace std;

void getNext(int *next,const string &s)
{
  next[0]=0;
  int j=0;
  for(int i=1;i<s.size();i++)
  {
    while(j > 0 && s[i] != s[j])
    {
      j=next[j-1];
    }
    if(s[i] == s[j]) j++;
    next[i]=j;
  }
}
int main()
{
  // 请在此输入您的代码
  //s1模式串
  //s2文本串
  string s1,s2;
  cin>>s1>>s2;
  int len=s1.size();
  if(len == 0) 
  {
    cout<<0<<endl;
    return 0;
  }
  int next[len];
  int ret=0;
  getNext(next,s1);
  int j=0;
  for(int i=0;i<s2.size();i++)
  {
    while(j > 0 && s2[i] != s1[j])
    {
      j=next[j-1];
    }
    if(s2[i] == s1[j]) j++;
    if(j == len ) ret++;
  }
  cout<<ret<<endl;
  return 0;
}
