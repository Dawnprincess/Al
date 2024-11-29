#include <iostream>
#include "../TestData.hpp"
#include "../TimeTracker.hpp"
#include "../File.hpp"
using namespace std;

int main() {
    
    for(int i = 0; i < 1000; i++){
       vector<int> test = TestData::generateOneDimensionalArray(i);
    auto sortFunction = [](vector<int>::iterator start, vector<int>::iterator end) {
        sort(start, end);
    };
    TimeTracker::measureTime(sortFunction, "sort", 100, test.begin(), test.end());
    FileWriter::appendToFile("datascale3.txt",i," ");
    }
}
    