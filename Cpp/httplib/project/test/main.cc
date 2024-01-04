#include "httplib.h"           // HTTP库
#include <jsoncpp/json/json.h> // JSON库
#include <iostream>
#include <string>

using namespace std;
void doTestGet(const httplib::Request &req, httplib::Response &res)
{
    cout << "执行doTestGet" << endl;
    // 获取请求头参数
    string userid = req.get_param_value("userid");

    // 处理逻辑......

    // 返回数据
    Json::Value resjson;
    if (userid == "1")
    {
        resjson["userid"] = userid;
        resjson["name"] = "坤坤";
        resjson["composition"] = "只因你太美";
        resjson["hobby"].append("唱");
        resjson["hobby"].append("跳");
        resjson["hobby"].append("rap");
        resjson["hobby"].append("篮球");
    }
    else
    {
        res.status = 404;
    }

    res.set_content(resjson.toStyledString(), "json");
}

int main()
{
    using namespace httplib;
    Server server;
    // Get请求
    server.Get("/test/get", doTestGet);
    // 设置监听端口
    server.listen("0.0.0.0", 8081);
}
