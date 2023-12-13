#include <iostream>
#include <string>
#include <stdio.h>
#include<log4cpp/Category.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/BasicLayout.hh>//基本布局是一个简单的固定的格式
#include<log4cpp/OstreamAppender.hh>

//注意:BasicLayout格式固定，所以一般需要用自定义格式，就需要下个类型了
using namespace std;
using namespace log4cpp;

void test()
{
    //1.创建目的地对象
    OstreamAppender *posAp=new OstreamAppender("log",&cout);
    //2.设置目的地的日志布局
    //这是一个简单的目的地布局（基本类型）
    posAp->setLayout(new BasicLayout());
    //3.创建Category对象
    Category &root = Category::getRoot();
    //4.设置好优先级
    root.setPriority(Priority::DEBUG);//给category对象设置优先级
    root.setAppender(posAp);//为此类别添加Appeder对象
    //还可以从root获取子模块
    Category &mod1 = root.getInstance("module1");
    //5.进行日志记录
    root.emerg("this is an emerge message");//本条日志的级别是emerg级别
	root.alert("this is an alert message");
	root.crit("this is a crit message");
	root.error("this is an error message");
	root.warn("this is a warn message");
	root.notice("this is a notice message");
	root.info("this is an info message");
	root.debug("this is a debug message");
	//还可以用子模块来写日志
    mod1.debug("xxxxxx");
    //6.释放申请资源，回收日志系统
    Category::shutdown();

}
int main()
{
    test();
    return 0;
}

