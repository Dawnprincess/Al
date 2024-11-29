//活动安排问题:
//输入:一组活动开始时间s[]，结束时间f[]
//输出:S最大相容活动集合
#include "../File.hpp"
#include "../TestData.hpp"
#include "../TimeTracker.hpp"
using namespace std;

void sort_with_indices(vector<int> &s, vector<int> &f) {
    // 创建一个索引数组
    vector<int> indices(f.size());
    for (int i = 0; i < f.size(); i++) {
        indices[i] = i; // 初始化索引数组
    }

    // 对f和indices同时进行排序
    sort(indices.begin(), indices.end(), [&f](int a, int b) {
        return f[a] < f[b]; // 根据f的值进行排序
    });

    // 根据排序后的indices数组更新s
    vector<int> sorted_s(s.size());
    vector<int> sorted_f(f.size());
    for (int i = 0; i < indices.size(); i++) {
        sorted_s[i] = s[indices[i]]; // 将s中的元素按照indices顺序放入sorted_s
        sorted_f[i] = f[indices[i]]; // 将f中的元素按照indices顺序放入sorted_f
    }
    
    s = sorted_s; // 更新s
    f = sorted_f; // 更新f
}
void is_sorted(vector<int> &s,vector<int> &f){
    for(int i = 0;i < f.size()-1;i++){
        if(f[i] > f[i+1]){
            sort_with_indices(s, f);
            return;
        }
    }
    return;
}

//由于需要检查f是否有序，
vector<bool> GreedySelect(vector<int> &s, vector<int> &f){
    is_sorted(s,f);
    int n = s.size(),i=0;
    vector<bool> A(n,false);
    A[0] = true;
    for(int j = 1;j < n;j++ ){
        if(s[j] >= f[i]){
            A[j] = true;
            i = j;
        }
    }
    return A;
}
int main(){
    /*vector<int> s = {1,3,0,5,3,5,6,8,8,2,12};
    vector<int> f = {4,5,6,7,8,9,10,11,12,13,14};
    vector<bool> A = GreedySelect(s,f);
    for(int i = 0;i < s.size();i++){
        if(A[i]){
            cout << "Activity " << i + 1 << " is selected." << endl;
        }
    }
    return 0;

*/
    // 测试数据
    vector<int> s,f;

    for(int i = 1;i < 1000;i++){
        s = TestData::generateOneDimensionalArray(i,0,100);
        f = TestData::generateOneDimensionalArray(i,0,100,true);
        TimeTracker::measureTime(GreedySelect,"GreedySelect2", 100, s, f);
        FileWriter::appendToFile("datascale2.txt", i," ");
    }
    return 0;
   
}