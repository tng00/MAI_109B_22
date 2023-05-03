#include "../include/Matrix.hpp"


bool Matrix::inputMatrix(const std::string &file_name) {
  clearVectors();
  std::ifstream fin("../tests/inputs/" + file_name);
  if (!fin.is_open()) {
    std::cout << "File is not opened\n";
    return false;
  }
  int rows, cols;
  fin >> rows >> cols;
  for (size_t i = 0; i < rows; ++i) {
    bool first_in_row = true;
    for (size_t j = 0; j < cols; ++j) {
      int val;
      fin >> val;
      if (val) {
        if (first_in_row) {
          M.push_back(A.size());
          A.push_back(j + 1);
          A.push_back(val);
          A.push_back(0);
          first_in_row = false;
          continue;
        }
        A.back() = A.size() + 1;
        A.push_back(j + 1);
        A.push_back(val);
        A.push_back(0);
      }
    }
    if (first_in_row) {
      M.push_back(-1);
    }
  }
  fin.close();
  return true;
}

void Matrix::printUsual() {
  if (M.empty()) {
    std::cout << "Input the matrix first!\n\n";
    return;
  }
  if (print_transposed) {
    Vector<int> &M_ = M_transposed;
    Vector<int> &A_ = A_transposed;
    std::cout << "This is the usual form of the transposed matrix:\n";
    for (size_t i = 0; i < M_.size(); ++i) {
      size_t cnt = M_.size();
      if (M_[i] == -1) {
        while (cnt--) {
          std::cout << 0 << ' ';
        }
      } else {
        size_t prev_col = -1;
        size_t col = A_[M_[i]] - 1;
        int val = A_[M_[i] + 1];
        size_t next = A_[M_[i] + 2];
        while (true) {
          int tmp = col - prev_col - 1;
          while (tmp > 0) {
            std::cout << 0 << ' ';
            --tmp;
            --cnt;
          }
          std::cout << val << ' ';
          --cnt;
          if (next) {
            prev_col = col;
            col = A_[next - 1] - 1;
            val = A_[next];
            next = A_[next + 1];
          } else {
            break;
          }
        }
        while (cnt--) {
          std::cout << 0 << ' ';
        }
      }
      std::cout << '\n';
    }
    std::cout << '\n';
    return;
  }
  std::cout << "This is the usual form of the given matrix:\n";
  Vector<int> &M_ = M;
  Vector<int> &A_ = A;
  for (size_t i = 0; i < M_.size(); ++i) {
    size_t cnt = M_.size();
    if (M_[i] == -1) {
      while (cnt--) {
        std::cout << 0 << ' ';
      }
    } else {
      size_t prev_col = -1;
      size_t col = A_[M_[i]] - 1;
      int val = A_[M_[i] + 1];
      size_t next = A_[M_[i] + 2];
      while (true) {
        int tmp = col - prev_col - 1;
        while (tmp > 0) {
          std::cout << 0 << ' ';
          --tmp;
          --cnt;
        }
        std::cout << val << ' ';
        --cnt;
        if (next) {
          prev_col = col;
          col = A_[next - 1] - 1;
          val = A_[next];
          next = A_[next + 1];
        } else {
          break;
        }
      }
      while (cnt--) {
        std::cout << 0 << ' ';
      }
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void Matrix::printSchematic() {
  if (M.empty()) {
    std::cout << "Input the matrix first!\n\n";
    return;
  }
  if (print_transposed) {
    Vector<int> &M_ = M_transposed;
    Vector<int> &A_ = A_transposed;
    std::cout << "This is a schematic form of the transposed matrix:\nM: ";
    for (auto &el : M_) {
      std::cout << el << ' ';
    }
    std::cout << "\nA: ";
    for (auto &el : A_) {
      std::cout << el << ' ';
    }
    std::cout << '\n' << '\n';
    return;
  }
  Vector<int> &M_ = M;
  Vector<int> &A_ = A;
  std::cout << "This is a schematic form of the given matrix:\nM: ";
  for (auto &el : M_) {
    std::cout << el << ' ';
  }
  std::cout << "\nA: ";
  for (auto &el : A_) {
    std::cout << el << ' ';
  }
  std::cout << '\n' << '\n';
}

bool Matrix::isSkewSymmetric() {
  for (size_t row = 0; row < M_transposed.size(); ++row) {
    if (M_transposed[row] == -1) {
      continue;
    } else {
      size_t col = A_transposed[M_transposed[row]] - 1;
      int val = A_transposed[M_transposed[row] + 1];
      size_t next = A_transposed[M_transposed[row] + 2];
      while (true) {
        if (M_transposed[col] == -1) {
          return false;
        }
        size_t col_idx = M_transposed[col];
        while (A_transposed[col_idx] - 1 < row) {
          col_idx += 3;
        }
        if (A_transposed[col_idx] - 1 != row) {
          return false;
        }
        if (col + 1 != M_transposed.size() && col_idx < M_transposed[col + 1]
            && A_transposed[col_idx] - 1 == row && val != -A_transposed[col_idx + 1]) {
          return false;
        }
        if (col + 1 == M_transposed.size() && col_idx <= A_transposed.size() - 3
            && A_transposed[col_idx] - 1 == row && val != -A_transposed[col_idx + 1]) {
          return false;
        }
        if (next) {
          col = A_transposed[next - 1] - 1;
          val = A_transposed[next];
          next = A_transposed[next + 1];
        } else {
          break;
        }
      }
    }
  }
  return true;
}

void Matrix::transpose() {
  int rows = M.size(), cols = M.size();
  for (int col = cols - 1; col >= 0; --col) {
    bool first_in_row = true;
    for (int row = rows - 1; row >= 0; --row) {
      if (M[row] != -1) {
        int last_col_idx;
        if (row == rows - 1) {
          last_col_idx = A.size() - 3;
        } else {
          int next_row_idx = row + 1;
          while (next_row_idx < M.size() && M[next_row_idx] == -1) {
            ++next_row_idx;
          }
          if (next_row_idx == M.size()) {
            last_col_idx = A.size() - 3;
          } else {
            last_col_idx = M[next_row_idx] - 3;
          }
        }
        while (last_col_idx > 0 && A[last_col_idx] - 1 > col) {
          last_col_idx -= 3;
        }
        if (last_col_idx >= M[row] && A[last_col_idx] - 1 == col) {
          if (first_in_row) {
            M_transposed.push_back(A_transposed.size());
            A_transposed.push_back(rows - row);
            A_transposed.push_back(A[last_col_idx + 1]);
            A_transposed.push_back(0);
            first_in_row = false;
          } else {
            A_transposed.back() = A_transposed.size() + 1;
            A_transposed.push_back(rows - row);
            A_transposed.push_back(A[last_col_idx + 1]);
            A_transposed.push_back(0);
          }
        }
      }
    }
    if (first_in_row) {
      M_transposed.push_back(-1);
    }
  }
}

void Matrix::checkMatrix() {
  if (M.empty()) {
    std::cout << "Input the matrix first!\n\n";
    return;
  }
  if (!is_transposed) {
    transpose();
    is_transposed = true;
  }
  print_transposed = true;
  printUsual();
  printSchematic();
  if (isSkewSymmetric()) {
    std::cout << "Transposed matrix is skew symmetric!" << "\n\n";
  } else {
    std::cout << "Transposed matrix is not skew symmetric!" << "\n\n";
  }
  print_transposed = false;
}

void Matrix::clearVectors() {
  A_transposed.clear();
  M_transposed.clear();
  A.clear();
  M.clear();
  is_transposed = false;
  print_transposed = false;
}
