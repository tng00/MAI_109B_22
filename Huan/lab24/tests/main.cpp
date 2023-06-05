#include <iostream>
#include <string>
#include "../include/ExpressionTree.hpp"


int main() {
  setlocale(LC_ALL, "Russian");
  std::string expression;
  std::wcout << L"Введите квадратный трехчлен:";
  getline(std::cin, expression);
  ExpressionTree tr;
  std::string postfix = tr.convertToReversePolish(expression);
  std::wcout << L"\nПостфиксная запись: ";
  std::cout << postfix;
  Node* root = tr.constructTree(postfix);
  std::wcout << L"\nИнфиксная запись: ";
  tr.makeInfixExpression(root);
  std::wcout << L"\nДерево:\n";
  tr.printTree(root);
  std::cout << "\n";
  tr.factorizeQuadraticExpression(root);
  delete root;
  return 0;
}
