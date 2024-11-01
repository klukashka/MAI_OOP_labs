#include "../include/figure.hpp"

template <Scalar T>
double Figure<T>::scalar_prod(Point<T> p1, Point<T> p2) const noexcept {
    return p1[0] * p2[0] + p1[1] * p2[1];
}

template <Scalar T>
static void init_eps(){
    if constexpr (std::is_integral<T>::value) {
        Figure<T>::eps = 0;
    } else if constexpr (std::is_floating_point<T>::value) {
        Figure<T>::eps = std::numeric_limits<T>::epsilon();
    } else {
        static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
        "T must be either an integral or floating-point type.");
    }
}

template<Scalar T>
T Figure<T>::eps = T();