#pragma once
#include <cmath>
#include <iostream>

class Point
{
    friend Point operator+(const Point& t, const Point& other);
    friend Point operator-(const Point& t, const Point& other);
    friend bool operator==(const Point& t, const Point& other);
    friend bool operator!=(const Point& t, const Point& other);

    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

public:
    Point();
    Point(const Point& other);
    Point& operator = (const Point& other);
    Point(double x, double y);
    double x_{};
    double y_{};
};