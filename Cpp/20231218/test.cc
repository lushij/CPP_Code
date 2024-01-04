#include "tinyxml2.h"
#include <iostream>

int main() {
    // 创建XML文档对象
    tinyxml2::XMLDocument doc;

    // 加载XML文件
    if (doc.LoadFile("test.xml") == tinyxml2::XML_SUCCESS) {
        // 获取根元素 <people>
        tinyxml2::XMLElement* root = doc.FirstChildElement("people");

        // 遍历所有 <person> 元素
        for (tinyxml2::XMLElement* personElement = root->FirstChildElement("person"); 
             personElement; personElement = personElement->NextSiblingElement("person")) {
            // 获取姓名、年龄和性别
            const char* name = personElement->FirstChildElement("name")->GetText();
            int age;
            personElement->FirstChildElement("age")->QueryIntText(&age);
            const char* gender = personElement->FirstChildElement("gender")->GetText();

            // 输出人员信息
            std::cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender << std::endl;
        }
    } else {
        std::cerr << "Failed to load XML file." << std::endl;
        return 1;
    }

    return 0;
}

