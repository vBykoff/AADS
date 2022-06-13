#include <iostream>

//2_4. Дан отсортированный массив различных целых чисел A[0..n-1]
//и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i]
//найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i]: O(log(k)).
//Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон
//для бинарного поиска размером порядка k с помощью экспоненциального поиска,
//а потом уже в нем делать бинарный поиск.

//Бинарный поиск ближайшего элемента
int binarySearch(int elem, int *a, size_t beg, size_t end) {
  size_t middle;

  //Выибираем 2 наиболее близких элемента
  while (end != beg + 1) {
    middle = (end + beg) / 2;
    if (elem == a[middle]) {
      return middle;
    }
    if (elem > a[middle] && middle != 0) {
      beg = middle;
    }
    else {
      end = middle;
    }
  }

  //Выбираем ближайший
  if (abs(a[beg] - elem) <= abs(a[end] - elem)) {
    return beg;
  }
  else {
    return end;
  }
}

//Определяем границы посика
int expSearch(int elem, int *a, size_t n) {
  size_t beg, end;
  for (end = 1; (end < n) && (elem > a[end]) ; end = end << 1) {}
  if (end > n - 1) {
    end = n - 1;
  }

  beg = end >> 1;
  return binarySearch(elem, a, beg, end);
}

//Запускаем экспоненциальный поиск для каждого элемента
void solution(int *a, const size_t n, int *b, const size_t m, int *result) {
  for (size_t i = 0; i < m; ++i) {
    result[i] = expSearch(b[i], a, n);
  }
}

int main() {
  size_t n,m;

  //A[1..n-1]
  std::cin >> n;
  int *a = new int[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  //B[1..m-1]
  std::cin >> m;
  int *b = new int[m];
  for (size_t i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  int *result = new int[m];
  solution(a, n, b, m, result);

  //Вывод результата
  for (size_t i = 0; i < m; ++i) {
    std::cout << result[i] << " ";
  }

  delete[] result;
  delete[] b;
  delete[] a;
  return 0;
}
