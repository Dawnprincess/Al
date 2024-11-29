//输入一个m*n的矩阵reward[][]，表示每个位置的收益
//输出:获得收益最大值Reward

#include"../TestData.hpp"
#include"../File.hpp"
#include"../TimeTracker.hpp"
using namespace std;
int dp1(vector<vector<int >> reward,int i,int j){
    if(i==0 && j==0)
        return reward[i][j];
    if(i<0 || j<0)
        return 0;
    return max(dp1(reward,i-1,j),dp1(reward,i,j-1))+reward[i][j];
}

int dp3(vector<vector<int>>& reward, int i, int j) {
    vector<vector<int>> dp(i, vector<int>(j, 0));
    dp[0][0] = reward[0][0];
    for(int m = 1;m<i;m++){
        dp[m][0] = dp[m-1][0] + reward[m][0];
    }
    for(int n = 1;n<j;n++){
        dp[0][n] = dp[0][n-1] + reward[0][n];
    }
    
    for (int m = 1; m < i; m++) {
        for (int n = 1; n < j; n++) {
            dp[m][n] = max(dp[m-1][n], dp[m][n-1]) + reward[m][n];
        }
    }
    
    return dp[i - 1][j - 1];
}
    
void Reward(vector<vector<int>> reward){
    //计算二维数组d的长和宽
    int m = reward.size();
    int n = reward[0].size();
    int temp = dp3(reward,m,n);
    //temp = dp1(reward,m-1,n-1);
    cout<<"scale: "<<m << "*"<<n<<", The maximum reward is: "<<temp<<endl;
    

    //测试时间
    //TimeTracker::measureTime(dp3,"dp3",1,reward,m,n);
    //将结果放在测试数据后面
    //FileWriter::appendToFile("testdata.txt",temp,"\n");
}
int main(){
    //给d赋初值4*4的矩阵
    //示例值
    /*100 200 200 200
      300 100 100 200
    200 500 600 400
      100 400 500 800
        int m = 4,n = 4;
    vector<vector<int>> d = {
        {100,200,200,200},
        {300,100,100,200},
        {200,500,600,400},
        {100,400,500,800}
    };

    Reward(d);
    return 0;
    */
    
    for(int i = 1;i<= 100;i++){
        vector<vector<int>> d = TestData::generateTwoDimensionalArray(i*i,i*i,100,999);
        
        Reward(d);
            /*if(i%10==0){
            FileWriter::appendToFile("dp3.txt","\n");
            FileWriter::appendToFile("datascale.txt","\n");
        }
        FileWriter::appendToFile("datascale.txt",i," ");
*/
            }
    return 0;
    }