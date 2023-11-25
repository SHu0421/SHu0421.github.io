
#include<iostream>
#include<vector>
#include<string>

using namespace std;


int main(){

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<long long> num;
    vector<long long> presum(n+1, 0);
    for (int i = 1; i <=n; i++)
    {
        long long tmp;
        scanf("%lld", &tmp);
        num.push_back(tmp);
        presum[i] = presum[i-1]+tmp;
        
    }
    long long res = 0;
    vector<long long> dp(n, 0);
    for (int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for (int j = i-1; j >=0; j--)
        {
            if(num[j+1]<0){
                cnt++;
                if(cnt>m){
                    break;
                }
            }
            if(presum[i] - presum[j]<=k){
                dp[i] = max(dp[i], presum[i] - presum[j]);
            }
        }
        res = max(res, dp[i]);
    }

    cout << res << endl;
    return 0;
}