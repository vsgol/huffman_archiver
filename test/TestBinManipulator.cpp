#include "BitFileManipulator.hpp"
#include "doctest.h"

TEST_CASE("Test BitFileManipulator: read and write") {
    std::ofstream("tmp");
    {
        BitFileWriter out("tmp");
        out << true << false << true << true << false << (uint8_t)(128) << -54321012 << true
            << false << true;
        out << (char)56 << 't' << 'r' << 'u' << 'e';
    }
    BitFileReader in("tmp");
    bool bit;
    uint8_t u = -14;
    bool b[4] = {true, false, false, false};
    int i = 1412;
    std::string s;

    in >> bit;
    in >> u;
    for (bool& j : b) in >> j;
    in >> i;

    CHECK(bit);
    CHECK(u == 6);
    CHECK_EQ(b[0], false);
    CHECK_EQ(b[1], false);
    CHECK_EQ(b[2], false);
    CHECK_EQ(b[3], true);
    CHECK(i == -54321012);

    in >> b[0] >> b[1] >> b[2];
    CHECK_EQ(b[0], true);
    CHECK_EQ(b[1], false);
    CHECK_EQ(b[2], true);

    for (; in != BitFileReader();) {
        char c;
        in >> c;
        s += c;
    }
    CHECK(s == "8true");
    remove("tmp");
}
