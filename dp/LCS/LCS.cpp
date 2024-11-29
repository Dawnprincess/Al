//输入:X,Y两个字符串,暂存数组c
//输出:LCS的长度
#include"../TestData.hpp"
#include"../TimeTracker.hpp"
#include"../File.hpp"
int LCS1(string X,string Y,int i, int j, int **c){
    if(i == 0 || j == 0)
        return 0;
    //c[i][j]=0;
    //优先查表，减少计算量,减少时间复杂度
    //if(c[i][j]!= -1)
     //   return c[i][j];
    
    if(X[i-1] == Y[j-1])
        c[i][j] = 1+LCS1(X,Y,i-1,j-1,c);
    else
        c[i][j] =  max(LCS1(X,Y,i-1,j,c),LCS1(X,Y,i,j-1,c));
    return c[i][j];
}
int LCSR1(string X,string Y,int i, int j){
    
    int **c = new int*[i+1];
    for(int k = 0;k<=i;k++)
        c[k] = new int[j+1];
    for(int k = 0;k<=i;k++)
        c[k][0] = 0;
    for(int k = 0;k<=j;k++)
        c[0][k] = 0;
    //备忘录法:初始化为-1，表示还没有计算，边界值在后续递归中赋值为0
    /*for(int k = 0;k<=i;k++){
        for(int l = 0;l<=j;l++)
            c[k][l] = -1;
    }
    */
    
    LCS1(X,Y,i,j,c);
    int lcs = c[i][j];
    for(int k = 0;k<=i;k++)
        delete[] c[k];
    delete[] c;
    return lcs;
}

void LCS2(string X,string Y,int **c,string **b){
    for(int i=1;i<=X.length();i++)
        c[i][0] = 0;
    for(int i=1;i<=Y.length();i++)
        c[0][i] = 0;
    for(int i=1;i<=X.length();i++){
        for(int j=1;j<=Y.length();j++){
            if(X[i-1] == Y[j-1]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = "↖";
            }
            //和去掉一个字母的子序列一样，取较大的
            else if(c[i-1][j] >= c[i][j-1]){
                //去掉X较大，同Xi-1Yj一样
                c[i][j] = c[i-1][j];
                b[i][j] = "↑";
            }
            else{
                //去掉Yj较大,同XiYj-1一样
                c[i][j] = c[i][j-1];
                b[i][j] = "←";
            }
        }
    }
}

int LCSR2(string X,string Y,int i,int j){
    int **c = new int*[i+1];
    for(int k = 0;k<=i;k++)
        c[k] = new int[j+1];
    for(int k = 0;k<=i;k++)
        c[k][0] = 0;
    for(int k = 0;k<=j;k++)
        c[0][k] = 0;
    string **b = new string*[i+1];
    for(int k = 0;k<=i;k++)
        b[k] = new string[j+1];
    for(int k = 0;k<=i;k++)
        b[k][0] = "";
    for(int k = 0;k<=j;k++)
        b[0][k] = "";
    LCS2(X,Y,c,b);
    //遍历输出LCS

    //初始化lcs为一个长度为i的空字符串
        /*string lcs(i,' ');

    cout<<"LCS is: "<<endl;
    int m = i,n = j;
    while(m>0 && n>0){
        if(b[m][n] == "↖"){
            lcs[m-1] = X[m-1];
            m--;
            n--;
        }
        else if(b[m][n] == "↑")
            m--;
        else
            n--;
    }

    for(m=0;m<X.length();m++)
    {
        if(lcs[m] != ' ')
            cout<<lcs[m];
    }
    cout<<endl;

    for(int m=1;m<=X.length();m++){
        for(int n=1;n<=Y.length();n++){
            cout<<b[m][n]<<" ";
        }
        cout<<endl;
    }

*/
        return c[i][j];
}
int main(){
    string X,Y;
    for(int i=1;i<=20;i++){

        Y = TestData::generateString(10+i);
        X = TestData::generateString(10*i);
        
        
        int result = LCSR2(X, Y, X.length(), Y.length());
        cout << "LCS ="<< result << endl;

        //调整写入文件顺序，确保强制中断程序时，datascale和testdata数据能对应
        TimeTracker::measureTime(LCSR1, "LCSR1", 100, X, Y, X.length(), Y.length());
        FileWriter::appendToFile("testdata.txt",result,"\n");

        FileWriter:: appendToFile("datascale.txt",10*i, " ");
        

    }

    return 0;
}
