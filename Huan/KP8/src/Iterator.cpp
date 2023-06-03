#include "../include/Iterator.hpp"

template<typename T>
Iterator<T>::Iterator(Node<T> *node) {
  node_ = node;
}

template<typename T>
Iterator<T> Iterator<T>::operator++() {
  if (node_) {
    node_ = node_->next_;
  }
  return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator--() {
  if (node_) {
    node_ = node_->prev_;
  }
  return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator+(int64_t num) {
  if (num > 0) {
    while (num-- && node_) {
      node_ = node_->next_;
    }
  } else if (num < 0) {
    while (num++ && node_) {
      node_ = node_->prev_;
    }
  }
  return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator-(int64_t num) {
  return *this + (-num);
}

template<typename T>
T &Iterator<T>::operator*() {
  return node_->value_;
}

template<typename T>
const T &Iterator<T>::operator*() const {
  return node_->value_;
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> left) const {
  return this->node_ == left.node_;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> left) const {
  return !(*this == left);
}
