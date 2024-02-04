//本程序是共享平台的公共功能模块，用于把xml文件入库到Oracle的表中
#include"_tool.h"

//参数解析对象
struct info_t
{
    char connstr[101];          // 数据库的连接参数。
    char charset[51];            // 数据库的字符集。
    char inifilename[301];    // 数据入库的参数配置文件。
    char xmlpath[301];         // 待入库xml文件存放的目录。
    char xmlpathbak[301];   // xml文件入库后的备份目录。
    char xmlpatherr[301];    // 入库失败的xml文件存放的目录。
    int  timetvl;                    // 本程序运行的时间间隔，本程序常驻内存。
    int  timeout;                   // 本程序运行时的超时时间。
    char pname[51];            // 本程序运行时的程序名。   
}ArgInfo;

//函数声明区
void EXIT(int sig);
void useHelp();
bool xmlToArgs(const char*strxmlbuffer);
void xmltodb();

//全局对象区
clogfile logfile;
cpactive pactive;
int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        useHelp();
        return -1;
    }
    signal(2,EXIT);
    signal(15,EXIT);
    if(logfile.open(argv[1])==false)
    {
        printf("打开日志(%s)失败,行数为%d\n",argv[1],__LINE__);
        return -1;
    }
    logfile.write("打开日志(%s)成功\n",argv[1]);
    if(xmlToArgs(argv[2])==false)
    {
        logfile.write("解析xml失败，行数为%d\n",__LINE__);
        return -1;
    }
#if 1
    pactive.addpinfo(ArgInfo.timeout,ArgInfo.pname);
    xmltodb();//业务处理主函数
#endif
    return 0;
}

void EXIT(int sig)
{
    printf("收到%d信号，程序退出\n",sig);
    exit(0);
}
void useHelp()
{
    printf("Using:~/project/tools/bin/xmltodb logfilename xmlbuffer\n\n");

    printf("Sample:~/project/tools/bin/procctl 10 ~/project/tools/bin/xmltodb ~/log/idc/xmltodb_vip.log "\
              "\"<connstr>idc/idcpwd@oracle_101</connstr><charset>Simplified Chinese_China.AL32UTF8</charset>"\
              "<inifilename>~/project/idc/ini/xmltodb.xml</inifilename>"\
              "<xmlpath>~/idcdata/xmltodb/vip</xmlpath><xmlpathbak>~/idcdata/xmltodb/vipbak</xmlpathbak>"\
              "<xmlpatherr>~/idcdata/xmltodb/viperr</xmlpatherr>"\
              "<timetvl>5</timetvl><timeout>50</timeout><pname>xmltodb_vip</pname>\"\n\n");

    printf("本程序是共享平台的公共功能模块，用于把xml文件入库到Oracle的表中。\n");
    printf("logfilename   本程序运行的日志文件。\n");
    printf("xmlbuffer     本程序运行的参数，用xml表示，具体如下：\n\n");
    printf("connstr     数据库的连接参数，格式：username/passwd@tnsname。\n");
    printf("charset     数据库的字符集，这个参数要与数据源数据库保持一致，否则会出现中文乱码的情况。\n");
    printf("inifilename 数据入库的参数配置文件。\n");
    printf("xmlpath     待入库xml文件存放的目录。\n");
    printf("xmlpathbak  xml文件入库后的备份目录。\n");
    printf("xmlpatherr  入库失败的xml文件存放的目录。\n");
    printf("timetvl     扫描xmlpath目录的时间间隔（执行入库任务的时间间隔），单位：秒，视业务需求而定，2-30之间。\n");
    printf("timeout     本程序的超时时间，单位：秒，视xml文件大小而定，建议设置30以上。\n");
    printf("pname       进程名，尽可能采用易懂的、与其它进程不同的名称，方便故障排查。\n\n");
}
bool xmlToArgs(const char*strxmlbuffer)
{
    memset(&ArgInfo,0,sizeof(struct info_t));
    loginUsr usr;
    string home="/home/";
    string tmp=home+usr.getUsr();
    string _home="~";
    getxmlbuffer(strxmlbuffer,"connstr",ArgInfo.connstr,100);
    if (strlen(ArgInfo.connstr)==0) { logfile.write("connstr is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"charset",ArgInfo.charset,50);
    if (strlen(ArgInfo.charset)==0) { logfile.write("charset is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"inifilename",ArgInfo.inifilename,300);
    if (strlen(ArgInfo.inifilename)==0) { logfile.write("inifilename is null.\n"); return false; }
    replacestr(ArgInfo.inifilename,_home,tmp);

    getxmlbuffer(strxmlbuffer,"xmlpath",ArgInfo.xmlpath,300);
    if (strlen(ArgInfo.xmlpath)==0) { logfile.write("xmlpath is null.\n"); return false; }
    replacestr(ArgInfo.xmlpath,_home,tmp);
    getxmlbuffer(strxmlbuffer,"xmlpathbak",ArgInfo.xmlpathbak,300);
    if (strlen(ArgInfo.xmlpathbak)==0) { logfile.write("xmlpathbak is null.\n"); return false; }
    replacestr(ArgInfo.xmlpathbak,_home,tmp);
    getxmlbuffer(strxmlbuffer,"xmlpatherr",ArgInfo.xmlpatherr,300);
    if (strlen(ArgInfo.xmlpatherr)==0) { logfile.write("xmlpatherr is null.\n"); return false; }
    replacestr(ArgInfo.xmlpatherr,_home,tmp);
    /* logfile.write("inifilename=%s,xmlpath=%s,xmlpathbak=%s,xmlpatherr=%s\n",ArgInfo.inifilename,ArgInfo.xmlpath,ArgInfo.xmlpathbak,ArgInfo.xmlpatherr); */
    getxmlbuffer(strxmlbuffer,"timetvl",ArgInfo.timetvl);
    if (ArgInfo.timetvl< 2) ArgInfo.timetvl=2;   
    if (ArgInfo.timetvl>30) ArgInfo.timetvl=30;

    getxmlbuffer(strxmlbuffer,"timeout",ArgInfo.timeout);
    if (ArgInfo.timeout==0) { logfile.write("timeout is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"pname",ArgInfo.pname,50);
    if (strlen(ArgInfo.pname)==0) { logfile.write("pname is null.\n"); return false; }

    return true;
}
void xmltodb()
{
    cdir dir;//目录对象



}

