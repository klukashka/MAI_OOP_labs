#include "../include/point.hpp"

template <Scalar T>
Point<T>::Point() noexcept : x_(0), y_(0) {}

template <Scalar T>
Point<T>::Point(T x, T y) noexcept : x_(x), y_(y) {}

template <Scalar T>
Point<T>::Point(const Point<T> &other) noexcept : x_(other.x_), y_(other.y_) {}

template <Scalar T>
Point<T> Point<T>::operator+(const Point<T>& other) const noexcept {
    return Point(x_ + other.x_, y_ + other.y_);
}   

template <Scalar T>
Point<T> Point<T>::operator-(const Point<T>& other) const noexcept {
    return Point(x_ - other.x_, y_ - other.y_);
}

template <Scalar T>
bool Point<T>::operator==(const Point<T>& other) const noexcept {
    return (x_ == other.x_) && (y_ == other.y_);
}

template <Scalar T>
bool Point<T>::operator!=(const Point<T> &other) const noexcept{
    return (x_ != other.x_) || (y_ != other.y_);
}

template <Scalar T>
bool Point<T>::operator<(const Point<T>& other) const noexcept{
    return x_ < other.x_ && y_ < other.y_;
}

template <Scalar T>
bool Point<T>::operator<=(const Point<T>& other) const noexcept{
    return x_ <= other.x_ && y_ <= other.y_;
}

template <Scalar T>
bool Point<T>::operator>(const Point<T>& other) const noexcept{
    return x_ > other.x_ && y_ > other.y_;
}

template <Scalar T>
bool Point<T>::operator>=(const Point<T>& other) const noexcept{
    return x_ >= other.x_ && y_ >= other.y_;
}

template <Scalar T>
Point<T>& Point<T>::operator=(const Point<T> &other) noexcept {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

template <Scalar T>
T& Point<T>::operator[](int ind) {
    if (ind == 0) return x_;
    if (ind == 1) return y_;
    throw std::out_of_range("Index out of range");
}

template <Scalar T>
T Point<T>::operator[](int ind) const {
    if (ind == 0) return x_;
    if (ind == 1) return y_;
    throw std::out_of_range("Index out of range");
}