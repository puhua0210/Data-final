#include <iostream>
#include <string>
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return
class MaxHeap{
private:
    double** arr;
    int size;
public:
    MaxHeap(int n){
        arr = new double* [n];
        for(int i=0;i<n;i++){
            arr[i]=new double[7];
        }
        size = n;
    }

    void insert(int i, double* a_row){
        copy(a_row, a_row + 5, arr[i]); //把a_row的前五列資料複製到arr[i]裡面
    }

    double get(int r,int c){
        return arr[r][c];
    }

    void MAX_HEAPIFY(int col, int n,int i){ //col是哪列資料 n是heap的大小 i是子樹的根
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if (left < n && arr[left][col] > arr[largest][col])
            largest = left;

        if (right < n && arr[right][col] > arr[largest][col])
            largest = right;

        // Swap and continue heapifying if root is not largest
        if (largest != i) {
            swap(arr[i], arr[largest]);
            MAX_HEAPIFY(col, n, largest);
        }
    }

    void heapSort(int col) { //col是哪列資料 
        // Build max heap
        for (int i = size/2; i >= 0; i--){
            MAX_HEAPIFY(col, size, i);
        }
        // Heap sort
        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            // Heapify root element to get highest element at root again
            MAX_HEAPIFY(col, i, 0);
        }
    }

    void daily_returns(){ // 要先sort by date才可以用，計算daily return並放在column 5
        for(int i=1;i<size;i++){
            arr[i][5] = (arr[i][4] - arr[i-1][4]) / arr[i-1][4]; //小數點 還不是百分比
        }
    }

    void intraday_return(){ // 要先sort by date才可以用，計算intraday return並放在column 6
        for(int i=0;i<size;i++){
            arr[i][6] = (arr[i][4] - arr[i][1]) / arr[i][1]; //小數點 還不是百分比
        }
    } 

    void show(){ //測試用
        for(int i=0;i<10;i++){
            for(int j=0;j<5;j++){
                if(j==0) cout << int(arr[i][j]) << " ";
                else cout << arr[i][j] << " ";
                
            }
            cout << endl;
        }
    }
};