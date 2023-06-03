#include "../include/Tree.hpp"

template<typename T>
Tree<T>::~Tree() {
  delete root;
}

template<typename T>
size_t Tree<T>::depth() const {
  return depth_helper(root);
}

template<typename T>
Node<T> *Tree<T>::get_root() {
  return root;
}

template<typename T>
Node<T> *Tree<T>::find(const T &val, Node<T> *node) {
  if (!node) {
    return nullptr;
  }
  if (node->value == val) {
    return node;
  }
  for (size_t i = 0; i < node->get_num_children(); ++i) {
    if (node->get_child(i)->value == val) {
      return node->get_child(i);
    }
    auto tmp = find(val, node->get_child(i));
    if (tmp) {
      return tmp;
    }
  }
}

template<typename T>
void Tree<T>::insert(T val, Node<T> *parent) {
  Node<T> *node = new Node<T>(val);

  if ((!root && parent) || (root && parent != root && !find_parent(root, parent))) {
    std::cout << "Error: parent node is not in tree" << '\n';
    return;
  }

  if (!root) {
    root = node;
    return;
  }

  if (!parent) {
    std::cout << "Error: parent node is null" << '\n';
    return;
  }

  parent->add_child(node);
}

template<typename T>
void Tree<T>::print(Node<T> *node, size_t depth, bool check_node) const {
  if (check_node) {
    Node<T> *parent = find_parent(root, node);

    if (parent == nullptr && node != root) {
      return;
    }
  }
  if (!node) {
    return;
  }

  for (size_t i = 0; i < depth; ++i) {
    std::cout << "\t";
  }

  std::cout << node->get_value() << '\n';

  for (size_t i = 0; i < node->get_num_children(); ++i) {
    print(node->children[i], depth + 1, false);
  }
}

template<typename T>
void Tree<T>::remove(Node<T> *node) {
  if (node == root) {
    delete root;
    root = nullptr;
    return;
  }

  Node<T> *parent = find_parent(root, node);

  if (parent == nullptr) {
    return;
  }

  parent->remove_child(node);
  delete node;
}

template<typename T>
size_t Tree<T>::depth_helper(const Node<T> *node) const {
  if (!node) {
    return 0;
  }

  size_t maxChildDepth = 0;
  for (size_t i = 0; i < node->get_num_children(); ++i) {
    size_t childDepth = depth_helper(node->children[i]);
    if (childDepth > maxChildDepth) {
      maxChildDepth = childDepth;
    }
  }

  return 1 + maxChildDepth;
}

template<typename T>
Node<T> *Tree<T>::find_parent(Node<T> *node, Node<T> *child) const {
  if (!node) {
    return nullptr;
  }

  for (size_t i = 0; i < node->get_num_children(); ++i) {
    if (node->children[i] == child) {
      return node;
    }

    auto parent = find_parent(node->children[i], child);

    if (parent) {
      return parent;
    }
  }

  return nullptr;
}
