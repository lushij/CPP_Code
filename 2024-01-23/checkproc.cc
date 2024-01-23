// 守护程序：检查共享内存中进程的心跳，如果超时就终止进程
#include "_public.h"
using namespace idc;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\n");
        printf("Using:./checkproc logfilename\n");
        printf("Example:~/project/tools/bin/procctl 10 ~/project/tools/bin/checkproc ~/tmp/log/checkproc.log\n\n");
        printf("本程序用于检查后台服务程序是否超时，如果已超时，就终止它。\n");
        printf("注意：\n");
        printf("  1）本程序由procctl启动，运行周期建议为10秒。\n");
        printf("  2）为了避免被普通用户误杀，本程序应该用root用户启动。\n");
        printf("  3）如果要停止本程序，只能用killall -9 终止。\n\n\n");
        return -1;
    }
    // 忽略全部的信号和io
    // closeioandsignal(true);

    // 打开日志文件
    clogfile logfile; // 程序运行的日志
    if (logfile.open(argv[1]) == false)
    {
        printf("logfile.open(%s) failed\n", argv[1]);
        return -1;
    }

    // 创建共享内存
    int shmid = -1;
    if ((shmid = shmget((key_t)SHMKEYP, MAXNUMP * sizeof(struct st_procinfo), 0666 | IPC_CREAT))== -1)
    {
        logfile.write("创建/获取共享内存(%x)失败。\n", SHMKEYP);
        return false;
    }
    // 将共享内存连接到当前进程的地址空间。
    struct st_procinfo *shm = (struct st_procinfo *)shmat(shmid, 0, 0);
    // 遍历共享内存中的全部记录，如果进程已超时就终止它
    for (int i = 0; i < MAXNUMP; ++i)
    {
        // 如果等于0 表示空闲记录
        if (shm[i].pid == 0)
        {
            continue;
        }
        // 如果记录的不等于0，表示是服务进程的心跳记录
        // 显示进程信息，程序稳定后，注释掉即可
        logfile.write("i=%d,pid=%d,pname=%s,timeout=%d\n", i, shm[i].pid, shm[i].pname, shm[i].timeout);
        // 如果进程不存在，共享内存中是残留的信息
        // 如果向进程发送0信号，判断他是否存在
        // 如果不存在，就删除它，continue；
        int ret = kill(shm[i].pid, 0); // 返回值0表示成功，-1表示失败
        if (ret == -1)
        {
            logfile.write("该进程pid = %d(%s) 已经不存在\n", shm[i].pid, shm[i].pname);
            bzero(&shm[i], sizeof(struct st_procinfo));
            continue;
        }
        // 判断进程的心跳是否超时，如果超时就终结它
        time_t now = time(0); // 获取当前时间
        // 如果进程未超时就继续
        if (now - shm[i].atime < shm[i].timeout)
            continue;

        // 一定要把进程的结构体进行备份，不能直接用共享内存的值，否则会把自己给杀死，因为杀死后，进程id变为0,再次判断会错把自己杀死
        struct st_procinfo tmp = shm[i];
        if (tmp.pid == 0)
            continue;
        // 如果超时
        logfile.write("进程pid = %d 已经超时\n", tmp.pid);
        // 发送信号15尝试正常终止
        kill(tmp.pid, 15);
        // 每隔一秒询问一次是否存在，累计5秒还没有杀死，就用9号信号强制杀死
        for (int i = 0; i < 5; ++i)
        {
            sleep(1);
            ret = kill(tmp.pid, 0);
            if (ret == -1)
                break; // 表示进程已退出
        }
        if (ret == -1)
        {
            logfile.write("该进程pid =%d 已经正常退出\n", tmp.pid);
        }
        else
        {
            kill(tmp.pid, 9);
            logfile.write("该进程pid =%d 已经强制退出\n", tmp.pid);
            bzero(&shm[i], sizeof(struct st_procinfo)); // 删除记录
        }
    }
    // 把共享内存从当前进程中分离。
    shmdt(shm);
}
