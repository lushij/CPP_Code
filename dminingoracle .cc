#if 0
本程序是数据中心的公共功能模块，用于从Oracle数据库源表抽取数据，生成xml文件。
作者:lushij
#endif
#include<sstream>
#include<vector>
#include"_public.h"
#include"_ooci.h"
using namespace idc;

struct info_t{
    char connstr[101];       // 数据库的连接参数。
    char charset[51];         // 数据库的字符集。
    char selectsql[1024];   // 从数据源数据库抽取数据的SQL语句。
    char fieldstr[501];        // 抽取数据的SQL语句输出结果集字段名，字段名之间用逗号分隔。
    char fieldlen[501];       // 抽取数据的SQL语句输出结果集字段的长度，用逗号分隔。
    char bfilename[31];     // 输出xml文件的前缀。
    char efilename[31];     // 输出xml文件的后缀。
    char outpath[256];      // 输出xml文件存放的目录。
    int    maxcount;           // 输出xml文件最大记录数，0表示无限制。xml文件将用于入库，如果文件太大，数据库会产生大事务。
    char starttime[52];      // 程序运行的时间区间
    char incfield[31];         // 递增字段名。若是不为空，表示按照增量抽取
    char incfilename[256]; // 已抽取数据的递增字段最大值存放的文件。保存上次抽取到的数据的节点数，和下面的数据库二选一
    char connstr1[101];     // 已抽取数据的递增字段最大值存放的数据库的连接参数。
    int    timeout;              // 进程心跳的超时时间。
    char pname[51];          // 进程名，建议用"dminingoracle_后缀"的方式。
}ArgInfo;

//函数声明
void useHelp();//帮助文档
void EXIT(int sig);
bool _xmltoArg(const char * strxmlbuffer);
bool instartTime();//判断是否在规定时间内
bool readincfield();//读取上次抽取数据的最大截止数
void _dminingoracle();//抽取业务处理
vector<string> splitString(const string& input, char delimiter);//分割字符
bool writeincfield(); //写入数据
//全局变量
clogfile logfile;
cpactive heart;
connection conn;
ccmdstr fieldname;         // 结果集字段名数组,  char fieldstr[501]; 抽取数据的SQL语句输出结果集字段名，字段名之间用逗号分隔。
ccmdstr fieldlen;          // 结果集字段长度数组。 char fieldlen[501]; 抽取数据的SQL语句输出结果集字段的长度，用逗号分隔。
long imaxincvalue;         // 递增字段的最大值。
int pos=-1;//位置



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
        printf("打开日志文件(%s)失败\n",argv[1]);
        return -1;
    }
    logfile.write("打开日志(%s)成功\n",argv[1]);
    logfile.write("解析xml中\n");
    //解析xml
    if(_xmltoArg(argv[2])==false)
    {
        EXIT(-1);
    }
    logfile.write("解析xml成功\n");
    //判断开始时间是否成立
#if 1
    if(instartTime()==false)
    {
        return 0;
    }
    //时间只要到了，就要加入信息
    heart.addpinfo(ArgInfo.timeout,ArgInfo.pname);
    //链接数据库
    if(conn.connecttodb(ArgInfo.connstr,ArgInfo.charset)!=0)
    {
        logfile.write("connect (%s) failed\n%s\n",ArgInfo.connstr,conn.message());
        EXIT(-1);
    }
    logfile.write("connection (%s) successful\n",ArgInfo.connstr);
    //读取上次最大值
    if(readincfield()==false)
    {
        EXIT(-1);
    }
    cout<<imaxincvalue<<endl;
    _dminingoracle();//业务处理
#endif
    return 0;
}

void useHelp()
{
     printf("Using:~/project/tools/bin/dminingoracle logfilename xmlbuffer\n\n");

    printf("Sample:~/project/tools/bin/procctl 3600 ~/project/tools/bin/dminingoracle ~/log/idc/dminingoracle_ZHOBTCODE.log "
              "\"<connstr>idc/idcpwd@oracle_101</connstr><charset>Simplified Chinese_China.AL32UTF8</charset>"\
              "<selectsql>select obtid,cityname,provname,lat,lon,height from T_ZHOBTCODE where obtid like '5%%%%'</selectsql>"\
              "<fieldstr>obtid,cityname,provname,lat,lon,height</fieldstr><fieldlen>5,30,30,10,10,10</fieldlen>"\
              "<bfilename>ZHOBTCODE</bfilename><efilename>togxpt</efilename><outpath>~/idcdata/dmindata</outpath>"\
              "<timeout>30</timeout><pname>dminingoracle_ZHOBTCODE</pname>\"\n\n");
    printf("      ~/project/tools/bin/procctl   30 ~/project/tools/bin/dminingoracle ~/log/idc/dminingoracle_ZHOBTMIND.log "\
              "\"<connstr>idc/idcpwd@oracle_101</connstr><charset>Simplified Chinese_China.AL32UTF8</charset>"\
              "<selectsql>select obtid,to_char(ddatetime,'yyyymmddhh24miss'),t,p,u,wd,wf,r,vis,keyid from T_ZHOBTMIND where keyid>:1 and obtid like '5%%%%'</selectsql>"\
              "<fieldstr>obtid,ddatetime,t,p,u,wd,wf,r,vis,keyid</fieldstr><fieldlen>5,19,8,8,8,8,8,8,8,15</fieldlen>"\
              "<bfilename>ZHOBTMIND</bfilename><efilename>togxpt</efilename><outpath>~/idcdata/dmindata</outpath>"\
              "<starttime></starttime><incfield>keyid</incfield>"\
              "<incfilename>~/idcdata/dmining/dminingoracle_ZHOBTMIND_togxpt.keyid</incfilename>"\
              "<timeout>30</timeout><pname>dminingoracle_ZHOBTMIND_togxpt</pname>"\
              "<maxcount>1000</maxcount><connstr1>scott/oracle@oracle_101</connstr1>\"\n\n");

    printf("本程序是共享平台的公共功能模块，用于从Oracle数据库源表抽取数据，生成xml文件。\n");
    printf("logfilename 本程序运行的日志文件。\n");
    printf("xmlbuffer   本程序运行的参数，用xml表示，具体如下：\n\n");

    printf("connstr     数据源数据库的连接参数，格式：username/passwd@tnsname。\n");
    printf("charset     数据库的字符集，这个参数要与数据源数据库保持一致，否则会出现中文乱码的情况。\n");
    printf("selectsql   从数据源数据库抽取数据的SQL语句，如果是增量抽取，一定要用递增字段作为查询条件，如where keyid>:1。\n");
    printf("fieldstr    抽取数据的SQL语句输出结果集的字段名列表，中间用逗号分隔，将作为xml文件的字段名。\n");
    printf("fieldlen    抽取数据的SQL语句输出结果集字段的长度列表，中间用逗号分隔。fieldstr与fieldlen的字段必须一一对应。\n");
    printf("outpath     输出xml文件存放的目录。\n");
    printf("bfilename   输出xml文件的前缀。\n");
    printf("efilename   输出xml文件的后缀。\n");
    printf("maxcount    输出xml文件的最大记录数，缺省是0，表示无限制，如果本参数取值为0，注意适当加大timeout的取值，防止程序超时。\n");
    printf("starttime   程序运行的时间区间，例如02,13表示：如果程序启动时，踏中02时和13时则运行，其它时间不运行。"\
         "如果starttime为空，表示不启用，只要本程序启动，就会执行数据抽取任务，为了减少数据源数据库压力"\
         "抽取数据的时候，如果对时效性没有要求，一般在数据源数据库空闲的时候时进行。\n");
    printf("incfield    递增字段名，它必须是fieldstr中的字段名，并且只能是整型，一般为自增字段。"\
          "如果incfield为空，表示不采用增量抽取的方案。\n");
    printf("incfilename 已抽取数据的递增字段最大值存放的文件，如果该文件丢失，将重新抽取全部的数据。\n");
    printf("connstr1    已抽取数据的递增字段最大值存放的数据库的连接参数。connstr1和incfilename二选一，connstr1优先。\n");
    printf("timeout     本程序的超时时间，单位：秒。\n");
    printf("pname       进程名，尽可能采用易懂的、与其它进程不同的名称，方便故障排查。\n\n\n");
}


void EXIT(int sig)
{
    printf("收到%d信号，程序退出\n",sig);
    exit(0);
}
bool _xmltoArg(const char * strxmlbuffer)
{
    memset(&ArgInfo,0,sizeof(struct info_t));

    getxmlbuffer(strxmlbuffer,"connstr",ArgInfo.connstr,100);       // 数据源数据库的连接参数。
    if (strlen(ArgInfo.connstr)==0) { logfile.write("connstr is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"charset",ArgInfo.charset,50);         // 数据库的字符集。
    if (strlen(ArgInfo.charset)==0) { logfile.write("charset is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"selectsql",ArgInfo.selectsql,1000);  // 从数据源数据库抽取数据的SQL语句。
    if (strlen(ArgInfo.selectsql)==0) { logfile.write("selectsql is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"fieldstr",ArgInfo.fieldstr,500);          // 结果集字段名列表。
    if (strlen(ArgInfo.fieldstr)==0) { logfile.write("fieldstr is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"fieldlen",ArgInfo.fieldlen,500);         // 结果集字段长度列表。
    if (strlen(ArgInfo.fieldlen)==0) { logfile.write("fieldlen is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"bfilename",ArgInfo.bfilename,30);   // 输出xml文件前缀。
    if (strlen(ArgInfo.bfilename)==0) { logfile.write("bfilename is null.\n"); return false; }
   
    getxmlbuffer(strxmlbuffer,"efilename",ArgInfo.efilename,30);    // 输出xml文件的后缀。
    if (strlen(ArgInfo.efilename)==0) { logfile.write("efilename is null.\n"); return false; }

    getxmlbuffer(strxmlbuffer,"outpath",ArgInfo.outpath,255);        // 输出xml文件目录名字
    if (strlen(ArgInfo.outpath)==0) { logfile.write("outpath is null.\n"); return false; }
    const char*usr=getlogin();
    string tmp=string("/home/")+usr;
    //将~替换为tmp;
    logfile.write("处理前%s\n",ArgInfo.outpath); 
    replacestr(ArgInfo.outpath,"~",tmp.c_str(),false);
    logfile.write("处理后%s\n",ArgInfo.outpath); 

    getxmlbuffer(strxmlbuffer,"maxcount",ArgInfo.maxcount);       // 输出xml文件的最大记录数，可选参数。

    getxmlbuffer(strxmlbuffer,"starttime",ArgInfo.starttime,50);     // 程序运行的时间区间，可选参数。

    getxmlbuffer(strxmlbuffer,"incfield",ArgInfo.incfield,30);          // 递增字段名，可选参数。

    getxmlbuffer(strxmlbuffer,"incfilename",ArgInfo.incfilename,255);  // 已抽取数据的递增字段最大值存放的文件，可选参数。
     //将~替换为tmp;
    logfile.write("处理前%s\n",ArgInfo.incfilename); 
    replacestr(ArgInfo.incfilename,"~",tmp.c_str(),false);
    logfile.write("处理后%s\n",ArgInfo.incfilename); 

    getxmlbuffer(strxmlbuffer,"connstr1",ArgInfo.connstr1,100);          // 已抽取数据的递增字段最大值存放的数据库的连接参数，可选参数。

    getxmlbuffer(strxmlbuffer,"timeout",ArgInfo.timeout);       // 进程心跳的超时时间。
    if (ArgInfo.timeout==0) { logfile.write("timeout is null.\n");  return false; }

    getxmlbuffer(strxmlbuffer,"pname",ArgInfo.pname,50);     // 进程名。
    if (strlen(ArgInfo.pname)==0) { logfile.write("pname is null.\n");  return false; }

    // 拆分ArgInfo.fieldstr到fieldname中。
    fieldname.splittocmd(ArgInfo.fieldstr,",");

    // 拆分ArgInfo.fieldlen到fieldlen中。
    fieldlen.splittocmd(ArgInfo.fieldlen,",");

    // 判断fieldname和fieldlen两个数组的大小是否相同。
    if (fieldlen.size()!=fieldname.size())
    {
        logfile.write("fieldstr和fieldlen的元素个数不一致。\n"); return false;
    }

    // 如果是增量抽取，incfilename和connstr1必二选一。
    if (strlen(ArgInfo.incfield)>0)//表示增量抽取
    {
        if ( (strlen(ArgInfo.incfilename)==0) && (strlen(ArgInfo.connstr1)==0) )
        {
            logfile.write("如果是增量抽取，incfilename和connstr1必二选一，不能都为空。\n"); return false;
        }
    }

    return true;

}
vector<string> splitString(const string& input, char delimiter) {
    vector<string> result;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}
bool instartTime()
{
    //程序运行的时间
    if(strlen(ArgInfo.starttime)!=0)
    {
        string tm=ltime1("hh24");//获取当前时间的小时
        vector<string>time;
        time=splitString(string(ArgInfo.starttime),',');
        string begin=time[0];
        string end=time[1];
        if(tm<=begin && tm<=end)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool readincfield()
{
    imaxincvalue=0;//初始化为0
    //读取保存最大值的数据，文件或数据库
    if(strlen(ArgInfo.incfield)==0)
    {
        return true;//表示不是增量查询
    }
    for(int i=0;i<fieldname.size();++i)
    {
        if(fieldname[i]==ArgInfo.incfield)//string可以直接和char*比较
        {
            pos=i;
        }
    }
    if(pos==-1)
    {
        logfile.write("该字段不存在\n");
        return false;
    }
    //表示可以取出数据
    if(strlen(ArgInfo.connstr1)!=0)
    {
        //表示数据库
        connection conn1;
        if(conn1.connecttodb(ArgInfo.connstr1,ArgInfo.charset)!=0)
        {
            logfile.write("链接失败\n");
            return false;
        }
        //查询数据
        sqlstatement stmt(&conn1);
        stmt.prepare("select maxincvalue from T_MAXINCVALUE where pname=:1");
        stmt.bindin(1,ArgInfo.pname);
        stmt.bindout(1,imaxincvalue);
        stmt.execute();
        stmt.next();
    }
    else
    {
        //从文件里取数据
        cifile ifile;
        if(ifile.open(ArgInfo.incfilename)==false)
        {
            return true;//可能是第一次或数据丢失
        }
        string line;
        ifile.readline(line);
        imaxincvalue=stol(line);
    }
    logfile.write("上次最大值为%ld\n",imaxincvalue);
    return true;
}
void _dminingoracle()//业务处理
{
    
    // 1）准备抽取数据的SQL语句。
    sqlstatement stmt(&conn);
    stmt.prepare(ArgInfo.selectsql);//采用printf类型参数，%%代表一个%
    logfile.write("sql语句为%s\n",ArgInfo.selectsql);
    // 2）绑定结果集的变量。
    string strfieldvalue[fieldname.size()];//数组
    for (int i=1;i<=fieldname.size();i++)
    {
        stmt.bindout(i,strfieldvalue[i-1],stoi(fieldlen[i-1]));//绑定结果集从1开始，数据下标是从0开始
    }
    //判断数据抽取的方式
    if(strlen(ArgInfo.incfield)!=0)
    {
        //进入这表示数据库操作
        stmt.bindin(1,imaxincvalue);
    }
    if(stmt.execute()!=0)
    {
        //执行sql语句
        logfile.write("stmt.excute failed\n%s出现在%s文件中第%d行\n",conn.message(),__FILE__,__LINE__);
        return;
    }
    //更新进程时间
    heart.uptatime();
    string outXmlName;//输出文件名
    int cnt=1;//输出的序号
    cofile ofile;
    // 4）获取结果集中的记录，写入xml文件。
    while (true)
    {
        if (stmt.next()!=0) break;         // 从结果集中获取一行记录。

        if (ofile.isopen()==false)
        {
            // 如果xml文件是未打开状态，打开xml文件。
            sformat(outXmlName,"%s/%s_%s_%s_%d.xml",\
                  ArgInfo.outpath,ArgInfo.bfilename,ltime1("yyyymmddhh24miss").c_str(),ArgInfo.efilename,cnt++);
            if (ofile.open(outXmlName)==false)
            {
                logfile.write("ofile.open(%s) failed.\n",outXmlName.c_str()); return;
            }
            ofile.writeline("<data>\n");          // 写入数据集开始的标签。
        }  

        // 把结果集中的每个字段的值写入xml文件。
        for (int i=1;i<=fieldname.size();i++)
            ofile.writeline("<%s>%s</%s>",fieldname[i-1].c_str(),strfieldvalue[i-1].c_str(),fieldname[i-1].c_str());

        ofile.writeline("<endl/>\n");    // 写入每行的结束标志。

        // 如果记录数达到starg.maxcount行就关闭当前文件。200 838 200 400 600
        if ( (ArgInfo.maxcount>0) && (stmt.rpc()%ArgInfo.maxcount==0) )
        {
            ofile.writeline("</data>\n");   // 写入文件的结束标志。

            if (ofile.closeandrename()==false)  // 关闭文件，把临时文件名改名为正式的文件名。
            {
                logfile.write("ofile.closeandrename(%s) failed.\n",outXmlName.c_str()); return;
            }

            logfile.write("生成文件%s(%d)。\n",outXmlName.c_str(),ArgInfo.maxcount);     

            heart.uptatime();    // 更新进程的心跳。 
        }

        // 更新递增字段的最大值。
        if ( (strlen(ArgInfo.incfield)!=0) && (imaxincvalue<stol(strfieldvalue[pos])) )
           imaxincvalue=stol(strfieldvalue[pos]);
    }

    // 5）如果maxcount==0或者向xml文件中写入的记录数不足maxcount，关闭文件。
    if (ofile.isopen()==true)
    {
        ofile.writeline("</data>\n");        // 写入数据集结束的标签。
        if (ofile.closeandrename()==false)
        {
            logfile.write("ofile.closeandrename(%s) failed.\n",outXmlName.c_str()); return ;
        }

        if (ArgInfo.maxcount==0)
            logfile.write("生成文件%s(%d)。\n",outXmlName.c_str(),stmt.rpc());
        else
            logfile.write("生成文件%s(%d)。\n",outXmlName.c_str(),stmt.rpc()%ArgInfo.maxcount);
    }

    // 把已抽取数据的最大值写入数据库表或starg.incfilename文件。
    if (stmt.rpc()>0) writeincfield(); 
}


bool writeincfield()
{
     // 如果incfield参数为空，表示不是增量抽取。
    if (strlen(ArgInfo.incfield)==0) return true;

     if (strlen(ArgInfo.connstr1)!=0)
    {
        // 把递增字段的最大值写入数据库的表。
        connection conn1;
        if (conn1.connecttodb(ArgInfo.connstr1,ArgInfo.charset)!=0)
        {
            logfile.write("connect database(%s) failed.\n%s\n",ArgInfo.connstr1,conn1.message()); return false;
        }
        logfile.write("connect database(%s) successful.\n%s\n",ArgInfo.connstr1,conn1.message()); return false;
        sqlstatement stmt(&conn1);
        stmt.prepare("update T_MAXINCVALUE set maxincvalue=:1 where pname=:2");
        stmt.bindin(1,imaxincvalue);
        stmt.bindin(2,ArgInfo.pname);
        if (stmt.execute()!=0)
        {
            if (stmt.rc()==942)  // 如果表不存在，stmt.execute()将返回ORA-00942的错误。
            {
                // 如果表不存在，就创建表，然后插入记录。
                conn1.execute("create table T_MAXINCVALUE(pname varchar2(50),maxincvalue number(15),primary key(pname))");
                conn1.execute("insert into T_MAXINCVALUE values('%s',%ld)",ArgInfo.pname,imaxincvalue);
                conn1.commit();
                return true;
            }
            else
            {
                logfile.write("stmt.execute() failed.\n%s\n%s\n",stmt.sql(),stmt.message()); return false;
            }
        }
        else
        {
            if (stmt.rpc()==0)
            {
			    // 如果记录不存在，就插入新记录。
                conn1.execute("insert into T_MAXINCVALUE values('%s',%ld)",ArgInfo.pname,imaxincvalue);
            }
            conn1.commit();
        }
    }
    else
    {
        // 把递增字段的最大值写入文件。
        cofile ofile;

        if (ofile.open(ArgInfo.incfilename,false)==false) 
        {
            logfile.write("ofile.open(%s) failed.\n",ArgInfo.incfilename); return false;
        }

        // 把已抽取数据的最大id写入文件。
        ofile.writeline("%ld",imaxincvalue);
    }

}
