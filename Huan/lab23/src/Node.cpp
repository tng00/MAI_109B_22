#include "../include/Node.hpp"

template<typename T>
Node<T>::Node(const T &val) {
  this->value = val;
  children = nullptr;
  num_children = 0;
}

template<typename T>
Node<T>::~Node() {
  for (size_t i = 0; i < num_children; ++i) {
    delete children[i];
  }
  delete[] children;
}

template<typename T>
T Node<T>::get_value() const {
  return value;
}

template<typename T>
Node<T> *Node<T>::get_child(size_t i) {
  if (i < num_children) {
    return children[i];
  } else {
    std::cout << "Error: index out of range\n";
    return nullptr;
  }
}

template<typename T>
size_t Node<T>::get_num_children() const {
  return num_children;
}

template<typename T>
void Node<T>::add_child(Node<T> *child) {
  auto **newChildren = new Node<T> *[num_children + 1];
  for (size_t i = 0; i < num_children; ++i) {
    newChildren[i] = children[i];
  }
  delete[] children;
  children = newChildren;
  children[num_children] = child;
  ++num_children;
}

template<typename T>
void Node<T>::remove_child(Node<T> *child) {
  int index = -1;
  for (size_t i = 0; i < num_children; ++i) {
    if (children[i] == child) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    return;
  }
  for (size_t i = index; i < num_children - 1; ++i) {
    children[i] = children[i + 1];
  }
  --num_children;
  auto **newChildren = new Node<T> *[num_children];
  for (size_t i = 0; i < num_children; ++i) {
    newChildren[i] = children[i];
  }
  delete[] children;
  children = newChildren;
}
