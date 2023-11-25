// 比如14的正因数有(1,2,7,14)，15的正因数有(1,3,5,15)，k=14满足条件。

#include<iostream>
#include<vector>
using namespace std;

// https://blog.csdn.net/qq_39763472/article/details/82428602 欧拉筛求质数的方法，确保用最小的质因数来筛，那么就不会出现一个数被筛了两次
// 欧拉筛法的原理便是通过最小素因子来消除
//https://oi-wiki.org/math/number-theory/sieve/#_11 用线性筛求数的因数个数的方法

//方法一: O(nlogn)
// vector<int> compute(int n){
//   vector<int> count(n+1, 1);
//   for(int i=2;i<n;i++){
//       for(int j=i;j<=n;j+=i){
//           count[j]++;
//     }
//   }
//     return count;
// }


// 方法二：dfs 回溯每个质数的次数 time数组，求积数可以得到cur_num, cur_num可以和每个质数相乘，得到下一个数, 下一个数的质数更新公式
// count[cur_num*ans[i]]=count[cur_num]/(time[i]+1)*(time[i]+2);
// O(nlogn)

void dfs(vector<int> &time, vector<int> &count, vector<int> &ans, int cur_num, int n){
    if(cur_num>n){
        return;
    }
    int cnt=ans.size();
    for(int i=0;i<cnt;i++){
        if(cur_num*ans[i]>n){
            break;
        }
        count[cur_num*ans[i]]=count[cur_num]/(time[i]+1)*(time[i]+2);
        time[i]++;
        dfs(time, count, ans, cur_num*ans[i], n); 
        time[i]--;
    }

}

vector<int> compute(int n){
    vector<int> ans;
    vector<int> vis(n+1, 0);
   //求n之内的质数
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            ans.push_back(i);
            for(int j=i*i;j<=n;j+=i){
                vis[j]=1;
            }
        }
    }
    int cnt=ans.size();
    vector<int> time(cnt, 0);
    vector<int> count(n+1, 0);
    count[1]=1;
    // count[2]=2;
    dfs(time, count, ans, 1, n); 
    return count;
}


// 线性筛



// 欧拉筛法保证后面的数都是最小素因子 * i得到
// 最小素因子改变 则*2
// 最小素因子不变，同时因为欧拉筛法，所以当前一定乘的是最小素因子，如果我们用num记录的是最小素因子的个数
// 那么 d[i * p[j]] = d[i] / num[i * p[j]] * (num[i * p[j]] + 1);

vector<int> pre(int n) {
    vector<int> d(n+1, 0);
    vector<int> v(n+1, 0);
    int tot=0;
    vector<int> p(n+1, 0);
    vector<int> num(n+1, 0);
    d[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) v[i] = 1, p[++tot] = i, d[i] = 2, num[i] = 1;
        for (int j = 1; j <= tot && i <= n / p[j]; ++j) {
            v[p[j] * i] = 1;
            if (i % p[j] == 0) {  // p[j] 是i的最小素因子
                num[i * p[j]] = num[i] + 1; //p[j]这个质因数的num
                d[i * p[j]] = d[i] / num[i * p[j]] * (num[i * p[j]] + 1);
                break; //欧拉筛的方法，确保每个数只会被计算一次
            } else {
                num[i * p[j]] = 1; //p[j]这个质因数的num  也就是最小素因子的个数
                d[i * p[j]] = d[i] * 2; // 最小素因子改变，所以*2  （1+1）
            }
        }
    }
    return d;
}
    
int main(){
    int n=4000;
    vector<int> count1=pre(n);
    vector<int> count2=compute(n);
    int size1=count1.size();
    int size2=count2.size();
    cout<<size1<<endl;
    cout<<size2<<endl;
    // bool flag=true;
    // for(int i=1;i<size1;i++){
    //     if(count1[i]!=count2[i]){
    //         cout<<i<<endl;
    //         cout<<count1[i]<<endl;
    //         cout<<count2[i]<<endl;
    //         flag=false;
    //         break;
    //     }
    // }
    // cout<<flag<<endl;
    bool flag = (count1==count2);
    cout<<flag<<endl;

  return 0;
}