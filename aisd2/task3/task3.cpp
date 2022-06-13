#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

template <typename T, typename Comparator = std::less<T>>
class BTree
{
 public:
  struct Node
  {
    Node(bool leaf)
        : leaf(leaf)
    {
    }

    ~Node()
    {
      for (Node *child: children)
      {
        delete child;
      }
    }

    bool leaf;
    std::vector<T> keys;
    std::vector<Node*> children;
  };

  BTree(size_t min_degree)
      : root(nullptr), t(min_degree)
  {
    assert(min_degree >= 2);
  }

  ~BTree()
  {
    if (root)
      delete root;
  }

  void Insert(const T &key)
  {
    if (!root)
      root = new Node(true);

    // ����� � ������: ���� ��� ������ �� ������ �������
    // ������������� ���� -- ������� ��������� ���, ����� ����������
    if (isNodeFull(root))
    {
      Node *newRoot = new Node(false);
      newRoot->children.push_back(root);
      root = newRoot;
      splitChild(root, 0);
    }

    // ������ ������ ����� �� ����������, ����� ������� insertNonFull
    insertNonFull(root, key);
  }

  void debugPrint()
  {
    debugPrint(root, 0);
  }

  void BFS() {
    if (!root) {
      return;
    }
    size_t pos = 0;
    size_t childCount = 0;
    std::queue<Node*> q;
    std::vector<int> layers;
    q.push(root);
    layers.push_back(1);

    while (!q.empty()) {
      Node *tmp = q.front();
      q.pop();

      for (auto i: tmp->keys) {
        std::cout << i << " ";
      }

      layers[pos]--;
      if (layers[pos] == 0) {
        std::cout << "\n";
        pos++;
      }
      for (auto i: tmp->children) {
        q.push(i);
      }
      layers.push_back(tmp->children.size());
    }
  }

 private:

  Node *root;
  size_t t;
  Comparator cmp;

  bool isNodeFull(Node *node)
  {
    return node->keys.size() == 2*t - 1;
  }

  // �������� ���� key � �������������� �� ������������� ���� node
  void insertNonFull(Node *node, const T &key)
  {
    int pos = node->keys.size() - 1;

    // �������������� �� ��������������� ���� -- ������� ����� ���� � ����
    if (node->leaf)
    {
      // ��������� ������ ������ ��� ������� ������
      node->keys.resize(node->keys.size() + 1);

      while (pos >= 0 && cmp(key, node->keys[pos]))
      {
        // ������� ����� ������ ������, ������� ������ �� 1
        node->keys[pos + 1] = node->keys[pos];
        pos--;
      }
      // ��������� ����� ���� �� ������������� � ����� �����
      node->keys[pos + 1] = key;

    }
      // �� ����, ������ ���� �������, ����� � ���� �� ���
    else
    {
      // ���� ������� �������, � �������� ������� ����
      while (pos >= 0 && cmp(key, node->keys[pos]))
      {
        pos--;
      }

      // ���� ������� � ��� �����, ���� ��� ������� �������
      if (isNodeFull(node->children[pos + 1]))
      {
        splitChild(node, pos + 1);
        // ����� ��������� ������� � ������� ���� �� ���� �������� ����
        // ���� ���������� � � ���

        if (cmp(node->keys[pos + 1], key))
          pos++;
      }
      insertNonFull(node->children[pos + 1], key);
    }
  }

  void debugPrint(Node *node, int indent)
  {
    std::cout << std::string(indent, ' ');
    std::cout << "keys: [";
    for (auto it = node->keys.begin(); it != node->keys.end(); it++)
    {
      std::cout << (*it);
      if (it + 1 != node->keys.end())
        std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    for (auto child: node->children)
    {
      debugPrint(child, indent + 4);
    }
  }

  ///////////////////////////////////////////////
  // ��������� �������������� ������� node �� ������� index
  // (���� ����������� ������)
  void splitChild(Node *node, size_t index) {


    Node *yNode = node->children[index];
    Node *zNode = new Node(yNode->leaf);
    T median = yNode->keys[t - 1];

    for (size_t i = 0; i < t - 1; ++i) {
      zNode->keys.push_back(yNode->keys[i + t]);
    }
    if (!yNode->leaf) {
      for (size_t i = 0; i < t; ++i) {
        zNode->children.push_back(yNode->children[i + t]);
      }
      yNode->children.resize(t);
    }
    yNode->keys.resize(t - 1);

    node->children.resize(node->children.size() + 1);
    for (size_t i = node->children.size() - 1; i > index + 1; --i) {
      node->children[i] = node->children[i - 1];
    }
    node->children[index + 1] = zNode;

    node->keys.resize(node->keys.size() + 1);
    for (size_t i = node->keys.size() - 1; i > index; --i) {
      node->keys[i] = node->keys[i - 1];
    }
    node->keys[index] = median;
   }

  // ������ ������� testBTree friend'��, ����� ����� �����������
  // ���������� � ��������� ����� ������
  friend void testBTree();
};

// ������ ������� �� ����������� � ������
void testBTree()
{
  BTree<char> tree(3);

  tree.root = new BTree<char>::Node(false);
  tree.root->keys = {'G', 'M', 'P', 'X'};

  {
    auto child = new BTree<char>::Node(true);
    child->keys = {'A', 'C', 'D', 'E'};
    tree.root->children.push_back(child);
  }

  {
    auto child = new BTree<char>::Node(true);
    child->keys = {'J', 'K'};
    tree.root->children.push_back(child);
  }
  {
    auto child = new BTree<char>::Node(true);
    child->keys = {'N', 'O'};
    tree.root->children.push_back(child);
  }
  {
    auto child = new BTree<char>::Node(true);
    child->keys = {'R', 'S', 'T', 'U', 'V'};
    tree.root->children.push_back(child);
  }
  {
    auto child = new BTree<char>::Node(true);
    child->keys = {'Y', 'Z'};
    tree.root->children.push_back(child);
  }

  std::cout << "Initial tree:" << std::endl;
  tree.debugPrint();
  std::cout << std::endl;

  std::string insertKeys = "BQLF";
  // ����������� ��������� � ������ �����
  for (auto c: insertKeys)
  {
    tree.Insert(c);
    std::cout << "After inserting " << c << ":" << std::endl;
    tree.debugPrint();
    std::cout << std::endl;
  }
}



int main() {
//  testBTree();
  int n, tmp;
  std::cin >> n;
  BTree<int> tree(n);
  while (std::cin >> tmp) {
    tree.Insert(tmp);
  }
  tree.BFS();
  tree.debugPrint();

}