#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream file("C:\\Users\\72161\\source\\repos\\DS2\\x64\\Debug\\data1.csv");
	ofstream outfile("C:\\Users\\72161\\source\\repos\\DS2\\x64\\Debug\\data2.csv");
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