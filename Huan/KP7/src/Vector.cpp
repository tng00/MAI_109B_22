#include "../include/Vector.hpp"

template<class T, class Allocator>
Vector<T, Allocator>::Vector() : size_(0), capacity_(0) {
  data_ = allocator_.allocate(capacity_);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t count, const T &value) : size_(count), capacity_(calculateCapacity(count)) {
  data_ = allocator_.allocate(capacity_);
  std::fill_n(data_, count, value);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector &other) {
  size_ = other.size();
  capacity_ = other.capacity();
  data_ = allocator_.allocate(capacity_);
  std::copy(other.begin(), other.end(), data_);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector &&other) noexcept {
  size_ = other.size();
  capacity_ = other.capacity();
  data_ = allocator_.allocate(capacity_);
  std::move(other.begin(), other.end(), data_);
  other.clear();
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init) {
  size_ = init.size();
  capacity_ = calculateCapacity(size_);
  data_ = allocator_.allocate(capacity_);
  std::copy(init.begin(), init.end(), data_);
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector() {
  if (data_ != nullptr) {
    for (size_t i = 0; i < size(); i++) {
      allocator_.destroy(&data_[i]);
    }
    allocator_.deallocate(data_, capacity());
    data_ = nullptr;
  }
}

template<class T, class Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator=(const Vector &other) {
  if (this == other) {
    return *this;
  }
  size_ = other.size();
  capacity_ = other.capacity();
  data_ = allocator_.allocate(capacity_);
  std::copy(other.begin(), other.end(), data_);
  return *this;
}

template<class T, class Allocator>
T &Vector<T, Allocator>::at(size_t pos) {
  if (pos < size()) {
    return data_[pos];
  }
  throw std::out_of_range("position is out of range");
}

template<class T, class Allocator>
const T &Vector<T, Allocator>::at(size_t pos) const {
  if (pos < size()) {
    return data_[pos];
  }

  throw std::out_of_range("position is out of range");
}

template<class T, class Allocator>
T &Vector<T, Allocator>::operator[](size_t pos) {
  return data_[pos];
}

template<class T, class Allocator>
const T &Vector<T, Allocator>::operator[](size_t pos) const {
  return data_[pos];
}

template<class T, class Allocator>
T &Vector<T, Allocator>::back() {
  return data_[size() - 1];
}

template<class T, class Allocator>
const T &Vector<T, Allocator>::back() const {
  return data_[size() - 1];
}

template<class T, class Allocator>
T *Vector<T, Allocator>::data() noexcept {
  return data_;
}

template<class T, class Allocator>
const T *Vector<T, Allocator>::data() const noexcept {
  return data_;
}

template<class T, class Allocator>
T* Vector<T, Allocator>::begin() noexcept {
  return data_;
}

template<class T, class Allocator>
const T* Vector<T, Allocator>::begin() const noexcept {
  return data_;
}

template<class T, class Allocator>
T* Vector<T, Allocator>::end() noexcept {
  return begin() + size_;
}

template<class T, class Allocator>
const T* Vector<T, Allocator>::end() const noexcept {
  return begin() + size_;
}

template<class T, class Allocator>
bool Vector<T, Allocator>::empty() const {
  return size() == 0;
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::size() const {
  return size_;
}

template<class T, class Allocator>
size_t Vector<T, Allocator>::capacity() const {
  return capacity_;
}

template<class T, class Allocator>
void Vector<T, Allocator>::reserve(size_t new_cap) {
  if (new_cap > capacity()) {
    reallocate(new_cap);
  }
  capacity_ = new_cap;
}

template<class T, class Allocator>
void Vector<T, Allocator>::shrink_to_fit() {
  for (size_t i = size(); i < capacity(); i++) {
    allocator_.destroy(data() + i);
  }
  capacity_ = size();
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
  for (size_t i = 0; i < size(); i++) {
    allocator_.destroy(data() + i);
  }
  size_ = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T &item) {
  if (size() == capacity()) {
    reallocate(capacity() + 1);
  }
  allocator_.construct(end(), item);
  ++size_;
}

template<class T, class Allocator>
template<class... Args>
T *Vector<T, Allocator>::emplace(const T *pos, Args &&... args) {
  const auto index = pos - begin();
  if (index < 0 || index > size()) {
    throw std::out_of_range("Insert index is out of range");
  }
  if (size() == capacity()) {
    reallocate(capacity() + 1);
  }
  T *it = &data_[index];
  std::move(it, end(), it + 1);
  allocator_.construct(it, args...);
  ++size_;
  return it;
}

template<class T, class Allocator>
template<class... Args>
void Vector<T, Allocator>::emplace_back(Args &&... args) {
  emplace(end(), std::forward<Args>(args)...);
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
  if (size_ > 0) {
    allocator_.destroy(end() - 1);
    --size_;
  }
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count) {
  resize(count, T());
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count, const T &value) {
  if (count > capacity()) {
    reallocate(count);
    for (size_t i = size(); i < count; i++) {
      allocator_.construct(data() + i, value);
    }
  } else if (count < size()) {
    for (size_t i = count; i < size(); i++) {
      allocator_.destroy(data() + i);
    }
  }
  size_ = count;
}

template<class T, class Allocator>
[[nodiscard]] size_t Vector<T, Allocator>::calculateCapacity(size_t newSize) const {
  if (capacity() > std::numeric_limits<size_t>::max(); - capacity() / 2) {
    return newSize;
  }
  const size_t newCapacity = capacity() * 1.5;
  if (newCapacity < newSize) {
    return newSize;
  }
  return newCapacity;
}

template<class T, class Allocator>
void Vector<T, Allocator>::reallocate(size_t minSize) {
  const size_t newCapacity = calculateCapacity(minSize);
  T *newData = allocator_.allocate(newCapacity);
  for (size_t i = 0; i < size_; i++) {
    allocator_.construct(&newData[i], std::move(data_[i]));
    allocator_.destroy(&data_[i]);
  }
  allocator_.deallocate(data_, capacity());
  data_ = newData;
  capacity_ = newCapacity;
}

template<class T, class Allocator>
bool operator==(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (int i = 0; i < lhs.size(); i++) {
    if (lhs.at(i) != rhs.at(i)) {
      return false;
    }
  }
  return true;
}

template<class T, class Allocator>
bool operator!=(const Vector<T, Allocator> &lhs, const Vector<T, Allocator> &rhs) {
  return !(lhs == rhs);
}