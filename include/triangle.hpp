#pragma once

#include "../include/figure.hpp"
#include <iostream>

class Triangle : public Figure {

    friend std::ostream& operator<<(std::ostream& os, const Triangle& f);
    friend std::istream& operator>>(std::istream& is, Triangle& f);

public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;

    virtual Point get_center() const noexcept override;

    Triangle& operator=(const Triangle &other);
    Triangle& operator=(Triangle &&other);
    bool operator==(const Triangle &other) const noexcept;
    explicit operator double() const noexcept override;

    ~Triangle(){};

private:
    double get_square() const noexcept override;
    Point points[3];
};