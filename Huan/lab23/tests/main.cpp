#include "../include/Tree.hpp"
#include <assert.h>

using namespace std;

int main() {
  // Test inserting a node as the root of an empty tree:
  {
    Tree<int> t;
    t.insert(1);
    assert(t.root->get_value() == 1);
  }

  // Test inserting a child node to the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    assert(t.root->children[0]->get_value() == 2);
  }

  // Test inserting multiple child nodes to the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    assert(t.root->children[0]->get_value() == 2);
    assert(t.root->children[1]->get_value() == 3);
  }

  // 1. Test inserting a node with a parent that does not exist:
  {
    Tree<int> t;
    Node<int> parent(10);
    std::cout << "1.\n";
    t.insert(20, &parent);
    t.print(t.root);
    std::cout << "----------------------------\n\n";
    // Should print "Error: parent node is not in tree"
  }

  // Test removing a node that is the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.remove(t.root);
    assert(t.root == nullptr);
  }

  // Test removing a child node from a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    t.remove(t.root->children[0]);
    assert(t.root->get_num_children() == 1);
    assert(t.root->children[0]->get_value() == 3);
  }

  // Test removing a node that is not in the tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    Node<int> n(4);
    t.remove(&n);
    assert(t.root->get_num_children() == 2);
  }

  // Test finding the depth of an empty tree:
  {
    Tree<int> t;
    assert(t.depth() == 0);
  }

  // Test finding the depth of a tree with one node:
  {
    Tree<int> t;
    t.insert(1);
    assert(t.depth() == 1);
  }

  // Test finding the depth of a tree with multiple levels:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    t.insert(4, t.root->children[0]);
    t.insert(5, t.root->children[0]);
    t.insert(6, t.root->children[1]);
    assert(t.depth() == 3);
  }

  // 2. Test printing an empty tree:
  {
    Tree<int> t;
    std::cout << "2.\n";
    t.print(t.root);
    std::cout << "----------------------------\n\n";
    // Expect no output
  }

  // 3. Test printing a tree with one node:
  {
    Tree<int> t;
    t.insert(1);
    std::cout << "3.\n";
    t.print(t.root);
    std::cout << "----------------------------\n\n";
    // Expect output: 1
  }

  // 4. Test printing a tree with multiple levels:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    t.insert(4, t.root->children[0]);
    t.insert(5, t.root->children[0]);
    t.insert(6, t.root->children[1]);
    std::cout << "4.\n";
    t.print(t.root);
    std::cout << "----------------------------\n\n";
    // Expect output:
    // 1
    //   2
    //     4
    //     5
    //   3
    //     6
  }

  // 5. Test and finding the depth of a tree with multiple levels:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.root);
    t.insert(3, t.root);
    t.insert(4, t.root->children[0]);
    t.insert(5, t.root->children[0]);
    t.insert(6, t.root->children[1]);
    t.insert(7, t.root->children[1]);
    t.insert(8, t.root);
    t.insert(9, t.root->children[2]);
    t.insert(10, t.root->children[2]->children[0]);
    t.insert(11, t.root->children[2]->children[0]->children[0]);
    t.insert(12, t.root->children[2]->children[0]->children[0]->children[0]);
    std::cout << "5.\n";
    t.print(t.root);
    std::cout << "----------------------------\n\n";
    assert(t.depth() == 6);
    // Expect output:
    // 1
    //   2
    //     4
    //     5
    //   3
    //     6
    //     7
    //   8
    //     9
    //       10
    //         11
    //           12
  }
}
