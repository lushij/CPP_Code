#include "_public.h"
using namespace idc;

int main()
{
    //学会使用封装的切割字符串操作
    ccmdstr cmdstr;
    string str="1,2,3,4,5";
    cmdstr.splittocmd(str,",");
    string buf;
    for(int idx=0;idx<5;++idx)
    {
        cmdstr.getvalue(idx,buf,250);
        cout<<buf<<endl;
    }
    return 0;
}

