#include <iostream>
#include <vector>

using namespace std;

class Queen{
private:
    int n;
    //x[i]记录第i个皇后第i行放置的列数
    vector<int> x;
    int solution;
    
public:
    Queen(int n){
        this->n = n;
        x = vector<int> (n+1,1);
        solution = 0;
    }
    //传入位置，查看是否冲突
    int Check(int row, int col){
        for(int i = 1;i < row;i++){
            if(col == x[i] || abs(row - i) == abs(col - x[i]))
                return 0;
        }
        return 1;
    }
    void backtrack(int index){
        if(index > n){
            solution++;
            return ;   
        }
        for(int i = 1; i < n + 1; i++){
            if(Check(index, i)){
                x[index] = i;
                backtrack(index + 1);
            }
        }
    }
    void solve(){
        backtrack(1);
        cout << "共有" << solution << "种解" << endl;
    }

};
int main(){
    for(int i =0 ;i < 50;i++){
        Queen q(i);
        q.solve();
    }
}