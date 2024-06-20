// MaxHeap.h

#ifndef MAXHEAP_H
#define MAXHEAP_H

class MaxHeap {
private:
    double** arr;
    int size;

public:
    MaxHeap(int n); // Constructor
    ~MaxHeap(); // Destructor
    void insert(int i, double* a_row);
    double get(int r, int c);
    void MAX_HEAPIFY(int col, int n, int i);
    void heapSort(int col);
    void daily_returns();
    void intraday_return();
    void show();
};

#endif // MAXHEAP_H
