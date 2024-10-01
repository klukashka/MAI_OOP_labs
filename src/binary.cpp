#include "../include/binary.hpp"


// ------- helpful functions and methods -----------

bool is_one_or_zero(char c){
    if (c == '0' or c == '1'){
        return true;
    }
    return false;
}

void Binary::invert(Binary& other) const {
    for (size_t i = 0; i < size_; ++i){
        if (other.array_[i] == '1'){
            other.array_[i] = '0';
        } else {
            other.array_[i] = '1';
        }
    }
}

void Binary::normalize_first_zeros(Binary& other) const {
    size_t i = other.size_;
    while(--i){
        if (other.array_[i] == '1'){
            break;
        } 
    }
    ++i;
    other.size_ = i;
    if (other.size_ == 0){
        other.size_ = 1;
        other.array_ = new unsigned char[size_];
        other.array_[0] = '0';
    }
}

void Binary::make_binary_of_this_size(Binary& other, size_t sz){
    Binary prev_other = other;
    other.array_ = new unsigned char(sz);
    other.size_ = sz;
    for (size_t i = 0; i < prev_other.size_; ++i){
        other.array_[i] = prev_other.array_[i];
    }
    for (size_t i = prev_other.size_; i < sz; ++i){
        other.array_[i] = '0';
    }
}

// ------------ constructors --------------

Binary::Binary() : size_(0), array_(nullptr){}

Binary::Binary(unsigned int other){
    if (other < 0){
        throw std::logic_error("Binary item cannot be negative");
    }
    if (other == 0){
        size_ = 1;
        array_ = new unsigned char[size_];
        array_[0] = '0';
    } else {
        size_ = sizeof(int)*8;
        array_ = new unsigned char[size_];
        for (int i = 0; i < size_/sizeof(unsigned char); ++i){
            if ((other >> i) & 1){
                array_[i] = '1';
            } else {
                array_[i] = '0';
            }
        }
        normalize_first_zeros(*this);
    }
}

Binary::Binary(const unsigned char* other, size_t other_size){
    array_ = new unsigned char[other_size];
    size_ = other_size;
    for (size_t i = 0; i < other_size; ++i){
        if (!is_one_or_zero(other[i])){
            throw std::logic_error("Not a binary number");
        }
        array_[i] = other[i];
    }
    normalize_first_zeros(*this);
}

Binary::Binary(const std::initializer_list<unsigned char>& other): array_(nullptr), size_(other.size()) {
    array_ = new unsigned char[other.size()];
    size_t i = other.size() - 1;
    for (unsigned char c : other) {
        if (!is_one_or_zero(c)) throw std::logic_error("Not a binary number");
        array_[i] = c;
        i--;
    }
    normalize_first_zeros(*this);
}

Binary::Binary(const Binary& other) : array_(nullptr), size_(other.size_){
    array_ = new unsigned char[size_]{};
    std::memcpy(array_, other.array_, other.size_);
}

Binary::Binary(const std::string& s) {
    array_ = new unsigned char[s.size()];
    size_ = s.size();
    size_t i = s.size() - 1;
    for (unsigned char c : s) {
        if (!is_one_or_zero(c)) throw std::logic_error("Not a binary number");
        array_[i] = c;
        i--;
    }
    normalize_first_zeros(*this);
}

Binary::Binary(const size_t n, unsigned char s) {
    if (!is_one_or_zero(s)) {
        throw std::logic_error("Not a binary number");
    }
    size_ = n;
    array_ = new unsigned char[n];
    for (size_t i = 0; i < n; ++i){
        array_[i] = s;
    }
    normalize_first_zeros(*this);
}

Binary::Binary(Binary&& other) noexcept : array_(other.array_), size_(other.size_){
    other.array_ = nullptr;
    other.size_ = 0;
}



// --------- operators ------------

Binary &Binary::operator=(const Binary& other) {
    if (this == &other){
        return *this;
    }
    Binary copy = other;
    std::swap(array_, copy.array_);
    std::swap(size_, copy.size_);
    return *this;
}

Binary &Binary::operator=(Binary&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (array_) {
        delete[] array_;
    }

    array_ = other.array_;
    size_ = other.size_;
    other.array_ = nullptr;
    other.size_ = 0;

    return *this;
}

bool Binary::operator==(const Binary &other) const noexcept {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (array_[i] != other.array_[i]) {
            return false;
        }
    }
    return true;
}

bool Binary::operator!=(const Binary& other) const noexcept {
    return !(*this == other);
}

bool Binary::operator<(const Binary &other) const noexcept {
    if (size_ < other.size_)
         return true;
    if (size_ > other.size_) 
         return false;
    size_t i = size_;
    while (--i){
        if (array_[i] < other.array_[i]) {
            return true;
        }
    }
    return false;
}

bool Binary::operator>(const Binary &other) const noexcept {
    return other < *this;
}

bool Binary::operator<=(const Binary &other) const noexcept {
    return !(other < *this);
}

bool Binary::operator>=(const Binary &other) const noexcept {
    return !(*this < other);
}

Binary Binary::operator+(const Binary& other) const noexcept {
    size_t max_size = std::max(other.size_, size_) + 1;
    unsigned char res[max_size];
    int remainder = 0;
    int first = 0, second = 0;
    int bin_sum;

    for (size_t i = 0; i < max_size; ++i){
        if (i < size_){
            first = array_[i] - '0';
        }
        if (i < other.size_){
            second = other.array_[i] - '0';
        }
        bin_sum = (first + second + remainder) % 2;
        res[i] = (unsigned char)(bin_sum + '0');
        remainder = (first + second + remainder) / 2;
        first = 0;
        second = 0;
    }
    if (res[max_size-1] == '0'){
        --max_size;
    }
    return Binary(res, max_size);
}

Binary Binary::operator-(const Binary& other) const {
    if (*this < other){
        throw std::logic_error("Difference is negative");
    }

    Binary res(other);
    if (this->size_ != other.size_){
        res.make_binary_of_this_size(res, this->size_); // attention!
    }
    invert(res);
    Binary one("1");
    res = *this + res + one;
    if (other.size_ < res.size_ && 1 < res.size_){
        --res.size_;
    }
    normalize_first_zeros(res);
    return res;
}

// --------- destructor --------------

Binary::~Binary() noexcept {
    if (size_ > 0) {
        size_ = 0;
        delete[] array_;
        array_ = nullptr;
    }
}

// ---------- output ----------

std::ostream& operator<<(std::ostream& os, const Binary& number) {
    size_t i = number.size_;
    while(i--) {
        os << static_cast<char>(number.array_[i]); 
    }
    return os;
}