#include "../include/Node.hpp"

template<typename T>
Node<T>::Node(T val) {
  this->value = val;
  children = nullptr;
  num_children = 0;
}

template<typename T>
Node<T>::~Node() {
  for (int i = 0; i < num_children; i++) {
    delete children[i];
  }
  delete[] children;
}

template<typename T>
T Node<T>::get_value() const {
  return value;
}

template<typename T>
int Node<T>::get_num_children() const {
  return num_children;
}

template<typename T>
void Node<T>::add_child(Node<T> *child) {
  children = (Node<T> **) realloc(children, (num_children + 1) * sizeof(Node<T> *));
  children[num_children] = child;
  num_children++;
}

template<typename T>
void Node<T>::remove_child(Node<T> *child) {
  int index = -1;
  for (int i = 0; i < num_children; i++) {
    if (children[i] == child) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    return;
  }
  num_children--;
  for (int i = index; i < num_children; i++) {
    children[i] = children[i + 1];
  }
  children = (Node<T> **) realloc(children, num_children * sizeof(Node<T> *));
}