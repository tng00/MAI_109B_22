#include "../include/Queue.hpp"

template<typename T>
Queue<T>::~Queue() {
  while (!empty()) {
    pop();
  }
}

template<typename T>
void Queue<T>::push(const T &value) {
  Node<T> *newNode = new Node(value);
  if (empty()) {
    front = newNode;
    rear = newNode;
  } else {
    rear->next = newNode;
    rear = newNode;
  }
  size++;
}

template<typename T>
void Queue<T>::pop() {
  if (empty()) {
    return;
  }

  Node<T> *temp = front;
  front = front->next;
  delete temp;
  size--;
}

template<typename T>
T &Queue<T>::getFront() const {
  if (empty()) {
    static T defaultValue;
    return defaultValue;
  }
  return front->data;
}

template<typename T>
bool Queue<T>::empty() const {
  return size == 0;
}

template<typename T>
size_t Queue<T>::getSize() const {
  return size;
}

template<typename T>
Iterator<T> Queue<T>::begin() {
  return Iterator(front);
}

template<typename T>
Iterator<T> Queue<T>::end() {
  return Iterator(rear->next);
}

template<typename T>
void Queue<T>::mergeSort() {
  if (size <= 1)
    return;

  Queue<T> leftQueue;
  Queue<T> rightQueue;

  int halfSize = size / 2;

  while (leftQueue.getSize() < halfSize) {
    leftQueue.push(getFront());
    pop();
  }
  while (!empty()) {
    rightQueue.push(getFront());
    pop();
  }

  leftQueue.mergeSort();
  rightQueue.mergeSort();

  while (!leftQueue.empty() && !rightQueue.empty()) {
    if (leftQueue.getFront() <= rightQueue.getFront()) {
      push(leftQueue.getFront());
      leftQueue.pop();
    } else {
      push(rightQueue.getFront());
      rightQueue.pop();
    }
  }

  while (!leftQueue.empty()) {
    push(leftQueue.getFront());
    leftQueue.pop();
  }

  while (!rightQueue.empty()) {
    push(rightQueue.getFront());
    rightQueue.pop();
  }
}
