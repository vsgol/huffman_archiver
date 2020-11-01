#include "CLI.hpp"
#include "HuffmanArchiver.hpp"
#include "doctest.h"

TEST_CASE("Compress and Extract: empty file") {
    {
        BitFileWriter out("Empty.txt");
    }
    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("Empty.txt", "result.o");
    huffman_extract.extractFile("result.o", "Empty_copy.txt");

    std::ifstream ifs1("Empty.txt", std::ios::binary);
    std::ifstream ifs2("Empty_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 0);
    remove("Empty.txt");
    remove("Empty_copy.txt");
    remove("result.o");
}

TEST_CASE("Compress and Extract: one letter") {
    {
        BitFileWriter out("OneChar.txt");
        out << 'F';
    }

    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("OneChar.txt", "result.o");
    huffman_extract.extractFile("result.o", "OneChar_copy.txt");

    std::ifstream ifs1("OneChar.txt", std::ios::binary);
    std::ifstream ifs2("OneChar_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 1);
    remove("OneChar.txt");
    remove("OneChar_copy.txt");
    remove("result.o");
}

TEST_CASE("Compress and Extract: many identical letters") {
    {
        BitFileWriter out("String.txt");
        for (int i = 0; i < 21; i++) {
            out << 'A';
        }
    }

    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("String.txt", "result.o");
    huffman_extract.extractFile("result.o", "String_copy.txt");

    std::ifstream ifs1("String.txt", std::ios::binary);
    std::ifstream ifs2("String_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 21);
    remove("String.txt");
    remove("String_copy.txt");
    remove("result.o");
}

TEST_CASE("Compress and Extract: big text") {
    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("Горе_от_ума.txt", "result.o");
    huffman_extract.extractFile("result.o", "Горе_от_ума_copy.txt");

    std::ifstream ifs1("Горе_от_ума.txt", std::ios::binary);
    std::ifstream ifs2("Горе_от_ума_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 280650);
    remove("Горе_от_ума_copy.txt");
    remove("result.o");
}

TEST_CASE("Compress and Extract: CMakeLists") {
    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("../CMakeLists.txt", "result.o");
    huffman_extract.extractFile("result.o", "../CMakeLists_copy.txt");

    std::ifstream ifs1("../CMakeLists.txt", std::ios::binary);
    std::ifstream ifs2("../CMakeLists_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 688);
    remove("../CMakeLists_copy.txt");
    remove("result.o");
}

TEST_CASE("Compress and Extract: All letters") {
    {
        BitFileWriter out("AllLetters.txt");
        for (int i = 0; i < 256; i++) {
            out << (char)i;
        }
    }

    HuffmanCompress huffman_compress;
    HuffmanExtract huffman_extract;

    huffman_compress.compressFile("AllLetters.txt", "result.o");
    huffman_extract.extractFile("result.o", "AllLetters_copy.txt");

    std::ifstream ifs1("test.txt", std::ios::binary);
    std::ifstream ifs2("test_copy.txt", std::ios::binary);
    std::istream_iterator<char> is1(ifs1);
    std::istream_iterator<char> is2(ifs2);

    CHECK(std::equal(is1, std::istream_iterator<char>(), is2));

    CHECK(huffman_compress.getSizeTabelle() == huffman_extract.getSizeTabelle());
    CHECK(huffman_compress.getSizeOutputFile() == huffman_extract.getSizeInputFile());
    CHECK(huffman_compress.getSizeInputFile() == huffman_extract.getSizeOutputFile());
    CHECK(huffman_compress.getSizeInputFile() == 256);
    remove("AllLetters.txt");
    remove("AllLetters_copy.txt");
    remove("result.o");
}
