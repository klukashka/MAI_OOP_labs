#include "../include/rectangle.hpp"

template <Scalar T>
bool Rectangle<T>::is_rectangle() const noexcept {
    double x1 = points[0][0]; double y1 = points[0][1];
    double x2 = points[1][0]; double y2 = points[1][1];
    double x3 = points[2][0]; double y3 = points[2][1];
    double x4 = points[3][0]; double y4 = points[3][1];

    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double c = sqrt(pow(std::abs(x3 - x4),2) + pow(std::abs(y3 - y4),2));
    double d = sqrt(pow(std::abs(x4 - x1),2) + pow(std::abs(y4 - y1),2));

    if (!(a == c && b == d)){
        return false;
    }
    for (int i = 1; i < 3; ++i){
        if (Figure<T>::scalar_prod(points[i] - points[i-1], points[i+1] - points[i]) > Figure<T>::eps){
            return false;
        }
    }
    if (Figure<T>::scalar_prod(points[0] - points[3], points[1] - points[0]) > Figure<T>::eps){
        return false;
    }
    if (Figure<T>::scalar_prod(points[3] - points[2], points[0] - points[3]) > Figure<T>::eps){
        return false;
    }
    return true;
}

template <Scalar T>
Rectangle<T>::Rectangle() : points{Point<T>(), Point<T>(), Point<T>(), Point<T>()} {}

template <Scalar T>
Rectangle<T>::Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) : points{p1, p2, p3, p4}  {
    if (!this->is_rectangle()){
        throw std::logic_error("Not a rectangle!");
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) : points{Point<T>(), Point<T>(), Point<T>(), Point<T>()}{
    for (int i = 0; i < 4; ++i){
        points[i] = other.points[i];
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(Rectangle<T>&& other) noexcept {
    for (int i = 0; i < 4; ++i){
        points[i] = other.points[i];
        other.points[i] = Point<T>();
    }
}

template <Scalar T>
Point<T> Rectangle<T>::get_center() const noexcept {
    Point<T> center;
    for(size_t i = 0; i < 4; ++i){
        center = center + points[i];    
    }
    center[0] = center[0] / 4;
    center[1] = center[1] / 4;
    return center;
}

template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 4; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 4; ++i){
        points[i] = std::move(other.points[i]);
        //points[i] = other.points[i];
        //other.points[i] = nullptr;
        
    }

    return *this;
}

template <Scalar T>
bool Rectangle<T>::operator==(const Rectangle<T>& other) const {
    for(size_t i = 0; i < 4; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

// template <Scalar T>
// std::ostream& operator<<(std::ostream& os, const Rectangle<T>& other){
//     // os << "Rectangle's coordinates: ";
//     for(size_t i = 0; i < 4; ++i){
//         os << other.points[i] << std::endl;
//     }
//     return os;
// }

// template <Scalar T>
// std::istream& operator>>(std::istream& is, Rectangle<T>& other) {
//     for (size_t i = 0; i < 4; ++i) {
//         is >> other.points[i];
//     }
//     return is;
// }

template <Scalar T>
double Rectangle<T>::get_square() const noexcept {
    double x1 = points[0][0]; double y1 = points[0][1];
    double x2 = points[1][0]; double y2 = points[1][1];
    double x3 = points[2][0]; double y3 = points[2][1];
    double x4 = points[3][0]; double y4 = points[3][1];
    
    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double S = a*b;
    return S;
}

template <Scalar T>
Rectangle<T>::operator double() const noexcept {
    return get_square();
}