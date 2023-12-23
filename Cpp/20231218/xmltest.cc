#include <iostream>
#include "tinyxml2.h"

int main() {
    // 加载XML文件
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("dream.xml") != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load the file." << std::endl;
        return 1;
    }

    // 获取根元素
    tinyxml2::XMLElement* root = doc.FirstChildElement("Data");
    if (!root) {
        std::cout << "Failed to find the root element." << std::endl;
        return 1;
    }

    // 读取数字
    int number;
    if (auto numberElement = root->FirstChildElement("Number")) {
        numberElement->QueryIntText(&number);
        std::cout << "Number: " << number << std::endl;
    } else {
        std::cout << "Failed to find the Number element." << std::endl;
    }

    // 读取字符串
    if (auto stringElement = root->FirstChildElement("String")) {
        const char* stringValue = stringElement->GetText();
        if (stringValue) {
            std::cout << "String: " << stringValue << std::endl;
        } else {
            std::cout << "Failed to get the String value." << std::endl;
        }
    } else {
        std::cout << "Failed to find the String element." << std::endl;
    }

    // 读取数组
    if (auto arrayElement = root->FirstChildElement("Array")) {
        for (auto item = arrayElement->FirstChildElement("Item"); item; item = item->NextSiblingElement("Item")) {
            int value;
            item->QueryIntText(&value);
            std::cout << "Array Item: " << value << std::endl;
        }
    } else {
        std::cout << "Failed to find the Array element." << std::endl;
    }

    return 0;
}

