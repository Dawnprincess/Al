#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct item {
    int value;
    int weight;
    double unitvalue;
    item(int v, int w) : value(v), weight(w) {
        unitvalue = (w == 0) ? 0 : (double)v / w;
    }
};

// 用于存储节点信息
struct Node {
    int index;             // 当前节点对应物品的索引
    int currentValue;      // 当前背包中的价值
    int currentWeight;     // 当前背包中的重量
    double upperBound;     // 当前节点的上限值
    vector<bool> solution; // 当前节点的解
    Node(int idx, int val, int wt, double bound, vector<bool> sol)
        : index(idx), currentValue(val), currentWeight(wt), upperBound(bound), solution(sol) {}
};

// 优先队列比较规则：上限值大的优先
struct Compare {
    bool operator()(const Node &a, const Node &b) {
        return a.upperBound < b.upperBound;
    }
};

class Knapsack {
private:
    vector<item> items;
    int c;                  // 背包容量
    int n;                  // 物品数量
    int bestvalue;          // 当前最优值
    vector<bool> bestsolution; // 当前最优解

public:
    Knapsack(vector<int> weight, vector<int> value, int c) {
        this->n = weight.size();
        // 添加虚拟根节点
        items.push_back(item(0, 0));
        for (int i = 1; i < n + 1; i++) {
            items.push_back(item(value[i - 1], weight[i - 1]));
        }
        this->c = c;
        bestvalue = 0;
        bestsolution.resize(n + 1, false);
    }

    double calbound(int index, int currentWeight, int currentValue) {
        if (currentWeight >= c || index > n)
            return currentValue;

        double bound = currentValue;
        int remainWeight = c - currentWeight;

        // 按单位价值排序（无需重新构造物品列表）
        vector<item> temp(items.begin() + index, items.end());
        sort(temp.begin(), temp.end(), [](const item &a, const item &b) {
            return a.unitvalue > b.unitvalue;
        });

        // 尽可能装入背包
        for (const auto &it : temp) {
            if (it.weight <= remainWeight) {
                bound += it.value;
                remainWeight -= it.weight;
            } else {
                bound += it.unitvalue * remainWeight;
                break;
            }
        }
        return bound;
    }

    void backtrack() {
        priority_queue<Node, vector<Node>, Compare> pq;

        // 初始化根节点
        Node root(0, 0, 0, calbound(0, 0, 0), vector<bool>(n + 1, false));
        pq.push(root);

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.index > n || current.currentWeight > c)
                continue;

            // 左子节点：选择当前物品
            int newWeight = current.currentWeight + items[current.index].weight;
            int newValue = current.currentValue + items[current.index].value;
            vector<bool> leftSolution = current.solution;
            leftSolution[current.index] = true;

            if (newWeight <= c && newValue > bestvalue) {
                bestvalue = newValue;
                bestsolution = leftSolution;
            }

            double leftBound = calbound(current.index + 1, newWeight, newValue);
            if (newWeight <= c && leftBound > bestvalue) {
                pq.push(Node(current.index + 1, newValue, newWeight, leftBound, leftSolution));
            }

            // 右子节点：跳过当前物品
            double rightBound = calbound(current.index + 1, current.currentWeight, current.currentValue);
            if (rightBound > bestvalue) {
                pq.push(Node(current.index + 1, current.currentValue, current.currentWeight, rightBound, current.solution));
            }
        }
    }

    void printSolution() {
        cout << "Best value: " << bestvalue << endl;
        cout << "Selected items: ";
        for (int i = 1; i <= n; i++) {
            if (bestsolution[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    vector<int> weights = {16, 15, 15};
    vector<int> values = {45, 25, 25};
    int capacity = 30;

    Knapsack knapsack(weights, values, capacity);
    knapsack.backtrack();
    knapsack.printSolution();

    return 0;
}
