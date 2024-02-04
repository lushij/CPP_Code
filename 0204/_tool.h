#pragma once
#include"_public.h"
#include"_ooci.h"
using namespace idc;
struct st_columns
{
    char _colname[31];//列名
    char _datatype[31];//列的数据类型，分为number,data,char三大类
    int _collen;//列的长度 number固定22，data固定19，char由表结构决定
    int _pkseq;//是否是主键，若是主键顺序从1开始，不是主键取值0
};


class ctcols
{
public:
    ctcols() 
    {
        initdata();
    }
    ~ctcols() {}
    //初始化函数
    void initdata();
    //获取指定表的全部字段信息
    bool allcols(connection & conn,char *tName);
    //获取指定表主键字段信息
    bool pkcols(connection & conn,char *tName);
public:
    vector<st_columns>_mVallCols;//存放全部字段信息的容器，字段就是每一列
    vector<st_columns>_mVpkCols;//存放主键字段名
    string _mAllCols;//全部字段名列表，以字符串存储 
    string _mPkCols;//主键字段名
        

};

class loginUsr
{
public:
    loginUsr();
    string getUsr() const;
    ~loginUsr();
private:
    string _usr;
};
