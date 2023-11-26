#include "../include/vector.hpp"

template <class T, class Allocator>
Vector<T, Allocator>::Vector(size_t count, const T &value) : size_(count) {
    capacity_ = size_ * 2;
    data_ = allocator_.allocate(capacity_);
    std::fill_n(data_, count, value);
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector &other) {
    size_ = other.size();
    capacity_ = other.capacity();
    data_ = allocator_.allocate(capacity_);
    std::copy(other.begin(), other.end(), data_);
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(Vector &&other) noexcept {
    size_ = other.size();
    capacity_ = other.capacity();
    data_ = other.data_;
    other.data_ = nullptr;
}

template <class T, class Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator=(const Vector &other) {
    if (*this == other) {
        return *this;
    }
    clear();
    reallocate(other.capacity());
    size_ = other.size();
    std::copy(other.begin(), other.end(), data_);
    return *this;
}

template <class T, class Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator=(Vector &&other) noexcept {
    if (*this == other) {
        return *this;
    }
    size_ = other.size();
    capacity_ = other.capacity();
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const std::initializer_list<T> &init) {
    size_ = init.size();
    capacity_ = size_ * 2;
    data_ = allocator_.allocate(capacity_);
    std::copy(init.begin(), init.end(), data_);
}

template <class T, class Allocator>
Vector<T, Allocator>::~Vector() {
    if (data_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        if (capacity_ > 0) {
            allocator_.deallocate(data_, capacity_);
        }
        data_ = nullptr;
    }
}

template <class T, class Allocator>
T &Vector<T, Allocator>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("Out of range.");
    }
    return data_[pos];
}

template <class T, class Allocator>
const T &Vector<T, Allocator>::operator[](size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("Out of range.");
    }
    return data_[pos];
}


template <class T, class Allocator>
T *Vector<T, Allocator>::begin() noexcept {
    return data_;
}

template <class T, class Allocator>
const T *Vector<T, Allocator>::begin() const noexcept {
    return data_;
}

template <class T, class Allocator>
T *Vector<T, Allocator>::end() noexcept {
    return data_ + size_;
}

template <class T, class Allocator>
const T *Vector<T, Allocator>::end() const noexcept {
    return data_ + size_;
}

template <class T, class Allocator>
bool Vector<T, Allocator>::empty() const {
    return size_ == 0;
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::size() const {
    return size_;
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::capacity() const {
    return capacity_;
}

template <class T, class Allocator>
void Vector<T, Allocator>::reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        reallocate(new_cap);
    }
}

template <class T, class Allocator>
void Vector<T, Allocator>::clear() {
    for (size_t i = 0; i < size_; i++) {
        data_[i].~T();
    }
    size_ = 0;
}

template <class T, class Allocator>
void Vector<T, Allocator>::push_back(const T &item) {
    if (capacity_ == 0) {
        reallocate(1);
    } else if (size_ == capacity_) {
        reallocate(capacity_ * 2);
    }
    data_[size_] = item;
    ++size_;
}

template <class T, class Allocator>
template <class... Args>
T *Vector<T, Allocator>::emplace(const T *pos, Args &&...args) {
    size_t index = pos - data_;
    if (index > size_) {
        throw std::out_of_range("Out of range.");
    }
    if (capacity_ == 0) {
        reallocate(1);
    } else if (size_ == capacity_) {
        reallocate(capacity_ * 2);
    }
    T* it = data_ + index;
    std::move(it, data_ + size_, it + 1);
    *it = T(args...);
    ++size_;
    return it;
}

template <class T, class Allocator>
template <class... Args>
void Vector<T, Allocator>::emplace_back(Args &&...args) {
    emplace(data_ + size_, std::forward<Args>(args)...);
}

template <class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    if (size_ > 0) {
        data_[size_ - 1].~T();
        --size_;
    }
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count) {
    resize(count, T());
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count, const T &value) {
    if (count > size_) {
        reserve(count * 2);
        for (size_t i = size_; i < count; ++i) {
            data_[i] = value;
        }
    } else if (count < size()) {
        for (size_t i = count; i < size_; ++i) {
            data_[i].~T();
        }
    }
    size_ = count;
}

template <class T, class Allocator>
void Vector<T, Allocator>::print() const {
    for (size_t i = 0; i < size_; ++i) {
        std::cout << data_[i] << " ";
    }
}

template <class T, class Allocator>
void Vector<T, Allocator>::reallocate(size_t newCapacity) {
    T *newData = allocator_.allocate(newCapacity);
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = std::move(data_[i]);
    }
    if (capacity_ > 0) {
        allocator_.deallocate(data_, capacity_);
    }
    data_ = newData;
    capacity_ = newCapacity;
}

template <class T, class Allocator>
bool operator==(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    if (lhs.size_ != rhs.size_) {
        return false;
    }
    for (size_t i = 0; i < lhs.size_; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <class T, class Allocator>
bool operator!=(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
    return !(lhs == rhs);
}
