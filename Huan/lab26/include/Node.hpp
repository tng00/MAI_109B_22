#ifndef LAB26_INCLUDE_NODE_HPP_
#define LAB26_INCLUDE_NODE_HPP_

template<typename T>
class Queue;

template<typename T>
class Iterator;

template<typename T>
class Node {
 private:
  T data;
  Node *next;

 public:
  friend class Queue<T>;
  friend class Iterator<T>;

  explicit Node(const T &value) : data(value), next(nullptr) {};

  ~Node() = default;
};

#endif //LAB26_INCLUDE_NODE_HPP_
