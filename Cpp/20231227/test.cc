#include <iostream>
#include <map>
#include <set>

int main() {
    std::map<std::string, std::set<int>> _lineNum;

    // 添加一些示例数据
    _lineNum["apple"].insert(1);
    _lineNum["apple"].insert(2);
    _lineNum["banana"].insert(3);
    _lineNum["orange"].insert(4);

    // 要查找的字符串
    std::string targetString = "apple";

    // 检查键是否存在，然后输出相应的整数集合信息
    auto it = _lineNum.find(targetString);
    if (it != _lineNum.end()) {
        std::cout << "Set for " << targetString << ": ";
        for (int num : it->second) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << targetString << " not found in the map." << std::endl;
    }

    return 0;
}

