#ifndef NODE_H
#define NODE_H

struct Node {
    double data[7];
    Node* next;

    Node(double* arr) {
        for (int i = 0; i < 7; i++) {
            data[i] = arr[i];
        }
        next = nullptr;
    }
};

#endif
