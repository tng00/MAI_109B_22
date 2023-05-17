#include "../include/Node.hpp"

template<typename T>
Node<T>::Node(const T &val) {
  value_ = val;
  prev_ = nullptr;
  next_ = nullptr;
}
