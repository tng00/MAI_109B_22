#include "../include/List.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <chrono>

void benchmark() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ifstream fin("../tests/tests.txt");
  if (!fin.is_open()) {
    std::cout << "file not found" << std::endl;
    return;
  }
  List<int64_t> test1;
  std::list<int64_t> test2;
  int64_t number, in_int;
  fin >> number;


  std::cout << "Benchmark " << number << ":\npush_back O(1)" << std::endl;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  for (int64_t y = 0; y < number; y++) {
    fin >> in_int;
    test1.push_back(in_int);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  fin.clear();
  fin.seekg(0);
  fin >> in_int;
  begin = std::chrono::steady_clock::now();
  for (int64_t y = 0; y < number; y++) {
    fin >> in_int;
    test2.push_back(in_int);
  }
  end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  if (test1.size() != test2.size()) {
    throw std::exception();
  }

  std::cout << "pop.back O(1)" << std::endl;
  begin = std::chrono::steady_clock::now();
  for (int64_t y = 0; y < number; y++) {
    test1.pop_back();
  }
  end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

  begin = std::chrono::steady_clock::now();
  for (int64_t y = 0; y < number; y++) {
    test2.pop_back();
  }
  end = std::chrono::steady_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  if (test1.size() != test2.size()) {
    throw std::exception();
  }
}
