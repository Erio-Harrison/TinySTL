#include <iostream>
#include "../../DataStructures/deque.h"  // �滻Ϊ����dequeʵ���ļ�

int main() {
    // ����deque�Ļ�������
    std::cout << "Testing deque...\n";

    // ����һ��int���͵�deque
    deque<int> dq;

    // ����´�����deque�Ƿ�Ϊ��
    std::cout << "Newly created deque is " << (dq.empty() ? "empty" : "not empty") << ".\n";

    // ���deque�Ĵ�С
    std::cout << "Size of deque: " << dq.size() << "\n";

    return 0;
}
