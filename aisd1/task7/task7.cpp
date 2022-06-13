#include <iostream>
#include <cassert>

typedef unsigned long long long_t;

void counting_sort(long_t *arr, size_t n, size_t byte)
{
  assert(arr != nullptr);
  assert(n > 0);

  size_t countBufSize = 256;
  int *countBuf = new int[countBufSize]();

  for (int i = 0; i < n; i++)
  {
    countBuf[arr[i] >> (8 * byte) & 0xFF]++;
  }

  for (int i = 1; i < countBufSize; i++)
  {
    countBuf[i] += countBuf[i - 1];
  }

  long_t *tmpBuf = new long_t[n]();

  for (int i = n - 1; i >= 0; i--)
  {
    int countBufPos = arr[i] >> (8 * byte) & 0xFF;
    countBuf[countBufPos]--;
    tmpBuf[countBuf[countBufPos]] = arr[i];
  }

  for (int i = 0; i < n; i++)
  {
    arr[i] = tmpBuf[i];
  }

  delete [] countBuf;
  delete [] tmpBuf;
}

void LSD_sort(long_t *arr, size_t n) {
  for (size_t i = 0; i < sizeof(long_t); ++i) {
    counting_sort(arr, n, i);
  }
}


int main(int argc, const char * argv[]) {
  int n = 0;
  std::cin >> n;
  long_t *arr = new long_t[n];

  for (int i = 0; i < n; i++)
  {
    std::cin >> arr[i];
  }

  LSD_sort(arr, n);

  for (int i = 0; i < n; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  delete[] arr;
  return 0;
}

