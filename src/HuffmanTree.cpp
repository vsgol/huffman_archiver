#include "HuffmanTree.hpp"

std::size_t HuffmanNode::getId() {
    static std::size_t shared_id = 0;
    return shared_id++;
}

HuffmanNode::HuffmanNode(std::size_t count, uint8_t symbol)
        : id_(getId())
        , count_(count)
        , symbol_(symbol) {
}

HuffmanNode::HuffmanNode(std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right)
        : left_(std::move(left))
        , right_(std::move(right))
        , id_(getId())
        , count_(left_->count_ + right_->count_)
        , symbol_('\0') {
}

bool HuffmanNode::isLeaf() const {
    return left_ == nullptr && right_ == nullptr;
}

bool HuffmanNode::NodeLess::operator()(const std::shared_ptr<HuffmanNode>& a,
                                       const std::shared_ptr<HuffmanNode>& b) {
    if (a->count_ == b->count_)
        return a->id_ < b->id_;
    return a->count_ < b->count_;
}

HuffmanTree::HuffmanTree(const std::unordered_map<uint8_t, std::size_t>& frequency_tabelle) {
    if (frequency_tabelle.empty())
        return;

    std::set<std::shared_ptr<HuffmanNode>, HuffmanNode::NodeLess> vertex_set;
    for (auto [symbol, frequency] : frequency_tabelle) {
        vertex_set.insert(std::make_shared<HuffmanNode>(frequency, symbol));
        if (frequency_tabelle.size() == 1)
            vertex_set.insert(std::make_shared<HuffmanNode>(frequency, symbol));
    }

    std::shared_ptr<HuffmanNode> tmp_v;
    while (vertex_set.size() > 1) {
        std::shared_ptr<HuffmanNode> left = *vertex_set.begin();
        vertex_set.erase(vertex_set.begin());
        std::shared_ptr<HuffmanNode> right = *vertex_set.begin();
        vertex_set.erase(vertex_set.begin());

        tmp_v = std::make_shared<HuffmanNode>(left, right);
        vertex_set.insert(tmp_v);
    }
    root_ = *vertex_set.begin();
    makeAllCodes(*root_);
}

HuffmanTree::HuffmanTree(const std::unordered_map<uint8_t, std::queue<bool>>& code_tabelle) {
    root_ = std::make_shared<HuffmanNode>();
    for (auto [symbol, code] : code_tabelle) {
        buildBranch(*root_, code, symbol);
    }
}

void HuffmanTree::buildBranch(HuffmanNode& node, std::queue<bool>& code, uint8_t symbol) {
    if (code.empty()) {
        node.symbol_ = symbol;
        return;
    }

    if (code.front()) {
        code.pop();
        if (!node.right_) {
            node.right_ = std::make_shared<HuffmanNode>();
        }
        buildBranch(*node.right_, code, symbol);
    } else {
        code.pop();
        if (!node.left_) {
            node.left_ = std::make_shared<HuffmanNode>();
        }
        buildBranch(*node.left_, code, symbol);
    }
}

void HuffmanTree::makeAllCodes(const HuffmanNode& node, const std::string& code) {
    if (node.isLeaf()) {
        symbol_to_code_[node.symbol_] = code;
        return;
    }
    makeAllCodes(*node.left_, code + '0');
    makeAllCodes(*node.right_, code + '1');
}

std::string HuffmanTree::getCode(uint8_t symbol) const {
    return symbol_to_code_.find(symbol)->second;
}
