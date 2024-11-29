#pragma once
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

vector<int> Filep(string filename){
    vector<int> data;
    ifstream inputFile(filename);
    if(!inputFile) {
        cerr << "cannot open file!" << endl;
        return data;
    }
    string line;
    while(getline(inputFile,line)){
        //每次获取一行，ss存储当前行，temp存放每个逗号前的一个数据，通过stoi转化
        stringstream ss(line);
        string temp;
        while(getline(ss,temp,',')){
            try {
                data.push_back(stoi(temp));
            } catch (const invalid_argument& e) {
                cerr << "invalid input: " << temp << endl;
            }
        }
    }
    inputFile.close();
    
    //将vector中的数据转换为数组
    int arr[data.size()];
    for(int i=0;i<data.size();i++)
        arr[i] = data[i];
    //显示数组中的数据
    cout << "the array is: ";
    for(int i=0;i<data.size();i++)
        cout << arr[i] << " ";
    cout << endl;
    return data;
}
void Fileg(string filename, vector<int> data){
    ofstream outputFile(filename);
    if(!outputFile) {
        cerr << "cannot open file!" << endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        outputFile << data[i];
        if(i!=data.size()-1)
            outputFile << ",";
    }
    outputFile.close();
}