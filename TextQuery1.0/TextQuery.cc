#include"TextQuery.h"

TextQuery::TextQuery() 
{
    //vector在不知道大小的情况下，先初始化大小，防止过度占用资源
    _eachLine.reserve(1000);
}
void TextQuery::readFile(const string &filename)
{
    std::ifstream ifs(filename);
    if(!ifs)
    {
        std::cerr<<"ifs "<<filename<<"failed"<<endl;
        return;
    }
    string line;
    int lineNumber=0;//存行数
    while(getline(ifs,line))
    {
        //读一行存一行原始的数据到vector
        _eachLine.push_back(line);
        preDealWord(line);
        std::istringstream iss(line);
        string word;
        while(iss>>word)
        {
            ++_wordFrequency[word];
            _lineNumber[word].insert(lineNumber);
        }
        ++lineNumber;//行数继续更新
    }
    ifs.close();
}
void TextQuery::query(const string &word)
{
    int cnt=_wordFrequency[word];//获取单词的词频
    cout<<word<<" occurs "<< cnt << (cnt>1? " times":" time")<<endl;
    auto lines=_lineNumber[word];
    for(auto &num:lines)
    {
        cout<<"     (line "<<num+1<<") "<<_eachLine[num+1]<<endl;
    }
}

void TextQuery:: preDealWord(string &line) 
{
    for(auto &ch:line)
    {
        if(!isalpha(ch))
        {
            //若不是字母用空格替代
            ch=' ';
        }
        else if(isupper(ch))
        {
            //大写变小写
            tolower(ch);
        }
    }


}
TextQuery::~TextQuery()
{
    _eachLine.clear();
    _eachLine.shrink_to_fit();
}

