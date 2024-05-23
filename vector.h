#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <initializer_list>

template<typename T>
class Vector {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;

    public:
        Vector();
        explicit Vector(size_t initial_size);
        Vector(std::initializer_list<T> init);
        Vector(const Vector& other);
        Vector(Vector&& other) noexcept;
        ~Vector();

        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        T& at(size_t index);
        const T& at(size_t index) const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        T* begin() noexcept;
        const T* begin() const noexcept;
        T* end() noexcept;
        const T* end() const noexcept;

        bool empty() const noexcept;
        size_t size() const noexcept;
        void reserve(size_t new_cap);
        size_t capacity() const noexcept;
        void shrink_to_fit();
        void assign(size_t n, const T& value);

        void clear() noexcept;
        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        void resize(size_t count);
        void resize(size_t count, const T& value);
        void emplace(size_t index, T&& value);
        void emplace_back(T&& value);

        bool operator==(const Vector& other) const;
        bool operator!=(const Vector& other) const;
};

size_t nextCapacity(const size_t &size);

#endif
