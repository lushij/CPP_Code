/*
 *本程序用于把全国气象站点参数文件中的数据进行入库T_ZHOBTCODE表中
 *作者：lushij
*/
#include"_public.h"
#include"_ooci.h"
using namespace idc;
clogfile logfile;//日志对象
connection conn;//数据库连接句柄
cpactive Heart;//进程的心跳

struct st_stcode
{
    char provname[31];//省
    char obtid[11];//站号
    char cityname[31];//站名
    char lat[11];//纬度
    char lon[11];//经度
    char height[11];//海拔高度
}stcode;

list<struct st_stcode>stcodeList;//存放全国站点参数的容器
bool loadStcode(const string & inifile);//把站点参数文件中的数据加载到容器中
void EXIT(int sig);//信号退出函数
void useHelp();
int main(int argc,char*argv[])
{
    if(argc!=5)
    {
        useHelp();
        return -1;
    }
    //处理信号
    signal(2,EXIT);
    signal(15,EXIT);
    //打开日志文件
    if(logfile.open(argv[4])==false)
    {
        printf("打开日志(%s)失败\n",argv[4]);
        return -1;
    }
    logfile.write("打开日志(%s)成功\n",argv[4]);
    
    //加载数据到容器中
    if(loadStcode(argv[1])==false)
    {
        logfile.write("加载(%s)失败\n",argv[1]);
        EXIT(-1);
    }
    logfile.write("加载(%s)成功\n",argv[1]);
    //连接数据库
    if(conn.connecttodb(argv[2],argv[3])!=0)
    {
        logfile.write("连接数据库(%s)失败\n%s\n",argv[2],conn.message());
        EXIT(-1);
    }
    logfile.write("连接数据库(%s) 成功\n",argv[2]);
    //准备插入和更新的数据的sql语句
    //
    //
    //插入表的sql语句
    sqlstatement stmtins(&conn);
    stmtins.prepare("insert into T_ZHOBTCODE(obtid,cityname,provname,lat,lon,height,keyid) \
                                values(:1,:2,:3,:4*100,:5*100,:6*10,SEQ_ZHOBTCODE.nextval)");
    //进项动态语句，oracle字段绑定
    //绑定的数据为字符串，字符串的长度最大要等于设置的长度减一
    stmtins.bindin(1,stcode.obtid,5);
    stmtins.bindin(2,stcode.cityname,30);
    stmtins.bindin(3,stcode.provname,30);
    stmtins.bindin(4,stcode.lat,10);
    stmtins.bindin(5,stcode.lon,10);
    stmtins.bindin(6,stcode.height,10);

    // 更新表的sql语句。
    sqlstatement stmtupt(&conn);  
    stmtupt.prepare("update T_ZHOBTCODE set cityname=:1,provname=:2,lat=:3*100,lon=:4*100,height=:5*10,upttime=sysdate\
         where obtid=:6");
    stmtupt.bindin(1,stcode.cityname,30);
    stmtupt.bindin(2,stcode.provname,30);
    stmtupt.bindin(3,stcode.lat,10);
    stmtupt.bindin(4,stcode.lon,10);
    stmtupt.bindin(5,stcode.height,10);
    stmtupt.bindin(6,stcode.obtid,5);
    int insertCnt=0;//插入数据条数
    int uptCnt=0;//更新数据条数
    ctimer timer;// 操作数据库消耗的时间。
    //遍历容器插入数据库或更新数据库操作
    for(auto &x:stcodeList)
    {
        //从容器中取出一条数据
        stcode = x;//为了动态绑定，需要把x复制到stcode中
        //执行插入的语句
        if(stmtins.execute()!=0)
        {
        // 错误代码为ORA-0001违返唯一约束，表示该站点的记录在表中已存在。
            if(stmtins.rc()==1)
            {
                //如果该记录已存在，则执行更新的语句
                if(stmtupt.execute()!=0)
                {
                    logfile.write("stmtupt.execute failed\n%s\n%s\n",stmtupt.sql(),stmtupt.message());
                   EXIT(-1); 
                }
                else
                {
                    ++uptCnt;
                }
            }
            else
            {
                //其他错误，程序退出
                logfile.write("stmtins.execute failed\n%s\n%s\n",stmtins.sql(),stmtins.message());
                EXIT(-1);
            }
        }
        else
        {
            ++insertCnt;
        }

    }
    logfile.write("总记录数%d,插入%d,更新%d,耗时%.2f秒\n",stcodeList.size(),
                  insertCnt,uptCnt,timer.elapsed());
    //提交事务
    conn.commit();
    return 0;
}

void useHelp()
{
        printf("\n");
        printf("Using:./obtcodetodb inifile connstr charset logfile\n");

        printf("Example:~/project/tools/bin/procctl 120 ~/project/idc/bin/obtcodetodb ~/project/idc/ini/stcode.ini "\
                  "\"idc/idcpwd@oracle_101\" \"Simplified Chinese_China.AL32UTF8\" ~/log/idc/obtcodetodb.log\n\n");

        printf("本程序用于把全国气象站点参数数据保存到数据库的T_ZHOBTCODE表中，如果站点不存在则插入，站点已存在则更新。\n");
        printf("inifile 全国气象站点参数文件名（全路径）。\n");
        printf("connstr 数据库连接参数：username/password@tnsname\n");
        printf("charset 数据库的字符集。\n");
        printf("logfile 本程序运行的日志文件名。\n");
        printf("程序每120秒运行一次，由procctl调度。\n\n\n");
}

//信号退出函数
void EXIT(int sig)
{
    logfile.write("收到%d信号，程序退出\n",sig);
     // 可以不写，在析构函数中会回滚事务和断开与数据库的连接。
    conn.rollback();
    conn.disconnect();   
    exit(0);
}
//把站点参数文件中的数据加载到容器中
bool loadStcode(const string & inifile)
{
     cifile ifile;
    // 打开站点参数文件。
    if (ifile.open(inifile)==false)
    {
        logfile.write("ifile.open(%s) failed.\n",inifile); return false;
    }
    string strbuffer;     // 存放从文件中读取的每一行。
    ccmdstr cmdstr;    // 用于拆分字符串。
    while (true)
    {
        // 从站点参数文件中读取一行，如果已读取完，跳出循环。
        if (ifile.readline(strbuffer)==false) break;

        // 把读取到的一行拆分。
        cmdstr.splittocmd(strbuffer,",");
        //省,站号,站名,纬度,经度,海拔高度  总共六个数据字段
        if(cmdstr.cmdcount()!=6) continue;     // 扔掉无效的行。

        // 把站点参数的每个数据项保存到站点参数结构体中。
        memset(&stcode,0,sizeof(struct st_stcode));
        cmdstr.getvalue(0, stcode.provname,30); // 省
        cmdstr.getvalue(1, stcode.obtid,5);    // 站号
        cmdstr.getvalue(2, stcode.cityname,30);  // 站名
        cmdstr.getvalue(3, stcode.lat,10);      // 纬度
        cmdstr.getvalue(4, stcode.lon,10);      // 经度
        cmdstr.getvalue(5, stcode.height,10);   // 海拔高度

        // 把站点参数结构体放入站点参数容器。
        stcodeList.push_back(stcode);
    }
    return true;
}
