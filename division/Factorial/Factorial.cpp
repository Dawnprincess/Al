//输入:n!
//输出:最终结果res
#include<iostream>
using namespace std;
int Factorial1(int n){
    if(n==1)
        return 1;
    else
        return n*Factorial1(n-1);
}
int Factorial2(int n){
    int res = 1;
    if(n==0)
        return res;
    for(int i=1;i<n+1;i++){
        res*=i;
    }
    return res;

}

int main(){
    //记录查找时间
    clock_t start, end;
    double time;
    start = clock();
    
    for(int i=1;i<1000000;i++)
    {

    Factorial1(10);
    }
    end = clock();
    time = (double)(end - start) / 1000000;
    cout     << "Factorial1(100) time: " << time << "s" << endl;

    start = clock();
    
    for(int i=1;i<1000000;i++)
    {

    Factorial1(100);
    }
    end = clock();
    time = (double)(end - start) / 1000000;
    cout     << "Factorial1(1000) time: " << time << "s" << endl;
    
    start = clock();
    
    for(int i=1;i<1000000;i++)
    {

    Factorial1(1000);
    }
    end = clock();
    time = (double)(end - start) / 1000000;
    cout     << "Factorial1(10000) time: " << time << "s" << endl;


    start = clock();
    
    for(int i=1;i<1000000;i++)
    {

    Factorial2(1000);
    }
    end = clock();
    time = (double)(end - start) / 1000000;
    cout     << "Factorial2(1000) time: " << time << "s" << endl;
       
   
}