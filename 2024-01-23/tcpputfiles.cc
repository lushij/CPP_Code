#include"_public.h"
using namespace idc;
struct arg_t{
    int clientType;//客户端的类型，1-上传2-下载本程序固定1
    char ip[31];//服务端的ip
    int port;//服务端的端口号
    char cPath[256];//本地文件存放的根目录 
    int type;//文件上传后本地文件的处理方式1-删除2-移动备份目录
    char cBkPath[256];//2对应的备份目录
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
bool _tcpputfile(bool& fg);
bool acttest();
bool sendFile(const string &filename,const int filesize);// 把文件的内容发送给对端。
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
    bool flag=true;//如果调用_tcpputfiles()发送文件中，flag=true,反之为false
    while(1)
    {
        //调用_tcpputfiles(),执行上传文件的任务
        if(_tcpputfile(flag)==false)
        {
            logFile.write("上传失败\n");
            EXIT(-1);
        }
        //但是如果刚刚上传的文件过大，所需时间可能过长，新来的文件
        //为了保证文件被尽快上传，进程不休眠。（只有在刚才文件上传任务的时候没有上传文件的情况下才休眠)
        if(flag==false)
        {
            sleep(ArgInfo.time);
            if(acttest()==false)
            {
                break;
            }
        }
        pactive.uptatime();
    }
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
    printf("Using:~/project/tools/bin/tcpputfiles logfilename xmlbuffer\n\n");

    printf("Sample:~/project/tools/bin/procctl 20 ~/project/tools/bin/tcpputfiles ~/log/idc/tcpputfiles_surfdata.log "\
              "\"<ip>127.0.0.1</ip><port>5005</port>"\
              "<cPath>/tmp/client</cPath><type>1</type>"
              "<sPath>/tmp/server</sPath>"\
              "<andchild>true</andchild><matcher>*.xml,*.txt,*.csv</matcher><time>10</time>"\
              "<timeout>50</timeout><pidName>tcpputfiles_surfdata</pidName>\"\n\n");

    printf("本程序是数据中心的公共功能模块，采用tcp协议把文件上传给服务端。\n");
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
    getxmlbuffer(str,"cBkPath",ArgInfo.cBkPath,250);
    tmp=string("/home/")+sysUser+ArgInfo.cBkPath;
    bzero(&ArgInfo.cBkPath,sizeof(ArgInfo.cBkPath));
    strncpy(ArgInfo.cBkPath,tmp.c_str(),250);
    tmp.clear();
    cout<<"cBkPath="<<ArgInfo.cBkPath<<endl;
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
     sformat(strsendbuffer,"%s<clientType>1</clientType>",str);
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
bool _tcpputfile(bool & fg)
{
    //首先把fg置为false
    fg=false;
    //打开目录
    cdir dir;//目录对象
    cout<<"打开文件目录"<<ArgInfo.cPath<<endl;
    if(dir.opendir(ArgInfo.cPath,ArgInfo.matcher,10000,ArgInfo.andChild)==false)
    {
        logFile.write("dir opendir falid\n");
        return false;
    }
    int delayed=0;//计数器，采用异步通讯的方式
    //遍历目录中的每一个文件
    while(dir.readdir())
    {
        //进到这里表面开始上传文件了
        fg=true;
        //把文件名修改时间文件大小组成报文发送对端
        sformat(strsendbuffer,"<filename>%s</filename><mtime>%s</mtime><size>%d</size>",
                dir.m_ffilename.c_str(),dir.m_mtime.c_str(),dir.m_filesize);
        if(tcpClient.write(strsendbuffer)==false)
        {
            logFile.write("tcpClient.write()failed\n");
            return false;
        }
        /* logFile<<"发送"<<dir.m_ffilename<<"\n"; */
        //发送文件内容
        logFile.write("send (%s) (%d) ...",dir.m_ffilename.c_str(),dir.m_filesize);
        if(sendFile(dir.m_ffilename,dir.m_filesize)==true)
        {
            logFile<<"ok"<<"\n";
            ++delayed;
        }
        else
        {
            logFile<<"failed\n";
            tcpClient.close();
            return false;
        }
        while(delayed>0)
        {
            //接收缓冲区的内容
            if(tcpClient.read(strrecvbuffer,-1)==false) break;
            //处理接收报文
            --delayed;//采用异步通讯，接受一个减去一个
            ackmessage(strrecvbuffer);
        }

    }
    pactive.uptatime();
    //继续接收回应报文
    while(delayed>0)
    {

        //接收缓冲区的内容
        if(tcpClient.read(strrecvbuffer,-1)==false) break;
        --delayed;//采用异步通讯，接受一个减去一个
        //处理接收报文
        ackmessage(strrecvbuffer);
    }
    return true;
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
bool sendFile(const string &filename,const int filesize)
{
    int  onread=0;         // 每次打算从文件中读取的字节数。
    char buffer[4096];   // 存放读取数据的buffer，buffer的大小可参考硬盘一次读取数据量（4K为宜）。
    int  totalbytes=0;    // 从文件中已读取的字节总数。
    cifile ifile;                 // 读取文件的对象。

    // 必须以二进制的方式操作文件。
    if (ifile.open(filename,ios::in|ios::binary)==false) return false;

    while (true)
    {
        memset(buffer,0,sizeof(buffer));

        // 计算本次应该读取的字节数，如果剩余的数据超过4096字节，就读4096字节。
        if (filesize-totalbytes>4096) onread=4096;
        else onread=filesize-totalbytes;

        // 从文件中读取数据。
        ifile.read(buffer,onread);

        // 把读取到的数据发送给对端。
        if (tcpClient.write(buffer,onread)==false)  { return false; }

        // 计算文件已读取的字节总数，如果文件已读完，跳出循环。
        totalbytes=totalbytes+onread;

        if (totalbytes==filesize) break;
    }

    return true;
}

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
