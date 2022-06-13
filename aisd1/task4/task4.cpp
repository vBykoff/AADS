#include <iostream>

//4.3 Планировщик процессов
//В операционной системе Technux есть планировщик процессов.
//Каждый процесс характеризуется:
//- приоритетом P
//- временем, которое он уже отработал t
//- временем, которое необходимо для завершения работы процесса T
//Планировщик процессов выбирает процесс с минимальным значением P * (t + 1),
//выполняет его время P и кладет обратно в очередь процессов.
//Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.
//Требуется посчитать кол-во переключений процессора.

struct Process {
  int P;
  unsigned int t;
  unsigned int T;
};

class ProcessComparator {
 public:
  bool operator() (const Process &p1, const Process &p2) {
    return p1.P * (p1.t + 1) <= p2.P * (p2.t + 1);
  }
};

//Min heap
template <class T, class Comparator>
class Heap
{
 public:

  Heap(const Comparator& p_cmp, size_t p_size = 3)
      : cmp(p_cmp), mSize(p_size), mPos(0) {
    mArray = new T[mSize];
  }

  Heap(Heap& p): cmp(p.p_cmp), mSize(p.p_size), mPos(p.mPos) {
    mArray = new T[mSize];
    for (size_t i = 0; i < mSize; ++i) {
      mArray[i] = p.mArray[i];
    }
  }

  void print() {
    std::cout << "[";
    for (size_t i = 0; i < mPos; ++i) {
      std::cout << "{t: " << mArray[i].t << "(" << mArray[i].P << "," << mArray[i].T
          << ") " << "Pr: " << mArray[i].P * (mArray[i].t + 1) << "} ";
    }
    std::cout << "] - mPos" << mPos << std::endl;
  }

  void add(const T& p_elem) {
    if (mPos >= mSize) {
      resize();
    }
    mArray[mPos] = p_elem;
    siftUp(mPos);
    mPos++;
  }
  const T& top() {
    if (mSize != 0) {
      return mArray[0];
    }
    else {
      return T();
    }
  }
  const T extractTop() {
    const T top = mArray[0];
    mArray[0] =  mArray[mPos - 1];

    mPos--;
    siftDown(0);
    return top;
  }

  bool isEmpty() {
    return mPos == 0;
  }

  ~Heap() {
    delete[] mArray;
  }

 private:

  void siftDown(size_t pPos)
  {
    while (  cmp(mArray[2 * pPos + 1], mArray[pPos]) && (2 * pPos + 1 < mPos)
          || cmp(mArray[2 * pPos + 2], mArray[pPos]) && (2 * pPos + 2 < mPos) //
          )
    {
      if (cmp(mArray[2 * pPos + 1], mArray[2 * pPos + 2]) && (2 * pPos + 1 < mPos)) {
        swap(mArray[pPos], mArray[2 * pPos + 1]);
        pPos = 2 * pPos + 1;
      }
      else if (cmp(mArray[2 * pPos + 2], mArray[2 * pPos + 1]) && (2 * pPos + 2 < mPos)) {
        swap(mArray[pPos], mArray[2 * pPos + 2]);
        pPos = 2 * pPos + 2;
      }
    }
  }
  void siftUp(size_t pPos)
  {
    while (cmp(mArray[pPos], mArray[(pPos - 1) / 2]) && (pPos > 0)){
      swap(mArray[(pPos - 1) / 2], mArray[pPos]);
      pPos = (pPos - 1) / 2;
    }
  }
  void swap(T& p1, T& p2) {
    T temp = p1;
    p1 = p2;
    p2 = temp;
  }
  void resize() {
    //mArray = (T*)realloc (mArray, 2 * mSize * sizeof(T));
    T* temp = new T[mSize];
    for (size_t i = 0; i < mSize; ++i) {
      temp[i] = mArray[i];
    }
    delete[] mArray;
    mSize *= 2;
    mArray = new T[mSize];
    for (size_t i = 0; i < mSize; ++i) {
      temp[i] = mArray[i];
    }
  }

  T* mArray;
  size_t mPos;
  size_t mSize;
  Comparator cmp;
};

int main() {
  size_t n;
  int P;
  unsigned int T;
  int count = 0;
  ProcessComparator cmp;

  std::cin >> n;
  Heap<Process, ProcessComparator> heap(cmp, n);

  Process temp;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> P >> T;
    temp.P = P;
    temp.T = T;
    temp.t = 0;
    heap.add(temp);
  }

  while (!heap.isEmpty()) {
    temp = heap.extractTop();

    temp.t += temp.P;
    if (temp.t < temp.T) {
      heap.add(temp);
    }
    count++;
  }
  std::cout << count << std::endl;
  return 0;
}

