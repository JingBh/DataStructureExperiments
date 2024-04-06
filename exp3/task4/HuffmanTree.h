#ifndef EXP3TASK4_HUFFMANTREE_H
#define EXP3TASK4_HUFFMANTREE_H

#include <functional>
#include <queue>
#include <string>
#include <unordered_map>

class HuffmanTree {
public:
    struct Node {
        char c;
        int weight;
        Node *lChild, *rChild;
    };

    HuffmanTree() = delete;
    explicit HuffmanTree(const std::string &from);
    ~HuffmanTree();
    std::unordered_map<char, std::string> mapping() const;
    std::string encode(const std::string &plain) const;
    std::string decode(const std::string &encoded) const;
private:
    Node *root;
};

#endif //EXP3TASK4_HUFFMANTREE_H
