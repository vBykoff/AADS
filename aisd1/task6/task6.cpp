#include <iostream>
//Дано множество целых чисел из [0..10^9] размера n.
//Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
//- 10%  перцентиль
//- медиана
//- 90%  перцентиль
//6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
//Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

template <class T>
void swap(T& p1, T& p2) {
  T temp = p2;
  p2 = p1;
  p1 = temp;
}

template<class T, class Comparator = std::less<T>>
int partition(T *pVec, size_t pBeg, size_t pEnd, Comparator cmp = Comparator()) {
  //Опорный элемент
  size_t pivot;
  if (cmp(pVec[pBeg], pVec[(pBeg + pEnd)/2]) && cmp(pVec[pEnd], pVec[pBeg])) {
    pivot = pBeg;
  } else if (cmp(pVec[pEnd], pVec[(pBeg + pEnd)/2]) && cmp(pVec[pBeg], pVec[pEnd])) {
    pivot = pEnd;
  } else {
    pivot = (pBeg + pEnd)/2;
  }
  swap(pVec[pivot], pVec[pEnd]);

  //Начальное значение i
  size_t i = pBeg - 1;
  //Начальное значение j
  size_t j = i + 1;

  while (j < pEnd) {
    if (cmp(pVec[j], pVec[pEnd])) {
      i++;
      swap(pVec[i], pVec[j]);
    }
    j++;
  }
  swap(pVec[pEnd], pVec[i + 1]);
  return i + 1;
}


template<class T, class Comparator = std::less<T>>
T kth_stat(T *pVec, size_t pSize, size_t k, Comparator cmp = Comparator()) {
  size_t beg = 0;
  size_t end = pSize - 1;
  while (true) {
    int pos = partition(pVec, beg, end, cmp);
    if (pos == k) {
      return pVec[pos];
    }
    else if (pos > k) {
      end = pos - 1;
    }
    else {
      beg = pos + 1;
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;
  int *array = new int[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  std::cout << kth_stat<int>(array, n, (n / 10.)) << std::endl;
  std::cout << kth_stat<int>(array, n, (n / 2)) <<  std::endl;
  std::cout << kth_stat<int>(array, n, (n * 9 / 10)) << std::endl;

  delete[] array;
  return 0;
}
