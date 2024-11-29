//利用分治思想设计实现合并排序
//输入：未排序的a[]
//输出：有序的a[]
#include "../Filep.hpp"
using namespace std;
//Merge()函数,合并两个有序数组
void Merge(vector<int>& a,int left,int mid,int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    //if(a[mid] <= a[mid+1]) return;
    //创建两个临时数组
    int L[n1],R[n2];
    //将a[]中的数据复制到L[]和R[]中
    for(int i=0;i<n1;i++)
        L[i] = a[left + i];
    for(int j=0;j<n2;j++)
        R[j] = a[mid + 1 + j];
    //合并两个有序数组
    int i = 0,j = 0,k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    //复制剩余的元素
    while(i < n1)
        a[k++] = L[i++];
    while(j < n2)
        a[k++] = R[j++];
    
}
void Merge2(vector<int>& a, int left, int mid, int right) {
    int i = left, j = mid + 1;
    
    // 如果已经有序，不需要合并
    //if (a[mid] <= a[mid + 1]) return;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            i++;
        } else {
            // 插入 a[j] 到合适的位置
            int temp = a[j];
            int k = j;
            while (k > i) {
                a[k] = a[k - 1];
                k--;
            }
            a[i] = temp;

            // 更新 i, mid 和 j 的位置
            i++;
            mid++;
            j++;
        }
    }
}
void Merge_sort(vector <int>& a,int left,int right){
    if(left < right){
        int mid = left + (right - left) / 2;//相比(right+left)/2不易溢出
        Merge_sort(a,left,mid);
        Merge_sort(a,mid+1,right);
        Merge2(a,left,mid,right);
    }
}

int main(){
    vector<int> data = Filep("bs-2.txt");
    //记录查找时间
    clock_t start, end;
    start = clock();
    for(int i = 0; i < 1000000; i++) {
        Merge_sort(data, 0, data.size() - 1);
    }
    end = clock();
    double time = (double)(end - start) / 1000000.0;
    for(int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    cout << data.size() << "numbers sorted in the time of " << time << "s" << endl;
    system("pause");
    }

