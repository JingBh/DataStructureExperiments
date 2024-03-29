#include <iostream>

#include "CircularQueue.h"
#include "LinkedQueue.h"

void testCircular() {
    CircularQueue<char> queue;
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;

    for (char i = 'a'; i <= 'k'; i++) {
        queue.enqueue(i);
    }
    std::cout << "添加元素 'a' - 'k'..." << std::endl;
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;
    std::cout << "队列内容为：" << queue << std::endl;
    std::cout << "队列长度为 " << queue.size() << std::endl;

    while (!queue.is_empty()) {
        std::cout << "出队元素为：" << queue.dequeue() << std::endl;
    }

    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;
}

void testLinked() {
    LinkedQueue<char> queue;
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;

    for (char i = 'a'; i <= 'e'; i++) {
        queue.enqueue(i);
    }
    std::cout << "添加元素 'a' - 'e'..." << std::endl;
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;
    std::cout << "队列内容为：" << queue << std::endl;
    std::cout << "队列长度为 " << queue.size() << std::endl;

    while (!queue.is_empty()) {
        std::cout << "出队元素为：" << queue.dequeue() << std::endl;
    }

    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;
}

int main() {
    std::cout << '\n'
        << "===== 测试循环队列 ====="
        << '\n' << std::endl;
    testCircular();

    std::cout << '\n'
        << "===== 测试链队列 ====="
        << '\n' << std::endl;
    testLinked();

    return 0;
}
