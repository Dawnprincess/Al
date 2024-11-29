/* 二分查找算法的C++实现
利用分治法进行二分查找
输入:一组排序好的数组arr和要查找的元素x
输出:若x在arr中，则返回其下标；否则返回-1
*/
#include"Filep.hpp"
#include <iostream>
#include<vector>
using namespace std;

int binary_search(vector<int> arr,int left,int right,int x){
    if(left > right)
        return -1;
    int mid = left + (right - left)/2;

    if(x == arr[mid]) return mid;

    if(x > arr[mid])
        return binary_search(arr, mid + 1, right, x);
    else
        return binary_search(arr, left, mid - 1, x);
}
int binary_search2(vector<int> arr, int left, int right, int x) {
while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] == x) return mid;

    if (arr[mid] < x)
        left = mid + 1;
    else
        right = mid - 1;
}
return -1;}

int main() {
    vector<int> data;
    data = Filep("bs-1.txt");
    //输入要查找的元素
    /*
    int x;
    cout << "enter the number you want to search: ";
    cin >> x;
    //输出查找结果
    int index = binary_search(data, 0, data.size() - 1, x);
    cout << "the index of number is  " << index << endl;
    */
/*
    int index;
    //记录查找时间
    clock_t start, end;
    start = clock();
    for(int i = 0; i < 1000000; i++) {
        index = binary_search(data, 0, data.size() - 1, rand()%data.size());
    }
    end = clock();
    double time = (double)(end - start) / 1000000.0;
    cout << "the time of searching is " << time << "s" << endl;
    system("pause");
    return 0;
*/
    int index;
    //记录查找时间
    clock_t start, end;
    start = clock();
    for(int i = 0; i < 1000000; i++) {
        index = binary_search2(data,0,data.size() - 1, rand()%data.size());
    }
    end = clock();
    double time = (double)(end - start) / 1000000.0;
    cout << "the time of searching2 is " << time << "s" << endl;
    system("pause");
    return 0;
}