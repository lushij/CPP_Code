#include <iostream>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/OstreamAppender.hh>

using std::cout;
using std::endl;
using namespace log4cpp;
 
void test0() 
{
	//1. 创建目的地对象
	OstreamAppender * posAp = new OstreamAppender("console", &cout);//(参数1，参数2)：参数1对该目的地起一个名字，参数2指定输出的流对象
	//2. 设置目的地的日志布局
	posAp->setLayout(new BasicLayout());

	//3. 创建Category对象
	Category & root = Category::getRoot();
	//4. 设置好优先级
	root.setPriority(Priority::DEBUG);// 给Category对象设置优先级
	
	root.setAppender(posAp);
	Category & module1 = root.getInstance("register");

	//5. 进行日志记录
	root.emerg("this is an emerge message");//本条日志的级别是emerg级别
	root.alert("this is an alert message");
	root.crit("this is a crit message");
	root.error("this is an error message");
	root.warn("this is a warn message");
	root.notice("this is a notice message");
	root.info("this is an info message");
	root.debug("this is a debug message");

	module1.debug("xxxxxx");

	//6. 释放申请资源,回收日志系统
	Category::shutdown();
} 
 
int main(void)
{
	test0();
	return 0;
}
