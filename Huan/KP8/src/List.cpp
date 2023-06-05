#include "../include/List.hpp"

template<typename T>
List<T>::List() {
  barrier_ = new Node<T>();
  barrier_->next_ = barrier_;
  barrier_->prev_ = barrier_;
  size_ = 0;
  begin_ = Iterator(barrier_);
  end_ = Iterator(barrier_);
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
}

template<typename T>
Iterator<T> List<T>::begin() {
  return begin_;
}

template<typename T>
Iterator<T> List<T>::end() {
  return end_;
}

template<typename T>
const Iterator<T> List<T>::begin() const {
  return begin_;
}

template<typename T>
const Iterator<T> List<T>::end() const {
  return end_;
}

template<typename T>
bool List<T>::empty() const {
  return begin_ == end_;
}

template<typename T>
size_t List<T>::size() const {
  return size_;
}

template<typename T>
Iterator<T> List<T>::find(Iterator<T> first, Iterator<T> last, const T &value) const {
  Iterator<T> cur = first;
  while (cur != last) {
    if (*cur == value) {
      return cur;
    }
    ++cur;
  }
  return end_;
}

template<typename T>
Iterator<T> List<T>::insert(Iterator<T> pos, const T &value) {
  auto *temp_node = new Node<T>(value);
  temp_node->next_ = pos.node_;
  temp_node->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = temp_node;
  pos.node_->prev_ = temp_node;
  ++size_;
  if (size_ == 1) {
    begin_ = begin_ + 1;
  } else if (pos == begin_) {
    begin_ = begin_ - 1;
  }
  return pos - 1;
}

template<typename T>
Iterator<T> List<T>::erase(Iterator<T> pos) {
  if (pos == end_) {
    return end_;
  }
  Iterator<T> res;
  res.node_ = pos.node_->next_;
  res.node_->prev_ = pos.node_->prev_;
  pos.node_->prev_->next_ = res.node_;
  --size_;
  if (pos == begin_) {
    begin_ = begin_ + 1;
  }
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
    if (find(first, last, *head) != end_) {
      this->erase(head);
    }
    ++head;
  }
  if (last != this->end()) {
    Iterator<T> tail = last;
    while (++tail != this->end()) {
      if (find(first, last, *tail) != end_) {
        this->erase(tail);
      }
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
  insert(this->end(), first);
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
  begin_.node_ = prev;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, List<T> &l) {
  for (Iterator<T> it = l.begin(); it != l.end(); ++it) {
    out << *it << ' ';
  }
  out << '\n';
  return out;
}
