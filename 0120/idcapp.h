#pragma once
#include"_public.h"
#include"_ooci.h"
using namespace idc;
class CZHOBTMIND
{


public:
    CZHOBTMIND(connection &conn,clogfile &logfile)
    :_conn(conn)
     ,_logfile(logfile)
    {}
    ~CZHOBTMIND() {}
    //拆分数据到结构体变量中
    bool splitbuffer(const string &line,const bool Isxml);
    //插入数据库
    bool inserttable();
private:
    struct st_zhobtmind
    {
        char obtid[6];            // 站点代码。
        char ddatetime[21];  // 数据时间，精确到分钟。
        char t[11];                 // 温度，单位：0.1摄氏度。
        char p[11];                // 气压，单位：0.1百帕。
        char u[11];                // 相对湿度，0-100之间的值。
        char wd[11];             // 风向，0-360之间的值。
        char wf[11];              // 风速：单位0.1m/s。
        char r[11];                // 降雨量：0.1mm。
        char vis[11];             // 能见度：0.1米。
    };
    connection &_conn;
    clogfile &_logfile;
    sqlstatement _stmt;//插入表操作的sql
    string _line;//从文件读取的一行数据
    struct st_zhobtmind _zhobtmind;
};

