// MaxHeap.cpp

#include "MaxHeap.h"
#include <algorithm>
#include <iostream>
#include <climits>

MaxHeap::MaxHeap(int n) {
    arr = new double* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new double[7]; // Assuming there are 7 columns in the data
    }
    size = n;
}

MaxHeap::~MaxHeap() {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void MaxHeap::insert(int i, double* a_row) {
    std::copy(a_row, a_row + 5, arr[i]); // Copy first 5 columns
}

double MaxHeap::get(int r, int c) {
    return arr[r][c];
}

void MaxHeap::MAX_HEAPIFY(int col, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left][col] > arr[largest][col])
        largest = left;

    if (right < n && arr[right][col] > arr[largest][col])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        MAX_HEAPIFY(col, n, largest);
    }
}

void MaxHeap::heapSort(int col) {
    for (int i = size / 2; i >= 0; i--) {
        MAX_HEAPIFY(col, size, i);
    }
    for (int i = size - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        MAX_HEAPIFY(col, i, 0);
    }
}

void MaxHeap::daily_returns() {
    for (int i = 1; i < size; i++) {
        arr[i][5] = (arr[i][4] - arr[i - 1][4]) / arr[i - 1][4] * 100.0;
    }
}

void MaxHeap::intraday_return() {
    for (int i = 0; i < size; i++) {
        arr[i][6] = (arr[i][4] - arr[i][1]) / arr[i][1] * 100.0;
    }
}

void MaxHeap::show() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == 0) std::cout << int(arr[i][j]) << " ";
            else std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
