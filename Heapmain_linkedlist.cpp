#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <time.h> 
#include "Vector.hpp"
#include "MaxHeap_linkedlist.cpp"
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return

int main() {
    string line;
    ifstream in;
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    ofstream out("C:/VScode C++ project/data structure/final_project/heap_linkedlist.txt");
    out<<"----------------------------------------Task(A)----------------------------------------------"<<endl;
    if (!in) {
        out << "開啟檔案失敗！" << endl;
        exit(1);
    }

    double START, END;
    START = clock();

    Vector<stock> bydate;
    MaxHeap heap;
    
    stock temp;
    int cut;
    while (getline(in, line)) {
        cut = line.find(",");
        temp.date = line.substr(0, cut);
        bool is_unique = true;
        for (int j = 0; j < heap.size(); j++) {
            if (heap.get(j).date == temp.date) {
                is_unique = false;
                break;
            }
        }
        if (!is_unique) continue;
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp.open = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp.high = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        cut = line.find(",");
        temp.low = stod(line.substr(0, cut));
        line = line.substr(cut + 1);

        temp.close = stod(line);

        bydate.push_back(temp);
        heap.insert(temp);
    }

    END = clock();
    out << "插入資料，建樹時間: " << (END - START) / CLOCKS_PER_SEC << endl;

    out << "(1) There are " << heap.size() << " unique dates in the dataset." << endl;

    heap.heapSort();
    out << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        out << heap.get(i).close << " on date " << heap.get(i).date << endl;
    }

    out << "(3) The 10 largest prices are:" << endl;
    for (int i = heap.size() - 10; i < heap.size(); i++) {
        out << heap.get(i).close << " on date " << heap.get(i).date << endl;
    }

    out << "(4) The first median price is " << heap.get(heap.size() / 2).close << " and its occurring date is " << heap.get(heap.size() / 2).date << endl;
    
    double daily_returns[bydate.size()];
    double max_return = 0, min_return = INT_MAX;
    string max_date, min_date;
    for (int i = 0; i < bydate.size() - 1; i++) {
        daily_returns[i] = (bydate[i + 1].close - bydate[i].close) / bydate[i].close * 100;
        
        if (daily_returns[i] > max_return) {
            max_return = daily_returns[i];
            max_date = bydate[i + 1].date;
        }
        if (daily_returns[i] < min_return) {
            min_return = daily_returns[i];
            min_date = bydate[i + 1].date;
        }
    }

    out << "(5) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    out << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    double intraday_return[bydate.size()];
    max_return = 0, min_return = INT_MAX;
    for (int i = 0; i < bydate.size(); i++) {
        intraday_return[i] = (bydate[i].close - bydate[i].open) / bydate[i].open * 100;
        if (intraday_return[i] > max_return) {
            max_return = intraday_return[i];
            max_date = bydate[i].date;
        }
        if (intraday_return[i] < min_return) {
            min_return = intraday_return[i];
            min_date = bydate[i].date;
        }
    }
    out << "(6) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    out << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    int n = heap.size() * 4;
    MaxHeap all_price;
    stock price;
    for (int i = 0; i < heap.size(); i++) {
        price.date = heap.get(i).date;
        price.close = heap.get(i).open;
        all_price.insert(price);
        price.close = heap.get(i).high;
        all_price.insert(price);
        price.close = heap.get(i).low;
        all_price.insert(price);
        price.close = heap.get(i).close;
        all_price.insert(price);
    }
    all_price.heapSort();
    out << "(10) The maximum prices are: " << all_price.get(n - 1).close << " on date " << all_price.get(n - 1).date << endl;
    out << "     The minimum prices are: " << all_price.get(0).close << " on date " << all_price.get(0).date << endl;
    out << "     The first median prices are: " << all_price.get(n / 2 - 1).close << " on date " << all_price.get(n / 2 - 1).date << endl;
    out << "     The second median prices are: " << all_price.get(n / 2).close << " on date " << all_price.get(n / 2).date << endl;

    END = clock();
    out << "建樹、排序與搜尋整體時間: " << (END - START) / CLOCKS_PER_SEC << endl;
    in.close();
    return 0;
}