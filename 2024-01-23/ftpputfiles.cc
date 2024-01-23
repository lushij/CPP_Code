#include "_public.h"
#include "_ftp.h"

using namespace idc;
// 结构体模块
// 参数解析到结构体
struct Info_t
{
    char host[31];          // 服务端的ip和post
    int mode;               // 传输模式
    char usr[31];           // 用户名
    char pasd[31];          // 密码
    char remotePath[256];   // 远程存放文件的目录
    char localPath[256];    // 本地存放文件的目录
    char matcher[256];      // 上传文件的匹配规则
    int type;               // 上传后处理方式，1-什么也不做，2-删除服务端文件，3-备份服务端文件
    char localBkPath[256]; // 类型3对应的备份目录
    char okFileInfo[256];   // 已上传成功的文件信息存放的文件
    int tmieout;            // 进程心跳超时的时间
    char pidName[256];      // 进程名，建议用"ftpputfiles_后缀"的方式
} ArgInfo;                  // 建立全局对象

// 文件信息的结构体
struct file_t
{
    string fName; // 文件名
    string fTime; // 文件修改时间
    file_t() = default;
    file_t(const string &name, const string &time)
        : fName(name), fTime(time)
    {
    }
    void clear()
    {
        fName.clear();
        fTime.clear();
    }
};

// 容器部分 --> 本程序需要四个容器
map<string, string> VokFile;   // 容器一：存放已上传成功文件，从ArgInfo结构体对象的okFileInfo变量中指定的文件名称中获取内容
list<struct file_t> Vdir;    // 容器二：上传前列出所要客服端中上传的文件名的容器，从本地文件目录中获取
list<struct file_t> VunDown;   // 容器三：本次不需要上传的文件的所属容器
list<struct file_t> Vupload; // 容器四：本次需要上传的文件的所属容器

// 函数声明部分
//  程序退出和信号2、15的处理函数。
void EXIT(int sig);
void help();                           // 帮助文档
bool xmlToArgInfo(const char *xmlbuf); // 解析xml到结构体变量
bool loadFile();//从本地文件目录遍历可下载文件信息
void loadOKfile();      // 加载okFileInfo文件中的数据到VoKFiLe容器中
void compmap();         // 比较vnlist和vok的信息，得到哪些是不需要下载的放在vundown，下载的放在Vupload中
void writeOkFileInfo(); // 把容器中不下载的文件即vundown中的数据写入ArgInfo.okFileInfo文件中，并且是覆盖之前的文件
void appednOkFile(struct file_t &fp);//追加到okfile的xml文件中
// 全局对象部分
clogfile logFile; // 日志对象
cftpclient ftp;   // ftp对象
cpactive Heart;   // 心跳对象

int main(int argc, char *argv[])
{
    // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程。
    // 但请不要用 "kill -9 +进程号" 强行终止。
    // closeioandsignal(true);       // 关闭0、1、2和忽略全部的信号，在调试阶段，这行代码可以不启用。
    signal(SIGINT, EXIT);
    signal(SIGTERM, EXIT);
    if (argc != 3)
    {
        help();
        return -1;
    }
    // 前提条件，解析xml
    xmlToArgInfo(argv[2]);
    cout<<"服务端地址"<<ArgInfo.remotePath<<endl;
    cout<<"本地地址"<<ArgInfo.localPath<<endl;
    cout<<"备份地址"<<ArgInfo.localBkPath<<endl;
    cout<<"已上传文件地址"<<ArgInfo.okFileInfo<<endl;
    Heart.addpinfo(ArgInfo.tmieout, sformat("getfiles_%d", getpid()));
    // 1.打开日志系统
    if (logFile.open(argv[1]) == false)
    {
        printf("打开(%s)日志失败\n", argv[1]);
        return -1;
    }
    logFile.write("打开(%s)日志成功\n", argv[1]);
    // 2.登录ftp服务器
    if (ftp.login(ArgInfo.host, ArgInfo.usr, ArgInfo.pasd, ArgInfo.mode) == false)
    {
        logFile.write("ftp login (%s %s %s %s)failed \n respond = %s", ArgInfo.host, ArgInfo.usr, ArgInfo.pasd, ArgInfo.mode, ftp.response());
        return -1;
    }
    logFile.write("ftp login ac\n");
    //3.从本地文件目录获取文件信息
    if(loadFile()==false)
    {
        logFile.write("loadfile failed\n");
        return -1;
    }
    Heart.uptatime();
    // //测试一下
    // cout<<"测试"<<endl;
    // cout<<"ArgInfo.checkTime="<<ArgInfo.checkTime<<" ArgInfo.type = "<<ArgInfo.type<<endl;
    // for(auto &x:Vnlist)
    // {
    //     logFile.write("文件名：%s 时间：%s \n",x.fName.c_str(),x.fTime.c_str());
    //     cout<<"文件名是"<<x.fName<<"时间是"<<x.fTime<<endl;
    // }

    // 6. 根据类型进行对应的上传
    if (ArgInfo.type == 1)
    {
        // 加载okFileInfo文件中的数据到VoKFiLe容器中
        loadOKfile();
        // 比较vnlist和vok的信息，得到哪些是不需要下载的放在vundown，下载的放在Vupload中
        compmap();
        // 把容器中不下载的文件即vundown中的数据写入ArgInfo.okFileInfo文件中，并且是覆盖之前的文件
        writeOkFileInfo();
    }
    else
    {
        Vdir.swap(Vupload); // 为了统一下载的容器，若是类型不是1的话，nlist就是所要下载的文件，进行交换一下到vdown里
    }
    Heart.uptatime();
    string remoteFname,localFname;
    for(auto &x:Vupload)
    {
        sformat(remoteFname,"%s/%s",ArgInfo.remotePath,x.fName.c_str());//拼接服务端的下载文件所在的全路径
        sformat(localFname,"%s/%s",ArgInfo.localPath,x.fName.c_str());//文件下载本地位置的全路径
        logFile.write("put %s ...",localFname.c_str());
        //由于上传没法知道时间，那我们只能看上传文件前后该文件的大小是否发生变化，若无变化就说明上传成功，反之停止上传
        if(ftp.put(localFname,remoteFname,true)==false)
        {
            logFile<<"Failed\nresponse = "<<ftp.response()<<"\n";
            return -1;
        }
        logFile<<"OK\n";
        Heart.uptatime();
        //上传完成后进行对应类型的操作
        if(ArgInfo.type==1)
        {
            //追加到okfile的xml文件中
            appednOkFile(x);
        }
        else if(ArgInfo.type==2)
        {
            //删除服务端的文件
            if(ftp.ftpdelete(localFname)==false)
            {
                logFile.write("ftp.ftpdelete (%s) failed \nresponse = %s\n",localFname.c_str(),ftp.response());
                return -1;
            }
        }
        else
        {
            //备份
            string tmp=sformat("%s/%s",ArgInfo.localBkPath,x.fName.c_str());//生成备份文件所在的全路径
            if(ftp.ftprename(localFname,tmp)==false)
            {
                logFile.write("ftprename (%s,%s) failed \n response=%s\n",localFname.c_str(),tmp.c_str(),ftp.response());
                return -1;
            }
        }
    }
    ftp.logout();
    logFile.write("login out\n");
    return 0;
}
void EXIT(int sig)
{
    printf("收到%d信号,程序退出\n", sig);
    exit(0);
}

void help()
{
    printf("Using:~/project/tools/bin/ftpputfiles logfilename xmlbuf\n\n");
    printf("Sample:~/project/tools/bin/procctl 30 ~/project/tools/bin/ftpputfiles ~/log/idc/ftpputfiles_test.log "
           "\"<host>172.25.73.116:21</host><mode>1</mode>"
           "<usr>lu</usr><pasd>1</pasd>"
           "<remotePath>/idcdata/surfdata</remotePath><localPath>/tmp/idc/surfdata</localPath>"
           "<matcher>*.TXT</matcher>"
           "<type>1</type><okFileInfo>/idcdata/ftplist/ftpgetfiles_test.xml</okFileInfo>"
           "<timeout>30</timeout><pidName>ftpgetfiles_test</pidName>\"\n\n\n");

    printf("本程序是通用的功能模块，用于本地目录中的文件上传到服务端的ftp服务器。\n");
    printf("logfilename是本程序运行的日志文件。\n");
    printf("xmlbuf为文件下载的参数，如下：\n");
    printf("<host>172.25.73.116:21</host> 远程服务端的IP和端口。\n");
    printf("<mode>1</mode> 传输模式，1-被动模式，2-主动模式，缺省采用被动模式。\n");
    printf("<usr>lu</usr> 远程服务端ftp的用户名。\n");
    printf("<pasd>1</pasd> 远程服务端ftp的密码。\n");
    printf("<remotePath>/idcdata/surfdata</remotePath> 远程服务端存放文件的目录。\n");
    printf("<localPath>/idcdata/surfdata</localpath> 本地文件存放的目录。\n");
    printf("<matcher>SURF_ZH*.XML,SURF_ZH*.CSV</matcher> 待下载文件匹配的规则。"
           "不匹配的文件不会被下载，本字段尽可能设置精确，不建议用*匹配全部的文件。\n");
    printf("<type>1</type> 文件下载成功后，远程服务端文件的处理方式："
           "1-什么也不做；2-删除；3-备份，如果为3，还要指定备份的目录。\n");
    printf("<localBkPath>/tmp/idc/surfdatabak</localBkPath> 文件上传成功后，本地文件的备份目录，"
           "此参数只有当type=3时才有效。\n");
    printf("<okFileInfo>/idcdata/ftplist/ftpputfiles_test.xml</okFileInfo> 已下载成功文件名清单，"
           "此参数只有当type=1时才有效。\n");
    printf("<timeout>30</timeout> 下载文件超时时间，单位：秒，视文件大小和网络带宽而定。\n");
    printf("<pidName>ftpputfiles_test</pidName> 进程名，尽可能采用易懂的、与其它进程不同的名称，方便故障排查。\n\n\n");
}

bool xmlToArgInfo(const char *xmlbuf) // 解析xml到结构体变量
{
    bzero(&ArgInfo, sizeof(struct Info_t));
    getxmlbuffer(xmlbuf, "host", ArgInfo.host, 30); // 解析host
    if (strlen(ArgInfo.host) == 0)
    {
        logFile.write("host is null\n");
        return false;
    }
    getxmlbuffer(xmlbuf, "mode", ArgInfo.mode); // 解析mode
    if (ArgInfo.mode != 2)
    {
        ArgInfo.mode = 1; // 不是2就是1
    }
    getxmlbuffer(xmlbuf, "usr", ArgInfo.usr, 30); // 解析usr
    if (strlen(ArgInfo.usr) == 0)
    {
        logFile.write("usr is null\n");
        return false;
    }
    getxmlbuffer(xmlbuf, "pasd", ArgInfo.pasd, 30); // 解析pasd
    if (strlen(ArgInfo.pasd) == 0)
    {
        logFile.write("pasd is null\n");
        return false;
    }
    string tmp;
    getxmlbuffer(xmlbuf, "remotePath", ArgInfo.remotePath, 250); // 解析remotePath
    if (strlen(ArgInfo.remotePath) == 0)
    {
        logFile.write("remotePath is null\n");
        return false;
    }
    //拼接可用的路径
    sformat(tmp,"/home/%s%s",ArgInfo.usr,ArgInfo.remotePath);
    //cout<<remotePath<<endl;
    bzero(&ArgInfo.remotePath,sizeof(ArgInfo.remotePath));
    strncpy(ArgInfo.remotePath,tmp.c_str(),255);
    tmp.clear();
    // cout<<ArgInfo.remotePath<<endl;
    getxmlbuffer(xmlbuf, "localPath", ArgInfo.localPath, 250); // 解析localPath
    if (strlen(ArgInfo.localPath) == 0)
    {
        logFile.write("localPath is null\n");
        return false;
    }
    sformat(tmp,"/home/%s%s",ArgInfo.usr,ArgInfo.localPath);
    bzero(&ArgInfo.localPath,sizeof(ArgInfo.localPath));
    strncpy(ArgInfo.localPath,tmp.c_str(),255);
    tmp.clear();
    getxmlbuffer(xmlbuf, "matcher", ArgInfo.matcher, 250); // 解析匹配规则matcher
    getxmlbuffer(xmlbuf, "type", ArgInfo.type);            // 解析type
    if (ArgInfo.type == 1)
    {
        // 增量下载文件
        getxmlbuffer(xmlbuf, "okFileInfo", ArgInfo.okFileInfo, 255);//解析okfiLE路径
        if (strlen(ArgInfo.okFileInfo) == 0)
        {
            logFile.write("okFileInfo is null\n");
            return false;
        }
        sformat(tmp,"/home/%s%s",ArgInfo.usr,ArgInfo.okFileInfo);
        bzero(&ArgInfo.okFileInfo,sizeof(ArgInfo.okFileInfo));
        strncpy(ArgInfo.okFileInfo,tmp.c_str(),255);
        tmp.clear();
    
    }
    if(ArgInfo.type==3)
    {
        //备份
        //<remoteBkPath>/tmp/idc/surfdatabak</remotebKPath>"
        getxmlbuffer(xmlbuf,"localBkPath",ArgInfo.localBkPath,255);//解析备份地址
        sformat(tmp,"/home/%s%s",ArgInfo.usr,ArgInfo.localBkPath);
        bzero(&ArgInfo.localBkPath,sizeof(ArgInfo.localBkPath));
        strncpy(ArgInfo.localBkPath,tmp.c_str(),255);
        cout<<ArgInfo.localBkPath<<endl;
        tmp.clear();
    }

    getxmlbuffer(xmlbuf, "timeout", ArgInfo.tmieout); // 解析进程心跳时间
    if (ArgInfo.tmieout == 0)
    {
        logFile.write("timeout is nullptr\n");
        return false;
    }
    getxmlbuffer(xmlbuf, "pidName", ArgInfo.pidName, 50);
    return true;
}
bool loadFile()
{
    Vdir.clear();
    cdir dir;
    //不包括子目录
    if(dir.opendir(ArgInfo.localPath,ArgInfo.matcher)==false)
    {
        logFile.write("dir.opendir(%s)failed\n",ArgInfo.localPath);
        return false;
    }    
    while(1)
    {
        if(dir.readdir()==false)break;
        Vdir.emplace_back(dir.m_filename,dir.m_mtime);
    }
    return true;
}
void loadOKfile() // 加载okFileInfo的xml文件中的数据到VoKFiLe容器中
{
    VokFile.clear();
    cifile ifile;
    if (ifile.open(ArgInfo.okFileInfo) == false) return; // 若是第一次运行，没有也是正常的
    string buf;
    struct file_t fInfo;
    while (1)
    {
        fInfo.clear();
        if (ifile.readline(buf) == false)
            break;
        getxmlbuffer(buf, "fName", fInfo.fName);
        getxmlbuffer(buf, "fTime", fInfo.fTime);
        VokFile[fInfo.fName] = fInfo.fTime;
    }
}
void compmap() // 比较dir和vok的信息，得到哪些是不需要下载的放在vundown，下载的放在Vupload中
{
    VunDown.clear();
    Vupload.clear();
    for (auto &x : Vdir)
    {
        auto it = VokFile.find(x.fName);
        if (it != VokFile.end())
        { 
            // 如果时间也相同，就不需要下载
            if (it->second == x.fTime)
            {
                VunDown.push_back(x);
            }
            else
            {
                Vupload.push_back(x);
            }
        }
        else
        {
            // 若没有找到，就需要下载
            Vupload.push_back(x);
        }
    }
}
void writeOkFileInfo() // 把容器中不下载的文件即vundown中的数据写入ArgInfo.okFileInfo的xml文件中，并且是覆盖之前的文件
{
    cofile ofile; // 写数据到文件
    if (ofile.open(ArgInfo.okFileInfo) == false)
    {
        logFile.write("file.open(%s) failed.\n", ArgInfo.okFileInfo);
        return;
    }

    for (auto &x : VunDown)
    {
        ofile.writeline("<fName>%s</fName><fTime>%s</fTime>\n", x.fName.c_str(), x.fTime.c_str());
    }
    ofile.closeandrename();
}
void appednOkFile(struct file_t &fp) // 追加到okfile的xml文件中
{
    cofile ofile;
    // 以追加的方式打开文件，注意第二个参数一定要填false。
    if (ofile.open(ArgInfo.okFileInfo, false, ios::app) == false)
    {
        logFile.write("file.open(%s) failed.\n", ArgInfo.okFileInfo);
        return;
    }
    ofile.writeline("<fName>%s</fName><fTime>%s</fTime>\n", fp.fName.c_str(), fp.fTime.c_str());
}