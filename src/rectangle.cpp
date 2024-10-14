#include "../include/rectangle.hpp"

double eps = std::numeric_limits<double>::epsilon();

double scalar_prod(Point p1, Point p2) noexcept {
    return p1.x_ * p2.x_ + p1.y_ * p2.y_;
} 

bool Rectangle::is_rectangle() const noexcept {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    double x4 = points[3].x_; double y4 = points[3].y_;
    
    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double c = sqrt(pow(std::abs(x3 - x4),2) + pow(std::abs(y3 - y4),2));
    double d = sqrt(pow(std::abs(x4 - x1),2) + pow(std::abs(y4 - y1),2));

    std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    if (!(a == c && b == d)){
        return false;
    }

    for (int i = 1; i < 4; ++i){
        if (scalar_prod(points[i] - points[i-1], points[i+1] - points[i]) > eps){
            return false;
        }
    }
    if (scalar_prod(points[0] - points[3], points[1] - points[0]) > eps){
        return false;
    }
    if (scalar_prod(points[3] - points[2], points[0] - points[3]) > eps){
        return false;
    }
    return true;
}

Rectangle::Rectangle() : points{Point(), Point(), Point(), Point()} {}

Rectangle::Rectangle(Point& p1, Point& p2, Point& p3, Point& p4) : points{p1, p2, p3, p4}  {
    if (!this->is_rectangle()){
        throw std::logic_error("Not a rectangle!");
    }
}

Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) : points{p1, p2, p3, p4}  {
    if (!this->is_rectangle()){
        throw std::logic_error("Not a rectangle!");
    }
}

Point Rectangle::get_center() const noexcept {
    double x = 0, y = 0;
    for(size_t i = 0; i < 4; ++i){
        x += points[i].x_;
        y += points[i].y_;
    }
    return Point(x / 4.0, y / 4.0);
}

Rectangle& Rectangle::operator=(const Rectangle &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < 4; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

Rectangle& Rectangle::operator=(Rectangle &&other){
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

bool Rectangle::operator==(const Rectangle& other){
    for(size_t i = 0; i < 4; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& other){
    // os << "Rectangle's coordinates: ";
    for(size_t i = 0; i < 4; ++i){
        os << other.points[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& other) {
    for (size_t i = 0; i < 4; ++i) {
        is >> other.points[i];
    }
    return is;
}

double Rectangle::get_square() const noexcept {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    double x4 = points[3].x_; double y4 = points[3].y_;
    
    double a = sqrt(pow(std::abs(x1 - x2),2) + pow(std::abs(y1 - y2),2));
    double b = sqrt(pow(std::abs(x2 - x3),2) + pow(std::abs(y2 - y3),2));
    double S = a*b;
    return S;
}

Rectangle::operator double() const noexcept {
    return get_square();
}