#include "../include/List.hpp"

template<typename T>
List<T>::List() {
  barrier_ = new Node<T>();
  barrier_->next_ = barrier_;
  barrier_->prev_ = barrier_;
  size_ = 0;
}

template<typename T>
List<T>::~List() {
  Node<T> *cur_node = barrier_->next_;
  while (cur_node != barrier_) {
    Node<T> *temp_node = cur_node;
    cur_node = cur_node->next_;
    delete temp_node;
  }
  delete barrier_;
  barrier_ = nullptr;
  size_ = 0;
}

template<typename T>
Iterator<T> List<T>::begin() const {
  Iterator<T> temp(barrier_->next_);
  return temp;
}

template<typename T>
Iterator<T> List<T>::end() const {
  Iterator<T> temp(barrier_);
  return temp;
}

template<typename T>
bool List<T>::empty() const {
  Iterator<T> first = this->begin();
  Iterator<T> last = this->end();
  return first == last;
}

template<typename T>
size_t List<T>::size() const {
  return size_;
}

template<typename T>
bool List<T>::find(Iterator<T> first, Iterator<T> last, const T &value) const {
  Iterator<T> cur = first;
  while (cur != last) {
    if (*cur == value) {
      return true;
    }
    ++cur;
  }
  if (last == this->end() && *last == value) {
    return true;
  }
  return false;
}

template<typename T>
Iterator<T> List<T>::insert(Iterator<T> pos, const T &value) {
  T temp_value = value;
  auto *temp_node = new Node<T>(temp_value);
  temp_node->next_ = pos.node_;
  temp_node->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = temp_node;
  pos.node_->prev_ = temp_node;
  ++size_;
  return Iterator<T>(temp_node);
}

template<typename T>
Iterator<T> List<T>::erase(Iterator<T> pos) {
  Iterator<T> res = this->end();
  if (res == pos) {
    return res;
  }
  res.node_ = pos.node_->next_;
  res.node_->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = res.node_;
  --size_;
  delete pos.node_;
  return res;
}

template<typename T>
void List<T>::lab_erase(Iterator<T> first, Iterator<T> last) {
  if (first == this->end()) {
    return;
  }
  Iterator<T> head = this->begin();
  while (head != first) {
    if (find(first, last, *head)) {
      this->erase(head);
    }
    ++head;
  }
  if (last != this->end()) {
    Iterator<T> tail = last + 1;
    while (tail != this->end()) {
      if (find(first, last, *tail)) {
        this->erase(tail);
      }
      ++tail;
    }
  }
  Iterator<T> it = first;
  while (it != last) {
    this->erase(it);
    ++it;
  }
}

template<typename T>
void List<T>::push_back(const T &value) {
  insert(this->end(), value);
}

template<typename T>
void List<T>::push_front(const T &value) {
  insert(this->begin(), value);
}

template<typename T>
void List<T>::pop_back() {
  erase(--(this->end()));
}

template<typename T>
void List<T>::pop_front() {
  erase((this->begin()));
}

template<typename T>
void List<T>::emplace_back() {
}

template<typename T>
template<typename... Args>
void List<T>::emplace_back(const T &first, const Args &...args) {
  push_back(first);
  emplace_back(args...);
}

template<typename T>
void List<T>::reverse() {
  Node<T> *prev = barrier_;
  Node<T> *curr = barrier_->next_;
  Node<T> *next;

  while (curr != barrier_) {
    next = curr->next_;
    curr->next_ = prev;
    curr->prev_ = next;
    prev = curr;
    curr = next;
  }
  barrier_->next_ = prev;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, List<T> &l)  {
  for (Iterator<T> it = l.begin(); it != l.end(); ++it) {
    out << *it << ' ';
  }
  out << '\n';
  return out;
}
