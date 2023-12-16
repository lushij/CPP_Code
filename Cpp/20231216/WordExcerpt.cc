#include <iostream>
#include <string>
#include <stdio.h>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
//map版本单词统计器
using namespace std;

class Direct
{
public:
    void readFile(const string filename)
    {
        ifstream ifs(filename); 
        if(!ifs)
        {
            cerr<<"open"<<filename<<"faile"<<endl;
            return;
        }
        string line;
        while(getline(ifs,line))//按行读取
        {
            istringstream iss(line);
            string word;
            while(iss>>word)
            {
                string newWord=dealWord(word);
                insert(newWord);
            }
        }
        ifs.close();
    }
    void saveData(const string&filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr<<"open"<<filename<<"fail"<<endl;
            return;
        }
#if 0
        //第一个版本（无序）
        for(auto &x:_wordInfo)
        {
            ofs<<x.first<<"\t"<<x.second<<endl;
        }
#endif
#if 0
       //第二个版本（有序(字典序)）
       vector<pair<string,int>>sortWord(_wordInfo.begin(),_wordInfo.end());
       sort(sortWord.begin(),sortWord.end());
       for(auto &x:sortWord)
       {
           ofs<<x.first<<"\t"<<x.second<<endl;
       }
#endif
#if 0
       vector<pair<string,int>>sortWord(_wordInfo.begin(),_wordInfo.end());
       sort(sortWord.begin(),sortWord.end()
             ,[](const auto &a,const auto &b)//lambda 表达式
                 {
                    return a.second>b.second;
                 }  
            );//按照词频来排序（大-->小）

       for(auto &x:sortWord)
       {
           ofs<<x.first<<"\t"<<x.second<<endl;
       }
#endif
#if 1
       vector<pair<string,int>>sortWord(_wordInfo.begin(),_wordInfo.end());
       sort(sortWord.begin(),sortWord.end());
       for(auto &x:sortWord)
       {
           ofs<<x.first<<"\t"<<x.second<<endl;
       }
#endif


       ofs.close();
    }
    string dealWord(const string &word)
    {
        for(size_t idx=0;idx!=word.size();++idx)
        {
            if(!isalpha(word[idx]))
            {
                return string();
            }
        }
        return word;
    }
    void insert(const string &word)
    {
        //判断是否为空单词串
        if(word!=string())
        {
           ++_wordInfo[word];
        }
    }
    
private:
    unordered_map<string,int>_wordInfo;
};
void test()
{
    Direct dict;
    dict.readFile("The_Holy_Bible.txt");
    dict.saveData("data.txt");
}
int main()
{
    test();
    return 0;
}

