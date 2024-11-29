#include "../File.hpp"
#include "../TestData.hpp"
#include "../TimeTracker.hpp"
using namespace std;

struct Item {
    int weight;
    int value;
    double unitvalue; // 更改为 double 类型

    Item(int v, int w) : value(v), weight(w), unitvalue((double)v / w) {} // 使用 unitvalue
};



class Knapsack {
private:
    vector<Item> items;
    int capacity;
    int n;
    int bestvalue; // 当前最高价值
    vector<bool> bestsolution; // 最优解决方案
    vector<bool> currentsolution; // 当前解决方案

public:
    Knapsack(vector<int> weights, vector<int> values, int capacity) {
    this->n = values.size();
    this->bestvalue = 0;
    this->capacity = capacity;

    for (int i = 0; i < n; i++) {
        items.push_back(Item(values[i], weights[i]));
    }

    // 按 unitvalue 从大到小排序
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return a.unitvalue > b.unitvalue;
    });

    bestsolution.resize(n, false);
    currentsolution.resize(n, false);
    }


    // 贪心算法计算最大上限
    double calbound(int index, int currentWeight, int currentValue) {
        // 如果已经超出最大重量，或者已经是最后一个物品，返回当前价值
        if(index >= n || currentWeight >= capacity) return currentValue;

        double bound = currentValue;
        int remainWeight = capacity - currentWeight;

        // 从当前物品开始，尽可能放入物品
        for(int i = index; i < n && remainWeight > 0; i++) {
            if(items[i].weight <= remainWeight) {
                // 如果物品完全可以放入背包，加入其价值
                bound += items[i].value;
                remainWeight -= items[i].weight;
            } else {
                // 如果物品不能完全放入，只能放入部分
                bound += items[i].unitvalue * remainWeight;
                break;  // 只放入部分物品后就不再继续
            }
        }
        return bound;
    }
    //不考虑容量，剩余最大价值
    double calbound2(int index, int currentWeight, int currentValue){
        // 如果已经超出最大重量，或者已经是最后一个物品，返回当前价值
        if(index >= n || currentWeight >= capacity) return currentValue;
        for(int i = index; i < n; i++){
            currentValue += items[i].value;
        }
        return currentValue;
    }
    void printNode(int index){
        //左右分支都已经处理完毕，可以回溯,显示死节点
        //计算节点的标号
        char c = 'A' + (1 << (index + 1)) - 1;
        //声明一个二进制数,
        int offset = 0;
        //计算二进制表示的节点标号
        for(int i = 0; i < index + 1; i++){
            //如果currentsolution[i]为true,则记为0
            if(currentsolution[i]){
                offset <<= 1;
            }
            else{
                offset <<= 1;
                offset += 1;
            }
        }
        
        c += offset;
        cout << "节点" << c << "的左右分支都已经处理完毕，可以回溯" << endl;
    }
    //index表示当前处理的物品，也即解空间树的层数，currentWeight表示当前背包的重量，currentValue表示当前背包的价值
    void backtrack(int index, int currentWeight, int currentValue) {
        // 先更新最优解
        if (currentWeight <= capacity && currentValue > bestvalue) {
            bestvalue = currentValue;
            bestsolution = currentsolution; // 保持当前解为最优解
        }
        else{
        // 剪枝,先判断解情况
        double bound = calbound(index, currentWeight, currentValue);
        if (bound <= bestvalue) return;
        }

        // 如果达到末尾
        if (index >=n-1){
            //printNode(index);
            return;
        }

        // 选择当前物品
        if (currentWeight + items[index + 1].weight <= capacity) {
            currentsolution[index + 1] = true;
            backtrack(index + 1, currentWeight + items[index + 1].weight, currentValue + items[index + 1].value);
            // 遍历该子树的其他分支后，恢复现场
            currentsolution[index + 1] = false;
        }

        // 没有选择当前物品
        backtrack(index + 1, currentWeight, currentValue);

       //printNode(index);
    }

    void solve() {
        backtrack(-1, 0, 0);
    }

    void printResult() {
        cout << "最大价值: " << bestvalue << endl;
        cout << "选择的物品: ";
        for (int i = 0; i < n; i++) {
            if (bestsolution[i]) {
                cout << "(价值: " << items[i].value << ", 重量: " << items[i].weight << ") ";
            }
        }
        cout << endl;
    }

    vector<bool> getBestSolution() {
        return bestsolution;
    }
};

void sovle(Knapsack &knapsack){
    knapsack.solve();
}
int main() {
    /*for(int i = 1; i <= 1000; i++){
    vector<int> values = TestData::generateOneDimensionalArray(i, 1, 10);
    vector<int> weights = TestData::generateOneDimensionalArray(i, 1, 10);

    //随机生成背包容量
    int capacity = rand() % 10 + 1;

    Knapsack knapsack(weights, values, capacity);
    TimeTracker::measureTime(sovle, "knapsack", 1, knapsack);
    FileWriter::appendToFile("datascale.txt",i ," ");


    }

    return 0;
    */
    vector<int> values = {45, 25, 25};
    vector<int> weights {16, 15, 15};
    vector<bool> bestsolution;

    Knapsack knapsack(weights, values, 30);
    knapsack.solve();
    bestsolution = knapsack.getBestSolution();
    for(int i = 0; i < values.size(); i++){
        cout << bestsolution[i] << " ";
    }
    cout << endl;
    return 0;
}
