#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<map>
#include<set>
#include<vector>

using std::endl;
using std::cin;
using std::cout;
using std::map;
using std::set;
using std::string;
using std::vector;


class TextQuery
{
public:
    //构造函数要初始化内存大小
    TextQuery();
    void readFile(const string &filename);
    void query(const string &word);
    ~TextQuery();

private:
    void preDealWord(string&line);
private:
    vector<string>_eachLine;//每一行句子
    map<string,int>_wordFrequency;//词频
    map<string,set<int>>_lineNumber;//出现的行数
};

