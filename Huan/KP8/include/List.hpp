#ifndef KP_8_INCLUDE_LIST_HPP_
#define KP_8_INCLUDE_LIST_HPP_
#include "Iterator.hpp"
#include <iostream>

template<typename T>
class List {
 public:
  List();
  ~List();

  Iterator<T> begin();
  Iterator<T> end();
  const Iterator<T> begin() const;
  const Iterator<T> end() const;

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;
  Iterator<T> find(Iterator<T> first, Iterator<T> last, const T &value) const;

  Iterator<T> insert(Iterator<T> pos, const T &value);
  Iterator<T> erase(Iterator<T> pos);
  void lab_erase(Iterator<T> first, Iterator<T> last);

  void push_back(const T &value);
  void push_front(const T &value);
  void pop_back();
  void pop_front();
  void emplace_back();
  template<typename... Args>
  void emplace_back(const T &first, const Args &...args);
  void reverse();

  template<typename F>
  friend std::ostream &operator<<(std::ostream &out, List<F> &x);

 private:
  Node<T> *barrier_;
  size_t size_;

  Iterator<T> begin_;
  Iterator<T> end_;
};

#include "../src/List.cpp"

#endif //KP_8_INCLUDE_LIST_HPP_
