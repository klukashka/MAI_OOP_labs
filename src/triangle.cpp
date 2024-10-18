#include "../include/triangle.hpp"

Triangle::Triangle() : points{Point(), Point(), Point()} {}

Triangle::Triangle(Point p1, Point p2, Point p3) : points{p1, p2, p3} {}

Triangle::Triangle(const Triangle& other) : points{Point(), Point(), Point()}{
    for (int i = 0; i < 3; ++i){
        points[i] = other.points[i];
    }
}

Triangle::Triangle(Triangle&& other) noexcept {
    for (int i = 0; i < 3; ++i){
        points[i] = other.points[i];
        other.points[i] = Point();
    }
}

Point Triangle::get_center() const noexcept {
    double x = 0, y = 0;
    for(size_t i = 0; i < 3; ++i){
        x += points[i].x_;
        y += points[i].y_;
    }
    return Point(x / 3.0, y / 3.0);
}

Triangle& Triangle::operator=(const Triangle &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 3; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

Triangle& Triangle::operator=(Triangle &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 3; ++i){
        points[i] = std::move(other.points[i]);
    }

    return *this;
}

bool Triangle::operator==(const Triangle& other) const noexcept{
    for(size_t i = 0; i < 3; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Triangle& other){
    for(size_t i = 0; i < 3; ++i){
        os << other.points[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& other) {
    for (size_t i = 0; i < 3; ++i) {
        is >> other.points[i];
    }
    return is;
}

double Triangle::get_square() const noexcept {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    
    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double c = sqrt(pow(std::abs(x1 - x3),2) + pow(std::abs(y1 - y3),2));
    double p = (a+b+c) / 2; // p - semi-perimeter
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    return S;
}

Triangle::operator double() const noexcept {
    return get_square();
}