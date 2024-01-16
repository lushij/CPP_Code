#!/bin/bash
#这是停止全部进程
#停止调度程序
killall -9 procctl

#尝试正常停止所有服务程序
killall  crtsurfdata deletefiles gzipfiles

#睡眠5秒，给进程一个退出的时间
sleep 5

#若服务程序还没有退出就强制杀死
killall -9 crtsurfdata deletefiles gzipfiles
