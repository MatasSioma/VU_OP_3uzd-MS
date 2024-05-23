#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "vector.h"
#include "pazymiai.h"


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

// Kitos funkcijos 
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        if (other.size_ > capacity_) {
            T* new_data = new T[nextCapacity(other.size_)];
            std::copy(other.data_, other.data_ + other.size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = nextCapacity(other.size_);
        } else {
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
        size_ = other.size_;
    }
    return *this;
}

// Move assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
void Vector<T>::reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        T* new_data = new T[new_cap];
        std::move(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }
}

template<typename T>
void Vector<T>::resize(size_t count, const T& value) {
    if (count > size_) {
        if (count > capacity_) {
            reserve(count);
        }
        std::fill(data_ + size_, data_ + count, value);
    }
    size_ = count;
}

template<typename T>
void Vector<T>::resize(size_t count) {
    resize(count, T());
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) reserve(nextCapacity(size_ + 1));
    data_[size_++] = value;
}

// Push back an element (move)
template<typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_) reserve(nextCapacity(size_ + 1));
    data_[size_++] = std::move(value);
}

// Clear the vector
template<typename T>
void Vector<T>::clear() noexcept {
    size_ = 0;
}

// Remove the last element
template<typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (size_ < capacity_) {
        T* new_data = new T[size_];
        std::move(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
}

template<typename T>
void Vector<T>::assign(size_t n, const T& value) {
    if (n > capacity_) reserve(n);
    for (size_t i = 0; i < n; i++) {
        data_[i] = value;
    }
    size_ = n;
}

template<typename T>
void Vector<T>::insert(size_t index, const T& value) {
    if (size_ == capacity_) reserve(nextCapacity(size_ + 1));
    for (size_t i = size_; i > index; i--) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
    size_++;
}

template<typename T>
void Vector<T>::insert_range(size_t index, size_t n, const T& value) {
    if (size_ + n > capacity_) reserve(nextCapacity(size_ + n));
    for (size_t i = size_ + n - 1; i > index + n - 1; i--) {
        data_[i] = data_[i - n];
    }
    for (size_t i = index; i < index + n; i++) {
        data_[i] = value;
    }
    size_ += n;
}

template<typename T>
void Vector<T>::emplace(size_t index, T&& value) {
    if (index > size_) throw std::out_of_range("Index out of range");
    if (size_ == capacity_) reserve(nextCapacity(size_ + 1));

    for (size_t i = size_; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = std::move(value);
    size_++;
}

template<typename T>
void Vector<T>::emplace_back(T&& value) {
    if (size_ == capacity_) reserve(nextCapacity(size_ + 1));
    data_[size_++] = std::move(value);
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (size_ != other.size_) {
        return false;
    }
    return std::equal(data_, data_ + size_, other.data_);
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
    return !(*this == other);
}

template class Vector<int>;
template class Vector<double>;
template class Vector<std::string>;
template class Vector<Studentas>;

// template class Vector<Studentas>;
