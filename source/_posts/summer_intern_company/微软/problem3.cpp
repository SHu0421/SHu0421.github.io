#include <iostream>
#include <vector>
using namespace std;


// 主要思路，使用动态规划，因为是两背包问题，因此dp多一个维度dp[i][j][z]代表选择第i个物品的时候，第一个背包剩余j空间, 第二个背包剩余z空间；得到状态转移为
// dp[i][j][z]=max(dp[i-1][j][z], dp[i][j-H[i-1]][z]+1, dp[i][j][z-H[i-1]]+1);
// 其中dp[i-1][j][z]表示不选择当前的物品，然后使用滚动数组将三维转为二维
int solution(vector<int> &H, int X, int Y) {
    // write your code in C++14 (g++ 6.2.0)
    int n = H.size();
    int dp[n + 1][X + 1][Y + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= X; j++)
        {
            for (int z = 0; z <= Y; z++)
            {
                dp[i][j][z] = 0;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= X; j++)
        {
            for (int z = 0; z <= Y; z++)
            {
                dp[i][j][z]=max(dp[i][j][z], dp[i-1][j][z]);
                if (j >= H[i-1])
                {
                    dp[i][j][z] = max(dp[i][j][z], dp[i-1][j - H[i-1]][z] + 1);
                }
                if (z >= H[i-1])
                {
                    dp[i][j][z] = max( dp[i][j][z], dp[i-1][j][z - H[i-1]] + 1);
                }
                res = max(res, dp[i][j][z]);
            }
        }
    }
    return res;
}


int solution(vector<int> &H, int X, int Y) {
    // write your code in C++14 (g++ 6.2.0)
    int n = H.size();
    int dp[X + 1][Y + 1];
    for (int j = 0; j <= X; j++)
    {
        for (int z = 0; z <= Y; z++)
        {
            dp[j][z] = 0;
        }
    }
    
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = X; j >= 0; j--)
        {
            for (int z = Y; z >= 0; z--)
            {
                if (j >= H[i-1])
                {
                    dp[j][z] = max(dp[j][z], dp[j - H[i-1]][z] + 1);
                }
                if (z >= H[i-1])
                {
                    dp[j][z] = max( dp[j][z], dp[j][z - H[i-1]] + 1);
                }
                res = max(res, dp[j][z]);
            }
        }
    }
    return res;
}
