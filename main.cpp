#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include "MaxHeap.cpp"
using namespace std;

int main() {
    //讀取檔案
    string line;
    int size = 0;

    ifstream in("data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }
    while (getline(in, line)) {
        size++; //暫存資料筆數(包含重複日期)
    }
    in.close();
    in.open("data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }

    string unique_date[11881];
    int i = 0;
    while (getline(in, line)) {
        bool is_unique = true;
        for (int j = 0; j < i; j++) {
            if (line.substr(0, line.find(",")) == unique_date[j]) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            unique_date[i] = line.substr(0, line.find(","));
            i++;
        }
    }

    in.close();
    in.open("data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }
    auto start = chrono::high_resolution_clock::now();
    size = i;//unique date數量(沒有重複日期)
    MaxHeap heap(size);//建立MaxHeap array
    double temp[7];
    i = 0;
    int cut;
    while (getline(in, line)) {
        cut = line.find(",");
        bool is_unique = true;
        for (int j = 0; j < i; j++) {
            if (line.substr(0, cut) == unique_date[j]) {
                is_unique = false;
                break;
            }
        }
        if (!is_unique) {
            continue;
        }
        temp[0] = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp[1] = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp[2] = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp[3] = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        temp[4] = stod(line);

        heap.insert(i, temp);
        i++;
    }
    cout << "Task(A):" << endl;
    //(1) Determine how many unique dates are in the dataset.
    cout << "(1) There are " << size << " unique dates in the dataset." << endl;

    //(2) Find the 10 smallest prices and which dates contain these smallest prices.
    heap.heapSort(4); //sort by close price
    cout << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    //(3) Find the 10 largest prices and which dates contain these largest prices.
    cout << "(3) The 10 largest prices are:" << endl;
    for (int i = size - 1; i >= size - 10; i--) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    //(4) Find the median price and its occurring date
    cout << "(4) The median price is " << heap.get(size / 2, 4) << " and its occurring date is " << int(heap.get(size / 2, 0)) << endl;

    //(5) Compute the daily return for every day (except the first day). Then determine what the 
    // maximum and minimum returns (return could be a negative value) are and on which day(s) they occur.
    heap.heapSort(0); //sort by date
    heap.daily_returns();
    double max_return = 0;
    double min_return = INT_MAX;
    int max_index;
    int min_index;
    for (int i = 1; i < size; i++) {
        if (heap.get(i, 5) > max_return) {
            max_return = heap.get(i, 5);
            max_index = i;
        }
        if (heap.get(i, 5) < min_return) {
            min_return = heap.get(i, 5);
            min_index = i;
        }
    }
    cout << "(5) The maximum return is " << max_return * 100 << "%" << " and it occurs on " << int(heap.get(max_index, 0)) << endl;
    cout << "    The minimum return is " << min_return * 100 << "%" << " and it occurs on " << int(heap.get(min_index, 0)) << endl;

    //(6) Compute the intraday return for every day. Then determine what the maximum and
    // minimum returns (return could be a negative value) are and on which day(s) they occur.
    heap.intraday_return();
    max_return = 0;
    min_return = INT_MAX;
    for (int i = 0; i < size; i++) {
        if (heap.get(i, 6) > max_return) {
            max_return = heap.get(i, 6);
            max_index = i;
        }
        if (heap.get(i, 6) < min_return) {
            min_return = heap.get(i, 6);
            min_index = i;
        }
    }
    cout << "(6) The maximum return is " << max_return * 100 << "%" << " and it occurs on " << int(heap.get(max_index, 0)) << endl;
    cout << "    The minimum return is " << min_return * 100 << "%" << " and it occurs on " << int(heap.get(min_index, 0)) << endl;

    //(10) Find the maximum, minimum and median prices using all the 4 columns of prices 
    // (i.e., Open_price, High_price, Low_price and Close_price) and determine on which date they occur.
    cout << "(10)" << endl;
    string priceTypes[4] = { "Open_price", "High_price", "Low_price", "Close_price" };
    for (int i = 1; i <= 4; i++) {
        heap.heapSort(i);
        cout << priceTypes[i - 1] << ":" << endl;
        cout << "The maximum is " << heap.get(size - 1, i) << " and it occurs on date " << int(heap.get(size - 1, 0)) << endl;
        cout << "The minimum is " << heap.get(0, i) << " and it occurs on date " << int(heap.get(0, 0)) << endl;
        cout << "The median is " << heap.get(size / 2, i) << " and it occurs on date " << int(heap.get(size / 2, 0)) << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "運行時間: " << duration.count() << " 秒" << std::endl;
    in.close();
    return 0;
}

