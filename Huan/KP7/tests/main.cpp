#include <iostream>
#include "../include/Matrix.hpp"
#include "../src/benchmark.cpp"


int main() {
  bool exit = false;
  int action;
  Matrix matrix;
  while (true) {
    if (exit) {
      break;
    }
    std::cout << "Choose action:\n1 - input matrix\n2 - print usual form\n3 - print schematic form\n"
                 "4 - transpose and check skew symmetric\n5 - benchmark\n6 - exit\n\n";
    std::cin >> action;
    std::string file_name;
    switch (action) {
      case 1:std::cout << "Enter file name in format: \"in\" + digit from 1 to 6. For example: in4.\n";
        std::cin >> file_name;
        if (!matrix.inputMatrix(file_name)) {
          std::cout << "Wrong file name! Choose 1 and try again.\n\n";
        }
        break;
      case 2:
        matrix.printUsual();
        break;
      case 3:
        matrix.printSchematic();
        break;
      case 4:
        matrix.checkMatrix();
        break;
      case 5:
        benchmark();
        break;
      case 6:
        exit = true;
        std::cout << "See you next time!\n\n";
        break;
      default:std::cout << "Wrong action!\n\n";
        break;
    }
  }
}
