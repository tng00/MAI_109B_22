#include "../include/Iterator.hpp"

template<typename T>
T &Iterator<T>::operator*() const {
  return current->data;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
  current = current->next;
  return *this;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator &other) const {
  return current != other.current;
}
