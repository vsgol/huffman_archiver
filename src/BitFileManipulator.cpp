#include "BitFileManipulator.hpp"

#include <cassert>

BitFileWriter::BitFileWriter(const std::string &filename) {
    out_.open(filename, std::ios_base::binary);
    count_ = for_record_ = 0;
}

BitFileWriter::~BitFileWriter() {
    if (!out_.is_open())
        return;
    if (count_)
        writeByte();
    out_.close();
}

void BitFileWriter::writeByte() {
    out_ << for_record_;
    //    out_.write(reinterpret_cast<char *>(&for_record_), sizeof(for_record_));
    count_ = for_record_ = 0;
}

void BitFileWriter::push_back(bool symbol) {
    for_record_ |= (symbol << count_++);
    if (count_ == 8)
        writeByte();
}

//-----------------------------------------------------------------------------

BitFileReader::BitFileReader(const std::string &filename) {
    pos_byte_ = byte_ = 0;
    in_.open(filename, std::ios_base::binary);
    eof_ = in_.eof();

    byte_ = readByte();
}

BitFileReader::BitFileReader(BitFileReader &other)
        : in_(move(other.in_))
        , byte_(other.byte_)
        , pos_byte_(other.pos_byte_)
        , eof_(other.eof_) {
}

BitFileReader::BitFileReader(BitFileReader &&other)
        : in_(move(other.in_))
        , byte_(other.byte_)
        , pos_byte_(other.pos_byte_)
        , eof_(other.eof_) {
}

BitFileReader::~BitFileReader() {
    if (in_.is_open())
        in_.close();
}

BitFileReader &BitFileReader::operator=(BitFileReader other) {
    this->swap(other);
    return *this;
}

bool BitFileReader::operator*() const {
    return static_cast<bool>((byte_ >> pos_byte_) & 1);
}

BitFileReader &BitFileReader::operator++() {
    if (++pos_byte_ == 8) {
        byte_ = readByte();
        eof_ = in_.eof();
        pos_byte_ = 0;
    }
    return *this;
}

bool BitFileReader::operator!=(const BitFileReader &other) const {
    return eof_ != other.eof_;
}

void BitFileReader::swap(BitFileReader &other) {
    in_.swap(other.in_);
    std::swap(pos_byte_, other.pos_byte_);
    std::swap(eof_, other.eof_);
    std::swap(byte_, other.byte_);
}

uint8_t BitFileReader::readByte() {
    uint8_t x;
    in_.read(reinterpret_cast<char *>(&x), sizeof(x));
    return x;
}
