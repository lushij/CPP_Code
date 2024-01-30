#include "_public.h"
using namespace idc;

int main()
{
    cofile ofile;
    ofile.open("a.txt");
    ofile.writeline("你好世界");
    ofile.closeandrename();
    return 0;
}

