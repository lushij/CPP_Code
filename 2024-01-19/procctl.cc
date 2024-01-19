//本程序是调度程序
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;


void usingHelp()
{
    printf("Using:./procctl timetvl program argv ...\n");
    printf("Example:~/project/tools/bin/procctl 10 /usr/bin/ls -al ./\n");
    printf("本程序是服务程序的调度程序，周期性启动服务程序或shell脚本。\n");
    printf("timetvl 运行周期，单位：秒。\n");
    printf("        被调度的程序运行结束后，在timetvl秒后会被procctl重新启动。\n");
    printf("        如果被调度的程序是周期性的任务，timetvl设置为运行周期。\n");
    printf("        如果被调度的程序是常驻内存的服务程序，timetvl设置小于5秒。\n");
    printf("program 被调度的程序名，必须使用全路径。\n");
    printf("...     被调度的程序的参数。\n");
    printf("注意，本程序不会被kill杀死，但可以用kill -9强行杀死。\n\n\n");
}
int main(int argc,char*argv[])
{
    if(argc < 3)
    {
        usingHelp();
        return -1;
    }

    //关闭信号和IO，本程序不希望被打扰
    //忽略信号和关闭io
    //注意：忽略信号和关闭io后，会影响到被调度程序，因为子进程取代被调度程序，子进程会继承父进程的信号处理方式
    for(int i=0;i<65;++i)
    {
        signal(i,SIG_IGN);
        close(i);
    }
    //守护进程
    //父进程退出，让子进程继续运行并且以0号进程为新的父进程进行回收
    if(fork()!=0) exit(0);
    //子进程处理业务
    //重新恢复父进程回收子进程
    signal(SIGCHLD,SIG_DFL);
    //定义一个和argv一样的数组
    char *pargv[argc];
    int cnt=0;
    for(int i=2;i<argc;++i)
    {
        pargv[i-2]=argv[i];
    }
    pargv[argc-2]=nullptr;//手动置空
    while(1)
    {
        if(fork()==0)
        {
            //子进程处理调度程序
            execv(argv[2],pargv);
            exit(0);
        }
        else
        {
            //父进程进行回收
            wait(nullptr);
            sleep(atoi(argv[1]));//休眠后会继续执行
        }
    }


    return 0;
}

