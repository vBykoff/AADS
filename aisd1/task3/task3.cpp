#include <iostream>
#include <vector>


class Queue {

  int *buffer_;
  size_t head_;
  size_t tail_;
  size_t size_;

  void resize() {
    int *temp = new int[size_];
    for (size_t i = 0, temp_iter = head_;
      temp_iter < tail_; ++i, temp_iter = (temp_iter + 1) % size_)
    {
      temp[i] = buffer_[temp_iter];
    }

    delete [] buffer_;
    buffer_ = new int[size_ * 2];

    for (size_t i = 0; i < size_; ++i) {
      buffer_[i] = temp[i];
    }
    size_ *= 2;
  }

 public:

  Queue()
      : head_(0)
      , tail_(0)
      , size_(2)
  {
    buffer_ = new int[size_];
  }

  Queue(int count)
  : head_(0)
  , tail_(0)
  , size_(count)
  {
    buffer_ = new int[size_];
  }

  ~Queue() {
    delete [] buffer_;
  }

  int dequeue() {
    if (head_ == tail_) {
      return -1;
    }
    int result = buffer_[head_];
    head_ = (head_ + 1) % size_;
    return result;
  }

  void enqueue(int elem) {
    if (head_ - tail_ <= 1) {
      resize();
    }
    buffer_[tail_] = elem;
    tail_ = (tail_ + 1) % size_;
  }

};

int main() {

  int a, b, count;
  std::cin >> count;
  Queue queue;
  for (int i = 0; i < count; ++i) {
    std::cin >> a >> b;
    if (a == 3) {
      queue.enqueue(b);
    }
    if (a == 2 && queue.dequeue() != b) {
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";
  return 0;
}