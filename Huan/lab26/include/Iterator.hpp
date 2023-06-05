#ifndef LAB26_INCLUDE_ITERATOR_HPP_
#define LAB26_INCLUDE_ITERATOR_HPP_

template<typename T>
class Queue;

template<typename T>
class Iterator {
 private:
  Node<T> *current;

 public:
  explicit Iterator(Node<T> *node) : current(node) {}

  T &operator*() const;

  Iterator &operator++();

  bool operator!=(const Iterator &other) const;
};

#include "../src/Iterator.cpp"

#endif //LAB26_INCLUDE_ITERATOR_HPP_
