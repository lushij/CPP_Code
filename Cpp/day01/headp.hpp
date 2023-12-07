#pragma once
// __cplusplus只有在c++的编译器会定义
// c的编译器没有该宏
#ifdef __cplusplus
extern "C"
{
#endif
    //只要放在该区域的代码，都会按照c的方式进行调用，不会进行名字改编
    int add(int x,int y)
    {
        return x+y;
    }

#ifdef __cplusplus
}
#endif
