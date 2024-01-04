#include <iostream>
#include <string>
#include <stdio.h>
#include<set>
#include<map>
using namespace std;

void test()
{
    //map(Key,Value)
    // //map的特征
    //1、map中的元素，key值是唯一的，不能重复，但是value可以相同
    //2、默认情况下，会按照key值升序排列
    //3、map的底层实现也是红黑树
    //
    //
    //set的基本特征
    //1、set里面的元素是唯一的，不能重复
    //2、默认情况下，set中的元素会按照升序排列
    //3、set的底层实现使用是红黑树
    //
    map<string,set<int>>data;
    data["a"].insert(1);
    data["a"].insert(2);
    data["b"].insert(1);
    data["c"].insert(1);
    data["d"].insert(1);
    auto it = data.find("a");
    if(it != data.end())
    {
        cout<<it->first <<endl;
        for(auto &x:it->second)
        {
            cout<<x<<endl;
        }
    }

}
void test1()
{
     //map的特征
    //1、map中的元素，key值是唯一的，不能重复，但是value可以相同
    //2、默认情况下，会按照key值升序排列
    //3、map的底层实现也是红黑树
    map<string,int>data;
    data.insert({"a",1});
    data.insert({"a",2});
    data.insert({"c",1});
    for(auto &x:data)
    {
        cout<<x.first<<x.second<<endl;
        //$ ./a.out 
        // a1
        // c1
        // 
        
    }
}
void test2()
{
    set<int>nums={1,2,3,2,3,5};
    for(auto &x:nums)
    {
        cout<<x<<endl;
    }
}
int main()
{
    test2();
    return 0;
}

