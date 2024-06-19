#include <iostream>
#include <string>
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return

struct stock
{
    string date;
    double open=0;
    double high=0;
    double low=0;
    double close=0;
};

class MaxHeap{
private:
    stock* arr;
    int size;
public:
    MaxHeap(int n){
        arr = new stock[n];
        size = n;
    }

    void insert(int i, stock s){
        arr[i] = s;
    }

    stock get(int i){
        return arr[i];
    }

    void MAX_HEAPIFY(int n,int i){ //by close_price n是heap的大小 i是子樹的根
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
        // Build max heap
        for (int i = size/2; i >= 0; i--){
            MAX_HEAPIFY(size, i);
        }
        // Heap sort
        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            // Heapify root element to get highest element at root again
            MAX_HEAPIFY(i, 0);
        }
    }

    void show(){ //測試用
        for(int i=0;i<10;i++){
            for(int j=0;j<5;j++){
                if(j==0) cout << int(arr[i].close) << " ";
                else cout << arr[i].close << " ";
            }
            cout << endl;
        }
    }
};