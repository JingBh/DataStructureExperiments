#include <cstddef>
#include <iostream>

#include "SeqList.h"

int main() {
    const SeqList<char> emptyList;
    std::cout << (emptyList.is_empty() ? "线性表为空" : "线性表不为空") << std::endl;

    SeqList list = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    std::cout << "添加元素 a-j" << std::endl;

    std::cout << "线性表内容为：" << list << std::endl;
    std::cout << "线性表长度为 " << list.size() << std::endl;
    std::cout << "获取索引为 1 的元素：" << list.get(1) << std::endl;

    std::size_t idx = list.locate('b');
    if (idx != SeqList<char>::INDEX_NOT_FOUND) {
        std::cout << "元素 'b' 的索引为：" << idx << std::endl;
    } else {
        std::cout << "找不到元素 'b'" << std::endl;
    }
    idx = list.locate('d');
    if (idx != SeqList<char>::INDEX_NOT_FOUND) {
        std::cout << "元素 'd' 的索引为：" << idx << std::endl;
    } else {
        std::cout << "找不到元素 'd'" << std::endl;
    }

    list.insert(1, 'z');
    std::cout << "在 i = 1 的位置插入元素 'z'" << std::endl;
    std::cout << "线性表内容为：" << list << std::endl;
    std::cout << "线性表长度为 " << list.size() << std::endl;

    list.remove(2);
    std::cout << "移除 i = 2 位置的元素" << std::endl;
    std::cout << "线性表内容为：" << list << std::endl;
    std::cout << "线性表长度为 " << list.size() << std::endl;

    std::cout << (list.is_empty() ? "线性表为空" : "线性表不为空") << std::endl;

    return 0;
}
