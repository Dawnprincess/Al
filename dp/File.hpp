#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <type_traits>
using namespace std;

class FileWriter {
public:
    // 将数据追加到指定的文件
    template <typename T>
    static void appendToFile(const std::string& fileName, const T& data) {
        // 以追加模式打开文件
        std::ofstream outFile(fileName, std::ios::app);

        if (!outFile) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        // 检查数据是否为std::vector类型，若是则逐个输出
        //这里使用if constexpr来判断是否为std::vector类型，若是则使用for循环逐个输出
        //该函数可以在编译期间确定类型，不仅是效率更高，可以避免编译器检查data类型错误导致不能编译
        if constexpr (std::is_same<T, std::vector<int>>::value) {
            for (const auto& i : data) {
                outFile << i << " ";
            }
        }
        else if constexpr (std::is_same<T, std::vector<vector<int>>>::value) {
            for(const auto& vec : data){
                for (const auto& i : vec) {
                    outFile << i << " ";
                }
                outFile << endl;
            }
        }
        else if constexpr (std::is_same<T, std::vector<double>>::value) {
            for (const auto& i : data) {
                outFile << i << " ";
            }
        }
        else if constexpr (std::is_same<T, std::vector<std::string>>::value) {
            for (const auto& i : data) {
                outFile << i << " ";
            }
        }
        else {
            // 非容器类型，直接输出
            outFile << data;
        }

        // 写入数据到文件

        // 关闭文件
        outFile.close();
    }

    // 如果需要追加多个数据，可以使用该方法，支持多个参数
    template <typename T, typename... Args>
    static void appendToFile(const std::string& fileName , const T& first, const Args&... args) {
        // 以追加模式打开文件
        std::ofstream outFile(fileName, std::ios::app);

        if (!outFile) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        // 使用递归的方式写入数据
        appendToFileHelper(outFile, first, args...);

        // 关闭文件
        outFile.close();

        std::cout << "Data successfully appended to " << fileName << std::endl;
    }

private:

    // 辅助函数，递归地写入多个数据
    template <typename T>
    static void appendToFileHelper(std::ofstream& outFile, const T& data) {
        outFile << data;
    }

    template <typename T, typename... Args>
    static void appendToFileHelper(std::ofstream& outFile, const T& first, const Args&... args) {
        outFile << first << " ";  // 可以根据需要添加分隔符，如空格
        appendToFileHelper(outFile, args...);
    }

    
};

#endif // FILE_HPP
