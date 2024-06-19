#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include "MaxHeap.cpp"
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return




int main(){
    //讀取檔案
    string line;
    int size = 0;
    
    ifstream in("C:/VScode C++ project/data structure/final_project/data1.csv");
    if (!in){
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    }   
    while (getline(in, line)){
        size++; //暫存資料筆數(包含重複日期)
    }
    in.close();
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    if (!in){
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    } 

    string unique_date[size];
    int i = 0;
    while (getline(in, line)){
        bool is_unique = true;
        for(int j=0;j<i;j++){
            if(line.substr(0, line.find(",")) == unique_date[j]){
                is_unique = false;
                break;
            }
        }
        if(is_unique){
            unique_date[i] = line.substr(0, line.find(","));
            i++;
        }
    }
    
    in.close();
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    if (!in){
        cout << "開啟檔案失敗！" << endl;
        exit(1);
    } 
    size = i;//unique date數量(沒有重複日期)
    MaxHeap heap(size);//建立MaxHeap array
    stock temp;
    i = 0;
    int cut;
    while (getline(in, line)){
        cut = line.find(",");
        bool is_unique = true;
        for(int j=0;j<i;j++){
            if(line.substr(0, cut) == unique_date[j]){
                is_unique = false;
                break;
            }
        }
        if(!is_unique){
            continue;
        }
        temp.date = line.substr(0, cut);
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
        
        heap.insert(i, temp);
        i++;
    }
    MaxHeap heapcopy = heap; //copy by date

    cout << "Task(A):" << endl;
    //(1) Determine how many unique dates are in the dataset.
    cout << "(1) There are "  << size << " unique dates in the dataset." << endl;

    //(2) Find the 10 smallest prices and which dates contain these smallest prices.
    heapcopy.heapSort(); //sort by close price
    cout << "(2) The 10 smallest prices are:" << endl;
    for(int i=0;i<10;i++){
        cout << heapcopy.get(i).close << " on date " << heapcopy.get(i).date << endl;
    }
    
    //(3) Find the 10 largest prices and which dates contain these largest prices.
    cout << "(3) The 10 largest prices are:" << endl;
    for(int i=size-10;i<size;i++){
        cout << heapcopy.get(i).close << " on date " << heapcopy.get(i).date << endl;
    }

    //(4) Find the median price and its occurring date
    cout << "(4) The first median price is " << heapcopy.get(size/2-1).close << " and its occurring date is " << heapcopy.get(size/2-1).date << endl;
    cout << "    The second median price is " << heapcopy.get(size/2).close << " and its occurring date is " << heapcopy.get(size/2).date << endl;

    //(5) Compute the daily return for every day (except the first day). Then determine what the 
    // maximum and minimum returns (return could be a negative value) are and on which day(s) they occur.
    
    double daily_returns[size];
    double max_return=0, min_return=INT_MAX;
    string max_date, min_date;
    for(int i=0;i<size-1;i++){
        daily_returns[i]=(heap.get(i+1).close-heap.get(i).close) / heap.get(i).close * 100;
        if(daily_returns[i] > max_return){
            max_return = daily_returns[i];
            max_date = heap.get(i+1).date;
        }
        if(daily_returns[i] < min_return){
            min_return = daily_returns[i];
            min_date = heap.get(i+1).date;
        }
    }
    cout << "(5) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;
    
    //(6) Compute the intraday return for every day. Then determine what the maximum and
    // minimum returns (return could be a negative value) are and on which day(s) they occur.
    double intraday_return[size];
    max_return=0, min_return=INT_MAX;
    for(int i=0;i<size;i++){
        daily_returns[i]=(heap.get(i).close-heap.get(i).open) / heap.get(i).open * 100;
        if(daily_returns[i] > max_return){
            max_return = daily_returns[i];
            max_date = heap.get(i).date;
        }
        if(daily_returns[i] < min_return){
            min_return = daily_returns[i];
            min_date = heap.get(i).date;
        }
    }
    cout << "(6) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    cout << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    //(10) Find the maximum, minimum and median prices using all the 4 columns of prices 
    // (i.e., Open_price, High_price, Low_price and Close_price) and determine on which date they occur.
    int n=size*4;
    MaxHeap all_price(n);
    stock price;
    for(int i=0;i<size;i++){ //第i天的四個價格
        price.date = heap.get(i).date;
        //四種價格都放入heap的close price
        price.close = heap.get(i).open;
        all_price.insert(i*4, price);
        price.close = heap.get(i).high;
        all_price.insert(i*4+1, price);
        price.close = heap.get(i).low;
        all_price.insert(i*4+2, price);
        price.close = heap.get(i).close;
        all_price.insert(i*4+3, price);
    }
    all_price.heapSort();
    cout << "(10) The maximum prices are: " << all_price.get(n-1).close << " on date " << all_price.get(n-1).date << endl;
    cout << "     The minimum prices are: " << all_price.get(0).close << " on date " << all_price.get(0).date << endl;
    cout << "     The first median prices are: " << all_price.get(n/2-1).close << " on date " << all_price.get(n/2-1).date << endl;
    cout << "     The second median prices are: " << all_price.get(n/2).close << " on date " << all_price.get(n/2).date << endl;
    in.close();
    return 0;
}

