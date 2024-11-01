#include "../include/figure_vector.hpp"

template <Scalar T>
FigureVector<T>::FigureVector() : buf(nullptr), size_(0), cap(3), head(0){
    buf = new Figure<T>*[cap];
    for (int i = 0; i < cap; i++) {
        buf[i] = nullptr;
    }
}

template <Scalar T>
void FigureVector<T>::resize(int new_size) {
    Figure<T>** tmp = new Figure<T>*[new_size];
    for (int i = 0; i < new_size; i++) {
        tmp[i] = nullptr;
    }
    for (int i = 0; i < size_; i++) {
        int ind = (head + i) % cap;
        tmp[i] = buf[ind];
    }
    delete [] buf;
    buf = tmp;
    cap = new_size;
    head = 0;
}

template <Scalar T>
int FigureVector<T>::size() const noexcept { 
    return size_;
}

template <Scalar T>
void FigureVector<T>::push_back(Figure<T>* val) noexcept {
    if (size_ == cap) {
        resize(cap * 2);
    }
    int ind = (head + size_) % cap;
    buf[ind] = val;
    size_++;
}

template <Scalar T>
const Figure<T>* FigureVector<T>::get(int ind) const {
    if (ind >= 0 && ind < size_) {
        int real_ind = (head + ind) % cap;
        return buf[real_ind];
    }
    throw std::out_of_range("Index is out of range");
}

template <Scalar T>
void FigureVector<T>::remove(int ind){
    if (ind < 0 || ind > size_) {
        throw std::invalid_argument("Index out of range");
    }
    Figure<T>** new_buf = new Figure<T>*[cap];

    for (int i = 0; i < ind; i++) {
        int old_ind = (head + i) % cap;
        new_buf[i] = buf[old_ind];
    }
    for (int i = ind; i < size_ - 1; i++) {
        int old_ind = (head + i + 1) % cap;
        new_buf[i] = buf[old_ind];
    }

    delete [] buf;
    buf = new_buf;
    size_--;

    if (size_ <= cap / 3) {
        resize(cap * 3/5);
    }
}

template <Scalar T>
FigureVector<T>::~FigureVector(){
    size_ = 0;
    cap = 0;
    head = 0;
    delete [] buf;
    buf = nullptr;
}