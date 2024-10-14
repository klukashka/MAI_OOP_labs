#pragma once

#include "../include/figure.hpp"
#include <iostream>

class Rectangle : public Figure {
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& f);
    friend std::istream& operator>>(std::istream& is, Rectangle& f);

public:
    Rectangle();
    Rectangle(Point& p1, Point& p2, Point& p3, Point& p4);
    Rectangle(Point p1, Point p2, Point p3, Point p4);

    virtual Point get_center() const noexcept override;

    Rectangle& operator=(const Rectangle &other);
    Rectangle& operator=(Rectangle &&other);
    bool operator==(const Rectangle &other);
    explicit operator double() const noexcept override;

    ~Rectangle(){};

private:
    double get_square() const noexcept override;
    bool is_rectangle() const noexcept;
    // double scalar_prod(Point p1, Point p2) const noexcept;
    Point points[4];
};