#include <iostream>
#include <chrono>

template<typename QueueType>
void benchmarkQueue(int numElements) {
  QueueType queue;

  // push elements
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < numElements; i++) {
    queue.push(i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> enqueueTime = end - start;
  std::cout << "Push time: " << enqueueTime.count() << " seconds\n";

  // pop elements
  start = std::chrono::high_resolution_clock::now();
  while (!queue.empty()) {
    queue.pop();
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> dequeueTime = end - start;
  std::cout << "Pop time: " << dequeueTime.count() << " seconds\n";
}
