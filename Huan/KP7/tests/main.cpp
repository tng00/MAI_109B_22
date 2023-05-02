#include <iostream>
#include "../include/Matrix.hpp"
#include "../src/benchmark.cpp"


int main() {
  bool exit = false, transposed = false;
  while (true) {
    if (exit) {
      break;
    }
    std::cout << "Choose action:\n1 - input matrix\n2 - print usual form\n3 - print schematic form\n"
                 "4 - transpose and check skew symmetric\n5 - benchmark\n6 - exit\n\n";
    int action;
    std::cin >> action;
    std::string file_name;
    switch (action) {
      case 1:std::cout << "Enter file name in format: \"in\" + digit 1 to 6. For example: in4.\n";
        std::cin >> file_name;
        if (!inputMatrix(file_name)) {
          std::cout << "Wrong file name!\n\n";
        }
        A_transposed.clear();
        M_transposed.clear();
        transposed = false;
        break;
      case 2:
        if (M.empty()) {
          std::cout << "Input the matrix first!\n\n";
          break;
        }
        printUsual();
        break;
      case 3:
        if (M.empty()) {
          std::cout << "Input the matrix first!\n\n";
          break;
        }
        printSchematic();
        break;
      case 4:
        if (M.empty()) {
          std::cout << "Input the matrix first!\n\n";
          break;
        }
        checkMatrix(transposed);
        transposed = true;
        break;
      case 5:
        benchmark();
        break;
      case 6:
        A.clear();
        M.clear();
        A_transposed.clear();
        M_transposed.clear();
        transposed = false;
        exit = true;
        std::cout << "See you next time!\n\n";
        break;
      default:std::cout << "Wrong action!\n\n";
        break;
    }
  }
}