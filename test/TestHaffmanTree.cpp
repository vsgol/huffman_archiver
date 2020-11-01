#include "BitFileManipulator.hpp"
#include "HuffmanTree.hpp"
#include "doctest.h"

TEST_CASE("Little tree") {
    std::shared_ptr<HuffmanNode> a(new HuffmanNode(12, 'a')), b(new HuffmanNode(1232, 'b')),
        c(new HuffmanNode(a, b)), d(new HuffmanNode(0, 'd'));
    HuffmanNode z(c, d);
    CHECK(z.symbol_ == '\0');
    CHECK(!z.isLeaf());

    CHECK(z.left_->symbol_ == '\0');
    CHECK(!z.left_->isLeaf());

    CHECK(z.left_->left_->symbol_ == 'a');
    CHECK(z.left_->right_->symbol_ == 'b');
    CHECK(z.left_->left_->isLeaf());
    CHECK(z.left_->right_->isLeaf());

    CHECK(z.right_->symbol_ == 'd');
    CHECK(z.right_->isLeaf());
}

TEST_CASE("Little HuffmanTree built by codes") {
    std::ofstream out("tmp");
    out << 1237561;
    out.close();
    BitFileReader in("tmp");

    std::string ans;
    uint8_t symbol;
    std::queue<bool> queue;
    std::unordered_map<uint8_t, std::queue<bool>> code_tabelle;

    queue.push(false), queue.push(false);
    code_tabelle['a'] = queue;
    queue.pop();
    queue.push(true);
    code_tabelle['b'] = queue;
    queue.pop(), queue.pop();
    queue.push(true);
    code_tabelle['c'] = queue;

    HuffmanTree tree(code_tabelle);
    for (; in != BitFileReader();) {
        tree.getSymbol(in, BitFileReader(), symbol);
        ans += symbol;
    }
    CHECK(ans == "cabcabaccaccaccacccbcacbbcabcbcacabca");
    remove("tmp");
}

TEST_CASE("Little HuffmanTree built by codes (only one letter)") {
    std::ofstream out("tmp");
    out << (uint8_t)0;
    out.close();
    BitFileReader in("tmp");

    std::string ans;
    uint8_t symbol;
    std::queue<bool> queue;
    std::unordered_map<uint8_t, std::queue<bool>> code_tabelle;

    queue.push(false);
    code_tabelle['a'] = queue;

    HuffmanTree tree(code_tabelle);
    for (; in != BitFileReader();) {
        tree.getSymbol(in, BitFileReader(), symbol);
        ans += symbol;
    }
    CHECK(ans == "aaaaaaaa");
    remove("tmp");
}

TEST_CASE("Little HuffmanTree built by frequencies") {
    std::unordered_map<uint8_t, std::size_t> frequency_tabelle;
    frequency_tabelle[' '] = 700;
    frequency_tabelle['a'] = 120;
    frequency_tabelle['b'] = 74;
    frequency_tabelle['c'] = 42;
    frequency_tabelle['d'] = 32;
    frequency_tabelle['e'] = 7;
    frequency_tabelle['f'] = 5;

    HuffmanTree tree(frequency_tabelle);

    CHECK(tree.getCode(' ') == "1");
    CHECK(tree.getCode('a') == "00");
    CHECK(tree.getCode('b') == "010");
    CHECK(tree.getCode('c') == "0110");
    CHECK(tree.getCode('d') == "01111");
    CHECK(tree.getCode('e') == "011101");
    CHECK(tree.getCode('f') == "011100");
}

TEST_CASE("Little HuffmanTree built by frequencies (only one letter)") {
    std::unordered_map<uint8_t, std::size_t> frequency_tabelle;
    frequency_tabelle[' '] = 700;

    HuffmanTree tree(frequency_tabelle);

    CHECK(tree.getCode(' ') == "1");
}
