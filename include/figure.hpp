#pragma once

#include <cstring>
#include <cmath>
#include "./point.hpp"

class Figure{
public:
    Figure() = default; 
    virtual Point get_center() const noexcept = 0; 
    virtual explicit operator double() const noexcept = 0; 
    virtual ~Figure() = default; 
private:
    virtual double get_square() const noexcept = 0;
};