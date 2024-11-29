//用于测试某个算法运行时间的类
//在其他文件调用该类，并传入算法及迭代次数，在算法开头记录shiftTime.start()，算法结束后记录shiftTime.stop()，即可测量算法运行时间
//传入参数包括:算法迭代次数,默认一百万次
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <string>

using namespace std;


class TimeTracker {
public:
    // 默认迭代次数为 10000
    template <typename Func, typename... Args>
    static void measureTime(Func func, const std::string& functionName, int iterations = 10000, Args&&... args) {
        // 获取开始时间
        auto start = chrono::high_resolution_clock::now();

        // 执行算法，进行迭代
        for (int i = 0; i < iterations; ++i) {
            func(forward<Args>(args)...);  // 调用传入的算法，并传递参数
        }

        // 获取结束时间
        auto end = chrono::high_resolution_clock::now();

        // 计算时间差
        chrono::duration<double> perduration = (end - start) / iterations;

        //将时间继续写入在名为functionName的txt文件中,用空格隔开
        ofstream outfile;
        outfile.open(functionName + ".txt", ios::app);
        outfile << perduration.count() << " ";
        outfile.close();

        }

};