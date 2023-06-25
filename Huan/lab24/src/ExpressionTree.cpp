#include "../include/ExpressionTree.hpp"

bool ExpressionTree::isOperator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int ExpressionTree::getPrecedence(char ch) {
  if (ch == '+' || ch == '-') {
    return 1;
  }
  if (ch == '*' || ch == '/') {
    return 2;
  }
  if (ch == '~') {
    return 3;
  }
  if (ch == '^') {
    return 4;
  }
  if (ch == '(' || ch == ')') {
    return 5;
  }
}

Node *ExpressionTree::constructTree(const std::string &postfix) {
  if (postfix.length() == 0) {
    return nullptr;
  }

  Vector<Node *> st;
  bool last_is_digit = false;

  for (char ch : postfix) {
    if (isspace(ch)) {
      last_is_digit = false;
      continue;
    }
    if (ch == '~') {
      Node *left = st.back();
      st.pop_back();
      Node *node = new Node(ch, left, nullptr);
      st.push_back(node);
    } else if (isOperator(ch)) {
      Node *right = st.back();
      st.pop_back();
      Node *left = st.back();
      st.pop_back();
      Node *node = new Node(ch, left, right);
      st.push_back(node);
    } else if (isdigit(ch)) {
      if (last_is_digit) {
        Node *left = st.back();
        st.pop_back();
        Node *node = new Node(ch, left, nullptr);
        st.push_back(node);
        continue;
      }
      st.push_back(new Node(ch));
      last_is_digit = true;
      continue;
    } else {
      st.push_back(new Node(ch));
    }
    last_is_digit = false;
  }
  return st.back();
}

std::string ExpressionTree::convertToReversePolish(const std::string &str) {
  std::string expression = str;
  std::string result;
  Vector<char> operators;

  // bracket check
  int counter = 0;
  for (char ch : expression) {
    if (ch == '(') {
      ++counter;
    } else if (ch == ')') {
      --counter;
    }
    if (counter < 0) {
      std::cout << "Wrong expression!\n";
      return "NULL";
    }
  }
  if (counter != 0) {
    std::cout << "Wrong expression!\n";
    return "NULL";
  }

  // add * to x
  for (auto it = expression.begin(); it != expression.end(); ++it) {
    if (isalpha(*it) && it != expression.begin() && isOperator(*(it - 1))) {
      auto tmp = expression.insert(it, '1');
      it = tmp;
    } else if (isalpha(*it) && it == expression.begin()) {
      auto tmp = expression.insert(it, '1');
      it = tmp;
    }
  }
  for (auto it = expression.begin(); it != expression.end(); ++it) {
    if (isalpha(*it) && it != expression.begin() && isdigit(*(it - 1))) {
      auto tmp = expression.insert(it, '*');
      it = tmp;
    }
  }

  // flags
  bool isUnaryMinus = true;
  bool lastIsDigit = false;

  // parce
  for (char ch : expression) {
    if (isspace(ch)) {
      continue;
    }
    // digit
    if (isdigit(ch)) {
      if (lastIsDigit) {
        result.back() = ch;
      } else {
        result += ch;
      }
      result += ' ';
      isUnaryMinus = false;
      lastIsDigit = true;
      continue;
    }
    // alpha
    if (isalpha(ch)) {
      result += ch;
      result += ' ';
      isUnaryMinus = false;
      lastIsDigit = false;
      continue;
    }
    // operators
    if (isUnaryMinus) {
      if (ch == '-') {
        operators.push_back('~');
        isUnaryMinus = false;
        lastIsDigit = false;
        continue;
      } else if (ch == '+') {
        continue;
      }
    }
    if (ch == '(') {
      operators.push_back(ch);
      isUnaryMinus = true;
    } else if (ch == ')') {
      while (!operators.empty() && operators.back() != '(') {
        result += operators.back();
        result += ' ';
        operators.pop_back();
      }
      if (operators.empty() || operators.back() != '(') {
        std::cout << operators.back() << " Wrong expression85!\n";
        return "NULL";
      }
      operators.pop_back();
      isUnaryMinus = false;
    } else {
      while (!operators.empty() && operators.back() != '(' &&
          getPrecedence(ch) <= getPrecedence(operators.back())) {
        if (operators.back() != '(') {
          result += operators.back();
          result += ' ';
          operators.pop_back();
        }
      }
      operators.push_back(ch);
      isUnaryMinus = false;
    }
    lastIsDigit = false;
  }

  while (!operators.empty()) {
    result += operators.back();
    result += ' ';
    operators.pop_back();
  }

  return result;
}

void ExpressionTree::makeInfixExpression(const Node *root) {
  if (root == nullptr) {
    return;
  }
  if (root->data == '~') {
    std::cout << "(-";
  }
  if (isOperator(root->data)) {
    std::cout << "(";
  }
  makeInfixExpression(root->left);
  if (root->data != '~') {
    std::cout << root->data;
  }
  makeInfixExpression(root->right);
  if (isOperator(root->data) || root->data == '~') {
    std::cout << ")";
  }
}

void ExpressionTree::printTree(Node const *first,
                               std::vector<std::string> const &lpref,
                               std::vector<std::string> const &cpref,
                               std::vector<std::string> const &rpref,
                               bool root,
                               std::shared_ptr<std::vector<std::vector<std::string>>> lines) {
  if (!first) {
    return;
  }
  auto vecConcat = [](std::vector<std::string> const &first, std::vector<std::string> const &second) {
    auto res = first;
    res.insert(res.end(), second.begin(), second.end());
    return res;
  };
  if (root) {
    lines = std::make_shared<std::vector<std::vector<std::string>>>();
  }
  if (first->left) {
    printTree(first->left,
              vecConcat(lpref, std::vector<std::string>({" ", " "})),
              vecConcat(lpref, std::vector<std::string>({"/", "|"})),
              vecConcat(lpref, std::vector<std::string>({"_", " "})),
              false,
              lines);
  }
  std::string node_val;
  node_val += first->data;
  lines->push_back(vecConcat(cpref, {node_val}));
  if (first->right) {
    printTree(first->right,
              vecConcat(rpref, std::vector<std::string>({"_", " "})),
              vecConcat(rpref, std::vector<std::string>({"\\", "|"})),
              vecConcat(rpref, std::vector<std::string>({" ", " "})),
              false,
              lines);
  }
  if (root) {
    std::vector<std::string> out;
    for (size_t l = 0;; ++l) {
      bool last = true;
      std::string line;
      for (size_t i = 0; i < lines->size(); ++i) {
        if (l < (*lines).at(i).size()) {
          line += lines->at(i)[l];
          last = false;
        } else {
          line += " ";
        }
      }
      if (last) {
        break;
      }
      out.push_back(line);
    }
    for (const auto &i : out) {
      std::cout << i << std::endl;
    }
  }
}

void ExpressionTree::getCoefficients(const Node *root, char coefficient) {
  if (root == nullptr) {
    return;
  }
  if (root->data == '~') {
    switch (coefficient) {
      case 'a':a_ += "-";
        break;
      case 'b':b_ += "-";
        break;
      case 'c':c_ += "-";
        break;
      default:break;
    }
  }
  getCoefficients(root->left, coefficient);
  if (root->data != '~') {
    switch (coefficient) {
      case 'a':a_ += root->data;
        break;
      case 'b':b_ += root->data;
        break;
      case 'c':c_ += root->data;
        break;
      default:break;
    }
  }
  getCoefficients(root->right, coefficient);
}

std::pair<Node *, char> ExpressionTree::factorizeQuadraticExpressionHelper(const Node *node) {
  if (node) {
    if (isdigit(node->data)) {
      getCoefficients(node, 'c');
      return {const_cast<Node *>(node), 'c'};
    }

    if (node->data == '*') {
      if (node->right->data == '~' || isdigit(node->right->data)) {
        if (node->left->data == '^' && node->left->right->data == '2') {
          getCoefficients(node->right, 'a');
          return {node->right, 'a'};
        } else if (isalpha(node->left->data)) {
          getCoefficients(node->right, 'b');
          return {node->right, 'b'};
        }
      } else if (node->left->data == '~' || isdigit(node->left->data)) {
        if (node->right->data == '^' && node->right->right->data == '2') {
          getCoefficients(node->left, 'a');
          return {node->left, 'a'};
        } else if (isalpha(node->right->data)) {
          getCoefficients(node->left, 'b');
          return {node->left, 'b'};
        }
      }
      return {nullptr, '0'};
    }

    if (node->data == '-' || node->data == '~') {
      std::pair<Node *, char> res;
      if (node->data == '-') {
        res = factorizeQuadraticExpressionHelper(node->right);
        factorizeQuadraticExpressionHelper(node->left);
      } else {
        res = factorizeQuadraticExpressionHelper(node->left);
      }
      switch (res.second) {
        case 'a':a_.insert(a_.begin(), '-');
          break;
        case 'b':b_.insert(b_.begin(), '-');
          break;
        case 'c':c_.insert(c_.begin(), '-');
          break;
        default:break;
      }
      return {res.first, 'c'};
    }

    factorizeQuadraticExpressionHelper(node->left);
    factorizeQuadraticExpressionHelper(node->right);
  }
}

void ExpressionTree::factorizeQuadraticExpression(const Node *root) {
  if (root == nullptr) {
    std::cout << "Empty trinomial!\n";
    return;
  }

  factorizeQuadraticExpressionHelper(root);
  if (a_.empty() || b_.empty() || c_.empty()) {
    std::cout << "Wrong trinomial!\n";
    return;
  }

  a = stoi(a_);
  b = stoi(b_);
  c = stoi(c_);
  int discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    std::cout << "No decomposition with integers!\n";
    return;
  }

  int sqrtDiscriminant = std::sqrt(discriminant);
  if (sqrtDiscriminant * sqrtDiscriminant != discriminant) {
    std::cout << "No decomposition with integers!\n";
    return;
  }

  if ((-b + sqrtDiscriminant) % (2 * a) != 0 || (-b - sqrtDiscriminant) % (2 * a) != 0) {
    std::cout << "No decomposition with integers!\n";
    return;
  }

  int x1 = (-b + sqrtDiscriminant) / (2 * a);
  int x2 = (-b - sqrtDiscriminant) / (2 * a);

  if (x1 * x2 == c / a) {
    std::string infix_str = (a == 1 ? "" : std::to_string(a) + "*") + "(x"
        + (x1 >= 0 ? "-" + std::to_string(x1) : "+" + std::to_string(-x1)) + ")*(x"
        + (x2 >= 0 ? "-" + std::to_string(x2) : "+" + std::to_string(-x2)) + ")";
    std::cout << "\nInfix form: ";
    std::cout << infix_str;
    std::string postfix_str = convertToReversePolish(infix_str);
    std::cout << "\nPostfix form: ";
    std::cout << postfix_str;
    Node *root = constructTree(postfix_str);
    std::cout << "\nTree:\n";
    printTree(root);
  } else {
    std::cout << "No decomposition with integers!\n";
  }
}
