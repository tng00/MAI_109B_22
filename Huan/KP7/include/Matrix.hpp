#ifndef KP_7_INCLUDE_MATRIX_HPP_
#define KP_7_INCLUDE_MATRIX_HPP_
#include <fstream>
#include "Vector.hpp"

class Matrix {
 public:
  bool inputMatrix(const std::string &file_name);
  void printUsual();
  void printSchematic();
  void checkMatrix();
 private:
  Vector<int> M, A, M_transposed, A_transposed;
  bool is_transposed = false;
  bool print_transposed = false;
  bool isSkewSymmetric();
  void transpose();
  void clearVectors();
};

#include "../src/Matrix.cpp"

#endif
