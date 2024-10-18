#pragma once
#include "../include/figure.hpp"

double Figure::scalar_prod(Point p1, Point p2) const noexcept {
    return p1.x_ * p2.x_ + p1.y_ * p2.y_;
}

double Figure::eps = std::numeric_limits<double>::epsilon();