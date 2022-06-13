#include <iostream>

//4_2. Порядковые статистики. Дано число N и N строк.
//Каждая строка содержит команду добавления или удаления натуральных чисел,
//а также запрос на получение k-ой порядковой статистики.
//Команда добавления числа A задается положительным числом A,
//команда удаления числа A задается отрицательным числом “-A”.
//Запрос на получение k-ой порядковой статистики задается числом k.
//Требования: скорость выполнения запроса - O(log n).
//
//Необходимо сделать 3 модификации:
//1. Добавить поддержку компараторов.
//2. Из двух функций findMin и removeMin сделать одну -- findAndRemoveMin,
//которая делает работу этих двух за один проход.
//3. Я вместо удаляемого подставляю минимальный элемент из правого поддерева.
//Вам нужно посмотреть на высоты правого и левого поддеревьев
//и использовать либо максимальный из левого,
//либо минимальный из правого, в зависимости от того,
//какое поддерево более глубокое (брать более глубокое).

template <typename T, typename Comparator = std::less<T>>
class AvlTree
{
  struct Node
  {
    Node(const T &data)
        : data(data), height(1), count(1), left(nullptr), right(nullptr)
    {
    }

    T data;
    size_t height;
    size_t count;
    Node *left;
    Node *right;
  };

 public:

  AvlTree()
      : root(nullptr)
  {
  }

  ~AvlTree()
  {
    destroyTree(root);
  }

  void Add(const T &data)
  {
    root = addInternal(root, data);
  }

  bool Has(const T &data)
  {
    Node *tmp = root;
    while (tmp)
    {
      if (tmp->data == data)
      {
        return true;
      }
      else if (cmp(tmp->data, data))
      {
        tmp = tmp->right;
      }
      else
      {
        tmp = tmp->left;
      }
    }
    return false;
  }

  void Delete(const T &data)
  {
    root = deleteInternal(root, data);
  }

  T KthStat(size_t k) {
    return kth_stat(root, k);
  }

 private:

  Node *root;
  Comparator cmp;

  void destroyTree(Node *node)
  {
    if (node)
    {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

  Node* deleteInternal(Node *node, const T &data)
  {
    if (!node)
      return nullptr;
    if (cmp(node->data, data))
    {
      node->right = deleteInternal(node->right, data);
    }
    else if (cmp(data, node->data))
    {
      node->left = deleteInternal(node->left, data);
    }
    else
    {
      Node *left = node->left;
      Node *right = node->right;

      delete node;

      ///////////////////////////////////// new

      if (getHeight(left) > getHeight(right))
      {

        if (!right)
          return left;

        auto temp = findAndRemoveMin(right);
        Node* min = temp.first;
        min->right = temp.second;
        min->left = left;

        return doBalance(min);
      }
      else
      {

        if (!left)
          return right;

        auto temp = findAndRemoveMax(left);
        Node* max = temp.first;
        max->left = temp.second;
        max->right = right;
        return doBalance(max);
      }
    }
    /////////////////////////////////////
    return doBalance(node);
  }

  ////////////////// new

  std::pair<Node*,Node*> findAndRemoveMin(Node *node) {
    if (!node->left) {
//      return node->right;
      return std::pair<Node*, Node*>(node, node->right);
    }

    std::pair<Node*, Node*> temp;
    temp = findAndRemoveMin(node->left);
    node->left = temp.second;

    return std::pair<Node*, Node*>(temp.first, doBalance(node));
  }

  std::pair<Node*,Node*> findAndRemoveMax(Node *node) {
    if (!node->right) {
      return std::pair<Node*, Node*>(node, node->left);
    }

    std::pair<Node*, Node*> temp;
    temp = findAndRemoveMax(node->right);
    node->right = temp.second;

    return std::pair<Node*, Node*>(temp.first, doBalance(node));
  }

  size_t getCount(Node *node) {
    return node ? node->count : 0;
  }

  void fixCount(Node *node) {
    node->count = getCount(node->left) + getCount(node->right) + 1;
  }

  T kth_stat(Node *node, size_t k) {
    T res;

    if (getCount(node->left) == k) {
      res = node->data;
    }
    else if (getCount(node->left) > k) {
      res = kth_stat(node->left, k);
    }
    else {
      res = kth_stat(node->right, k - getCount(node->left) - 1);
    }

    return res;
  }

  ///////////////////////

  Node* findMin(Node *node)
  {
    while (node->left)
      node = node->left;
    return node;
  }

  Node* removeMin(Node *node)
  {
    if (!node->left)
      return node->right;
    node->left = removeMin(node->left);
    return doBalance(node);
  }

  Node* addInternal(Node *node, const T &data)
  {
    if (!node)
      return new Node(data);
    if (!cmp(data, node->data))
    {
      node->right = addInternal(node->right, data);
    }
    else
    {
      node->left = addInternal(node->left, data);
    }
    return doBalance(node);
  }

  size_t getHeight(Node *node)
  {
    return node ? node->height : 0;
  }

  void fixHeight(Node *node)
  {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  Node* rotateLeft(Node *node)
  {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    fixHeight(node);
    fixHeight(tmp);
    fixCount(node);
    fixCount(tmp);
    return tmp;
  }

  Node* rotateRight(Node *node)
  {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fixHeight(node);
    fixHeight(tmp);
    fixCount(node);
    fixCount(tmp);
    return tmp;
  }

  int getBalance(Node *node)
  {
    return getHeight(node->right) - getHeight(node->left);
  }

  Node* doBalance(Node *node)
  {
    fixHeight(node);

    switch (getBalance(node))
    {
      case 2:
      {
        if (getBalance(node->right) < 0)
          node->right = rotateRight(node->right);
        return rotateLeft(node);
      }
      case -2:
      {
        if (getBalance(node->left) > 0)
          node->left = rotateLeft(node->left);
        return rotateRight(node);
      }
      default:
        return node;
    }
  }

};

int main() {

  AvlTree<int> tree;
  char op;
  std::string key;
  int count;
  std::cin >> count;
  int elem, k;
  for (int i = 0; i < count; ++i) {
    std::cin >> elem >> k;
    if (elem > 0) {
      tree.Add(elem);
    }
    else {
      tree.Delete(-elem);
    }
    std::cout << tree.KthStat(k) << std::endl;
  }
  return 0;
}
