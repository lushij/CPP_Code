#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::shared_ptr;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::ifstream;
using std::istringstream;

class QueryResult;


class TextQuery
{
public:
    using line_no = vector<string>::size_type;//C++11
    /* typedef vector<string>::size_type line_no;//C++98 */

    TextQuery(ifstream &ifs);
    QueryResult query(const string &sought) const;

private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};


class QueryResult
{
public:
    using line_no = vector<string>::size_type;
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f)
    : sought(s)
    , lines(p)
    , file(f)
    {

    }

    /* friend std::ostream &print(std::ostream &os, const QueryResult &rhs); */
    friend std::ostream &operator<<(std::ostream &os, const QueryResult &rhs);
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};
TextQuery::TextQuery(ifstream &ifs)
: file(new vector<string>())
{
    string text;
    while(getline(ifs, text)) //获取每一行
    {
        file->push_back(text);//保存此文本
        int n = file->size() - 1;//当前行号

        istringstream iss(text);
        string word;
        while(iss >> word)
        {
            //如果单词不在wm中，以之为下标在wm中添加一项
            auto &lines = wm[word];//lines是一个shared_ptr
            if(!lines)
            {
                lines.reset(new set<line_no>());//分配一个新的set
            }
            lines->insert(n);//将此行号插入set中
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    //如果没有找到sought，返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>());

    //使用find而不是下标运算符来查找单词，避免将单词添加到wm中
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);//没有找到
    }
    else
    {
        return QueryResult(sought, loc->second, file);
    }

}
/* std::ostream &print(std::ostream &os, const QueryResult &rhs) */
std::ostream &operator<<(std::ostream &os, const QueryResult &rhs)
{
    os << rhs.sought << " occurs " << rhs.lines->size() << "  "
       << ((rhs.lines->size() > 1) ? "times" : "time")   << endl;

    for(auto num : *rhs.lines)
    {
        os << "\t(line " << num + 1 << ") "
           << *(rhs.file->begin() + num ) << endl;
    }

    return os;
}

void runQueries(ifstream &infile)
{
    TextQuery tq(infile);

    while(1)
    {
        cout << "enter word to look for, or q to quit:";

        string s;
        if(!(cin >> s) || s == "q")
            break;
        /* print(cout, tq.query(s)) << endl; */
        /* print(cout, tq.query(s)) << endl; */
        cout << tq.query(s) << endl;
    }
}
int main(int argc, char **argv)
{
    ifstream ifs("china_daily.txt");
    runQueries(ifs);
    return 0;
}

