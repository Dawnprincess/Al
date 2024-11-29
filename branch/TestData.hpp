//生成随机测试数据，并写入testdata.txt文件中
#pragma once

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
#include "File.hpp"

using namespace std;

class TestData {
public:
    // 生成一维整数数组（vector<int>），随机数或已排序数
    static vector<int> generateOneDimensionalArray(int numElements, int lowerLimit = 0, int upperLimit = 100, bool sorted = false) {
        vector<int> result;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(lowerLimit, upperLimit);

        // 生成随机整数
        for (int i = 0; i < numElements; ++i) {
            result.push_back(dis(gen));
        }

        // 如果需要排序，进行排序
        if (sorted) {
            sort(result.begin(), result.end());
        }
        
        FileWriter::appendToFile("testdata.txt", result) ;
        FileWriter::appendToFile("testdata.txt", "\n") ;
        return result;
    }

    // 生成字符串，支持字符范围及大小写
    static string generateString(int length, bool upperCase = true) {
        string result;
        random_device rd;
        mt19937 gen(rd());

        // 字母范围，只有大写字母或小写字母
        string charRange = upperCase ? "ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "abcdefghijklmnopqrstuvwxyz";
        uniform_int_distribution<> dis(0, charRange.size() - 1);

        // 生成指定长度的字符串
        for (int i = 0; i < length; ++i) {
            result += charRange[dis(gen)];
        }

        FileWriter::appendToFile("testdata.txt",result, " ");

        return result;
    }

    // 生成二维整数数组（vector<vector<int>>）
    static vector<vector<int>> generateTwoDimensionalArray(int rows, int cols, int lowerLimit = 0, int upperLimit = 100) {
        vector<vector<int>> result;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(lowerLimit, upperLimit);

        for (int i = 0; i < rows; ++i) {
            vector<int> row;
            for (int j = 0; j < cols; ++j) {
                row.push_back(dis(gen));
            }
            result.push_back(row);
        }
        //FileWriter::appendToFile("testdata.txt", result) ;

    return result;
    }
};
