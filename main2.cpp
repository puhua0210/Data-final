#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <cfloat> // for DBL_MAX
#include "MaxHeap.cpp"
using namespace std;

int main() {
    string line;
    int size = 0;

    cout << "Please enter your CSV data (end input with an empty line):" << endl;
    vector<string> lines;
    while (getline(cin, line) && !line.empty()) {
        lines.push_back(line);
        size++;
    }

    // Process header line (if present)
    if (!lines.empty()) {
        cout << "Header: " << lines[0] << endl;
        lines.erase(lines.begin());
        size--;
    }

    // Unique dates
    vector<string> unique_dates;
    int i = 0, day_counter = 0;
    for (const auto& line : lines) {
        string date = line.substr(0, line.find(","));
        bool is_unique = true;
        for (const auto& unique_date : unique_dates) {
            if (date == unique_date) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            if (day_counter % 5 == 0) { // 每五天选择第一天
                unique_dates.push_back(date);
                cout << "Selected date: " << date << endl;
                i++;
            }
            day_counter++;
        }
    }

    size = unique_dates.size(); // unique date count
    MaxHeap heap(size); // Create MaxHeap array
    double temp[7];
    i = 0;
    day_counter = 0;
    for (const auto& line : lines) {
        string date = line.substr(0, line.find(","));
        bool is_unique = true;
        for (const auto& unique_date : unique_dates) {
            if (date == unique_date) {
                is_unique = false;
                break;
            }
        }
        if (!is_unique) {
            continue;
        }
        if (day_counter % 5 == 0) { // 每五天选择第一天
            stringstream ss(line);
            string item;
            int col = 0;
            while (getline(ss, item, ',')) {
                temp[col] = stod(item);
                col++;
            }
            heap.insert(i, temp);
            i++;
        }
        day_counter++;
    }

    cout << "Task(B):" << endl;
    //(1) 确定数据集中有多少个唯一日期。
    cout << "(1) There are " << size << " unique dates in the sampled dataset." << endl;

    //(2) 找出10个最低的收盘价以及这些最低价格出现的日期。
    heap.heapSort(4); // sort by close price
    cout << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    //(3) 找出10个最高的收盘价以及这些最高价格出现的日期。
    cout << "(3) The 10 largest prices are:" << endl;
    for (int i = size - 1; i >= size - 10; i--) {
        cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << endl;
    }

    //(4) 找出中位数价格及其出现的日期。
    cout << "(4) The median price is " << heap.get(size / 2, 4) << " and its occurring date is " << int(heap.get(size / 2, 0)) << endl;

    //(5) 计算每日回报率，找出最大和最小的回报率以及它们出现的日期。
    heap.heapSort(0); // sort by date
    heap.daily_returns();
    double max_return = 0;
    double min_return = DBL_MAX;
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

    //(6) 计算每日的日内回报率，找出最大和最小的回报率以及它们出现的日期。
    heap.intraday_return();
    max_return = 0;
    min_return = DBL_MAX;
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

    //(10) 使用所有四列价格（Open_price, High_price, Low_price, Close_price）找出最大、最小和中位数价格及其出现的日期。
    cout << "(10)" << endl;
    string priceTypes[4] = { "Open_price", "High_price", "Low_price", "Close_price" };
    for (int i = 1; i <= 4; i++) {
        heap.heapSort(i);
        cout << priceTypes[i - 1] << ":" << endl;
        cout << "The maximum is " << heap.get(size - 1, i) << " and it occurs on date " << int(heap.get(size - 1, 0)) << endl;
        cout << "The minimum is " << heap.get(0, i) << " and it occurs on date " << int(heap.get(0, 0)) << endl;
        cout << "The median is " << heap.get(size / 2, i) << " and it occurs on date " << int(heap.get(size / 2, 0)) << endl;
    }

    auto start = chrono::high_resolution_clock::now(); // 定义开始时间
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "运行时间: " << duration.count() << " 秒" << endl;

    return 0;
}
