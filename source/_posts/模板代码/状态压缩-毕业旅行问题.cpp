// 毕业旅行问题
// 小明目前在做一份毕业旅行的规划。打算从北京出发，分别去若干个城市，然后再回到北京，每个城市之间均乘坐高铁，
// 且每个城市只去一次。由于经费有限，希望能够通过合理的路线安排尽可能的省一些路上的花销。给定一组城市和每对城市之间的火车票的价钱，
// 找到每个城市只访问一次并返回起点的最小车费花销。

// 解决方案：使用状态压缩

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int getAns(vector<vector<int> > &nums){
    const int MAX = 0x0fffffff;
    int n = nums.size();
    int stateNum = 1 << n;
    // dp[i][j]中的i是一个二进制形式的数，表示经过城市的集合，如0111表示经过了城市0,1,2
    // dp[i][j]表示经过了i中的城市，并且以j结尾的路径长度
    vector<vector<int> > dp(stateNum,vector<int>(n,MAX));
    dp[1][0] = 0; //从城市0出发，所以经过城市0，以城市0结尾的路径为0
    //从城市0出发，更新和其他城市的距离
    for(int i=1;i<stateNum;i++){
        for(int j=0;j<n;j++){
            if(dp[i][j] != MAX){ //如果已经访问过
                for(int k=0;k<n;k++){
                    if( (i & (1 << k) ) == 0){ 
                        //没有访问过k，且从这里到k的距离小于原来的距离，则更新
                        dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k],dp[i][j] + nums[j][k]);
                    }
                }
            }
        }
    }
    int res = MAX;
    for(int i=1;i<n;i++){
        res = min(res,dp[stateNum-1][i] + nums[i][0]);
    }
    return res;
}
int main(int argc, char const *argv[])
{
   int n;
    while(cin>>n){
        vector<vector<int>> edges(n,vector<int>(n,0));
        int x;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>edges[i][j];
            }
        }
        cout<<getAns(edges)<<endl;
    }
    return 0;
}