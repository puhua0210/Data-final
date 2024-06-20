#include <iostream>
#include <string>
#include "stock.h"
#include "linkedlist.h"
using namespace std;

class MaxHeap {
private:
    LinkedList<stock> arr;

public:
    MaxHeap() {}

    int size() {
        return arr.size();
    }

    void insert(stock s) {
        arr.push_back(s);
        int i = arr.size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && arr.get(parent).close < arr.get(i).close) {
            swap(arr.get(i), arr.get(parent));
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    stock get(int i) {
        return arr.get(i);
    }

    void MAX_HEAPIFY(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr.get(left).close > arr.get(largest).close)
            largest = left;

        if (right < n && arr.get(right).close > arr.get(largest).close)
            largest = right;

        if (largest != i) {
            swap(arr.get(i), arr.get(largest));
            MAX_HEAPIFY(n, largest);
        }
    }

    void heapSort() {
        for (int i = arr.size() - 1; i >= 0; i--) {
            swap(arr.get(0), arr.get(i));
            MAX_HEAPIFY(i, 0);
        }
    }

    void show() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                if (j == 0) cout << int(arr.get(i).close) << " ";
                else cout << arr.get(i).close << " ";
            }
            cout << endl;
        }
    }
};
