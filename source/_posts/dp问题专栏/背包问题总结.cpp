// 1. 0-1背包
for (int i = 0; i < n;i++){
    for (int j = V; j >= w[i];j--){
        dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    }
}

// 2. 完全背包
for (int i = 0; i < n;i++){
    for (int j = w[i]; j <=V ;j++){
        dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
    }
}
// 3. 多重背包
for (int i = 0; i < n;i++){
    for (int j = V; j >=v[i] ;j++){ //多重背包问题也必须倒着遍历
        for (int z = 0; z <= k;z++){
            if(j>=z*w[i]){
                dp[j] = max(dp[j], dp[j - z*w[i]] + c[i]*z);
            }
        }
            
    }
}


// 4. 分组背包
for (int i = 0; i < n;i++){
    for (int j = V; j >= 0;j--){
        for (int z = 0; z < nums[i];z++){ //每一个组最多只能选择一个物品， 理解为一组内的物品互斥
            if(j>=w[i][z]){
                dp[j] = max(dp[j], dp[j - w[i][z]] + c[i][z]);
            }
        }
    }
}

例题:1800.浮点数组合和(分组背包+打印背包)

// 5. 混合背包
for (循环物品种类)
{
    if (是 0 - 1 背包)
        套用 0 - 1 背包代码;
    else if (是完全背包)
        套用完全背包代码;
    else if (是多重背包)
        套用多重背包代码;
}


// 6. 二维费用背包, 比如消耗时间和价值， 最后如何让个数最多
for (int k = 1; k <= n; k++) {
  for (int i = m; i >= mk; i--)    // 对经费进行一层枚举
    for (int j = t; j >= tk; j--)  // 对时间进行一层枚举
      dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1);
}

// 7. 有依赖的背包
//对于包含一个主件和若干个附件的集合有以下可能性：仅选择主件，选择主件后再选择一个附件，选择主件后再选择两个附件……
// 主件和附件的搭配，转换为一个组里面的多种情况，因而转为分组背包



// 8. 背包输出方案
//我们可以用 g[i][v表示第 i 件物品占用空间为 v 的时候是否选择了此物品。然后在转移时记录是选用了哪一种策略（选或不选）。
int v = V;  // 记录当前的存储空间
// 因为最后一件物品存储的是最终状态，所以从最后一件物品进行循环
for (从最后一件循环至第一件) {
  if (g[i][v]) {
    选了第 i 项物品;
    v -= 第 i 项物品的价值;
  } else
    未选第 i 项物品;
}



//9.求总方案数
dp[0] = 1;
for (int i = 0; i < n; i++)
{
    for (int j = V; j >= w[i];j--){
        dp[j] = dp[j]+ dp[j - w[i]]; //选或者不选这个物品方案总数之和
    }
}



// 10.求最优解方案总数：
    c[0] = 1;
for (int i = 0; i < n; i++)
{
    for (int j = V; j >= 0;j--){
        int tmp = max(dp[j], dp[j - w[i]] + c[i]);
        if(tmp==dp[j]){
            c += cnt[j]; //去掉了一维，实际上代表的是c[i][j]+=c[i-1][j]
        }
        if(tmp==dp[j - w[i]] + c[i]){
            c += cnt[j - w[i]];
        }
        dp[j] = tmp;
        cnt[j] = c;
    }
}

int max = 0;  // 寻找最优解, 因为背包体积最大值有可能装不满，所以最优解不一定是 dp[V]??????
for (int i = 0; i <= V; i++) {
  max = max(max, dp[i]);
}
int res = 0;
for (int i = 0; i <= V; i++) {
  if (dp[i] == max) {
    res += cnt[i];  // 求和最优解方案数
  }
}

// 11. 背包的第 k 优解 
//之前记录的是最优，这里需要记录第k个最优，所以需要多一维，
//同时，需要使用双指针，对a[k]=dp[j][k], b[k]=dp[j - w[i]][k] + c[i]进行双指针排序（合并两个有序数组） 记录到dp[j][k]中
