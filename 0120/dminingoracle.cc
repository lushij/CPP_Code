/*
 *  程序名：dminingoracle.cpp，本程序是数据中心的公共功能模块，用于从Oracle数据库源表抽取数据，生成xml文件。
 *  作者：lushij
*/
#include "_public.h"
#include "_ooci.h"
using namespace idc;
void useHelp();

int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        useHelp();
        return -1;
    }

    return 0;
}

void useHelp()
{

}
