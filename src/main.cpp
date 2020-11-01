#include <iostream>
#include <stdexcept>

#include "CLI.hpp"
#include "HuffmanArchiver.hpp"

int main(int argc, const char** argv) {
    WorkMode args;

    try {
        args = parseArgs(argc, argv);
    } catch (const std::invalid_argument& err) {
        std::cerr << err.what();
        return 1;
    }
    std::ios_base::sync_with_stdio(false);

    if (args.type_ == ActionType::compress) {
        HuffmanCompress huffman;

        huffman.compressFile(args.in_name_, args.out_name_);

        std::cout << huffman.getSizeInputFile() << '\n';
        std::cout << huffman.getSizeOutputFile() << '\n';
        std::cout << huffman.getSizeTabelle() << '\n';
    } else if (args.type_ == ActionType::extract) {
        HuffmanExtract huffman;

        huffman.extractFile(args.in_name_, args.out_name_);

        std::cout << huffman.getSizeInputFile() << '\n';
        std::cout << huffman.getSizeOutputFile() << '\n';
        std::cout << huffman.getSizeTabelle() << '\n';
    }
}
