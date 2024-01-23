#开发框架的头文件路径
PUBINCL= -I ~/project/public

#开发框架的cpp文件名
PUBCPP = ~/project/public/_public.cpp

#编译参数
CFLAGS = -g -std=c++11 -lpthread 


all:procctl checkproc deletefiles gzipfiles ftpgetfiles ftpputfiles fileserver  tcpputfiles tcpgetfiles
procctl:procctl.cc
	g++  $(CFLAGS) -o procctl procctl.cc $(PUBINCL) $(PUBCPP)
	cp -f procctl ../bin/
checkproc:checkproc.cc
	g++  $(CFLAGS) -o checkproc  checkproc.cc $(PUBINCL) $(PUBCPP)
	cp -f checkproc ../bin/
deletefiles:deletefiles.cc
	g++  $(CFLAGS) -o deletefiles  deletefiles.cc $(PUBINCL) $(PUBCPP)
	cp -f deletefiles ../bin/
gzipfiles:gzipfiles.cc
	g++  $(CFLAGS) -o gzipfiles gzipfiles.cc $(PUBINCL) $(PUBCPP)
	cp -f gzipfiles ../bin/
ftpgetfiles:ftpgetfiles.cc
	g++  $(CFLAGS) -o ftpgetfiles ftpgetfiles.cc $(PUBINCL) $(PUBCPP) ~/project/public/libftp.a  ~/project/public/_ftp.cpp
	cp -f ftpgetfiles ../bin/
ftpputfiles:ftpputfiles.cc
	g++  $(CFLAGS) -o ftpputfiles ftpputfiles.cc $(PUBINCL) $(PUBCPP) ~/project/public/libftp.a  ~/project/public/_ftp.cpp
	cp -f  ftpputfiles ../bin/
fileserver:fileserver.cc
	g++  $(CFLAGS) -o fileserver fileserver.cc $(PUBINCL) $(PUBCPP) 
	cp -f  fileserver ../bin/
tcpgetfiles:tcpgetfiles.cc
	g++  $(CFLAGS) -o tcpgetfiles tcpgetfiles.cc $(PUBINCL) $(PUBCPP) 
	cp -f  tcpgetfiles ../bin/
tcpputfiles:tcpputfiles.cc
	g++  $(CFLAGS) -o tcpputfiles tcpputfiles.cc $(PUBINCL) $(PUBCPP) 
	cp -f  tcpputfiles ../bin/
clean:
	rm -rf procctl checkproc deletefiles gzipfiles ftpgetfiles ftpputfiles fileserver tcpgetfiles tcpputfiles

