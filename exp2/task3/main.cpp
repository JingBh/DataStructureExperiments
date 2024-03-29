#include <iostream>

#include "LinkedCircularQueue.h"

int main() {
    LinkedCircularQueue<char> queue;

    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;

    for (char i = 'a'; i <= 'e'; i++) {
        queue.enqueue(i);
    }
    std::cout << "添加元素 'a' - 'e'..." << std::endl;
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;
    std::cout << "队列内容为：" << queue << std::endl;

    while (!queue.is_empty()) {
        std::cout << "出队元素为：" << queue.dequeue() << std::endl;
    }

    for (char i = 'a'; i <= 'e'; i++) {
        queue.enqueue(i);
    }
    queue.empty();
    std::cout << (queue.is_empty() ? "队列为空" : "队列不为空") << std::endl;

    return 0;
}
