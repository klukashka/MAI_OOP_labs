#pragma once
#include <iostream>
#include <type_traits>
#include <cmath>




template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    Point() noexcept;
    Point(const Point<T>& other) noexcept;
    Point<T>& operator=(const Point<T>& other) noexcept;
    Point(T x, T y) noexcept;

    Point<T> operator+(const Point<T>& other)const noexcept;
    Point<T> operator-(const Point<T>& other)const noexcept;
    bool operator==(const Point<T>& other) const noexcept;
    bool operator!=(const Point<T>& other) const noexcept;
    bool operator<(const Point<T>& other) const noexcept;
    bool operator<=(const Point<T>& other) const noexcept;
    bool operator>(const Point<T>& other) const noexcept;
    bool operator>=(const Point<T>& other) const noexcept;
    T& operator[](int index) ;
    T operator[](int index) const;

    friend std::istream& operator>>(std::istream &is, Point<T> &p){
        is >> p.x_ >> p.y_;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p){
        os << "x  " << p[0] << ", y  " << p[1];
        return os;
    }
private:
    T x_{};
    T y_{};
};