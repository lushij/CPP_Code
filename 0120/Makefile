#开发框架头文件路径
PUBINCL = -I ~/project/public

#开发框架cpp文件名,这里直接包含进来，方便调试
PUBCPP = ~/project/public/_public.cpp

#编译参数
CFLAGS = -g -std=c++11

#########################################################
#ORACLE头文件路径
ORAINCL = -I$(ORACLE_HOME)/rdbms/public -I ~/project/public/db/oracle
#oracle库文件路径
ORALIB = -L$(ORACLE_HOME)/lib -L.
#oraacle的oci库
ORALIBS = -lclntsh
#开发框架的oracle的cpp
ORACPP = ~/project/public/db/oracle/_ooci.cpp

all:crtsurfdata obtcodetodb obtmindtodb

crtsurfdata:crtsurfdata.cc
	g++ $(CFLAGS) -o crtsurfdata crtsurfdata.cc $(PUBINCL) $(PUBCPP) 
	cp crtsurfdata ../bin/
# checkproc:checkproc.cc
	# g++ $(CFLAGS) -o checkproc checkproc.cc $(PUBINCL) $(PUBCPP) 
	# cp checkproc ../bin/
	#
obtcodetodb:obtcodetodb.cc
	g++ $(CFLAGS) -o obtcodetodb  obtcodetodb.cc $(PUBINCL) $(PUBCPP) $(ORACPP) $(ORALIB) $(ORALIBS) $(ORAINCL)
	cp obtcodetodb ../bin/

obtmindtodb:obtmindtodb.cc idcapp.cc
	g++ $(CFLAGS) -o obtmindtodb obtmindtodb.cc idcapp.cc  $(PUBINCL) $(PUBCPP) $(ORACPP) $(ORALIB) $(ORALIBS) $(ORAINCL)
	cp obtmindtodb ../bin/
clean:
	rm -f crtsurfdata obtcodetodb obtmindtodb

