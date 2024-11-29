//利用分治思想设计实现快速排序
//输入：未排序的a[]
//输出：有序的a[]
#include"Filep.hpp"
using namespace std;

int Median_of_three(vector<int>& a, int left, int right) {
    int mid = left + (right - left) / 2;
    if (a[left] > a[mid]) swap(a[left], a[mid]);
    if (a[left] > a[right]) swap(a[left], a[right]);
    if (a[mid] > a[right]) swap(a[mid], a[right]);
    return mid;
}
int Partition(vector<int>& a,int left,int right){
    int pivot = a[right];
    //int pivot = Median_of_three(a, left, right);
    //swap(a[pivot], a[right]);
    int i = left - 1;
    for(int j = left; j < right; j++){
        if(a[j] < pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[i+1],a[right]);
    return i+1;
}
void Quick_sort(vector<int>& a,int left,int right){
    if(left < right){
        int pivot = Partition(a,left,right);
        Quick_sort(a,left,pivot-1);
        Quick_sort(a,pivot+1,right);
    }
    
}


void Quick_sort2(vector<int>& a, int left, int right) {
    while (left < right) {
        int pivot = Partition(a, left, right);
        
        // 如果左子数组比右子数组小，递归左边，右边通过循环处理
        if (pivot - left < right - pivot) {
            Quick_sort2(a, left, pivot - 1);  // 递归左半部分
            left = pivot + 1;  // 循环右半部分
        } else {
            Quick_sort2(a, pivot + 1, right); // 递归右半部分
            right = pivot - 1;  // 循环左半部分
        }
    }
}


int main(){

   
    vector<int> data = Filep("bs-2.txt");

    //记录查找时间
    clock_t start, end;
    start = clock();
    for(int i = 0; i < 1000000; i++) {
        Quick_sort2(data, 0, data.size() - 1);
    }
    end = clock();
    double time = (double)(end - start) / 1000000.0;
    cout << data.size() << "numbers sorted in the time of " << time << "s" << endl;
    system("pause");
}
