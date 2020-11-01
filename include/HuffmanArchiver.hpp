#ifndef HW_03_HUFFMANENCODER_HPP
#define HW_03_HUFFMANENCODER_HPP

#include <iterator>

#include "BitFileManipulator.hpp"
#include "ByteFileReader.hpp"
#include "HuffmanTree.hpp"

class HuffmanCompress {
public:
    void compressFile(const std::string& in_file, const std::string& out_file);

    uint64_t getSizeInputFile() const {
        return size_input_file_;
    }
    uint64_t getSizeOutputFile() const {
        return size_output_file_;
    }
    uint64_t getSizeTabelle() const {
        return size_tabelle_;
    }

private:
    void initTabelle(ByteFileReader& begin, const ByteFileReader& end);
    void compress(ByteFileReader& begin, const ByteFileReader& end, BitFileWriter& dest);

    HuffmanTree tree_;
    std::unordered_map<uint8_t, std::size_t> tabelle_;
    uint64_t size_input_file_ = 0, size_output_file_ = 0, size_tabelle_ = 0;
};

class HuffmanExtract {
public:
    void extractFile(const std::string& in_file, const std::string& out_file);

    uint64_t getSizeInputFile() const {
        return size_input_file_;
    }
    uint64_t getSizeOutputFile() const {
        return size_output_file_;
    }
    uint64_t getSizeTabelle() const {
        return size_tabelle_;
    }

private:
    void initTabelle(BitFileReader& begin);
    void extract(BitFileReader& begin, BitFileReader end, BitFileWriter& dest);

    HuffmanTree tree_;
    std::unordered_map<uint8_t, std::queue<bool>> tabelle_;
    uint64_t size_input_file_ = 0, size_output_file_ = 0, size_tabelle_ = 0;
    uint64_t number_of_char_ = 0;
};

#endif  // HW03_HUFFMANENCODER_HPP
