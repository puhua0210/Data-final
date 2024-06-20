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
    string line;
    ifstream in;
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    ofstream out("C:/VScode C++ project/data structure/final_project/heap_array.txt");
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
    out<<"----------------------------------------Task(B)----------------------------------------------"<<endl;

    in.open("C:/VScode C++ project/data structure/final_project/data2.csv");//每5天取樣一次
    if (!in) {
        out << "開啟檔案失敗！" << endl;
        exit(1);
    }

    double START2, END2;
    START2 = clock();

    Vector<stock> bydate2;
    MaxHeap heap2;
    
    stock temp2;
    int cut2;
    while (getline(in, line)) {
        cut2 = line.find(",");
        temp2.date = line.substr(0, cut2);
        bool is_unique2 = true;
        for (int j = 0; j < heap2.size(); j++) {
            if (heap2.get(j).date == temp2.date) {
                is_unique2 = false;
                break;
            }
        }
        if (!is_unique2) continue;
        line = line.substr(cut2 + 1);

        cut2 = line.find(",");
        temp2.open = stod(line.substr(0, cut2));
        line = line.substr(cut2 + 1);

        cut2 = line.find(",");
        temp2.high = stod(line.substr(0, cut2));
        line = line.substr(cut2 + 1);

        cut2 = line.find(",");
        temp2.low = stod(line.substr(0, cut2));
        line = line.substr(cut2 + 1);

        temp2.close = stod(line);

        bydate2.push_back(temp2);
        heap2.insert(temp2);
    }

    END2 = clock();
    out << "插入資料，建樹時間: " << (END2 - START2) / CLOCKS_PER_SEC << "秒" << endl;

    out << "(1) There are " << heap2.size() << " unique dates in the dataset." << endl;

    heap2.heapSort();
    out << "(2) The 10 smallest prices are:" << endl;
    for (int i = 0; i < 10; i++) {
        out << heap2.get(i).close << " on date " << heap2.get(i).date << endl;
    }

    out << "(3) The 10 largest prices are:" << endl;
    for (int i = heap2.size() - 10; i < heap2.size(); i++) {
        out << heap2.get(i).close << " on date " << heap2.get(i).date << endl;
    }

    out << "(4) The first median price is " << heap2.get(heap2.size() / 2 - 1).close << " and its occurring date is " << heap2.get(heap2.size() / 2 - 1).date << endl;
    out << "    The second median price is " << heap2.get(heap2.size() / 2).close << " and its occurring date is " << heap2.get(heap2.size() / 2).date << endl;
    
    double daily_returns2[bydate2.size()];
    double max_return2 = 0, min_return2 = INT_MAX;
    string max_date2, min_date2;
    for (int i = 0; i < bydate2.size() - 1; i++) {
        daily_returns2[i] = (bydate2[i + 1].close - bydate2[i].close) / bydate2[i].close * 100;
        
        if (daily_returns2[i] > max_return2) {
            max_return2 = daily_returns2[i];
            max_date2 = bydate2[i + 1].date;
        }
        if (daily_returns2[i] < min_return2) {
            min_return2 = daily_returns2[i];
            min_date2 = bydate2[i + 1].date;
        }
    }

    out << "(5) The maximum daily return is " << max_return2 << "%" << " and it occurs on " << max_date2 << endl;
    out << "    The minimum daily return is " << min_return2 << "%" << " and it occurs on " << min_date2 << endl;

    double intraday_return2[bydate2.size()];
    max_return2 = 0, min_return2 = INT_MAX;
    for (int i = 0; i < bydate2.size(); i++) {
        intraday_return2[i] = (bydate2[i].close - bydate2[i].open) / bydate2[i].open * 100;
        if (intraday_return2[i] > max_return2) {
            max_return2 = intraday_return2[i];
            max_date2 = bydate2[i].date;
        }
        if (intraday_return2[i] < min_return2) {
            min_return2 = intraday_return2[i];
            min_date2 = bydate2[i].date;
        }
    }
    out << "(6) The maximum intraday return is " << max_return2 << "%" << " and it occurs on " << max_date2 << endl;
    out << "    The minimum intraday return is " << min_return2 << "%" << " and it occurs on " << min_date2 << endl;

    int n2 = heap2.size() * 4;
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
    out << "(10) The maximum prices are: " << all_price2.get(n2 - 1).close << " on date " << all_price2.get(n2 - 1).date << endl;
    out << "     The minimum prices are: " << all_price2.get(0).close << " on date " << all_price2.get(0).date << endl;
    out << "     The first median prices are: " << all_price2.get(n2 / 2 - 1).close << " on date " << all_price2.get(n2 / 2 - 1).date << endl;
    out << "     The second median prices are: " << all_price2.get(n2 / 2).close << " on date " << all_price2.get(n2 / 2).date << endl;

    END2 = clock();
    out << "建樹、排序與搜尋整體時間: " << (END2 - START2) / CLOCKS_PER_SEC << "秒" << endl;
    in.close();
    return 0;
}