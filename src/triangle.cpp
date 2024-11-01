#include "../include/triangle.hpp"

template <Scalar T>
Triangle<T>::Triangle() : points{Point<T>(), Point<T>(), Point<T>()} {}

template <Scalar T>
Triangle<T>::Triangle(Point<T> p1, Point<T> p2, Point<T> p3) : points{p1, p2, p3} {}

template <Scalar T>
Triangle<T>::Triangle(const Triangle<T>& other) : points{Point<T>(), Point<T>(), Point<T>()}{
    for (int i = 0; i < 3; ++i){
        points[i] = other.points[i];
    }
}

template <Scalar T>
Triangle<T>::Triangle(Triangle<T>&& other) noexcept {
    for (int i = 0; i < 3; ++i){
        points[i] = other.points[i];
        other.points[i] = Point<T>();
    }
}

template <Scalar T>
Point<T> Triangle<T>::get_center() const noexcept {
    Point<T> center;
    for(size_t i = 0; i < 3; ++i){
        center = center + points[i];    
    }
    center[0] = center[0] / 3;
    center[1] = center[1] / 3;
    return center;
}

template <Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T> &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 3; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

template <Scalar T>
Triangle<T>& Triangle<T>::operator=(Triangle<T> &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 3; ++i){
        points[i] = std::move(other.points[i]);
    }

    return *this;
}

template <Scalar T>
bool Triangle<T>::operator==(const Triangle<T>& other) const noexcept{
    for(size_t i = 0; i < 3; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

// template <Scalar T>
// std::ostream& operator<<(std::ostream& os, const Triangle<T>& other){
//     for(size_t i = 0; i < 3; ++i){
//         os << other.points[i] << std::endl;
//     }
//     return os;
// }

// template <Scalar T>
// std::istream& operator>>(std::istream& is, Triangle<T>& other) {
//     for (size_t i = 0; i < 3; ++i) {
//         is >> other.points[i];
//     }
//     return is;
// }

template <Scalar T>
double Triangle<T>::get_square() const noexcept {
    double x1 = points[0][0]; double y1 = points[0][1];
    double x2 = points[1][0]; double y2 = points[1][1];
    double x3 = points[2][0]; double y3 = points[2][1];
    
    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double c = sqrt(pow(std::abs(x1 - x3),2) + pow(std::abs(y1 - y3),2));
    double p = (a+b+c) / 2; // p - semi-perimeter
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    return S;
}

template <Scalar T>
Triangle<T>::operator double() const noexcept {
    return get_square();
}