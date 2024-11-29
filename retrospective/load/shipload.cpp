#include <iostream>
#include <vector>
#include <algorithm>
#include "../TestData.hpp"
#include "../File.hpp"
#include "../TimeTracker.hpp"
using namespace std;

class Knapsack {
private:
    vector<int> weights;   // 物品的重量
    int capacity;          // 背包的容量（船的容量）
    int n;                 // 物品数量
    vector<bool> bestsolution;  // 最优解

public:
    Knapsack(vector<int> w, int c) {
        weights = w;
        capacity = c;
        n = w.size();
        bestsolution.resize(n, false);
    }

    // 0/1 背包问题：动态规划求解最大装载重量
    void solve() {
        vector<int> dp(capacity + 1, 0);  // dp[i]表示容量为i时能装载的最大重量
        vector<vector<bool>> chosen(n + 1, vector<bool>(capacity + 1, false));

        for (int i = 1; i <= n; ++i) {
            for (int j = capacity; j >= weights[i - 1]; --j) {
                if (dp[j - weights[i - 1]] + weights[i - 1] > dp[j]) {
                    dp[j] = dp[j - weights[i - 1]] + weights[i - 1];
                    chosen[i][j] = true;
                }
            }
        }

        // 获取最优解
        int w = capacity;
        for (int i = n; i >= 1; --i) {
            if (chosen[i][w]) {
                bestsolution[i - 1] = true;
                w -= weights[i - 1];
            }
        }
    }

    void printResult() {
        int totalWeight = 0;
        cout << "最优装载方案（货物编号及重量）: ";
        for (int i = 0; i < n; ++i) {
            if (bestsolution[i]) {
                cout << "(" << i + 1 << ": " << weights[i] << "kg) ";
                totalWeight += weights[i];
            }
        }
        cout << "\n总重量: " << totalWeight << "kg\n";
    }

    vector<bool> getBestSolution() {
        return bestsolution;
    }
};

// 装载问题求解
void solveShipLoadingProblem(vector<int> weights, int capacity1, int capacity2) {
    // 解决第一艘船的装载问题
    Knapsack knapsack1(weights, capacity1);
    knapsack1.solve();
    vector<bool> solution1 = knapsack1.getBestSolution();
    knapsack1.printResult();

    // 准备第二艘船的剩余货物
    vector<int> remainingWeights;
    for (int i = 0; i < weights.size(); ++i) {
        if (!solution1[i]) {  // 如果该物品没有被选中
            remainingWeights.push_back(weights[i]);
        }
    }

    // 解决第二艘船的装载问题
    if (!remainingWeights.empty()) {
        Knapsack knapsack2(remainingWeights, capacity2);
        knapsack2.solve();
        knapsack2.printResult();
    } else {
        cout << "第二艘船无需装载更多货物。\n";
    }
}

int main() {


    for(int i = 1; i <= 1000; i++){
        vector<int> weights = TestData::generateOneDimensionalArray(i,1 ,30);   // 货物的重量
        int capacity1 = rand()%100 + 1;                  // 第一艘船的容量
        int capacity2 = 20;                  // 第二艘船的容量

        TimeTracker::measureTime(solveShipLoadingProblem,"Time",5,weights,capacity1,capacity2);
        solveShipLoadingProblem(weights, capacity1, capacity2);
        FileWriter::appendToFile("datascale.txt", i ," ");
    }

    return 0;
}
