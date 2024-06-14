#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include "MaxHeap.h"
using namespace std;

int main() {
    string line;
    int size = 0;

    ifstream in("C:\\Users\\72161\\source\\repos\\DataStruct\\x64\\Debug\\data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }
    while (getline(in, line)) {
        size++;
    }
    in.close();

    in.open("C:\\Users\\72161\\source\\repos\\DataStruct\\x64\\Debug\\data1.csv");
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
    in.open("C:\\Users\\72161\\source\\repos\\DataStruct\\x64\\Debug\\data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }
    size = i;
    MaxHeap heap;
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

        heap.insert(temp);
        i++;
    }

    cout << "Task(A):" << endl;
    cout << "(1) There are " << size << " unique dates in the dataset." << endl;

    heap.heapSort(4);
    cout << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    cout << "(3) The 10 largest prices are:" << endl;
    for (int i = size - 1; i >= size - 10; i--) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    cout << "(4) The median price is " << heap.get(size / 2, 4) << " and its occurring date is " << int(heap.get(size / 2, 0)) << endl;

    heap.heapSort(0);
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

    cout << "(10)" << endl;
    string priceTypes[4] = { "Open_price", "High_price", "Low_price", "Close_price" };
    for (int i = 1; i <= 4; i++) {
        heap.heapSort(i);
        cout << priceTypes[i - 1] << ":" << endl;
        cout << "The maximum is " << heap.get(size - 1, i) << " and it occurs on date " << int(heap.get(size - 1, 0)) << endl;
        cout << "The minimum is " << heap.get(0, i) << " and it occurs on date " << int(heap.get(0, 0)) << endl;
        cout << "The median is " << heap.get(size / 2, i) << " and it occurs on date " << int(heap.get(size / 2, 0)) << endl;
    }
    in.close();
    return 0;
}
