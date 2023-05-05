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
  Vector<int> M;
  Vector<int> A;
  Vector<int> M_transposed;
  Vector<int> A_transposed;
  
  bool is_transposed = false;
  bool print_transposed = false;
  
  void transpose();
  
  bool isSkewSymmetric();
  
  void clearVectors();
};

#include "../src/Matrix.cpp"

#endif
