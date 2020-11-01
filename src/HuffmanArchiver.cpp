#include "HuffmanArchiver.hpp"

void HuffmanCompress::compressFile(const std::string& in_file, const std::string& out_file) {
    BitFileWriter dest(out_file);
    ByteFileReader in_iterator(in_file);
    ByteFileReader Eof;

    initTabelle(in_iterator, Eof);

    in_iterator = ByteFileReader(in_file);
    compress(in_iterator, Eof, dest);
}

void HuffmanCompress::initTabelle(ByteFileReader& begin, const ByteFileReader& end) {
    size_input_file_ = 0;
    for (; begin != end; ++begin)
        tabelle_[*begin]++, ++size_input_file_;

    tree_ = HuffmanTree(tabelle_);
}

void HuffmanCompress::compress(ByteFileReader& begin,
                               const ByteFileReader& end,
                               BitFileWriter& dest) {
    size_tabelle_ += 16 + 64;
    dest << (uint16_t)tabelle_.size();
    dest << (uint64_t)size_input_file_;
    for (auto& symbol_and_freq : tabelle_) {
        std::string code = tree_.getCode(symbol_and_freq.first);

        size_tabelle_ += 16 + code.size();
        dest << symbol_and_freq.first;
        dest << (uint8_t)code.size();
        for (char symbol : code) dest << (symbol == '1');
    }

    for (; begin != end; ++begin) {
        std::string code = tree_.getCode(*begin);
        size_output_file_ += code.size();
        for (char symbol : code) dest << (symbol == '1');
    }
    size_output_file_ = (size_output_file_ + 7) >> 3;
    size_tabelle_ = (size_tabelle_ + 7) >> 3;
}

void readBinaryCode(BitFileReader& begin, std::queue<bool>& code, uint8_t size) {
    for (std::size_t index = 0; index < size; ++index) {
        bool bit;
        begin >> bit;
        code.push(bit);
    }
}

void HuffmanExtract::extractFile(const std::string& in_file, const std::string& out_file) {
    BitFileWriter dest(out_file);
    BitFileReader fileReader(in_file);
    BitFileReader Eof;

    initTabelle(fileReader);
    extract(fileReader, Eof, dest);
}

void HuffmanExtract::initTabelle(BitFileReader& begin) {
    std::uint16_t size = 0;
    size_tabelle_ = 0;
    size_input_file_ = 0;

    begin >> size;
    begin >> number_of_char_;
    size_tabelle_ += 16 + 64;

    for (std::size_t index = 0; index < size; index++) {
        uint8_t symbol = 0;
        uint8_t code_size = 0;
        std::queue<bool> code;

        begin >> symbol;
        begin >> code_size;
        readBinaryCode(begin, code, code_size);
        size_tabelle_ += 16 + code_size;
        tabelle_[symbol] = code;
    }
    size_tabelle_ = (size_tabelle_ + 7) >> 3;

    tree_  = HuffmanTree(tabelle_);
}

void HuffmanExtract::extract(BitFileReader& begin, BitFileReader end, BitFileWriter& dest) {
    for (uint64_t i = 0; i < number_of_char_; ++i) {
        uint8_t symbol;
        size_input_file_ += tree_.getSymbol(begin, end, symbol);
        size_output_file_++;
        dest << symbol;
    }
    size_input_file_ = (size_input_file_ + 7) >> 3;
}
