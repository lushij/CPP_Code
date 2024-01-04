#include <iostream>
#include <string>
#include <stdio.h>
#include<vector>
#include<set>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

class Read
{
public:
    Read(string filename)
        :_filename(filename)
         ,_dict()
         ,_lineNum()
         ,_lines()
         ,_cnt(0)
    {
        _lines.push_back(string());
    }
    void readFile()
    {
        ifstream ifs(_filename);
        if(!ifs)
        {
            cerr<<"open fail "<<_filename<<endl;
            return;
        }
        string line;
        while(getline(ifs,line))
        {
            _lines.push_back(line);
            ++_cnt;//行数
            string word;
            if(line!=string())
            {

                istringstream iss(line);
                while(iss>>word)
                {
                    //处理问题
                    string newWord=dealWord(word);
                    if(newWord!=string())
                    {
                        //在处理
                        pushDeal(newWord);
                    }
                }
            }
        }

        ifs.close();
    }
    string dealWord(string old) const
    {
        for(size_t idx=0;idx!=old.size();++idx)
        {
            if(!isalpha(old[idx]))//既不是字母
            {
                return string();
            }
        }
        return old;
    }
    void pushDeal(string newWord)
    {
        ++ _dict[newWord];//更新词频
        _lineNum[newWord].insert(_cnt);//某单词出现的行数
    }

    void show(string words)
    {
        if(_dict[words]==0)
        {
            cout<<"未找到"<<endl;
        }
        else
        {
            cout<<words<<" occurs "<<_dict[words]<<" times."<<endl;
            printLine(words);
        }
    }
    void printLine(string& word)const
    {
        auto it=_lineNum.find(word);
        if (it != _lineNum.end())
        {
            for(auto &idx:it->second)
            {
                cout<<"( line "<<idx<<")"<<_lines[idx]<<endl;
            }
        }
    }
    ~Read()
    {

    }
private:
    string _filename;
    unordered_map <string,int>_dict;//词频统计
    map<string,set<int>>_lineNum;//出现的行数
    vector<string>_lines;
    int _cnt;//行数
};

void cinInfo(string & filename)
{
    /* cout<<"请输入你要查阅的文件名称>>"; */
    while(cin>>filename,!cin.eof())
    {
        if(cin.bad())
        {
            cout<<"cin is bad"<<endl;
            return;
        }
        else if(cin.fail())
        {
            cin.clear();
            //返回 std::streamsize 类型的最大值
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"请重新输入>>";
        }
        else
        {
            break;
        }
    }
}


void test()
{
    string filename="china_daily.txt";
    Read r1(filename);
    r1.readFile();
    while(1)
    {
        cout<<"请输入你要查找的单词>>";
        string name;
        cinInfo(name);
        r1.show(name);
    }
}
int main()
{
    test();
    return 0;
}

