#ifndef INCLUDE_NODE_HPP_
#define INCLUDE_NODE_HPP_
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Node {
 public:
  Node<T> **children;

  Node(T val);
  ~Node();

  T get_value() const;
  int  get_num_children() const;
  void add_child(Node<T> *child);
  void remove_child(Node<T> *child);

 private:
  T value;
  int num_children;
};

#include "../src/Node.cpp"

#endif
