#pragma once
#include <iostream>
#include <limits>

template <class T, class Allocator = std::allocator<T>>
class Vector {
public:
    Vector() = default;
    Vector(size_t count, const T &value = T());
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;
    Vector(const std::initializer_list<T> &init);
    ~Vector();

    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;
    T *begin() noexcept;
    const T *begin() const noexcept;
    T *end() noexcept;
    const T *end() const noexcept;

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;

    void reserve(size_t new_cap);
    void clear();

    void push_back(const T &item);
    template <class... Args>
    T *emplace(const T *pos, Args &&...args);
    template <class... Args>
    void emplace_back(Args &&...args);
    void pop_back();
    void resize(size_t count);
    void resize(size_t count, const T &value);

    void print() const;

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *data_ = nullptr;
    Allocator allocator_;
    void reallocate(size_t minSize);
};
