#include"_public.h"
using namespace idc;

void EXIT(int sig)
{
    printf("程序退出 接收信号为%d\n",sig);
    exit(0);
}
cpactive pactive;                 // 进程的心跳。要定义全局对象，因为exit函数不会调用局部对象的析构函数，只调用全局对象的析构函数。
int main(int argc,char*argv[])
{
    if (argc != 4)
    {
        printf("\n");
        printf("Using:~/project/tools/bin/deletefiles pathname matchstr timeout\n\n");
        printf("Example:~/project/tools/bin/deletefiles ~/tmp/idc/surfdata \"*.xml,*.json,*.csv\" 0.01\n");
        cout << R"(        ~/project/tools/bin/deletefiles ~/log/idc "*.log.20*" 0.02)" << endl;
        printf("        ~/project/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/log/idc \"*.log.20*\" 0.02\n");
        printf("        ~/project/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/tmp/idc/surfdata \"*.xml,*.json,*.csv\" 0.01\n\n");
        printf("这是一个工具程序，用于删除历史的数据文件或日志文件。\n");
        printf("本程序把pathname目录及子目录中timeout天之前的匹配matchstr文件全部删除，timeout可以是小数。\n");
        printf("本程序不写日志文件，也不会在控制台输出任何信息。\n\n\n");
        return -1;
    }
    //忽略全部信号和io
    closeioandsignal(true);//在测试阶段可以注释掉，方便调试,后期关闭注释后，后面的输出代码也不需要删除，没啥影响
    signal(2,EXIT);
    signal(15,EXIT);
    //加入心跳
    pactive.addpinfo(30,"deletefiles");
    //获取被定义为历史数据文件的时间点
    string strtimeout=ltime1("yyyymmddhh24miss",0-(int)(atof(argv[3])*24*60*60));
    //cout<<"time = "<<strtimeout<<endl; //调试信息用


    //打开目录
    cdir dir;
    if(dir.opendir(argv[1],argv[2],10000,true) == false)
    {
        printf("打开目录失败\n");
    }

    while(dir.readdir() == true)
    {
        //把文件的时间与历史文件的时间点比较，如果更早就需要删除
        if(dir.m_mtime < strtimeout )
        {
            if(remove(dir.m_ffilename.c_str()) == 0)//删除函数，C语言库函数
            {
                cout<<"remove ("<<dir.m_ffilename<<") OK"<<endl;
            }
            else
            {
                cout<<"remove ("<<dir.m_ffilename<<") ERR"<<endl;
            }
        }
    }
    return 0;


}
    