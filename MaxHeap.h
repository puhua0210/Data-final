#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include "Node.h"

class MaxHeap {
private:
    Node* head;
    int size;

public:
    MaxHeap() {
        head = nullptr;
        size = 0;
    }

    void insert(double* a_row) {
        Node* newNode = new Node(a_row);
        newNode->next = head;
        head = newNode;
        size++;
    }

    double get(int index, int col) {
        Node* temp = head;
        for (int i = 0; i < index && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            std::cerr << "Index out of bounds!" << std::endl;
            return -1;
        }
        return temp->data[col];
    }

    Node* getNode(int index) {
        Node* temp = head;
        for (int i = 0; i < index && temp != nullptr; i++) {
            temp = temp->next;
        }
        return temp;
    }

    void swap(Node* a, Node* b) {
        double temp[7];
        for (int i = 0; i < 7; i++) {
            temp[i] = a->data[i];
            a->data[i] = b->data[i];
            b->data[i] = temp[i];
        }
    }

    void MAX_HEAPIFY(int col, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        Node* largestNode = getNode(largest);
        Node* leftNode = getNode(left);
        Node* rightNode = getNode(right);

        if (left < n && leftNode->data[col] > largestNode->data[col]) {
            largest = left;
        }

        if (right < n && rightNode->data[col] > getNode(largest)->data[col]) {
            largest = right;
        }

        if (largest != i) {
            swap(getNode(i), getNode(largest));
            MAX_HEAPIFY(col, n, largest);
        }
    }

    void heapSort(int col) {
        for (int i = size / 2 - 1; i >= 0; i--) {
            MAX_HEAPIFY(col, size, i);
        }

        for (int i = size - 1; i >= 0; i--) {
            swap(getNode(0), getNode(i));
            MAX_HEAPIFY(col, i, 0);
        }
    }

    void daily_returns() {
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            curr->data[5] = (curr->data[4] - prev->data[4]) / prev->data[4];
            prev = curr;
            curr = curr->next;
        }
    }

    void intraday_return() {
        Node* curr = head;
        while (curr != nullptr) {
            curr->data[6] = (curr->data[4] - curr->data[1]) / curr->data[1];
            curr = curr->next;
        }
    }

    void show() {
        Node* temp = head;
        int count = 0;
        while (temp != nullptr && count < 10) {
            for (int j = 0; j < 5; j++) {
                if (j == 0) std::cout << int(temp->data[j]) << " ";
                else std::cout << temp->data[j] << " ";
            }
            std::cout << std::endl;
            temp = temp->next;
            count++;
        }
    }

    int getSize() {
        return size;
    }
};

#endif
