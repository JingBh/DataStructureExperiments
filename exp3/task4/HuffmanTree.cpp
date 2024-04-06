#include <stdexcept>

#include "HuffmanTree.h"

void _release(HuffmanTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    _release(t->lChild);
    _release(t->rChild);
    delete t;
}

void _traversal(const HuffmanTree::Node *t, const std::string &chain, const std::function<void (const HuffmanTree::Node *, const std::string &)> &cb) {
    if (t == nullptr) {
        return;
    }
    if (t->c) {
        cb(t, chain);
    }
    _traversal(t->lChild, chain + '0', cb);
    _traversal(t->rChild, chain + '1', cb);
}

HuffmanTree::HuffmanTree(const std::string &from) {
    std::unordered_map<char, int> frequencies;
    for (const char c : from) {
        frequencies[c]++;
    }

    std::priority_queue<Node *, std::vector<Node *>, std::function<bool (Node *, Node *)>> queue{[](Node *v1, Node *v2) {
        return v1->weight > v2->weight;
    }};
    for (const auto &[c, frequency] : frequencies) {
        queue.push(new Node{c, frequency});
    }

    while (queue.size() > 1) {
        Node *left = queue.top();
        queue.pop();
        Node *right = queue.top();
        queue.pop();
        queue.push(new Node{'\0', left->weight + right->weight, left, right});
    }

    root = queue.top();
}

HuffmanTree::~HuffmanTree() {
    _release(root);
}

std::unordered_map<char, std::string> HuffmanTree::mapping() const {
    std::unordered_map<char, std::string> res;
    _traversal(root, "", [&res](const Node *node, const std::string &encoding) {
        res[node->c] = encoding;
    });
    return res;
}

std::string HuffmanTree::encode(const std::string &plain) const {
    std::string res;
    const auto _mapping = mapping();
    for (const char c : plain) {
        res += _mapping.at(c);
    }
    return res;
}

std::string HuffmanTree::decode(const std::string &encoded) const {
    std::string res;
    const Node *p = root;
    for (const char c : encoded) {
        if (c == '0') {
            p = p->lChild;
        } else if (c == '1') {
            p = p->rChild;
        } else {
            throw std::runtime_error("invalid encoding");
        }
        if (p == nullptr) {
            throw std::runtime_error("unable to decode");
        }
        if (p->c) {
            res += p->c;
            p = root;
        }
    }
    if (p != root) {
        // has incomplete character
        throw std::runtime_error("unable to decode");
    }
    return res;
}
