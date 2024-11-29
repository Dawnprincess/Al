//输入:n个矩阵相乘的矩阵链,以及他们的维度p
//输出:总相乘次数最少的划分
#include"../TimeTracker.hpp"
#include"../TestData.hpp"
using namespace std;
void MatrixChain(vector<int> p,vector<vector<int>> &m,int n,vector<vector<int>> &s){
    for(int i=0;i<n;i++)
        m[i][i] = 0;//初始化第一个对角线,即一个矩阵，乘次数为0
    
    //矩阵链长度，从2开始
    for(int r=2; r<=n;r++){

        //起始位置
        for(int i=1;i<=n-r+1;i++){
            //结束位置
            int j = i+r-1;
            if(j >= n)
                break;
            //初始化下一对角线
            m[i][j] = m[i][i] + m[i+1][j] + p[i-1]*p[i]*p[j];
            //初始化分割点
            s[i][j] = i;
            //断点位置
            for(int k = i;k < j;k++){
                int t = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(t < m[i][j])
                    {
                        m[i][j] = t;
                        s[i][j] = k;
                    }
            }
        }
    }
}

void  PrintOptimalParents(int i,int j,vector<vector<int>> s){
    //s中记录了断点的位置,i,j
    if(i == j)
        cout << "A" << i;
    else{
        cout << '(';
        PrintOptimalParents(i, s[i][j],s);
        PrintOptimalParents(s[i][j] + 1, j, s);
        cout<<')';
    }
}
int MatrixChain2(vector<int> p,int i,int j){
    //采取递归法，而不用表格记录
    if(i == j)
        return 0;
    int min_cost = INT_MAX;
    for(int k = i; k < j; k++){
        int cost = MatrixChain2(p, i, k) + MatrixChain2(p, k+1, j) + p[i-1]*p[k]*p[j];
        min_cost = min(min_cost, cost);

    }
    return min_cost;
}
int main(){
    /*简单正确性测试
    vector<vector<int>> m(7,vector<int>(7));

        vector<vector<int>> s(7,vector<int>(7));
        //vector<int> data = TestData::generateOneDimensionalArray(4);
        vector<int> data = {30,35,15,5,10,20,25};
        MatrixChain(data,m,7,s);
        
        for(int i=1;i<=7;i++){
            cout << data[i-1] << " ";
        }
        cout << endl;
        for(int i=1;i<7;i++){
            for(int j=1;j<7;j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    return 0;
*/
//MatrixChain测试
    /* for(int i = 1; i <= 20; i++){
        vector<int> p = TestData::generateOneDimensionalArray(5 * i);
        vector<vector<int>> m(5* i,vector<int>(5 * i));
        
        vector<vector<int>> s(5* i,vector<int>(5 * i));
        TimeTracker::measureTime(MatrixChain, "MatrixChain",10, p, m, 5 * i, s);
        for(int j = 1; j < 5 * i; j++){
            for(int k = 1; k < 5 * i; k++){
            FileWriter::appendToFile("testdata.txt",m[j][k]," ");
            }
            FileWriter::appendToFile("testdata.txt","\n");
        }
        FileWriter::appendToFile("datascale.txt",5 * i," ");
    } */

//MatrixChain2测试

        for(int i = 1; i <= 10; i++){
            vector<int> data = TestData::generateOneDimensionalArray(5 + i);
            
            int cost = MatrixChain2(data, 1, 5 + i - 1);

            FileWriter::appendToFile("datascale2.txt",5 + i," ");
            TimeTracker::measureTime(MatrixChain2, "MatrixChain2",1, data, 1, 5 + i);
            cout << "cost: " << cost << endl;
        }


    return 0;
}