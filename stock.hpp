#ifndef STOCK_HPP
#define STOCK_HPP
#include <iostream>
using namespace std;

class stock{
public:
    string date;
    double open;
    double high;
    double low;
    double close;

    stock(){
        date = "";
        open = 0;
        high = 0;
        low = 0;
        close = 0;
    }
};
#endif