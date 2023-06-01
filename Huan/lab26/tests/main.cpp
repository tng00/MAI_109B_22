#include <iostream>
#include <queue>
#include "../include/Queue.hpp"
#include "../src/benchmark.cpp"

int main() {
  Queue<int> queue;
  queue.push(1);
  queue.push(3);
  queue.push(5);
  queue.push(2);
  queue.push(4);

  std::cout << "Original Queue: ";
  for (const auto &item : queue) {
    std::cout << item << " ";
  }

  queue.mergeSort();

  std::cout << "\nSorted Queue: ";
  for (const auto &item : queue) {
    std::cout << item << " ";
  }


  const int numElements = 1000000;
  std::cout << "\n\nBenchmarking custom Queue implementation:\n";
  benchmarkQueue<Queue<int>>(numElements);
  std::cout << "\nBenchmarking std::queue implementation:\n";
  benchmarkQueue<std::queue<int>>(numElements);
}
