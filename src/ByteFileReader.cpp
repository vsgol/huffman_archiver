#include "ByteFileReader.hpp"

#include <cassert>

ByteFileReader::ByteFileReader(const std::string& filename) {
    in_ = std::ifstream(filename);
    symbol_ = in_.get();
    eof_ = in_.eof();
}

ByteFileReader::ByteFileReader(ByteFileReader& other)
        : in_(move(other.in_))
        , symbol_(other.symbol_)
        , eof_(other.eof_) {
}

ByteFileReader::ByteFileReader(ByteFileReader&& other)
        : in_(move(other.in_))
        , symbol_(other.symbol_)
        , eof_(other.eof_) {
}

ByteFileReader::~ByteFileReader() {
    if (in_.is_open())
        in_.close();
}

ByteFileReader& ByteFileReader::operator=(ByteFileReader other) {
    this->swap(other);
    return *this;
}

uint8_t ByteFileReader::operator*() const {
    return symbol_;
}

ByteFileReader& ByteFileReader::operator++() {
    symbol_ = in_.get();
    eof_ = in_.eof();
    return *this;
}

bool ByteFileReader::operator!=(const ByteFileReader& other) const {
    return eof_ != other.eof_;
}

void ByteFileReader::swap(ByteFileReader& other) {
    in_.swap(other.in_);
    std::swap(symbol_, other.symbol_);
    std::swap(eof_, other.eof_);
}
