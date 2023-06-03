#include "../src/benchmark.cpp"
#include "../include/List.hpp"
#include <iostream>

using namespace std;

int main() {
  //benchmark();
  std::cout << "Benchmark finished!\n\n\n";
  List<int64_t> x;
  cout << "Created List\n\n\n";
  cout << "Is empty:\n" << x.empty() << '\n';
  cout << "Size:\n" << x.size() << '\n';

  cout << "\n\nTest insert:\n";
  x.insert(x.end(), 3);
  x.insert(x.end(), 4);
  x.insert(x.begin(), 1);
  x.insert(x.begin() + 1, 2);
  cout << x << "Must output:\n1 2 3 4\n";

  cout << "Is empty:\n";
  cout << x.empty() << '\n';
  cout << "Size:\n";
  cout << x.size() << '\n';
  cout << "First element:\n";
  cout << *x.begin() << '\n';
  cout << "Last element:\n";
  cout << (*(--x.end())) << '\n';

  cout << "\n\nTest push, pop and emplace:\n";
  cout << "pop_back()\n";
  x.pop_back();
  cout << x;
  cout << "pop_front()\n";
  x.pop_front();
  cout << x;
  cout << "pop_back()\n";
  x.pop_back();
  cout << x;
  cout << "pop_front()\n";
  x.pop_front();
  cout << x;
  cout << "push_back(9)\n";
  x.push_back(9);
  cout << x;
  cout << "push_back(10)\n";
  x.push_back(10);
  cout << x;
  cout << "push_front(11)\n";
  x.push_front(11);
  cout << x;
  cout << "emplace_back(55, 8, 13, -9999, 6, 9, 14, 11, -9999, 55, 1812, -4096)\n";
  x.emplace_back(55, 8, 13, -9999, 6, 9, 14, 11, -9999, 55, 1812, -4096);
  cout << x;

  cout << "\n\nIterator test:\n";
  cout << "List: " << '\n' << x;
  cout << "Is empty: " << x.empty() << '\n';
  cout << "Size: " << x.size() << '\n';
  cout << "x.begin(): " << *x.begin() << '\n';
  cout << "x.end() + (-3): " << *(x.end() + (-3)) << '\n';
  cout << "x.end() - 3: " << *(x.end() - 3) << '\n';

  cout << "\n\nReverse test:\n";
  cout << "Reverse\n";
  x.reverse();
  cout << x;
  cout << "Reverse\n";
  x.reverse();
  cout << x;

  cout << "\n\nLab_erase test:\nErase range [begin() + 8, end() - 5)\n";
  x.lab_erase(x.begin() + 8, x.end() - 5);
  cout << x;
  cout << "Erase range [end() - 4, end())\n";
  x.lab_erase(x.end() - 4, x.end());
  cout << x;

  cout << "\n\nAll tests finished!\n";
}
