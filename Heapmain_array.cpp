#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <time.h> 
#include "MaxHeap_array.cpp"
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return

int main() {
    cout<<"----------------------------------------Task(A)----------------------------------------------"<<endl;
    string line;
    ifstream in;
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }

    double START, END;
    START = clock();

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

        heap.insert(temp);
    }
    END = clock();
    cout << "插入資料，建樹時間: " << (END - START) / CLOCKS_PER_SEC << endl;

    MaxHeap heapcopy = heap;
    cout << "(1) There are " << heapcopy.size() << " unique dates in the dataset." << endl;

    heapcopy.heapSort();
    cout << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << heapcopy.get(i).close << " on date " << heapcopy.get(i).date << endl;
    }

    cout << "(3) The 10 largest prices are:" << endl;
    for (int i = heapcopy.size() - 10; i < heapcopy.size(); i++) {
        cout << heapcopy.get(i).close << " on date " << heapcopy.get(i).date << endl;
    }

    cout << "(4) The first median price is " << heapcopy.get(heap.size() / 2 - 1).close << " and its occurring date is " << heapcopy.get(heap.size() / 2 - 1).date << endl;
    cout << "    The second median price is " << heapcopy.get(heap.size() / 2).close << " and its occurring date is " << heapcopy.get(heap.size() / 2).date << endl;
    
    double daily_returns[heap.size()];
    double max_return = 0, min_return = INT_MAX;
    string max_date, min_date;
    for (int i = 0; i < heap.size() - 1; i++) {
        daily_returns[i] = (heap.get(i + 1).close - heap.get(i).close) / heap.get(i).close * 100;
        if (daily_returns[i] > max_return) {
            max_return = daily_returns[i];
            max_date = heap.get(i + 1).date;
        }
        if (daily_returns[i] < min_return) {
            min_return = daily_returns[i];
            min_date = heap.get(i + 1).date;
        }
    }
    cout << "(5) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    double intraday_return[heap.size()];
    max_return = 0, min_return = INT_MAX;
    for (int i = 0; i < heap.size(); i++) {
        intraday_return[i] = (heap.get(i).close - heap.get(i).open) / heap.get(i).open * 100;
        if (intraday_return[i] > max_return) {
            max_return = intraday_return[i];
            max_date = heap.get(i).date;
        }
        if (intraday_return[i] < min_return) {
            min_return = intraday_return[i];
            min_date = heap.get(i).date;
        }
    }
    cout << "(6) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

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
    cout << "(10) The maximum prices are: " << all_price.get(n - 1).close << " on date " << all_price.get(n - 1).date << endl;
    cout << "     The minimum prices are: " << all_price.get(0).close << " on date " << all_price.get(0).date << endl;
    cout << "     The first median prices are: " << all_price.get(n / 2 - 1).close << " on date " << all_price.get(n / 2 - 1).date << endl;
    cout << "     The second median prices are: " << all_price.get(n / 2).close << " on date " << all_price.get(n / 2).date << endl;

    END = clock();
    cout << "建樹、排序與搜尋整體時間: " << (END - START) / CLOCKS_PER_SEC << endl;
    in.close();
    cout<<"----------------------------------------Task(B)----------------------------------------------"<<endl;

    in.open("C:/VScode C++ project/data structure/final_project/data2.csv");//每5天取樣一次
    if (!in) {
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }

    START = clock();

    MaxHeap heap2;
    while (getline(in, line)) {
        cut = line.find(",");
        temp.date = line.substr(0, cut);
        bool is_unique = true;
        for (int j = 0; j < heap2.size(); j++) {
            if (heap2.get(j).date == temp.date) {
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

        heap2.insert(temp);
    }
    END = clock();
    cout << "插入資料，建樹時間: " << (END - START) / CLOCKS_PER_SEC << endl;

    MaxHeap heapcopy2 = heap2;
    cout << "Task(B):" << endl;
    cout << "(1) There are " << heapcopy2.size() << " unique dates in the dataset." << endl;

    heapcopy2.heapSort();
    cout << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << heapcopy2.get(i).close << " on date " << heapcopy2.get(i).date << endl;
    }

    cout << "(3) The 10 largest prices are:" << endl;
    for (int i = heapcopy2.size() - 10; i < heapcopy2.size(); i++) {
        cout << heapcopy2.get(i).close << " on date " << heapcopy2.get(i).date << endl;
    }

    cout << "(4) The first median price is " << heapcopy2.get(heap2.size() / 2 - 1).close << " and its occurring date is " << heapcopy2.get(heap2.size() / 2 - 1).date << endl;
    cout << "    The second median price is " << heapcopy2.get(heap2.size() / 2).close << " and its occurring date is " << heapcopy2.get(heap2.size() / 2).date << endl;
    
    double daily_returns2[heap2.size()];
    max_return = 0, min_return = INT_MAX;
    max_date="", min_date="";
    for (int i = 0; i < heap2.size() - 1; i++) {
        daily_returns2[i] = (heap2.get(i + 1).close - heap2.get(i).close) / heap2.get(i).close * 100;
        if (daily_returns2[i] > max_return) {
            max_return = daily_returns2[i];
            max_date = heap2.get(i + 1).date;
        }
        if (daily_returns2[i] < min_return) {
            min_return = daily_returns2[i];
            min_date = heap2.get(i + 1).date;
        }
    }
    cout << "(5) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    double intraday_return2[heap2.size()];
    max_return = 0, min_return = INT_MAX;
    for (int i = 0; i < heap2.size(); i++) {
        intraday_return2[i] = (heap2.get(i).close - heap2.get(i).open) / heap2.get(i).open * 100;
        if (intraday_return2[i] > max_return) {
            max_return = intraday_return2[i];
            max_date = heap2.get(i).date;
        }
        if (intraday_return2[i] < min_return) {
            min_return = intraday_return2[i];
            min_date = heap2.get(i).date;
        }
    }
    cout << "(6) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    n = heap2.size() * 4;
    MaxHeap all_price2;
    stock price2;
    for (int i = 0; i < heap2.size(); i++) {
        price2.date = heap2.get(i).date;
        price2.close = heap2.get(i).open;
        all_price2.insert(price2);
        price2.close = heap2.get(i).high;
        all_price2.insert(price2);
        price2.close = heap2.get(i).low;
        all_price2.insert(price2);
        price2.close = heap2.get(i).close;
        all_price2.insert(price2);
    }
    all_price2.heapSort();
    cout << "(10) The maximum prices are: " << all_price2.get(n - 1).close << " on date " << all_price2.get(n - 1).date << endl;
    cout << "     The minimum prices are: " << all_price2.get(0).close << " on date " << all_price2.get(0).date << endl;
    cout << "     The first median prices are: " << all_price2.get(n / 2 - 1).close << " on date " << all_price2.get(n / 2 - 1).date << endl;
    cout << "     The second median prices are: " << all_price2.get(n / 2).close << " on date " << all_price2.get(n / 2).date << endl;

    END = clock();
    cout << "建樹、排序與搜尋整體時間: " << (END - START) / CLOCKS_PER_SEC << endl;

    in.close();
    return 0;
}