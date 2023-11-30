#pragma once
#include <iostream>
template <typename T>
class Stack{
private:
  T *data;
  int dataSize = 0; 
  int dataCapacity = 8; 
  int extendRatio = 2;

public:
  Stack(){
    data = new T[dataCapacity];
    if (data == nullptr){
      throw "Failed to allocate memory";
    }
  }
  Stack(int capacity){
    data = new T[capacity];
    if (data == nullptr){
      throw "Failed to allocate memory";
    }
  }

  ~Stack(){
    delete[] data;
  }

  void clear(){
    dataSize = 0;
    dataCapacity = 8;
    delete[] data;
    data = new T[dataCapacity];
    if (data == nullptr){
      throw "Failed to allocate memory";
    }
  }

  void extendCapacity(){  // 新增扩容量
    int newCapacity = dataCapacity * extendRatio;
    T *tmp = data;
    data = new T[newCapacity];
    if (data == nullptr){
      throw "Failed to allocate memory";
    }
    for (int i = 0; i < dataSize; i++){
      data[i] = tmp[i];
    }
    delete[] tmp;
    dataCapacity = newCapacity;
  }

  void push(T val){
    if (dataSize == dataCapacity){
      extendCapacity();
    }
    data[dataSize] = val;
    dataSize++;
  }

  void pop(){
    if (dataSize == 0){
      throw "Stack is empty";
    }
    dataSize--;
  }

  T top(){
    if (dataSize == 0){
      throw "Stack is empty";
    }
    return data[dataSize - 1];
  }

  int size() const{
    return dataSize;
  }

  bool empty(){
    return dataSize == 0;
  }
};