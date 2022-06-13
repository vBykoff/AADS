#include <iostream>
#include <vector>

//Реализуйте структуру данных типа “множество строк” на основе динамической
//хеш-таблицы с открытой адресацией. Хранимые строки непустые
//и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления
//значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми.
//Перехеширование выполняйте при добавлении элементов в случае,
//когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество,
//удаления строки из множества и проверки принадлежности данной строки множеству.
//
//1_2. Для разрешения коллизий используйте двойное хеширование.
//Требования: В таблице запрещено хранение указателей на описатель элемента.


const size_t INITIAL_CAPACITY = 8;
const float MAX_ALPHA = 0.75;

class StringHasher {
 public:

  StringHasher(unsigned int prime = 71)
      : prime_(prime)
  {
  }

  size_t operator()(const std::string &str)
  {
    size_t hash = 0;
    for (int i = 0; i < str.size(); i++)
    {
      hash = hash * prime_ + str[i];
    }
    return hash;
  }
 private:
  unsigned int prime_;
};

enum Condition {NIL, DEL, KEY};

template<class T>
struct HashElem {
  Condition mCondition;
  size_t mKey;
  T mData;
};

template<class T, class Hasher>
class HashTable {

  std::vector<HashElem<T>> vector_;
  size_t size_;
  Hasher hasher_;

  void grow() {

    std::vector<HashElem<T>> new_vec = std::move(vector_);

    HashElem<T> temp;
    temp.mCondition = NIL;
    vector_ = std::vector<HashElem<T>>(new_vec.size() * 2, temp);

    for (size_t i = 0; i < new_vec.size(); ++i) {
      if (new_vec[i].mCondition == KEY) {
        Add(new_vec[i].mData);
      }
    }
  }

  size_t doubleHash(const std::string &key, const size_t i) {
    return (hasher_(key) + (2 * hasher_(key) + 1) * i) % vector_.size();
  }

 public:

  HashTable(size_t pInitialCapacity = INITIAL_CAPACITY)
  : size_(0)
  {
    HashElem<T> temp;
    temp.mCondition = NIL;
    vector_ = std::vector<HashElem<T>>(pInitialCapacity, temp);
  }
  ~HashTable() = default;

  bool Add(const std::string &elem) {
    size_t firstDelPos = -1;
    size_t currentPos = -1;
    size_t key = hasher_(elem);

    //0 0 8
    if ((size_ + 1) > vector_.size() * MAX_ALPHA) {
//      std::cout << size_ << " " << vector_.size() * MAX_ALPHA << " " << vector_.size() << std::endl;
      grow();
    }

    for (size_t i = 0; i < vector_.size(); ++i) {
      currentPos = doubleHash(elem, i);
      if (vector_[currentPos].mCondition == DEL) {
        if (firstDelPos == -1) {
          firstDelPos = currentPos;
        }
      }
      else if (vector_[currentPos].mCondition == NIL) {
        if (firstDelPos == -1) {
          vector_[currentPos].mKey = key;
          vector_[currentPos].mData = elem;
          vector_[currentPos].mCondition = KEY;
          size_++;
          return true;
        } else {
          vector_[firstDelPos].mKey = key;
          vector_[firstDelPos].mData = elem;
          vector_[firstDelPos].mCondition = KEY;
          size_++;
          return true;
        }
      }
      else if (vector_[currentPos].mCondition == KEY) {
        if (vector_[currentPos].mKey == key) {
          return false;
        }
      }
    }

    vector_[firstDelPos].mKey = key;
    vector_[firstDelPos].mData = elem;
    vector_[firstDelPos].mCondition = KEY;
    size_++;
    return true;
  }

  bool Delete(const std::string &elem) {
    size_t firstDelPos = -1;
    size_t currentPos = -1;
    size_t key = hasher_(elem);

    for(size_t i = 0; i < size_; ++i) {
      currentPos = doubleHash(elem, i);
      if (vector_[currentPos].mCondition == DEL) {
        continue;
      }
      else if (vector_[currentPos].mCondition == NIL) {
        return false;
      }
      else if (vector_[currentPos].mCondition == KEY) {
        if (vector_[currentPos].mKey == key) {
          vector_[currentPos].mCondition = DEL;
          return true;
        }
      }
    }
    return false;
  }
  bool Has(const std::string &elem) {
    size_t currentPos = -1;
    size_t key = hasher_(elem);

    for (size_t i = 0; i < size_; ++i) {
      currentPos = doubleHash(elem, i);
      if (vector_[currentPos].mCondition == DEL) {
        continue;
      }
      else if (vector_[currentPos].mCondition == NIL) {
        return false;
      }
      else if (vector_[currentPos].mCondition == KEY) {
        if (vector_[currentPos].mKey == key) {
          return true;
        }
      }
    }
    return false;
  }

};

int main() {
  HashTable<std::string, StringHasher> table;
  char op;
  std::string key;

  while (std::cin >> op >> key)
  {
    switch (op)
    {
      case '+':
      {
        std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
      case '-':
      {
        std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
      case '?':
      {
        std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      }
    }
  }
  return 0;
}
