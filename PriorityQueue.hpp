#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
  std::vector<T> heap;

  void heapifyUp(int index) {
    while (index > 0 && heap[parent(index)] > heap[index]) {
      std::swap(heap[parent(index)], heap[index]);
      index = parent(index);
    }
  }

  void heapifyDown(int index) {
    int size = heap.size();
    int smallest = index;

    int l = left(index);
    int r = right(index);

    if (l < size && heap[l] < heap[smallest]) smallest = l;
    if (r < size && heap[r] < heap[smallest]) smallest = r;

    if (smallest != index) {
      std::swap(heap[index], heap[smallest]);
      heapifyDown(smallest);
    }
  }

  int parent(int i) { return (i - 1) / 2; }
  int left(int i) { return 2 * i + 1; }
  int right(int i) { return 2 * i + 2; }

public:
  void push(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
  }

  void pop() {
    if (heap.empty())
    throw std::runtime_error("Heap is empty");

    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
    heapifyDown(0);
  }

  T top() const {
    if (heap.empty())
    throw std::runtime_error("Heap is empty");
    return heap[0];
  }

  bool empty() const {
    return heap.empty();
  }

  int size() const {
    return heap.size();
  }
};

#endif
