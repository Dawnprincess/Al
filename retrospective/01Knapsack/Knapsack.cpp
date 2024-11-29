#include "../File.hpp"
#include "../TestData.hpp"
#include "../TimeTracker.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct item{
    int weight;
    int value;
    double unitvalue;
    item(int w,int v): value(v), weight(w){
        if(w == 0)
            unitvalue = 0;
        else
            unitvalue = value / weight;

    };
};

class Knapsack{
private:
    vector<item> items;
    int c;
    int n;
    int bestvalue;
    vector<bool> bestsolution;
    vector<bool> currentsolution;

public:
    Knapsack(vector<int> weight,vector<int> value,int c){
        this->n = weight.size();
        //腾出0作为根节点,item中的下标和物品序号一一对应
        items.push_back(item(0, 0)); // 加入一个空物品，位于根节点处，方便计算
        for (int i = 1; i < n + 1; i++) {
            items.push_back(item(weight[i - 1], value[i - 1]));
        }
        this->c = c;
        bestvalue = 0;
        bestsolution.resize(n + 1, false);
        currentsolution.resize(n + 1, false);
    }
    
    void printNode(int index){
        //左右分支都已经处理完毕，可以回溯,显示死节点
        //计算节点的标号
        char c = 'A' + (1 << index) - 1;
        //声明一个二进制数,
        int offset = 0;
        //计算二进制表示的节点标号
        for(int i = 1; i < index + 1; i++){
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
    double calbound(int index, int currentWeight, int currentValue) {
        // 如果已经超出最大重量，或者已经是最后一个物品，返回当前价值
        if(index >= n || currentWeight >= c) return currentValue;

        double bound = currentValue;
        int remainWeight = c - currentWeight;
        vector<item> temp;
        for(int i = 0; i < n + 1;i++){
            temp.push_back(item(items[i].weight,items[i].value));
        }

        // 按 unitvalue 从大到小排序
        sort(temp.begin(), temp.end(), [](const item &a, const item &b) {
            return a.unitvalue > b.unitvalue;
        });

        // 从当前物品开始，尽可能放入物品
        for(int i = index; i < n && remainWeight > 0; i++) {
            if(temp[i].weight <= remainWeight) {
                // 如果物品完全可以放入背包，加入其价值
                bound += temp[i].value;
                remainWeight -= temp[i].weight;
            } else {
                // 如果物品不能完全放入，只能放入部分
                bound += temp[i].unitvalue * remainWeight;
                break;  // 只放入部分物品后就不再继续
            }
        }
        return bound;
    }
    void backtrack(int n, int currentweight,int currentvalue){
        if(currentvalue > bestvalue){
            bestvalue = currentvalue;
            bestsolution = currentsolution;
        }
        if(n > this->n)
            return;

        if(currentweight + items[n + 1].weight <= this->c){
            currentsolution[n + 1] = true; 
            backtrack(n + 1,currentweight + items[n + 1].weight, currentvalue + items[n + 1].value);
            currentsolution[n + 1] = false;
        }

        if(calbound(n, currentweight,currentvalue) > bestvalue){
            backtrack(n + 1,currentweight,currentvalue);
        }
        //printNode(n);
    }
    void solve(){
        backtrack(0,0,0);
        /*cout << "the bestsolution is:"<< bestvalue <<endl;
        for(int i = 1; i < n+ 1;i++){
            cout << bestsolution[i] << " ";
        }
        cout << endl;
        */

    }

};
void sovle(Knapsack &knapsack){
    knapsack.solve();
}
int main(){
    /*
    vector<int> w = {16, 15, 15},p = {45,25, 25};
    int c = 30;
    Knapsack k(w,p,c);
    k.solve();
    */
    for(int i = 1; i <= 1000; i++){
    vector<int> values = TestData::generateOneDimensionalArray(i, 1, 10);
    vector<int> weights = TestData::generateOneDimensionalArray(i, 1, 10);

    //随机生成背包容量
    int capacity = rand() % 10 + 1;

    Knapsack knapsack(weights, values, capacity);
    TimeTracker::measureTime(sovle, "knapsack", 1, knapsack);
    FileWriter::appendToFile("datascale.txt",i ," ");


    }

    return 0;
}