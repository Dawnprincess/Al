//分数背包问题
//输入:物品价值，重量
//输出:最大价值v

#include "../TestData.hpp"
#include "../TimeTracker.hpp"
#include "../File.hpp"
using namespace std;

struct Item{
    int value;
    int weight;
    double vperw; //单位重量价值
    Item() : value(0), weight(0), vperw(0.0) {} // 添加默认构造函数
    Item(int v, int w):value(v), weight(w), vperw(v*1.0/w){}
};
//按单位重量价值选择
double backpack1(vector<int>& values, vector<int>& weights, int W){
    int n = values.size();
    vector<Item> items(n);
    //初始化items，将传入参数转化为Item结构体
    for(int i=0; i<n; i++){
        items[i] = Item(values[i], weights[i]);
    }
    //sort(items.begin(), items.end(), [](const Item& a, const Item& b){ return a.vperw > b.vperw; });//按单位重量价值排序
   sort(items.begin(), items.end(), [](const Item& a, const Item& b){ return a.weight < b.weight; });//按重量排序
   //sort(items.begin(), items.end(), [](const Item& a, const Item& b){ return a.value > b.value; });//按价值排序
    //v记录最大价值，w记录当前剩余背包容量
    double v = 0, w = W;
    
    for(int i = 0; i < n; i++){
        if(w < items[i].weight)
        {
            v += w * items[i].vperw;
            break;
        }
        else{
            v += items[i].value;
            w -= items[i].weight;
        }
    }
    return v;
}

int main(){
    vector<int> v = {25,24,15},w = {18,15,10};
    double res = backpack1(v, w, 20);
    cout << res << endl;
   
   /* vector<int> s,f;
    int C = 0;

    for(int i = 1;i < 500;i++){
        s = TestData::generateOneDimensionalArray(i,0,100,true);
        f = TestData::generateOneDimensionalArray(i,0,100,true);
        //随机生成背包容量
        C = rand() % 100 + 1;
        FileWriter::appendToFile("testdata.txt", C," ","\n");
        FileWriter::appendToFile("testdata.txt", "res=",backpack1(s,f,C),"\n");
        TimeTracker::measureTime(backpack1,"backpack11", 100, s, f, C);
        FileWriter::appendToFile("datascale11.txt", i," ");
    }
    return 0;*/
}