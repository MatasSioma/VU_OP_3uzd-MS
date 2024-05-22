#include <iostream>
#include <cmath>
#include <algorithm>

#include "vector.h"

size_t nextCapacity(const size_t &size) {
    size_t capacity = 2;
    int power = ceil(log((double)size) / log(2.0));
    for (int i = 0; i < power; i++) capacity *= 2;
    return capacity;
}

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {};

template<typename T>
Vector<T>::Vector(size_t initial_size)
    : size_(initial_size), capacity_(nextCapacity(initial_size)), data_(new T[nextCapacity(initial_size)]) {
    for (size_t i = 0; i < size_; i++) data_[i] = T();
}

template<typename T>
Vector<T>::Vector(const Vector& other)
    : size_(other.size_), capacity_(other.capacity_), data_(new T[other.capacity_]) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}