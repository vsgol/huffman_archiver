#ifndef HW_03_BITFILEMANIPULATOR_HPP
#define HW_03_BITFILEMANIPULATOR_HPP

#include <fstream>
#include <unordered_map>

class BitFileWriter {
public:
    BitFileWriter(const std::string& filename);
    ~BitFileWriter();

    template <class T>
    BitFileWriter& operator<<(T obj) {
        for (std::size_t index = 0; index < sizeof(obj) * 8; ++index)
            push_back((bool)((obj >> index) & 1));
        return *this;
    }

    BitFileWriter& operator<<(bool obj) {
        push_back(obj);
        return *this;
    }

private:
    std::ofstream out_;
    uint8_t for_record_ = 0;
    std::size_t count_ = 0;
    void writeByte();
    void push_back(bool symbol);
};

class BitFileReader {
public:
    BitFileReader() = default;
    BitFileReader(BitFileReader& other);
    BitFileReader(BitFileReader&& other);
    ~BitFileReader();
    BitFileReader(const std::string& filename);
    BitFileReader& operator=(BitFileReader other);

    [[nodiscard]] bool operator*() const;
    BitFileReader& operator++();
    [[nodiscard]] bool operator!=(const BitFileReader& other) const;
    template <class T>
    BitFileReader& operator>>(T& obj) {
        obj = 0;
        for (std::size_t index = 0; index < sizeof(obj) * 8; ++index) {
            obj |= (static_cast<std::size_t>(**this) << static_cast<std::size_t>(index));
            ++*this;
        }
        return *this;
    }

    BitFileReader& operator>>(bool& obj) {
        obj = **this;
        ++*this;
        return *this;
    }

private:
    std::ifstream in_;
    uint8_t byte_ = 0;
    std::size_t pos_byte_ = 0;
    bool eof_ = true;

    void swap(BitFileReader& other);
    uint8_t readByte();
};

#endif  // HW_03_BITFILEMANIPULATOR_HPP
