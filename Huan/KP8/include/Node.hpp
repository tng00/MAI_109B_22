#ifndef KP_8_INCLUDE_NODE_HPP_
#define KP_8_INCLUDE_NODE_HPP_
#include <iostream>
#include "friend_class.hpp"

template<typename T>
class Node {
 public:
  friend class Iterator<T>;
  friend class List<T>;

  Node() = default;
  explicit Node(const T &val);
  ~Node() = default;

 private:
  T value_;
  Node *prev_ = nullptr;
  Node *next_ = nullptr;
};

#include "../src/Node.cpp"

#endif //KP_8_INCLUDE_NODE_HPP_
