#include <iostream>
#include <string>
#include <stdio.h>
#include<unordered_map>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

bool cmp(const pair<string,int>&a,const pair<string,int>&b)
{
    return a.second>b.second;
}

void test()
{
    vector<pair<string,int>>vps;
    vps.push_back(make_pair("word",1));
    vps.push_back(make_pair("word",2));
    vps.push_back(make_pair("word",3));
    vps.push_back(make_pair("word",4));
    vps.push_back(make_pair("word",5));
    vps.push_back(make_pair("word",6));
    vps.push_back(make_pair("word",7));
    //1.自定义比较函数
    //sort(vps.begin(),vps.end(),cmp);//和下面的完全等价，下面的是标准库里的
    //2.运用标准库的降序和升序函数，参数改一下即可
    //sort(vps.begin(), vps.end(), greater<pair<string, int>>());
    //3.运用 lambda 表达式
    sort(vps.begin(), vps.end()
                 ,[](const pair<string,int>&a,const pair<string,int>&b)
                    { return a.second>b.second;}
         );
    
    for(auto &x:vps)
    {
        cout<<x.first<<"\t"<<x.second<<endl;
    }
}
int main()
{
    test();
    return 0;
}

