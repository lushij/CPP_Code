#pragma once
/* 最好是在声明时候写默认参数， */
/* 如果声明时候不写默认参数， */
/* 而在定义时候写默认参数， */
/* 则函数调用在函数定义之后 */
int add(int x,int y,int z);
int sub(int x,int y=0);//推荐使用
