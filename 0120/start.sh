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
#从~/tmp/idc/surfdata目录下载原始的气象观测数据文件，存放在~/idcdata/surfdata目录中
~/project/tools/bin/procctl 30 ~/project/tools/bin/ftpgetfiles ~/log/idc/ftpgetfiles_surfdata.log "<host>172.25.73.116:21</host><mode>1</mode><usr>lu</usr><pasd>1</pasd><remotePath>/tmp/idc/surfdata</remotePath><localPath>/idcdata/surfdata</localPath><matcher>SURF_ZH*.XML,SURF_ZH*.CSV</matcher><type>1</type><okFileInfo>/idcdata/ftplist/ftpgetfiles_surfdata.xml</okFileInfo><checkTime>true</checkTime><timeout>80</timeout><pidName>ftpgetfiles_surfdata</pidName>"
#清理/idcdata/surfdata目录中的0.04天之前的文件
~/procctl/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/idcdata/surfdata "*" 0.04

#把~/tmp/idc/surfdata目录中的原始文件上传到~/tmp/ftpputest目录中
#注意：需要提前创建好服务端的目录 
~/project/tools/bin/procctl 30 ~/project/tools/bin/ftpputfiles ~/log/idc/ftpputfiles_surfdata.log "<host>172.25.73.116:21</host><mode>1</mode><usr>lu</usr><pasd>1</pasd><remotePath>/tmp/ftpputest</remotePath><localPath>/tmp/idc/surfdata</localPath><matcher>SURF_ZH*.JSON</matcher><type>1</type><okFileInfo>/idcdata/ftplist/ftpgetfiles_surfdata.xml</okFileInfo><timeout>80</timeout><pidName>ftpgetfiles_surfdata</pidName>"
#清理~/tmp/ftpputest目录中0.04之前的文件
~/procctl/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/tmp/ftpputest "*" 0.04
#tcp传输的服务端
~/project/tools/bin/procctl 10 ~/project/tools/bin/fileserver 5005 ~/log/idc/fileserver.log

#把目录~/tmp/ftpputest中的文件上传到~/tmp/tcpputest目录中
~/project/tools/bin/procctl 20 ~/project/tools/bin/tcpputfiles ~/log/idc/tcpputfiles_surfdata.log "<ip>127.0.0.1</ip><port>5005</port><cPath>/tmp/ftpputest</cPath><type>1</type><sPath>/tmp/tcpputest</sPath><andchild>true</andchild><matcher>*.xml,*.json,*.csv</matcher><time>10</time><timeout>50</timeout><pidName>tcpputfiles_surfdata</pidName>"
#把目录~/tmp/tcpputest目录文件下载到~/tmp/tcpgetest目录中
~/project/tools/bin/procctl 20 ~/project/tools/bin/tcpgetfiles ~/log/idc/tcpgetfiles_surfdata.log "<ip>127.0.0.1</ip><port>5005</port><cPath>/tmp/tcpgetest</cPath><type>1</type><sPath>/tmp/tcpputest</sPath><andchild>true</andchild><matcher>*.xml,*.json,*.csv</matcher><time>10</time><timeout>50</timeout><pidName>tcpgetfiles_surfdata</pidName>"
#清理~/tmp/tcpgetest目录中的文件
~/procctl/tools/bin/procctl 300 ~/project/tools/bin/deletefiles ~/tmp/tcpgetest "*" 0.02

