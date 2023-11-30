#pragma once
#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while(!empty()) {
            dequeue();
        }
    }

    bool empty() const {
        return front == nullptr;
    }

    size_t getSize() const {
        return size;
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        size--;

        if (empty()) {
            rear = nullptr;  // reset rear when the last element is removed
        }
    }

    T& peek() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    const T& peek() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    T& at(int index){
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index is out of range");
        }
        Node* temp = front;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
};
