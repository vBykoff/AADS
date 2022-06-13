#include <iostream>
#include <vector>
#include <deque>

//Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
//Требуется построить бинарное дерево, заданное наивным порядком вставки.
//Т.е., при добавлении очередного числа K в дерево с корнем root,
//если root→Key ≤ K, то узел K добавляется в правое поддерево root;
//иначе в левое поддерево root.
//Требования: Рекурсия запрещена.
//Решение должно поддерживать передачу функции сравнения снаружи.
//
//2_2. Выведите элементы в порядке pre-order (сверху вниз).



template<class T, class Comparator = std::less<T>>
class BinaryTree {
  struct Node {
    T data;
    Node *left;
    Node *right;

    Node(const T data)
    : data(data), left(nullptr), right(nullptr)
    {}
  };

  Comparator cmp_;
  Node *root_;

  class deleteFunc {
   public:
    void operator()(Node *p) {
      delete p;
    }
  };

  class PrintFunc {
   public:
    void operator()(Node *p) {
      std::cout << p->data << " ";
    }
  };

  template<class Func>
  void PreOrderDFS() {
    Func f;
    std::deque<Node*> stack;

    stack.push_back(root_);
    Node *temp;

    while (!stack.empty()) {
      temp = stack.back();
      Node *right = temp->right;
      Node *left = temp->left;

      f(stack.back());
      stack.pop_back();

      if (right)
        stack.push_back(right);
      if (left)
        stack.push_back(left);
    }
  }

 public:

  BinaryTree()
  : cmp_(Comparator()), root_(nullptr)
  {}

  Node* add(const T elem) {
    Node *temp = root_;
    if (!root_) {
      root_ = new Node(elem);
      return root_;
    }
    while (true) {
      if (cmp_(elem, temp->data)) {
        if (temp->left) {
          temp = temp->left;
        }
        else {
          temp->left = new Node(elem);
          return temp->left;
        }
      }
      else {
        if (temp->right) {
          temp = temp->right;
        }
        else {
          temp->right = new Node(elem);
          return temp->right;
        }
      }
    }

  }


  void PrintPreOrderDFS() {
    PreOrderDFS<PrintFunc>();
  }

  ~BinaryTree() {
    //
    Node *temp = root_;
    PreOrderDFS<deleteFunc>();
  }

};


int main() {
  BinaryTree<int> tree;
  int n, temp;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> temp;
    tree.add(temp);
  }
  tree.PrintPreOrderDFS();
  return 0;
}