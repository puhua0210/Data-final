#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <time.h> 
#include "RBtree.cpp"
using namespace std;

//col 0    1    2    3   4     5            6
//    date open high low close daily_return intraday_return

int main(){  
    //讀取檔案
    string line;
    ifstream in;
    in.close();
    in.open("C:/VScode C++ project/data structure/final_project/data1.csv");
    ofstream out("C:/VScode C++ project/data structure/final_project/RBtree.txt");
    if (!in){
        out << "開啟檔案失敗！" << endl;
        exit(1);
    } 
    out<<"----------------------------------------Task(A)----------------------------------------------"<<endl;

    double START, END; 
    START = clock();

    RBtree rbtree;//建立rbtree
    Vector<stock> vec;//存放不重複的rbtree的資料(日期排序)
    stock temp;
    int cut;
    while (getline(in, line)){
        cut = line.find(",");
        temp.date = line.substr(0, cut);
        bool is_unique = true;
        for(int j=0;j<vec.size();j++){
            if(vec[j].date == temp.date){
                is_unique = false;
                break;
            }
        }
        if(!is_unique) continue; //如果日期重複就不加入
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
        
        rbtree.insertElement(temp);
        vec.push_back(temp);
    }
    END = clock();
    out << "插入資料，建樹時間: " << (END - START) / CLOCKS_PER_SEC << endl;
    
    Vector<stock> veccopy; //原本的vec是照日期排序的 不要動到 
    //2~4題使用heapcopy
    //(1) Determine how many unique dates are in the dataset.
    out << "(1) There are "  << vec.size() << " unique dates in the dataset." << endl;

    //(2) Find the 10 smallest prices and which dates contain these smallest prices.
    rbtree.inOrder(rbtree.getroot(), veccopy);//排序rbtree close price放到veccopy
    out << "(2) The 10 smallest prices are:" << endl;
    for(int i=0;i<10;i++){
        out << veccopy[i].close << " on date " << veccopy[i].date << endl;
    }
    
    //(3) Find the 10 largest prices and which dates contain these largest prices.
    out << "(3) The 10 largest prices are:" << endl;
    for(int i=veccopy.size()-10;i<veccopy.size();i++){
        out << veccopy[i].close << " on date " << veccopy[i].close << endl;
    }

    //(4) Find the median price and its occurring date
    out << "(4) The first median price is " << veccopy[veccopy.size()/2-1].close << " and its occurring date is " << veccopy[veccopy.size()/2-1].date << endl;
    out << "    The second median price is " << veccopy[veccopy.size()/2].close << " and its occurring date is " << veccopy[veccopy.size()/2].date << endl;

    //(5) Compute the daily return for every day (except the first day). Then determine what the 
    // maximum and minimum returns (return could be a negative value) are and on which day(s) they occur.
    
    double daily_returns[vec.size()];
    double max_return=0, min_return=INT_MAX;
    string max_date, min_date;
    for(int i=0;i<vec.size()-1;i++){
        daily_returns[i]=(vec[i+1].close-vec[i].close) / vec[i].close * 100;
        if(daily_returns[i] > max_return){
            max_return = daily_returns[i];
            max_date = vec[i+1].date;
        }
        if(daily_returns[i] < min_return){
            min_return = daily_returns[i];
            min_date = vec[i+1].date;
        }
    }
    out << "(5) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    out << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;
    
    //(6) Compute the intraday return for every day. Then determine what the maximum and
    // minimum returns (return could be a negative value) are and on which day(s) they occur.
    double intraday_return[vec.size()];
    max_return=0, min_return=INT_MAX;
    for(int i=0;i<vec.size();i++){
        daily_returns[i]=(vec[i].close-vec[i].open) / vec[i].open * 100;
        if(daily_returns[i] > max_return){
            max_return = daily_returns[i];
            max_date = vec[i].date;
        }
        if(daily_returns[i] < min_return){
            min_return = daily_returns[i];
            min_date = vec[i].date;
        }
    }
    out << "(6) The maximum return is " << max_return << "%" << " and it occurs on " << max_date << endl;
    out << "    The minimum return is " << min_return << "%" << " and it occurs on " << min_date << endl;

    //(10) Find the maximum, minimum and median prices using all the 4 columns of prices 
    // (i.e., Open_price, High_price, Low_price and Close_price) and determine on which date they occur.
    int n=vec.size()*4;
    RBtree all_price;
    stock price;
    for(int i=0;i<vec.size();i++){ //第i天的四個價格
        price.date = vec[i].date;
        //四種價格都放入heap的close price
        price.close = vec[i].open;
        all_price.insertElement(price);
        price.close = vec[i].high;
        all_price.insertElement(price);
        price.close = vec[i].low;
        all_price.insertElement(price);
        price.close = vec[i].close;
        all_price.insertElement(price);
    }
    Vector<stock> vec2;//存放all_price的資料
    all_price.inOrder(all_price.getroot(), vec2);//排序all_price rbtree放到vec2

    out << "(10) The maximum prices are: " << vec2[n-1].close << " on date " << vec2[n-1].date << endl;
    out << "     The minimum prices are: " << vec2[0].close << " on date " << vec2[0].date << endl;
    out << "     The first median prices are: " << vec2[n/2-1].close << " on date " << vec2[n/2-1].date << endl;
    out << "     The second median prices are: " << vec2[n/2].close << " on date " << vec2[n/2].date << endl;
    
    END = clock();
    out << "建樹、排序與搜尋整體時間: " << (END - START) / CLOCKS_PER_SEC << endl;

    in.close();
    return 0;
}

