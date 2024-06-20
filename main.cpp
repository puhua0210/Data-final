#include <iostream>
#include "DataStorage.h"
#include <climits>
#include "MaxHeap.h"

int main() {
    DataStorage ds;
    if (!ds.loadData("data.csv")) {
        std::cerr << "Failed to load data." << std::endl;
        return 1;
    }

    std::vector<std::vector<double>>& data = ds.getData();
    int size = data.size();

    MaxHeap heap(size);
    for (int i = 0; i < size; ++i) {
        heap.insert(i, data[i].data());
    }

    heap.heapSort(4); // Sort by close price

    // Example: Displaying the 10 smallest prices
    std::cout << "The 10 smallest prices:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << std::endl;
    }

    // Example: Displaying the 10 largest prices
    std::cout << "The 10 largest prices:" << std::endl;
    for (int i = size - 1; i >= size - 10; --i) {
        std::cout << heap.get(i, 4) << " on date " << int(heap.get(i, 0)) << std::endl;
    }

    // Compute daily return
    heap.daily_returns();
    double max_return = 0;
    double min_return = INT_MAX;
    int max_index;
    int min_index;
    for (int i = 1; i < size; ++i) {
        double dailyReturn = heap.get(i, 5) * 100.0; // Convert to percentage
        if (dailyReturn > max_return) {
            max_return = dailyReturn;
            max_index = i;
        }
        if (dailyReturn < min_return) {
            min_return = dailyReturn;
            min_index = i;
        }
    }
    std::cout << "The maximum daily return is " << max_return << "% and it occurs on date " << int(heap.get(max_index, 0)) << std::endl;
    std::cout << "The minimum daily return is " << min_return << "% and it occurs on date " << int(heap.get(min_index, 0)) << std::endl;

    // Compute intraday return
    heap.intraday_return();
    max_return = 0;
    min_return = INT_MAX;
    for (int i = 0; i < size; ++i) {
        double intradayReturn = heap.get(i, 6) * 100.0; // Convert to percentage
        if (intradayReturn > max_return) {
            max_return = intradayReturn;
            max_index = i;
        }
        if (intradayReturn < min_return) {
            min_return = intradayReturn;
            min_index = i;
        }
    }
    std::cout << "The maximum intraday return is " << max_return << "% and it occurs on date " << int(heap.get(max_index, 0)) << std::endl;
    std::cout << "The minimum intraday return is " << min_return << "% and it occurs on date " << int(heap.get(min_index, 0)) << std::endl;

    // Find the maximum, minimum and median prices using all columns
    std::string priceTypes[4] = { "Open_price", "High_price", "Low_price", "Close_price" };
    for (int i = 1; i <= 4; ++i) {
        heap.heapSort(i);
        std::cout << priceTypes[i - 1] << ":" << std::endl;
        std::cout << "The maximum is " << heap.get(size - 1, i) << " and it occurs on date " << int(heap.get(size - 1, 0)) << std::endl;
        std::cout << "The minimum is " << heap.get(0, i) << " and it occurs on date " << int(heap.get(0, 0)) << std::endl;
        std::cout << "The median is " << heap.get(size / 2, i) << " and it occurs on date " << int(heap.get(size / 2, 0)) << std::endl;
    }

    return 0;
}
