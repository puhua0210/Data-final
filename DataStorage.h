// DataStorage.h

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include <string>

class DataStorage {
private:
    std::vector<std::vector<double>> data; // Store the data as vector of vectors of doubles

public:
    DataStorage(); // Constructor
    bool loadData(const std::string& filename); // Load data from CSV file
    std::vector<std::vector<double>>& getData(); // Accessor for data
};

#endif // DATASTORAGE_H
