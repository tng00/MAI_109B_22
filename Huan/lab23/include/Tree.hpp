#ifndef INCLUDE_TREE_HPP_
#define INCLUDE_TREE_HPP_
#include "Node.hpp"

template<typename T>
class Tree {
 public:
  Node<T> *root;
  Tree();
  ~Tree();

  int depth() const;
  void insert(T val, Node<T> *parent = nullptr);
  void print(Node<T> *node, int depth = 0, bool check_node = true) const;
  void remove(Node<T> *node);

 private:
  int depth_helper(const Node<T> *node) const;
  Node<T> *find_parent(Node<T> *node, Node<T> *child) const;
};

#include "../src/Tree.cpp"

#endif
