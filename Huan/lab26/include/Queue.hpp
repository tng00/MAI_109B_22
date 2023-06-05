#ifndef LAB26_INCLUDE_QUEUE_HPP_
#define LAB26_INCLUDE_QUEUE_HPP_
#include "Node.hpp"
#include "Iterator.hpp"
#include <iostream>

template<typename T>
class Queue {
 private:
  Node<T> *front;
  Node<T> *rear;
  size_t size;

 public:
  Queue() : front(nullptr), rear(nullptr), size(0) {}
  ~Queue();

  void push(const T &value);
  void pop();

  T &getFront() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t getSize() const;

  Iterator<T> begin();
  Iterator<T> end();

  void mergeSort();
};

#include "../src/Queue.cpp"

#endif //LAB26_INCLUDE_QUEUE_HPP_
