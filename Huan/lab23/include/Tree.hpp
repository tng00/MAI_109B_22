#ifndef INCLUDE_TREE_HPP_
#define INCLUDE_TREE_HPP_
#include "Node.hpp"

template<typename T>
class Tree {
 public:
  Tree() : root(nullptr) {}
  ~Tree();

  [[nodiscard]] size_t depth() const;
  Node<T> *get_root();
  Node<T> *find(const T &val, Node<T> *node);

  void insert(T val, Node<T> *parent = nullptr);
  void print(Node<T> *node, size_t depth = 0, bool check_node = true) const;
  void remove(Node<T> *node);

 private:
  Node<T> *root;
  size_t depth_helper(const Node<T> *node) const;
  Node<T> *find_parent(Node<T> *node, Node<T> *child) const;
};

#include "../src/Tree.cpp"

#endif
