#include "../include/Tree.hpp"
#include <assert.h>

using namespace std;

int main() {
  // Test inserting a node as the root of an empty tree:
  {
    Tree<int> t;
    t.insert(1);
    assert(t.get_root()->get_value() == 1);
  }

  // Test inserting a child node to the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    assert(t.get_root()->get_child(0)->get_value() == 2);
  }

  // Test inserting multiple child nodes to the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    assert(t.get_root()->get_child(0)->get_value() == 2);
    assert(t.get_root()->get_child(1)->get_value() == 3);
  }

  // 1. Test inserting a node with a parent that does not exist:
  {
    Tree<int> t;
    Node<int> parent(10);
    std::cout << "1.\n";
    t.insert(20, &parent);
    t.print(t.get_root());
    std::cout << "----------------------------\n\n";
    // Should print "Error: parent node is not in tree"
  }

  // Test removing a node that is the root of a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.remove(t.get_root());
    assert(t.get_root() == nullptr);
  }

  // Test removing a child node from a tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    t.remove(t.get_root()->get_child(0));
    assert(t.get_root()->get_num_children() == 1);
    assert(t.get_root()->get_child(0)->get_value() == 3);
  }

  // Test removing a node that is not in the tree:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    Node<int> n(4);
    t.remove(&n);
    assert(t.get_root()->get_num_children() == 2);
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
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    t.insert(4, t.get_root()->get_child(0));
    t.insert(5, t.get_root()->get_child(0));
    t.insert(6, t.get_root()->get_child(1));
    assert(t.depth() == 3);
  }

  // 2. Test printing an empty tree:
  {
    Tree<int> t;
    std::cout << "2.\n";
    t.print(t.get_root());
    std::cout << "----------------------------\n\n";
    // Expect no output
  }

  // 3. Test printing a tree with one node:
  {
    Tree<int> t;
    t.insert(1);
    std::cout << "3.\n";
    t.print(t.get_root());
    std::cout << "----------------------------\n\n";
    // Expect output: 1
  }

  // 4. Test printing a tree with multiple levels:
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    t.insert(4, t.get_root()->get_child(0));
    t.insert(5, t.get_root()->get_child(0));
    t.insert(6, t.get_root()->get_child(1));
    std::cout << "4.\n";
    t.print(t.get_root());
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
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    t.insert(4, t.get_root()->get_child(0));
    t.insert(5, t.get_root()->get_child(0));
    t.insert(6, t.get_root()->get_child(0));
    t.insert(7, t.get_root()->get_child(1));
    t.insert(8, t.get_root());
    t.insert(9, t.get_root()->get_child(2));
    t.insert(10, t.get_root()->get_child(2)->get_child(0));
    t.insert(11, t.get_root()->get_child(2)->get_child(0)->get_child(0));
    t.insert(12, t.get_root()->get_child(2)->get_child(0)->get_child(0)->get_child(0));
    std::cout << "5.\n";
    t.print(t.get_root());
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

  // Test finding node
  {
    Tree<int> t;
    t.insert(1);
    t.insert(2, t.get_root());
    t.insert(3, t.get_root());
    t.insert(4, t.get_root()->get_child(0));
    t.insert(5, t.get_root()->get_child(0));
    t.insert(6, t.get_root()->get_child(0));
    t.insert(7, t.get_root()->get_child(1));
    t.insert(8, t.get_root());
    t.insert(9, t.get_root()->get_child(2));
    t.insert(10, t.get_root()->get_child(2)->get_child(0));
    t.insert(11, t.get_root()->get_child(2)->get_child(0)->get_child(0));
    t.insert(12, t.get_root()->get_child(2)->get_child(0)->get_child(0)->get_child(0));
    assert(t.find(12, t.get_root())->get_value() == 12);
    assert(t.find(11, t.get_root())->get_value() == 11);
    assert(t.find(10, t.get_root())->get_value() == 10);
    assert(t.find(5, t.get_root())->get_value() == 5);
    assert(t.find(1, t.get_root())->get_value() == 1);
    assert(t.find(100000, t.get_root()) == nullptr);
  }
}
