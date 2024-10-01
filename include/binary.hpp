#pragma once
#include <iostream>
#include <string>
#include <cstring>

class Binary{
public:
    Binary();
    Binary (unsigned int other);
    Binary (const unsigned char* other, size_t other_size);
    Binary (const std::initializer_list<unsigned char>& other);
    Binary (const Binary& other);
    Binary (const std::string& other);
    Binary (const size_t n, unsigned char s);
    Binary (Binary&& other) noexcept;

    Binary& operator=(const Binary& other);
    Binary& operator=(Binary&& other) noexcept;
    bool operator==(const Binary& other) const noexcept;
    bool operator!=(const Binary& other) const noexcept;
    bool operator<(const Binary& other) const noexcept;
    bool operator>(const Binary& other) const noexcept;
    bool operator<=(const Binary& other) const noexcept;
    bool operator>=(const Binary& other) const noexcept;
    Binary operator+(const Binary& other) const noexcept;
    Binary operator-(const Binary& other) const ;

    virtual ~Binary() noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Binary& number);
private:
    size_t size_;
    unsigned char* array_;
    void invert(Binary& other) const;
    void normalize_first_zeros(Binary& other) const;
    void make_binary_of_this_size(Binary& other, size_t sz);
};