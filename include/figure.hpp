#pragma once

#include <cstring>
#include <cmath>
#include "./point.hpp"

template <Scalar T>
class Figure{
public:
    Figure() = default; 
    virtual Point<T> get_center() const noexcept = 0; 
    virtual explicit operator double() const noexcept = 0; 
    virtual ~Figure() = default; 
    static T eps;
    double scalar_prod(Point<T> p1, Point<T> p2) const noexcept;
private:
    virtual double get_square() const noexcept = 0;
    static void init_eps();
};