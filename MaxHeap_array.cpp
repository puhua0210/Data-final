#include <iostream>
#include <string>
#include "stock.hpp"
#include "Vector.hpp"
using namespace std;

//col 0    1    2    3   4    
//    date open high low close 
class MaxHeap{
private:
    Vector<stock> arr;

public:
    MaxHeap(){}

    int size(){
        return arr.size();
    }

    void insert(stock s) {
        arr.push_back(s);
        int i = arr.size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && arr[parent].close < arr[i].close) {
            swap(arr[i], arr[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    stock get(int i){
        return arr[i];
    }

    void MAX_HEAPIFY(int n, int i){ //by close_price n是heap的大小 i是子樹的根
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        
        if (left < n && arr[left].close > arr[largest].close)
            largest = left;

        if (right < n && arr[right].close > arr[largest].close)
            largest = right;

        // Swap and continue heapifying if root is not largest
        if (largest != i) {
            swap(arr[i], arr[largest]);
            MAX_HEAPIFY(n, largest);
        }
    }

    void heapSort() { //col是哪列資料 
        // Heap sort
        for (int i = arr.size() - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            // Heapify root element to get highest element at root again
            MAX_HEAPIFY(i, 0);
        }
    }

    void show() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i].close;
            cout << endl;
        }
    }
};