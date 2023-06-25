#ifndef LAB24__EXPRESSIONTREE_HPP_
#define LAB24__EXPRESSIONTREE_HPP_

#include "Node.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "../../KP_7/include/Vector.hpp"
#include <functional>
#include <memory>

class ExpressionTree {
 public:
  ExpressionTree() = default;
  ~ExpressionTree() = default;

  std::string convertToReversePolish(const std::string &str);
  void makeInfixExpression(const Node *root);
  Node *constructTree(const std::string &postfix);
  void getCoefficients(const Node *root, char coefficient = '0');
  void factorizeQuadraticExpression(const Node *root);
  void printTree(Node const *first,
                 std::vector<std::string> const &lpref = std::vector<std::string>(),
                 std::vector<std::string> const &cpref = std::vector<std::string>(),
                 std::vector<std::string> const &rpref = std::vector<std::string>(),
                 bool root = true,
                 std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr);

 private:
  int a, b, c; // coefficients of square trinomial
  std::string a_, b_, c_; // coefficients to convert to int

  bool isOperator(char ch);
  int getPrecedence(char ch);
  std::pair<Node *, char> factorizeQuadraticExpressionHelper(const Node *node);
};

#include "../src/ExpressionTree.cpp"

#endif //LAB24__EXPRESSIONTREE_HPP_
