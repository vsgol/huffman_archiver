//
// Created by vsg on 14.04.2020.
//
#ifndef HW_03_HUFFMANTREE_HPP
#define HW_03_HUFFMANTREE_HPP

#include <algorithm>
#include <cassert>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>

class HuffmanNode {
public:
    HuffmanNode() = default;
    HuffmanNode(std::size_t count, uint8_t symbol);
    HuffmanNode(std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right);

    [[nodiscard]] bool isLeaf() const;

    class NodeLess {
    public:
        bool operator()(const std::shared_ptr<HuffmanNode>& a,
                        const std::shared_ptr<HuffmanNode>& b);
    };

    std::shared_ptr<HuffmanNode> left_ = nullptr, right_ = nullptr;
    std::size_t id_ = -1, count_ = -1;
    uint8_t symbol_ = '\0';

    static std::size_t getId();
};

class HuffmanTree {
public:
    HuffmanTree() = default;
    explicit HuffmanTree(const std::unordered_map<uint8_t, std::size_t>& frequency_tabelle);
    explicit HuffmanTree(const std::unordered_map<uint8_t, std::queue<bool>>& code_tabelle);

    template <class Iterator>
    uint8_t getSymbol(Iterator& it, Iterator end, uint8_t& symbol) const;
    [[nodiscard]] std::string getCode(uint8_t symbol) const;

private:
    void buildBranch(HuffmanNode& node, std::queue<bool>& code, uint8_t symbol);
    void makeAllCodes(const HuffmanNode& node, const std::string& code = "");

    std::unordered_map<uint8_t, std::string> symbol_to_code_ = {};
    std::shared_ptr<HuffmanNode> root_ = {};
};

template <class Iterator>
uint8_t HuffmanTree::getSymbol(Iterator& it, Iterator end, uint8_t& symbol) const {
    std::shared_ptr<HuffmanNode> cur = root_;
    uint8_t count = 0;
    for (; it != end; ++it, ++count) {
        if (*it) {
            cur = cur->right_;
        } else {
            cur = cur->left_;
        }
        if (cur->isLeaf()) {
            ++it;
            symbol = cur->symbol_;
            return ++count;
        }
    }
    return count;
}

#endif  // HW_03_HUFFMANTREE_HPP
