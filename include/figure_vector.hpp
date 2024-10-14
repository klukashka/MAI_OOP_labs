#pragma once
#include "./figure.hpp"

class FigureVector
{
    public:
        FigureVector();
        void resize(int new_size);
        int  size() const noexcept;
        void push_back(Figure* val)noexcept;
        const Figure* get(int ind) const;
        void remove(int ind) ;

        ~FigureVector();

    private:
        Figure** buf;
        int size_;
        int cap;
        int head;
};