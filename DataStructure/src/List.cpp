#ifndef LIST_CPP
#define LIST_CPP
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @file list.cpp
 * @brief Implementation of a dynamic array-based list data structure.
 *
 * This file contains the implementation of a dynamic array-based list data
 * structure, which supports various operations such as appending, inserting,
 * removing, popping, counting, reversing, extending, searching for differences,
 * concatenating, and indexing.
 *
 * The list is implemented using a dynamic array, which is automatically resized
 * when necessary. The initial capacity of the array is 8, and the extend ratio
 * is 2.
 *
 * @tparam Elemtype The type of elements stored in the list.
/*/

template <typename Elemtype> class List {

private:
  Elemtype *data;
  int dataSize = 0;
  int dataCapacity = 8;
  int extendRatio = 2;

public:
  List() {
    data = new Elemtype[dataCapacity];
    if (data == nullptr) {
      throw "Failed to allocate memory";
    }
  }
  List(int capacity) {
    data = new Elemtype[capacity];
    if (data == nullptr) {
      throw "Failed to allocate memory";
    }
  }

  ~List() {
    delete[] data;
    // std::cout << "Delete"<< std::endl;
  }

  Elemtype* begin() {
    return data;
  }

  // 返回指向数据结束的迭代器
  Elemtype* end() {
    return data + dataSize;
  }

  void clear() {
    dataSize = 0;
    dataCapacity = 8;
    delete[] data;
    data = new Elemtype[dataCapacity];
    if (data == nullptr) {
      throw "Failed to allocate memory";
    }
  }

  int size() const { return dataSize; }

  const int capacity() { return dataCapacity; }

  const bool empty() { return dataSize == 0; }

  void extendCapacity() { // 新增扩容量
    int newCapacity = capacity() * extendRatio;
    Elemtype *tmp = data;
    data = new Elemtype[newCapacity];
    if (data == nullptr) {
      throw "Failed to allocate memory";
    }
    for (int i = 0; i < size(); i++) {
      data[i] = tmp[i];
    }
    delete[] tmp;
    dataCapacity = newCapacity;
  }

  // 在尾部追加元素
  void append(const Elemtype &val) {
    if (size() + 1 > capacity()) {
      extendCapacity();
    }
    data[size()] = val;
    dataSize++;
  }

  // 在索引位置插入val
  void insert(const int &index, const Elemtype &val) {
    // std::cout<< "start insert" <<std::endl;
    if (index >= size() || index < 0) {
      throw "index out of range";
    }
    // std::cout<< "zzz"<<std::endl;
    if (size() + 1 > capacity()) {
      extendCapacity();
    }
    // std::cout<< "zzz"<<std::endl;
    for (int i = size() - 1; i >= index; i--) {
      // std::cout<< "i is "<< i << std::endl;
      data[i + 1] = data[i];
    }
    data[index] = val;
    dataSize++;
    std::cout << "insert finished" << std::endl;
  }

  // 移除对应元素
  void remove(int index) {
    if (index >= size() || index < 0)
      throw "index out of range";
    for (int i = index; i < size() - 1; i++) {
      data[i] = data[i + 1];
    }
    delete data[index];
    dataSize--;
  }

  // 弹出最后一个元素
  Elemtype pop(int index = -1) {
    if (index >= size() || index < -1)
      throw "index out of range";
    if (index == -1) {
      dataSize--;
      return data[size()];
    }
    Elemtype temp = data[index];
    for (int i = index; i < size() - 1; i++) {
      data[i] = data[i + 1];
    }
    dataSize--;
    return temp;
  }

  int count(Elemtype val) {
    int res = 0;
    for (int i = 0; i < size(); i++) {
      if (data[i] == val)
        res++;
    }
    return res;
  }

  bool judgeHuiwen() {
    if (size() <= 1)
      return true;
    int begin = 0, end = size() - 1;
    while (begin < end) {
      if (data[begin] != data[end])
        return false;
      begin++;
      end--;
    }
    return true;
  }

  void reverse() {
    int begin = 0, end = size() - 1;
    while (begin < end) {
      Elemtype temp;
      temp = data[begin];
      data[begin] = data[end];
      data[end] = temp;
      begin++;
      end--;
    }
  }

  Elemtype &at(int index) {
    if (index >= size() || index < 0)
      throw "index out of range";
    return data[index];
  }

  List<Elemtype> operator+(const List<Elemtype> &other) {
    List<Elemtype> res;
    for (int i = 0; i < size(); i++) {
      res.append(data[i]);
    }
    for (int i = 0; i < other.size(); i++) {
      res.append(other[i]);
    }
    return res;
  }

  Elemtype operator[](int index) {
    if (index >= size() || index < -size())
      throw "index out of range";
    if (index < 0)
      return data[index + size()];
    else
      return data[index];
  }

  const int &operator[](int index) const {
    if (index >= size() || index < -size())
      throw "index out of range";
    if (index < 0)
      return data[index + size()];
    else
      return data[index]; // 在这里返回相应的元素，不允许修改对象
  }

  // 打印
  void display() {
    for (int i = 0; i < size(); i++) {
      std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
  }
};
#endif