#include "_tool.h"

//初始化函数
void ctcols:: initdata()
{
    _mVallCols.clear();
    _mVpkCols.clear();
    _mAllCols.clear();
    _mPkCols.clear();
}
//获取指定表的全部字段信息
bool ctcols:: allcols(connection & conn,char *tName)
{
    _mVallCols.clear();    // 清空vallcols容器。
    _mAllCols.clear();      // 清空字符串。

    //oracle封装数据库操作对象使用的顺序
    //1先练接数据库，建立数据库句柄
    //2创建语句对象，并且填入句柄
    //3准备sql语句
    //4执行语句


    struct st_columns stcolumns;

    sqlstatement stmt;//操作数据库语句对象
    stmt.connect(&conn);//连接句柄
    // 从USER_TAB_COLUMNS字典中获取表全部的字段，注意：1）把结果集转换成小写；2）数据字典中的表名是大写。
    stmt.prepare("\
            select lower(column_name),lower(data_type),data_length from USER_TAB_COLUMNS\
            where table_name=upper(:1) order by column_id");
    stmt.bindin(1,tName,30);
    stmt.bindout(1,stcolumns._colname,30);
    stmt.bindout(2,stcolumns._datatype,30);
    stmt.bindout(3,stcolumns._collen);

    // 只有当数据库连接异常（网络断开、数据库出了问题）时，stmt.execute()才会返回失败。
    if (stmt.execute()!=0) return false;

    while (true)
    {
        memset(&stcolumns,0,sizeof(struct st_columns));

        if (stmt.next()!=0) break;
        //每次读取一行完整的信息，进行处理
        // 列的数据类型，分为char、date和number三大类。
        // 如果业务有需要，可以修改以下的代码，增加对更多数据类型的支持。

        // 各种字符串类型，rowid当成字符串处理。
        if (strcmp(stcolumns._datatype,"char")==0)            strcpy(stcolumns._datatype,"char");
        if (strcmp(stcolumns._datatype,"nchar")==0)          strcpy(stcolumns._datatype,"char");
        if (strcmp(stcolumns._datatype,"varchar2")==0)     strcpy(stcolumns._datatype,"char");
        if (strcmp(stcolumns._datatype,"nvarchar2")==0)   strcpy(stcolumns._datatype,"char");
        if (strcmp(stcolumns._datatype,"rowid")==0)        { strcpy(stcolumns._datatype,"char");  stcolumns._collen=18; }

        // 日期时间类型。yyyymmddhh24miss
        if (strcmp(stcolumns._datatype,"date")==0)             stcolumns._collen=14;

        // 数字类型。
        if (strcmp(stcolumns._datatype,"number")==0)      strcpy(stcolumns._datatype,"number");
        if (strcmp(stcolumns._datatype,"integer")==0)       strcpy(stcolumns._datatype,"number");
        if (strcmp(stcolumns._datatype,"float")==0)           strcpy(stcolumns._datatype,"number");

        // 如果字段的数据类型不在上面列出来的中，忽略它。
        if ( (strcmp(stcolumns._datatype,"char")!=0) &&
             (strcmp(stcolumns._datatype,"date")!=0) &&
             (strcmp(stcolumns._datatype,"number")!=0) ) continue;

        // 如果字段类型是number，把长度设置为22。
        if (strcmp(stcolumns._datatype,"number")==0) stcolumns._collen=22;

        _mAllCols = _mAllCols + stcolumns._colname + ",";        // 拼接全部字段字符串。每执行依次拼接一行的COLUMN

        _mVallCols.push_back(stcolumns);                                 // 把字段信息放入容器中。
    }

    // 删除m_allcols最后一个多余的逗号。
    if (stmt.rpc()>0) deleterchr(_mAllCols,',');            // obtid,ddatetime,....,keyid

    return true;

        
}
//获取指定表主键字段信息
//这行sql语句获取结果集字段包括 COLUMN和POSITION两列
bool ctcols:: pkcols(connection & conn,char *tName)
{
    _mVpkCols.clear();
    _mPkCols.clear();
    st_columns stcolumns;
    sqlstatement stmt;
    stmt.connect(&conn);
    //准备sql语句
    stmt.prepare(
        "select lower(column_name),position from USER_CONS_COLUMNS\
         where table_name=upper(:1)\
           and constraint_name=(select constraint_name from USER_CONSTRAINTS\
                               where table_name=upper(:2) and constraint_type='P'\
                                 and generated='USER NAME')\
         order by position"
    );
    //然后进行绑定输入输出
    stmt.bindin(1,tName,30);
    stmt.bindin(2,tName,30);
    stmt.bindout(1,stcolumns._colname,30);//输出主键字段名COLUMN
    stmt.bindout(2,stcolumns._pkseq);//绑定主键信息,实际是position字段的值

    //绑定后进行执行语句
    if(stmt.execute()!=0) return false;//0表示成功，在数据库中
    while(1)
    {
        bzero(&stcolumns,sizeof(struct st_columns));
        if(stmt.next()!=0)
        {
            break;//表示结束
        }
        _mPkCols=_mPkCols+stcolumns._colname+",";//拼接字符串
        _mVallCols.push_back(stcolumns);
    }
    if(stmt.rpc()>0)
    {
        //获取影响记录的行数
        deleterchr(_mPkCols,',');//去除右边的字符
    }
    // 双重循环遍历进行更新全部字段信息容器中的pkseq即_mVallcols
    //以主键字段信息表容器为参照物
    for (auto &a : _mVpkCols)
    {
        for (auto &b : _mVallCols)
        {
            if (strcmp(a._colname, b._colname) == 0)
            {
                b._pkseq = a._pkseq;
                break;
            }
        }
    }
    return true;
}


loginUsr::loginUsr()
{
    const char *name = getlogin();
    _usr = string(name);
}
string loginUsr:: getUsr() const
{
    return _usr;
}
loginUsr::~loginUsr()
{
    _usr.clear();
}
