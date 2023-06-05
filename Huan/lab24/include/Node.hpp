#ifndef LAB24_CMAKE_BUILD_DEBUG_NODE_HPP_
#define LAB24_CMAKE_BUILD_DEBUG_NODE_HPP_

class ExpressionTree;

class Node {
 private:
  char data;
  Node *left, *right;

 public:
  friend class ExpressionTree;

  explicit Node(char data);

  Node(char data, Node *left, Node *right);

  ~Node();
};

#include "../src/Node.cpp"

#endif //LAB24_CMAKE_BUILD_DEBUG_NODE_HPP_
