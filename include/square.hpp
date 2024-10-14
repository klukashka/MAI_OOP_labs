#pragma once

#include "../include/figure.hpp"
#include <iostream>

class Square : public Figure {
    friend std::ostream& operator<<(std::ostream& os, const Square& other);
    friend std::istream& operator>>(std::istream& is, Square& other);

public:
    Square();
    Square(Point& p1, Point& p2, Point& p3, Point& p4);
    Square(Point p1, Point p2, Point p3, Point p4);

    virtual Point get_center() const noexcept override;

    Square& operator=(const Square &other);
    Square& operator=(Square &&other);
    bool operator==(const Square &other);
    explicit operator double() const noexcept override;

    ~Square(){};

private:
    double get_square() const noexcept override;
    bool is_square() const noexcept;
    // double scalar_prod(Point p1, Point p2) const noexcept;
    Point points[4];
};