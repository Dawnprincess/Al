//线性时间选择
//输入:无序的数组a[],要查找第k小
//输出:输出第k小的元素a[k]

#include "../Filep.hpp"
using namespace std;
//划分函数
int partition(vector<int>& a,int l,int r,int pivotIndex){
    int pivotvalue = a[pivotIndex];
    //将划分点放在首部
    swap(a[pivotIndex],a[l]);
    int i=l,j=r+1;
    while(true){
        while(a[++i] < pivotvalue && i<r);
        while(a[--j] > pivotvalue);
        if(i>=j){
            break;
        }
        swap(a[i],a[j]);

    }
    a[l]=a[j];
    a[j]= pivotvalue;
    
    
    return j;

}
//选择函数
int RandomizedSelect(vector<int>& a,int l,int r,int k){
    
    if(r == l) return a[l];
    //随机划分
    int pivotIndex = l + rand() % (r - l + 1);
    //划分点的位于第几小
    int pivotpos = partition(a,l,r,pivotIndex);
    int j = pivotpos - l;

    //k和j相同时，直接返回
    if(k == j) {
        return a[pivotpos];
    } else if(k < j) {
        return RandomizedSelect(a, l, pivotpos - 1, k);
    } else {
        return RandomizedSelect(a, pivotpos + 1, r, k - j - 1);
    }
}
int linearTimeSelect(vector<int>& arr, int k) {
    return RandomizedSelect(arr, 0, arr.size() - 1, k);
}

int main() {
    //最后将vector中的数据转换为数组

    /*vector<int> arr = Filep("bs-2.txt");
    for(int i=0;i<arr.size();i++){
        cout << "第 " << i + 1 << " 小的元素是 " << linearTimeSelect(arr, i) << endl;
    }
    return 0;

*/
    vector<int> data = Filep("bs-2.txt");
    //记录查找时间
    clock_t start, end;
    start = clock();
    int i,j;
    for(i = 0; i < 1000000; i++) {
        for(j = 0; j < data.size(); j++) {
            linearTimeSelect(data, j);
        }
    }
    end = clock();
    double time = (double)(end - start) / 1000000.0 /data.size();
    cout << data.size() << "numbers sorted in the time of " << time << "s" << endl;
    system("pause");

    return 0;
}