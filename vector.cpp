#include <iostream>
#include "vector.h"
#include <cmath>

int nextCapacity(const size_t &size) {
    int pow = ceil(log((double)size) / log(2.0));
    return pow;
}

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {};

template<typename T>
Vector<T>::Vector(size_t initial_size)
    : size_(initial_size), capacity_(initial_size), data_(new T[initial_size]) {
    // Initialize memory to default of T
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = T();
    }
}