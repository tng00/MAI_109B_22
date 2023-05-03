#ifndef KP_7_INCLUDE_VECTOR_HPP_
#define KP_7_INCLUDE_VECTOR_HPP_
#include <iostream>
#include <limits>

template<class T, class Allocator = std::allocator<T>>
class Vector {
 public:
  Vector();
  explicit Vector(size_t count, const T &value = T());
  Vector(const Vector &other);
  Vector(Vector &&other) noexcept;
  Vector(const std::initializer_list<T>& init);
  ~Vector();
  Vector &operator=(const Vector &other);

  T &at(size_t pos);
  const T &at(size_t pos) const;
  T &operator[](size_t pos);
  const T &operator[](size_t pos) const;
  T &back();
  const T &back() const;
  T* begin() noexcept;
  const T* begin() const noexcept;
  T* end() noexcept;
  const T* end() const noexcept;

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;
  [[nodiscard]] size_t capacity() const;

  void reserve(size_t new_cap);
  void shrink_to_fit();
  void clear();

  void push_back(const T &item);
  template<class... Args>
  T* emplace(const T* pos, Args &&... args);
  template<class... Args>
  void emplace_back(Args &&... args);
  void pop_back();
  void resize(size_t count);
  void resize(size_t count, const T &value);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *data_;
  Allocator allocator_;

  T *data() noexcept;
  const T *data() const noexcept;
  [[nodiscard]] size_t calculateCapacity(size_t newSize) const;
  void reallocate(size_t minSize);
};

#include "../src/Vector.cpp"

#endif //KP_7_INCLUDE_VECTOR_HPP_
