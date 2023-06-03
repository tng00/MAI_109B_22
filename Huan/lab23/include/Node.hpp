#ifndef INCLUDE_NODE_HPP_
#define INCLUDE_NODE_HPP_
#include <iostream>

template<typename T>
class Tree;

template<typename T>
class Node {
 public:
  friend class Tree<T>;
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
  Node<T> **children;
};

#include "../src/Node.cpp"

#endif
