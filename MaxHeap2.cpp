#include <iostream>
#include <string>
using namespace std;

// col 0    1    2    3   4     5            6
//     date open high low close daily_return intraday_return
class MaxHeap {
private:
    double** arr;
    int size;
public:
    MaxHeap(int n) {
        arr = new double* [n];
        for (int i = 0; i < n; i++) {
            arr[i] = new double[7];
        }
    }
    
    void insert(int index, double temp[]) {
        for (int j = 0; j < 5; j++) {
            arr[index][j] = temp[j];
        }
        arr[index][5] = 0; // daily_return
        arr[index][6] = 0; // intraday_return
    }
    
    double get(int index, int col) {
        return arr[index][col];
    }

    void heapify(int n, int i, int col) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left][col] > arr[largest][col])
            largest = left;

        if (right < n && arr[right][col] > arr[largest][col])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(n, largest, col);
        }
    }

    void heapSort(int col) {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i, col);

        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(i, 0, col);
        }
    }

    void daily_returns() {
        for (int i = 1; i < size; i++) {
            arr[i][5] = (arr[i][4] - arr[i - 1][4]) / arr[i - 1][4];
        }
    }

    void intraday_return() {
        for (int i = 0; i < size; i++) {
            arr[i][6] = (arr[i][3] - arr[i][1]) / arr[i][1];
        }
    }
};
