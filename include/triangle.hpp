#pragma once

#include "../include/figure.hpp"
#include <iostream>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle();
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;

    virtual Point<T> get_center() const noexcept override;

    Triangle& operator=(const Triangle &other);
    Triangle& operator=(Triangle &&other);
    bool operator==(const Triangle &other) const noexcept;
    explicit operator double() const noexcept override;

    ~Triangle(){};

    friend std::ostream& operator<<(std::ostream& os, const Triangle<T>& other){
        for(size_t i = 0; i < 3; ++i){
            os << other.points[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Triangle<T>& other) {
        for (size_t i = 0; i < 3; ++i) {
            is >> other.points[i];
        }
        return is;
    }

private:
    double get_square() const noexcept override;
    Point<T> points[3];
};