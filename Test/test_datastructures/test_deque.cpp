#include <iostream>
#include "../../DataStructures/deque.h"  // 替换为您的deque实现文件

int main() {
    // 测试deque的基本功能
    std::cout << "Testing deque...\n";

    // 创建一个int类型的deque
    deque<int> dq;

    // 检查新创建的deque是否为空
    std::cout << "Newly created deque is " << (dq.empty() ? "empty" : "not empty") << ".\n";

    // 检查deque的大小
    std::cout << "Size of deque: " << dq.size() << "\n";

    return 0;
}
