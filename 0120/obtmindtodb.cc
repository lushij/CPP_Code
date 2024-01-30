/*
 *本程序：把气象观测数据文件入库T_ZHOBTMIND表中支持xml和csv两种格式
 *作者：lushij
 *
*/
#include"idcapp.h"
using namespace idc;

clogfile logfile;
cpactive heart;
connection conn;    // 数据库连接。
void useHelp();//帮助文档
void EXIT(int sig);//信号处理退出函数

void _obtmindtodb(const char*pathname,const char*connstr,const char*charset);
int main(int argc,char*argv[])
{
    if(argc!=5)
    {
        useHelp();
        return -1;
    }
    signal(2,EXIT);
    signal(15,EXIT);
    if(logfile.open(argv[4])==false)
    {
        printf("打开(%s)失败\n",argv[4]);
        return -1;
    }
    logfile.write("打开日志(%s)成功\n",argv[4]);
    heart.addpinfo(30,"obtmindtodb");//添加进程心跳信息到共享内存
     // 业务处理主函数。
    _obtmindtodb(argv[1],argv[2],argv[3]);
    return 0;
}

//帮助文档
void useHelp()
{
    printf("Using:./obtmindtodb pathname connstr charset logfile\n");
    printf("Example:~/project/tools/bin/procctl 10 ~/project/idc/bin/obtmindtodb ~/idcdata/surfdata "\
           "\"idc/idcpwd@oracle_101\" \"Simplified Chinese_China.AL32UTF8\" ~/log/idc/obtmindtodb.log\n\n");
    printf("本程序用于把全国气象观测数据文件入库到T_ZHOBTMIND表中，支持xml和csv两种文件格式，数据只插入，不更新。\n");
    printf("pathname 全国气象观测数据文件存放的目录。\n");
    printf("connstr  数据库连接参数：username/password@tnsname\n");
    printf("charset  数据库的字符集。\n");
    printf("logfile  本程序运行的日志文件名。\n");
    printf("程序每10秒运行一次，由procctl调度。\n\n\n");
}
//信号处理退出函数
void EXIT(int sig)
{
    printf("收到%d信号，程序退出\n",sig);
    exit(0);
}

void _obtmindtodb(const char*pathname,const char*connstr,const char*charset)
{
    cdir dir;
    //打开存放气象观测数据文件的目录
    if(dir.opendir(pathname,"*.csv,*.xml")==false)
    {
        logfile.write("opendir (%s) failed\n",pathname);
        return;
    }
    CZHOBTMIND ZHOBTMIND(conn,logfile);  // 操作气象观测数据表的对象。
    //用循环读取目录中的每一个文件
    while(1)
    {
        //读一个文件
        if(dir.readdir()==false) break;//表示读取完成
        if(conn.isopen()==false)
        {
            //如果有文件处理，再判断数据库的连接状态，若是未连接先连接数据库
            if(conn.connecttodb(connstr,charset)!=0)
            {
                //表示失败
                logfile.write("connect (%s) failed\n%s\n",connstr,conn.message());
                return;
            }
            logfile.write("connect database(%s) ok.\n",connstr);
        }
        //打开文件根据文件类型进行对应判断操作
        cifile ifile;
        if(ifile.open(dir.m_ffilename)==false)
        {
            logfile.write("打开文件(%s)失败\n",dir.m_ffilename.c_str());
            return;
        }
        int totalCnt=0;//总条数
        int insCnt=0;//插入数据条数
        ctimer ctm;//计时器
        bool Isxml=matchstr(dir.m_ffilename,"*.xml");//判断是否是xml文件,true-xml,false-csv
        string line;//读取每一行数据
        if(Isxml==false)
        {
            //csv文件
            //丢掉数据的首行(字段名)
            ifile.readline(line);
        }
        //读取每一个文件的有效数据行数
        while(1)
        {
            if(Isxml==true)
            {
                if(ifile.readline(line,"<endl/>")==false) break;//xml文件有行结束标志
            }
            else
            {
                if(ifile.readline(line)==false) break;//csv没有
            }
            totalCnt++;
            //把一下繁琐操作封装一个类
            //解析数据
            ZHOBTMIND.splitbuffer(line,Isxml);
            //把解析后的数据插入数据库
            if(ZHOBTMIND.inserttable()==true) insCnt++;//成功记录加1
        }
        //关闭并删除已处理得文件
        ifile.closeandremove();
        conn.commit();
        logfile.write("已处理文件%s(总数为%d,成功插入条数为%d),耗时%.2f秒\n",dir.m_ffilename.c_str(),totalCnt,insCnt,ctm.elapsed());
        heart.uptatime();
    }


}
