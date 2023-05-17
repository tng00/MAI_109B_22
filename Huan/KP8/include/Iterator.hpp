#ifndef KP_8_INCLUDE_ITERATOR_HPP_
#define KP_8_INCLUDE_ITERATOR_HPP_
#include "Node.hpp"

template<typename T>
class Iterator {
 public:
  friend List<T>;

  Iterator() = default;
  explicit Iterator(Node<T> *node);
  ~Iterator() = default;

  Iterator operator++();
  Iterator operator--();

  Iterator operator+(int64_t num);
  Iterator operator-(int64_t num);

  T &operator*();
  const T &operator*() const;

  bool operator==(Iterator left) const;
  bool operator!=(Iterator left) const;

 private:
  Node<T> *node_;
};

#include "../src/Iterator.cpp"

#endif //KP_8_INCLUDE_ITERATOR_HPP_
