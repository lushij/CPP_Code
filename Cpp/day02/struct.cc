#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
struct Stu_S{
    int _age;//企业命名法，在结构体或类中，实体即对象命名加_
    int _id;
    Stu_S()//构造函数
        :_id(0)
         ,_age(10)
    {

    }
    void print()
    {
        printf("id = %d 的学生 age = %d\n",_id,_age);
    }
};

void test()
{
    Stu_S s;//定义结构体变量时可以省略struct
    s._id=1;//在结构体中的变量默认为public
    s._age=18;
    s.print();//在C++中结构体内可以写函数，而在C语言中，需要用到函数指针来代替了
              //因此在C++中更加简单好用
    Stu_S s2;
    s2.print();
}
int main()
{
    test();
    return 0;
}

