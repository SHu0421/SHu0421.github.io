---
title: DP问题专栏
categories:
  - dp问题专栏
---
DAG上的dp

UVa 437 巴比伦塔 The Tower of Babylon

这道题求最高的塔，其实就是一个记忆化dfs的过程
一些需要注意的点：
1. 因为不可能出现一个立方体同时叠两次，因此不需要vis
2. 因为有三种叠法，所以需要3个方向
3. 因为最开始让谁做底部是不清楚的，所以使用循环遍历方法
4. 因为一个底确定之后的最高是确定的，因此使用记忆化搜索，避免重复计算
5. 对于这种题情况多，再加上dfs的题，先分析一两个小的情况（if-else, 三个方向分情况讨论）， 再暴力（dfs）， 再优化（记忆化数组）
6. 类似最长路问题


树状dp: dfs+dp
主要是针对图有层级结构（没有上司的舞会），或者选择课程这样的dp, 主要是背包和树状dp结合
使用dfs+dp

- 一般解题步骤：
- 先使用dfs记录子节点的状态：dp[i][0]/ dp[i][1]/ dp[i][k]
- 然后计算当前节点的状态转移 (u是父节点， i是子节点)
```C++
dp[u][a+b] = max(dp[u][a+b], dp[u][a]+dp[i][b]) //课程的转移方程
或者
dp[u][0] += max(dp[i][0], dp[i][1]); //上司的转移方程
dp[u][1] += dp[i][0];
```

- 例题
洛谷 P2014 CTSC1997 选课 （挺难的）
- 加入一门课程，森林转为树，求解dp[0][m+1]
- 我们枚举 u点的每个子结点 ，同时枚举以 i 为根的子树选了几门课程，将子树的结果合并到 u 上。注意这个使用a的取值范围随着访问的子树的数量逐渐增加

```C++
int dfs(int u) {
  int p = 1;
  f[u][1] = s[u];
  for (auto v : e[u]) {
    int siz = dfs(v);
    // 注意下面两重循环的上界和下界
    // 只考虑已经合并过的子树，以及选的课程数超过 m+1 的状态没有意义
    for (int i = min(p, m + 1); i; i--)
      for (int j = 1; j <= siz && i + j <= m + 1; j++)
        f[u][i + j] = max(f[u][i + j], f[u][i] + f[v][j]);  // 转移方程
    p += siz; //p逐渐增加
  }
  return p;
}
```

换根dp: 两次dfs， 找到换根前后dp的转移公式
- 树和图dfs不一样，不需要使用vis,只需要记录一下当前index，和当前index的father就能避免访问同一节点


数位dp感觉比较难

不要62
https://blog.csdn.net/Enjoying_Science/article/details/44082929 动态规划
https://www.cnblogs.com/wenruo/p/4725005.html 动态规划，解释有点问题
http://www.calvinneo.com/2017/09/23/HDU2089%E4%B8%8D%E8%A6%8162/ dfs
https://www.programminghunter.com/article/8939658418/ dfs


600. 不含连续1的非负整数


