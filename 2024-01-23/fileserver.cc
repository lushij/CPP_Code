#include"_public.h"
using namespace idc;
struct arg_t{
    int clientType;//客户端的类型，1-上传2-下载
    char cPath[256];//客户端的文件存放的根目录
    int type;//文件上传或下载成功后，处理的方式 1-删除2-移到备份目录
    bool andChild;//是否包括cPath目录下的子目录
    char matcher[256];//匹配规格
    char sPath[256];//服务端存放文件的根目录
    char sBkPath[256];//服务器的备份目录
    int time;//扫描时间
    int timeout;//进程心跳的时间
    char pidName[256];//进程的名字
}ArgInfo;

clogfile logFile;//服务程序的运行日志
ctcpserver tcpServer;//创建tcp通讯服务端
cpactive pactive;//心跳对象
void FathExit(int sig);//父进程退出程序
void ChildExit(int sig);//子进程退出程序
void useHelp();//帮助文档
bool clientLogin();//客户端连接函数
void recvFile();//上传文件函数
bool sendFile();//下载函数
bool recvFile(const string&name,const string &time,int size);
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
    signal(2,FathExit);
    signal(15,FathExit);
    if(logFile.open(argv[2])==false)
    {
        //打开日志失败
        cout<<"打开日志"<<argv[2]<<"失败"<<endl;
        return -1;
    }
    //服务端初始化
    cout<<argv[1]<<endl;
    if(tcpServer.initserver(atoi(argv[1]))==false)
    {
        cout<<atoi(argv[1])<<endl;
        //因为ip地址设置为任意，所以只要端口没有被占用就会成功
        logFile.write("tcp server init failed \n");
        return -1;
    }
    while(1)
    {
        //等待客户端的链接
        if(tcpServer.accept()==false)
        {
            logFile.write("accept is failed\n");
            FathExit(-1);
        }
        logFile.write("accept (%s) suc\n",tcpServer.getip());
        if(fork()>0)
        {
            //父进程退出继续等待accept
            tcpServer.closeclient();
            continue;
        }
        //子进程操作,并且重新设置子进程信号
        signal(2,ChildExit);
        signal(15,ChildExit);
        //子进程关闭监听fd
        tcpServer.closelisten();
        //子进程处理客户端请求
        if(clientLogin()==false)
        {
            ChildExit(-1);
        }
        //客户端连接上,并且把进程的心跳加入共享内存
        pactive.addpinfo(ArgInfo.timeout,ArgInfo.pidName);
        //如果clientType==1,调用上传文件的主函数
        if(ArgInfo.clientType==1)
        {
            cout<<1<<endl;
            recvFile();
        }
        else
        {
            cout<<2<<endl;
            /* sendFile();//下载文件函数 */
        }
        //处理完成后
        ChildExit(0);
    }
    return 0;   
}

// 父进程退出函数。
void FathExit(int sig)
{
    // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
    signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

    logFile.write("父进程退出，sig=%d。\n",sig);

    tcpServer.closelisten();    // 关闭监听的socket。

    kill(0,15);     // 通知全部的子进程退出。

    exit(0);
}
// 子进程退出函数。
void ChildExit(int sig)  
{
    // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
    signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

    logFile.write("子进程退出，sig=%d。\n",sig);

    tcpServer.closeclient();    // 关闭客户端的socket。

    exit(0);
}

void useHelp()
{
     printf("Using:./fileserver port logfile\n");
      printf("Example:./fileserver 5005 ~/log/idc/fileserver.log\n");
      printf("         ~/project/tools/bin/procctl 10 ~/project/tools/bin/fileserver 5005 ~/log/idc/fileserver.log\n\n\n"); 
}
bool clientLogin()//客户端连接函数
{
    // 接收客户端的登录报文。
    if (tcpServer.read(strrecvbuffer,10)==false)
    {
        logFile.write("tcpServer.read() failed.\n"); return false;
    }
    logFile.write("strrecvbuffer=%s\n",strrecvbuffer.c_str());

    // 解析客户端登录报文，不需要对参数做合法性判断，客户端已经判断过了。
    memset(&ArgInfo,0,sizeof(struct arg_t));
    getxmlbuffer(strrecvbuffer,"clientType",ArgInfo.clientType);
    logFile.write("ctype=%d\n",ArgInfo.clientType);
    getxmlbuffer(strrecvbuffer,"cPath",ArgInfo.cPath);
    logFile.write("cpath before =%s\n",ArgInfo.cPath);
    string tmp="/home/";
    const char *usr=getlogin();
    tmp=tmp+usr+ArgInfo.cPath;
    bzero(&ArgInfo.cPath,sizeof(ArgInfo.cPath));
    strncpy(ArgInfo.cPath,tmp.c_str(),tmp.size());
    tmp.clear();
    logFile.write("对端地址%s\n",ArgInfo.cPath);
    getxmlbuffer(strrecvbuffer,"sPath",ArgInfo.sPath);
    tmp=string("/home/")+usr+ArgInfo.sPath;
    bzero(&ArgInfo.sPath,sizeof(ArgInfo.sPath));
    strncpy(ArgInfo.sPath,tmp.c_str(),tmp.size());
    logFile.write("服务端地址%s\n",ArgInfo.sPath);
    tmp.clear();
    getxmlbuffer(strrecvbuffer,"sBkPath",ArgInfo.sBkPath);
    tmp=string("/home/")+usr+ArgInfo.sBkPath;
    bzero(&ArgInfo.sBkPath,sizeof(ArgInfo.sBkPath));
    strncpy(ArgInfo.sBkPath,tmp.c_str(),tmp.size());
    logFile.write("服务端备份地址%s\n",ArgInfo.sBkPath);
    tmp.clear();
    getxmlbuffer(strrecvbuffer,"andChild",ArgInfo.andChild);
    getxmlbuffer(strrecvbuffer,"type",ArgInfo.type);
    getxmlbuffer(strrecvbuffer,"matcher",ArgInfo.matcher);

    getxmlbuffer(strrecvbuffer,"time",ArgInfo.time);        // 执行任务的周期。
    getxmlbuffer(strrecvbuffer,"timeout",ArgInfo.timeout);     // 进程超时的时间。
    getxmlbuffer(strrecvbuffer,"pidName",ArgInfo.pidName,50);    // 进程名。

    // 为什么要判断客户端的类型？不是只有1和2吗？ 防止非法的连接请求。
    if ( (ArgInfo.clientType!=1) && (ArgInfo.clientType!=2) )
        strsendbuffer="failed";
    else
        strsendbuffer="ok";

    if (tcpServer.write(strsendbuffer)==false)
    {
        logFile.write("tcpserver.write() failed.\n"); return false;
    }

    logFile.write("%s login %s.\n",tcpServer.getip(),strsendbuffer.c_str());

    return true;

}
void recvFile()//接收文件函数
{
    while(1)
    {
        pactive.uptatime();

        //接收客户端的报文
        if(tcpServer.read(strrecvbuffer,ArgInfo.time+10)==false)
        {
            logFile.write("tcpserver read() failed\n");
            return ;
        }
        //处理心跳报文,模拟长时间活跃功能
        if(strrecvbuffer=="<act>ok</act>")
        {
            strsendbuffer="ok";
            if(tcpServer.write(strsendbuffer)==false)
            {
                logFile.write("tcpServer write failed\n");
                return ;
            }

        }
        //处理上传文件的请求报文
        if(strrecvbuffer.find("<filename>")!=string::npos)
        {
            string cFname;//对端文件名
            string cFtime;//文件时间
            int fSize;//文件大小
            getxmlbuffer(strrecvbuffer,"filename",cFname);
            getxmlbuffer(strrecvbuffer,"mtime",cFtime);
            getxmlbuffer(strrecvbuffer,"size",fSize);
            //客户端和服务端的文件目录不一样，注意以下代码的第三个参数
            logFile.write("原始对端文件名%s\n",cFname.c_str());
            string sFname;
            sFname=cFname;
            logFile.write("对端文件目录%s\n",ArgInfo.cPath);
            logFile.write("服务端文件目录%s\n",ArgInfo.sPath);
            logFile.write("对端文件名%s\n",sFname.c_str());
            replacestr(sFname,ArgInfo.cPath,ArgInfo.sPath,false);
            logFile.write("文件名替换后%s\n",sFname.c_str());
            logFile.write("recv (%s) size=%d...",sFname.c_str(),fSize);
            //开始接收文件内容
            if(recvFile(sFname,cFtime,fSize)==true)
            {
                //接收成功
                logFile<<"ok\n";
                sformat(strsendbuffer,"<filename>%s</filename><result>ok</result>",cFname.c_str());
            }
            else
            {
                logFile<<"failed\n";
                sformat(strsendbuffer,"<filename>%s</filename><result>failed</result>",cFname.c_str());
            }
            //把确认报文返回回去
            if(tcpServer.write(strsendbuffer)==false)
            {
                logFile.write("tcpServer write() failed \n");
                return ;
            }
        }
    }
}

bool recvFile(const string&name,const string &time,int size)
{
    int  totalbytes=0;          // 已接收文件的总字节数。
    int  onread=0;              // 本次打算接收的字节数。
    char buffer[4096];        // 接收文件内容的缓冲区。
    cofile ofile;                   // 写入文件的对象。

    // 必须以二进制的方式操作文件。
    if (ofile.open(name,true,ios::out|ios::binary)==false) return false;

    while (true)
    {
        memset(buffer,0,sizeof(buffer));

        // 计算本次应该接收的字节数。
        if (size-totalbytes>4096) onread=4096;
        else onread=size-totalbytes;

        // 接收文件内容。
        if (tcpServer.read(buffer,onread)==false)  return false; 

        // 把接收到的内容写入文件。
        ofile.write(buffer,onread);

        // 计算已接收文件的总字节数，如果文件接收完，跳出循环。
        totalbytes=totalbytes+onread;

        if (totalbytes==size) break;
    }

    ofile.closeandrename();

    // 文件时间用当前时间没有意义，应该与对端的文件时间保持一致。
    setmtime(name,time);
    return true;
}
bool sendFile()//下载函数
{

}

