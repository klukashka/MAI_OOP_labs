#pragma once

#include "../include/figure.hpp"
#include <iostream>

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle();
    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    virtual Point<T> get_center() const noexcept override;

    Rectangle& operator=(const Rectangle &other);
    Rectangle& operator=(Rectangle &&other);
    bool operator==(const Rectangle &other) const;
    explicit operator double() const noexcept override;

    ~Rectangle(){};
    
    friend std::ostream& operator<<(std::ostream& os, const Rectangle<T>& other){
        for(size_t i = 0; i < 4; ++i){
            os << other.points[i] << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rectangle<T>& other) {
        for (size_t i = 0; i < 4; ++i) {
            is >> other.points[i];
        }
        return is;
    }

private:
    double get_square() const noexcept override;
    bool is_rectangle() const noexcept;
    Point<T> points[4];
};