#ifndef INCLUDE_NODE_HPP_
#define INCLUDE_NODE_HPP_
#include <iostream>
#include <algorithm>

template<typename T>
class Node {
 public:
  Node<T> **children;

  explicit Node(const T &val);
  ~Node();

  T get_value() const;
  Node<T> *get_child(size_t i);
  [[nodiscard]] size_t get_num_children() const;

  void add_child(Node<T> *child);
  void remove_child(Node<T> *child);

 private:
  T value;
  size_t num_children;
};

#include "../src/Node.cpp"

#endif
