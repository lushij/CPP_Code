#include"_public.h"
using namespace idc;
struct arg_t{
    int clientType;//客户端的类型，1-上传2-下载本程序固定2
    char ip[31];//服务端的ip
    int port;//服务端的端口号
    char cPath[256];//本地文件存放的根目录 
    int type;//文件上传后本地文件的处理方式1-删除2-移动备份目录
    char sBkPath[256];//2对应的备份目录
    bool andChild;
    char matcher[256];
    char sPath[256];//服务端文件存放的本地目录
    int time;
    int timeout;
    char pidName[256];//进程的名字
}ArgInfo;

clogfile logFile;//服务程序的运行日志
ctcpclient tcpClient;//创建tcp通讯客户端
cpactive pactive;//心跳对象
void useHelp();//帮助文档
bool Login(const char*str);//客户端连接函数
bool xmlToArg(const char*arg);//解析xml参数到结构体函数对象
void EXIT(int sig);
void _tcpgetfile();
bool acttest();
bool recvFile(const string &filename,const string&mtime,const int filesize);// 把文件的内容发送给对端。
bool ackmessage(const string &strrecvbuffer);
string strrecvbuffer;//处理接收到的报文
string strsendbuffer;//发送的报文


int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        useHelp();
        return -1;
    }
    //设置关闭全部的io
    signal(2,EXIT);
    signal(15,EXIT);
    cout<<"打开日志..."<<endl;
    if(logFile.open(argv[1])==false)
    {
        //打开日志失败
        cout<<"打开日志"<<argv[2]<<"失败"<<endl;
        return -1;
    }
    //解析xml文件
    if(xmlToArg(argv[2])==false)
    {
        logFile.write("xmlToArg failed\n");
        return -1;
    }
    logFile.write("xmlToArg suc\n");
    pactive.addpinfo(ArgInfo.timeout,ArgInfo.pidName);

    if(tcpClient.connect(ArgInfo.ip,ArgInfo.port)==false)
    {
        logFile.write("connect is failed\n");
        return -1;
    }
    if(Login(argv[2])==false)
    {
        logFile.write("login failed\n");
        return -1;
    }
    //调用下载函数
    _tcpgetfile();
    return 0;
}

void EXIT(int sig)
{
    printf("收到%d sig信号，程序退出\n",sig);
    exit(0);
}
void useHelp()
{
    printf("\n");
    printf("Using:~/project/tools/bin/tcpgetfiles logfilename xmlbuffer\n\n");

    printf("Sample:~/project/tools/bin/procctl 20 ~/project/tools/bin/tcpgetfiles ~/log/idc/tcpgetfiles_surfdata.log "\
              "\"<ip>127.0.0.1</ip><port>5005</port>"\
              "<cPath>/tmp/client</cPath><type>1</type>"
              "<sPath>/tmp/server</sPath>"\
              "<andchild>true</andchild><matcher>*.xml,*.txt,*.csv</matcher><time>10</time>"\
              "<timeout>50</timeout><pidName>tcpgetfiles_surfdata</pidName>\"\n\n");

    printf("本程序是数据中心的公共功能模块，采用tcp协议把文件从服务端下载到本地。\n");
    printf("logfilename   本程序运行的日志文件。\n");
    printf("xmlbuffer     本程序运行的参数，如下：\n");
    printf("ip            服务端的IP地址。\n");
    printf("port          服务端的端口。\n");
    printf("type         文件上传成功后的处理方式：1-删除文件；2-移动到备份目录。\n");
    printf("cPath    本地文件存放的根目录。\n");
    printf("cBkPath 文件成功上传后，本地文件备份的根目录，当type==2时有效。\n");
    printf("andchild      是否上传cPath目录下各级子目录的文件，true-是；false-否，缺省为false。\n");
    printf("matcher     待上传文件名的匹配规则，如\"*.TXT,*.XML\"\n");
    printf("sPath       服务端文件存放的根目录。\n");
    printf("time      扫描本地目录文件的时间间隔，单位：秒，取值在1-30之间。\n");
    printf("timeout       本程序的超时时间，单位：秒，视文件大小和网络带宽而定，建议设置50以上。\n");
    printf("pidName         进程名，尽可能采用易懂的、与其它进程不同的名称，方便故障排查。\n\n");
}

bool xmlToArg(const char * str)
{
    bzero(&ArgInfo,sizeof(struct arg_t));
    getxmlbuffer(str,"ip",ArgInfo.ip,30);
    if(strlen(ArgInfo.ip)==0)
    {
        cout<<"failed"<<endl;
        return false;
    }
    getxmlbuffer(str,"port",ArgInfo.port);
    getxmlbuffer(str,"cPath",ArgInfo.cPath,250);
    string tmp="/home/";
    const char *sysUser=getlogin();//获取当前系统的用户名
    cout<<sysUser<<endl;
    tmp=tmp+sysUser+ArgInfo.cPath;
    bzero(&ArgInfo.cPath,sizeof(ArgInfo.cPath));
    strncpy(ArgInfo.cPath,tmp.c_str(),250);
    cout<<"cPath="<<ArgInfo.cPath<<endl;
    tmp.clear();
    getxmlbuffer(str,"sBkPath",ArgInfo.sBkPath,250);
    tmp=string("/home/")+sysUser+ArgInfo.sBkPath;
    bzero(&ArgInfo.sBkPath,sizeof(ArgInfo.sBkPath));
    strncpy(ArgInfo.sBkPath,tmp.c_str(),250);
    tmp.clear();
    cout<<"sBkPath="<<ArgInfo.sBkPath<<endl;
    getxmlbuffer(str,"type",ArgInfo.type);
    getxmlbuffer(str,"andChild",ArgInfo.andChild);
    getxmlbuffer(str,"matcher",ArgInfo.matcher,250);
    getxmlbuffer(str,"time",ArgInfo.time);
    getxmlbuffer(str,"sPath",ArgInfo.sPath,250);
    tmp=string("/home/")+sysUser+ArgInfo.sPath;
    bzero(&ArgInfo.sPath,sizeof(ArgInfo.sPath));
    strncpy(ArgInfo.sPath,tmp.c_str(),250);
    tmp.clear();
    cout<<"sPath="<<ArgInfo.sPath<<endl;
    getxmlbuffer(str,"timeout",ArgInfo.timeout);
    getxmlbuffer(str,"pidName",ArgInfo.pidName,250);
   if(ArgInfo.time>30)ArgInfo.time=30;//没必要超过30s
   if(ArgInfo.timeout<=ArgInfo.time)
   {
       logFile.write("starg.timeout(%d) <= starg.timetvl(%d).\n",ArgInfo.timeout,ArgInfo.time); return false;
   }
   return true;  
}

bool Login(const char*str)
{
     sformat(strsendbuffer,"%s<clientType>2</clientType>",str);
     if(tcpClient.write(strsendbuffer)==false)
     {
         return false;
     }
     if(tcpClient.read(strrecvbuffer,10)==false)
     {
         return false;
     }
     /* cout<<strrecvbuffer<<endl; */
     logFile.write("login (%s) (%d) 成功\n",ArgInfo.ip,ArgInfo.port);
     return true;

}
void _tcpgetfile()
{
    while(1)
    {
        pactive.uptatime();//更新心跳
        //接收服务器的报文
        if(tcpClient.read(strrecvbuffer,ArgInfo.time)==false)
        {
            logFile.write("tcp read failed\n");
            return;
        }
        //处理心跳报文
        if(strrecvbuffer=="<act>ok</act>")
        {
            strsendbuffer="ok";
            if(tcpClient.write(strsendbuffer)==false)
            {
                logFile.write("tcp write failed\n");
                return;
            }
        }
        //处理下载报文
        if(strrecvbuffer.find("<filename>")!=string::npos)
        {
            //解析下载的报文
           string sFname;
           string sTime;
           int size;
           getxmlbuffer(strrecvbuffer,"filename",sFname);
           getxmlbuffer(strrecvbuffer,"mtime",sTime);
           getxmlbuffer(strrecvbuffer,"size",size);
           string cFname=sFname;
           replacestr(cFname,ArgInfo.sPath,ArgInfo.cPath,false);
           //接收文件的内容
           logFile.write("gets (%s) (%d)...",cFname.c_str(),size);
           if(recvFile(cFname,sTime,size)==true)
           {
               logFile<<"ok\n";
               sformat(strsendbuffer,"<filename>%s</filename><result>ok</result>",cFname.c_str());
           }
           else
           {
               logFile<<"failed\n";
               sformat(strsendbuffer,"<filename>%s</filename><result>falied</result>",cFname.c_str());
           }
           if(tcpClient.write(strsendbuffer)==false)
           {
               logFile.write("return val failed\n");
               return;
           }

        }
    }
}

bool acttest()
{
    strsendbuffer="<act>ok</act>";
    if(tcpClient.write(strsendbuffer)==false)
    {
        return false;
    }
    if(tcpClient.read(strrecvbuffer,10)==false)
    {
        return false;
    }
    return true;
}

// 把文件的内容发送给对端。
bool recvFile(const string &filename,const string&mtime,const int filesize)
{
    int  onread=0;         // 每次打算从文件中读取的字节数。
    char buffer[4096];   // 存放读取数据的buffer，buffer的大小可参考硬盘一次读取数据量（4K为宜）。
    int  totalbytes=0;    // 从文件中已读取的字节总数。
    cofile ofile;                 // 读取文件的对象。
    newdir(filename);//创建文件
    // 必须以二进制的方式操作文件。
    if (ofile.open(filename,ios::in|ios::binary)==false) return false;

    while (true)
    {
        memset(buffer,0,sizeof(buffer));

        // 计算本次应该读取的字节数，如果剩余的数据超过4096字节，就读4096字节。
        if (filesize-totalbytes>4096) onread=4096;
        else onread=filesize-totalbytes;

        // 把读取到的数据写到文件中
        if (tcpClient.read(buffer,onread)==false)  { return false; }
        ofile.write(buffer,onread);

        // 计算文件已读取的字节总数，如果文件已读完，跳出循环。
        totalbytes=totalbytes+onread;

        if (totalbytes==filesize) break;
    }
    ofile.closeandrename();
    //重置文件时间
    setmtime(filename,mtime);
    return true;
}

#if 0
// 处理传输文件的响应报文（删除或者转存本地的文件）。
bool ackmessage(const string &strrecvbuffer)
{
    // <filename>/tmp/client/2.xml</filename><result>ok</result>
    string filename;   // 本地文件名。
    string result;        // 对端接收文件的结果。
    getxmlbuffer(strrecvbuffer,"filename",filename);
    getxmlbuffer(strrecvbuffer,"result",result);

    // 如果服务端接收文件不成功，直接返回（下次执行文件传输任务时将会重传）。
    if (result!="ok") return true;

    // 如果starg.ptype==1，删除文件。
    if (ArgInfo.type==1)
    {
        if (remove(filename.c_str())!=0) { logFile.write("remove(%s) failed.\n",filename.c_str()); return false; }
    }

    // 如果starg.ptype==2，移动到备份目录。
    if (ArgInfo.type==2)
    {
        // 生成转存后的备份目录文件名。  例如：/tmp/client/2.xml   /tmp/clientbak/2.xml
        string bakfilename=filename;
        replacestr(bakfilename,ArgInfo.cPath,ArgInfo.cBkPath,false);   // 注意，第三个参数一定要填false。
        if (renamefile(filename,bakfilename)==false)
        { logFile.write("renamefile(%s,%s) failed.\n",filename.c_str(),bakfilename.c_str()); return false; }
    }

    return true;
}
#endif
