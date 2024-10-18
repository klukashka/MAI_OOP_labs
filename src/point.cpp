#include "../include/point.hpp"

Point::Point() : x_{0}, y_{0} {}

Point::Point(double x, double y) : x_{x}, y_{y} {}

Point::Point(const Point &other) : x_(other.x_), y_(other.y_) {}

Point operator+(const Point& t, const Point& other){
    return Point(t.x_ + other.x_, t.y_ + other.y_);
}

Point operator-(const Point& t, const Point& other){
    return Point(t.x_ - other.x_, t.y_ - other.y_);
}

bool operator==(const Point& t, const Point& other){
    return (t.x_ == other.x_) && (t.y_ == other.y_);
}

bool operator!=(const Point &t, const Point &other){
    return (t.x_ != other.x_) || (t.y_ != other.y_);
}

Point& Point::operator=(const Point &other){
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

std::istream& operator>>(std::istream &is, Point &p){
    double x, y;
    is >> x >> y;
    p.x_ = x;
    p.y_ = y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    os << "x  " << p.x_ << ", y  " << p.y_;
    return os;
}