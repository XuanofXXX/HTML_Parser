#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename Elemtype> struct Node {
  Elemtype data;
  Node *next;

  Node() : data(), next(nullptr) {}
  Node(Elemtype value) : data(value), next(nullptr) {}
};

// 定义链表类
template <typename Elemtype> class LinkList {

private:
public:
  Node<Elemtype> *head;
  int dataSize;
  LinkList() : head(new Node<Elemtype>()), dataSize(0) {}

  int size() { return dataSize; }

  bool empty() { return dataSize == 0; }

  void prepend(Elemtype val) {
    Node<Elemtype> *newNode = new Node<Elemtype>(val);
    if (newNode == nullptr) {
      throw "Failed to allocate memory";
    }
    newNode->next = head->next;
    head->next = newNode;
    dataSize++;
  }

  void pop(int index = -1) { remove(index); }

  void append(Elemtype val) {
    Node<Elemtype> *cur = head;
    while (cur->next) {
      cur = cur->next;
    }
    Node<Elemtype> *newNode = new Node<Elemtype>(val);
    if (newNode == nullptr) {
      throw "Failed to allocate memory";
    }
    cur->next = newNode;
    dataSize++;
  }

  void display() {
    if (!head->next) {
      std::cout << "None" << std::endl;
      return;
    }

    int maxtimes = 10;
    Node<Elemtype> *cur = head;
    cur = cur->next;
    int time = 1;

    while (cur && time <= maxtimes) {
      time++;
      std::cout << cur->data << " -> ";
      cur = cur->next;
    }
    if (dataSize > maxtimes)
      std::cout << "... -> None" << std::endl;
    else
      std::cout << "None" << std::endl;
  }

  void insert(int pos, Elemtype val) {
    Node<Elemtype> *cur = head;
    Node<Elemtype> *newNode = new Node<Elemtype>(val);
    if (newNode == nullptr) {
      throw "Failed to allocate memory";
    }
    while (pos--) {
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    dataSize++;
  }

  Elemtype remove(int pos) {
    Node<Elemtype> *cur = head;
    while (pos--) {
      cur = cur->next;
    }
    Node<Elemtype> *tar = cur->next;
    cur->next = cur->next->next;
    dataSize--;
    return tar->data;
  }

  bool find(Elemtype val) {
    Node<Elemtype> *cur = head;
    if (dataSize < 1)
      return false;
    cur = cur->next;
    while (cur) {
      if (cur->data == val) {
        return true;
      }
      cur = cur->next;
    }
    return false;
  }

  void reverse() {
    if (dataSize <= 1)
      return;

    Node<Elemtype> *cur = head->next;
    Node<Elemtype> *prev = nullptr;
    Node<Elemtype> *next = nullptr;

    while (cur) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
    head->next = prev;
  }

  int count(Elemtype val) {
    int res = 0;
    if (!head->next)
      return 0;
    Node<Elemtype> *cur = head;
    cur = cur->next;
    while (cur) {
      if (cur->data == val)
        res++;
      cur = cur->next;
    }
    return res;
  }

  bool judgeHuiwen() {
    if (dataSize <= 1)
      return true;
    Node<Elemtype> *newHead = new Node<Elemtype>();
    if (newHead == nullptr) {
      throw "Failed to allocate memory";
    }
    Node<Elemtype> *cur = head->next;
    while (cur) {
      Node<Elemtype> *newNode = new Node<Elemtype>(cur->data);
      if (newNode == nullptr) {
        throw "Failed to allocate memory";
      }
      newNode->next = newHead;
      newHead = newNode;
      cur = cur->next;
    }
    Node<Elemtype> *cur1 = head->next;
    Node<Elemtype> *cur2 = newHead;
    while (cur1) {
      if (cur1->data != cur2->data)
        return false;
      cur1 = cur1->next;
      cur2 = cur2->next;
    }
    return true;
  }

  void extend(LinkList<Elemtype> *other) {
    Node<Elemtype> *cur = head;
    while (cur->next) {
      cur = cur->next;
    }
    Node<Elemtype> *cur_other = other->head->next;
    while (cur_other) {

      Node<Elemtype> *newNode = new Node<Elemtype>(cur_other->data);
      if (newNode == nullptr) {
        throw "Failed to allocate memory";
      }
      cur->next = newNode;

      cur = cur->next;
      cur_other = cur_other->next;
    }
    this->dataSize += other->dataSize;
  }

  void clear() {
    Node<Elemtype> *cur = head;
    while (cur->next) {
      Node<Elemtype> *next = cur->next;
      delete cur;
      cur = next;
    }
    delete head;
    head = new Node<Elemtype>();
    if (head == nullptr) {
      throw "Failed to allocate memory";
    }
    dataSize = 0;
  }

  Elemtype at(int index) {
    if (index >= size() || index < -size())
      throw "index out of range";
    if (index < 0)
      index += size();
    Node<Elemtype> *cur = head;
    cur = cur->next;
    while (index--) {
      cur = cur->next;
    }
    return cur->data;
  }

  Elemtype operator[](int index) {
    if (index >= size() || index < -size())
      throw "index out of range";
    if (index < 0)
      index += size();
    Node<Elemtype> *cur = head;
    cur = cur->next;
    while (index--) {
      cur = cur->next;
    }
    return cur->data;
  }

  LinkList<Elemtype> &operator+=(LinkList<Elemtype> &other) {
    extend(other);
    return *this;
  }

  ~LinkList() {
    Node<Elemtype> *cur = head;
    while (cur) {
      Node<Elemtype> *next = cur->next;
      delete cur;
      cur = next;
    }
  }
};