#ifndef HW03_BYTEFILEREADER_HPP
#define HW03_BYTEFILEREADER_HPP

#include <fstream>
#include <istream>
#include <string>

class ByteFileReader {
public:
    ByteFileReader() = default;
    ByteFileReader(ByteFileReader& other);
    ByteFileReader(ByteFileReader&& other);
    ~ByteFileReader();
    ByteFileReader(const std::string& filename);
    ByteFileReader& operator=(ByteFileReader other);

    uint8_t operator*() const;
    ByteFileReader& operator++();
    [[nodiscard]] bool operator!=(const ByteFileReader& other) const;

    template <class T>
    ByteFileReader& operator>>(T& obj) {
        in_ >> obj;
        return *this;
    }

private:
    std::ifstream in_;
    uint8_t symbol_ = 0;
    bool eof_ = true;

    void swap(ByteFileReader& other);
};
#endif  //HW03_BYTEFILEREADER_HPP
