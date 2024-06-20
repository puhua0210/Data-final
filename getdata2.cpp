#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream file("C:/VScode C++ project/data structure/final_project/data1.csv");
	ofstream outfile("C:/VScode C++ project/data structure/final_project/data2.csv");
	int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
        if (count % 5 == 1) {
            outfile << line << "\n";
        }
    }
    file.close();
    outfile.close();
}