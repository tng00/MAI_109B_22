#ifndef KP_7_INCLUDE_MATRIX_HPP_
#define KP_7_INCLUDE_MATRIX_HPP_
#include <fstream>
#include "Vector.hpp"

Vector<int> M, A, M_transposed, A_transposed;

bool inputMatrix(const std::string &file_name);
void printUsual(bool is_transposed = false);
void printSchematic(bool is_transposed = false);
bool isSkewSymmetric();
void Transpose();
void checkMatrix(bool transposed);

#include "../src/Matrix.cpp"

#endif
