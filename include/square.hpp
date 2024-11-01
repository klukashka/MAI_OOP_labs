#pragma once

#include "../include/figure.hpp"
#include <iostream>

template <Scalar T>
class Square : public Figure<T> {
public:
    Square();
    Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Square(const Square& other);
    Square(Square&& other) noexcept;

    virtual Point<T> get_center() const noexcept override;

    Square& operator=(const Square &other);
    Square& operator=(Square &&other);
    bool operator==(const Square &other) const;
    explicit operator double() const noexcept override;

    ~Square(){};

    friend std::ostream& operator<<(std::ostream& os, const Square<T>& other){
        // os << "Square's coordinates: ";
        for(size_t i = 0; i < 4; ++i){
            os << other.points[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Square<T>& other) {
        for (size_t i = 0; i < 4; ++i) {
            is >> other.points[i];
        }
        return is;
    }

private:
    double get_square() const noexcept override;
    bool is_square() const noexcept;
    // double scalar_prod(Point p1, Point p2) const noexcept;
    Point<T> points[4];
};