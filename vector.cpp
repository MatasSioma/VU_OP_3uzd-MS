#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "vector.h"
// #include "pazymiai.h"


size_t nextCapacity(const size_t &size) {
    double power = ceil(log((double)size) / log(2.0));
    return pow(2.0, power);
}

//Konstruktoriai

template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {};

template<typename T>
Vector<T>::Vector(size_t initial_size)
    : size_(initial_size), capacity_(nextCapacity(initial_size)), data_(new T[nextCapacity(initial_size)]) {
    for (size_t i = 0; i < size_; i++) data_[i] = T();
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : size_(init.size()), capacity_(nextCapacity(init.size())), data_(new T[nextCapacity(init.size())]) {
    std::copy(init.begin(), init.end(), data_);
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

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
}


// Setteriai/getteriai

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
T& Vector<T>::front() {
    return data_[0];
}

template<typename T>
const T& Vector<T>::front() const {
    return data_[0];
}

template<typename T>
T& Vector<T>::back() {
    return data_[size_ - 1];
}

template<typename T>
const T& Vector<T>::back() const {
    return data_[size_ - 1];
}

template<typename T>
size_t Vector<T>::size() const noexcept {
    return size_;
}

template<typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

template<typename T>
size_t Vector<T>::capacity() const noexcept {
    return capacity_;
}

//Iteratoriu funkcijos

template<typename T>
T* Vector<T>::begin() noexcept {return data_;}
template<typename T>
const T* Vector<T>::begin() const noexcept {return data_;}
template<typename T>
T* Vector<T>::end() noexcept {return data_ + size_;}
template<typename T>
const T* Vector<T>::end() const noexcept {return data_ + size_;}

template class Vector<int>;
template class Vector<double>;
// template class Vector<Studentas>;
