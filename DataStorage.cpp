// DataStorage.cpp

#include "DataStorage.h"
#include <fstream>
#include <sstream>
#include <iostream>

DataStorage::DataStorage() {
    // Initialize the data vector
}

bool DataStorage::loadData(const std::string& filename) {
    // Load data from CSV file into data vector
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (getline(infile, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }

    infile.close();
    return true;
}

std::vector<std::vector<double>>& DataStorage::getData() {
    return data;
}
