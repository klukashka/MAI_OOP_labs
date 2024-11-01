#pragma once
#include "./figure.hpp"

template <Scalar T>
class FigureVector
{
    public:
        FigureVector();
        void resize(int new_size);
        int  size() const noexcept;
        void push_back(Figure<T>* val)noexcept;
        const Figure<T>* get(int ind) const;
        void remove(int ind) ;

        ~FigureVector();

    private:
        Figure<T>** buf;
        int size_;
        int cap;
        int head;
};