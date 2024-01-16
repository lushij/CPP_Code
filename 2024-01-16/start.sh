#!/bin/bash
#这是启动数据共享平台的程序

#启动守护模块,建议用超级用户启动
~/project/tools/bin/procctl 10 ~/project/tools/bin/checkproc ~/tmp/log/checkproc.log

#生成气象站点的分钟数据，每一分钟运行一次
~/project/tools/bin/procctl 60 ~/project/idc/bin/crtsurfdata ~/project/idc/ini/stcode.ini ~/tmp/idc/surfdata ~/log/idc/crtsurfdata.log csv,xml,json
#清理原始的气象观测目录(~/tmp/idc/surfdata)中的历史数据文件
~/project/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/tmp/idc/surfdata "*.xml,*.csv,*.json" 0.02
#压缩日志
~/project/tools/bin/procctl 300 ~/project/tools/bin/gzipfiles ~/log/idc/  "*.log.20*" 0.02
