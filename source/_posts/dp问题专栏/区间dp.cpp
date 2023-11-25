
//区间dp,一般枚举的是len, 常用于解决回文串，打气球最大分数，和合并石子类问题


//如果是链条

//如果是环，就将环转为链，然后求dp[1][n] dp[2][n+1] d[n+1][2n]中的最大值
// C++ Version
for (len = 2; len <= n; len++){ // len为1的时候根本不会进入第三层循环
    for (i = 1; i+len-1<=n ; i++) {
        int j = len + i - 1;
        for (k = i; k < j && k <= n - 1; k++)
        f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
    }
}
  

//如果是环，就将环转为链，然后求dp[1][n] dp[2][n+1] d[n+1][2n]中的最大值
// C++ Version
for (len = 2; len <= n; len++)
  for (i = 1; i+len-1<=2*n; i++) {
    int j = len + i - 1;
    for (k = i; k < j && k <= 2 * n - 1; k++)
      f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
  }