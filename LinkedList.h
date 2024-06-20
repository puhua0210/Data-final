#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
using namespace std;

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int current_size;

public:
    LinkedList() : head(nullptr), tail(nullptr), current_size(0) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        current_size++;
    }

    void pop_back() {
        if (current_size == 0) return;

        if (current_size == 1) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        current_size--;
    }

    int size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

    T front() const {
        if (head) return head->data;
        return T();
    }

    T back() const {
        if (tail) return tail->data;
        return T();
    }

    T& get(int index) {
        if (index < 0 || index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
};
#endif
