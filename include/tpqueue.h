// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
template<typename T, int kSize>
class TPQueue {
    // реализация шаблона очереди с приоритетом на кольцевом буфере
    T arr[kSize];
    int first, last, stored;
    void insert(const T& value);  // сдвинуть очередь
 public:
    TPQueue();
    void push(const T& value);
    const T& pop();
    const T& popBack();
    bool isEmpty();
    bool isFull();

    void print();
};

struct SYM {
    char ch;
    int prior;
};


template <typename T, int kSize>
TPQueue<T, kSize>::TPQueue(): first(0), last(0), stored(0), arr{SYM{}} {}

template <typename T, int kSize>
void TPQueue<T, kSize>::push(const T &value) {
    if (isFull())
        throw std::length_error("TPQueue::push -> Queue is full!");
    if (value.prior > arr[first].prior) {
        if (first > 0) {
            arr[--first] = value;
            ++stored;
        } else {
            insert(value);
        }
    } else {
        insert(value);
    }
}

template <typename T, int kSize>
void TPQueue<T, kSize>::insert(const T& value) {
    T replacedValue1 = value;
    T replacedValue2;
    bool didReplace = false;
    int pointer = first;
    while (pointer <= last) {
        if (stored > 0 && arr[pointer].prior >= value.prior) {
            ++pointer;
            continue;
        }
        replacedValue2 = arr[pointer];
        arr[pointer] = replacedValue1;
        replacedValue1 = replacedValue2;
        didReplace = true;
        ++pointer;
    }
    if (didReplace) {
        arr[pointer] = replacedValue1;
        ++last;
        ++stored;
    }
    std::cout << ">> Stored: \n" << first <<
        " - " << last << " - " << stored << std::endl;
    this->print();
}

template <typename T, int kSize>
const T& TPQueue<T, kSize>::pop() {
    if (isEmpty())
        throw std::runtime_error("TPQueue::pop -> Queue is empty!");
    --stored;
    return arr[first++ % kSize];
}

template <typename T, int kSize>
const T& TPQueue<T, kSize>::popBack() {
    if (isEmpty())
        throw std::runtime_error("TPQueue::popBack -> Queue is empty!");
    --stored;
    return arr[last-- % kSize];
}

template <typename T, int kSize>
bool TPQueue<T, kSize>::isEmpty() {
    return first == last && stored == 0;
}

template <typename T, int kSize>
bool TPQueue<T, kSize>::isFull() {
    return stored == kSize;
}

template <typename T, int kSize>
void TPQueue<T, kSize>::print() {
    std::cout << '[';
    for (auto e : arr) {
        std::cout << e.ch << ", ";
    }
    std::cout << ']' << std::endl;
}

#endif  // INCLUDE_TPQUEUE_H_
