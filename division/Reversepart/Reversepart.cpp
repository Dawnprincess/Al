//输入一个无序数字序列，找出所有的逆序对，即比自己位置靠后的数更大的数，两者构成
//输入:无序数组arr,
//输出:所有的逆序对

//分析，在合并排序中，当一个数组被分为两个数组再合并时，会发现每一个左数组的数字比右数组大时，移向总数组，可以将所有逆序对找到
#include<iostream>
#include"../Filep.hpp"


void Merge(vector<int> &a,int left,int mid,int right){
    if(a[mid] <= a[mid+1]) return;
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
        else{
            for(int m=i;m<n1;m++){
                //一个数从右数组进去后，此时左数组后续都可与其构成逆序对!!!
                cout << "<" << L[m] << "," << R[j] << "> ";
            }
            a[k++] = R[j++];
            //输出逆序对
        }
    }
    //复制剩余的元素
    while(i < n1)
        a[k++] = L[i++];
    while(j < n2)
        a[k++] = R[j++];
    
}
// 递归的归并排序
void Merge_sort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        Merge_sort(arr, left, mid);
        Merge_sort(arr, mid + 1, right);
        // 合并
        Merge(arr, left, mid, right);
    }
}

// 查找逆序对的函数
void Reversepart(vector<int> arr) {
    Merge_sort(arr, 0, arr.size() - 1);
}

int main() {
    vector<int> test = Filep("bs-2.txt");
     clock_t start, end;
    start = clock();
    for(int i = 0; i < 1000; i++) {
        Reversepart(test);
        cout <<endl;
    }
    end = clock();
    double time = (double)(end - start) / 1000.0;
    
    
    cout << "the time of 100 times Reversepart is " << time << "s" << endl;
    return 0;
}