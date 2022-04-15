#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;

set<string> res;
void dfs(int index, string &s, string &cur)
{
    if(index==s.size()){
        if(cur!=""){
            res.insert(cur);
        }
        return;
    }
    bool left = (!cur.empty() && cur.back() == '0') || cur.empty();
    bool right = (index + 1 < s.size() && s[index + 1] == '0') || index == s.size() - 1;
    if (left&&right&&s[index]=='1'){
         dfs(index + 1, s, cur);
    }
       
    
}

int main(){
    string s;
    cin >> s;
    s = s;
    int size = s.size();
    string path;
    dfs(0, s, path);
    cout<<res.size()<<endl;
    // int MOD = pow(10, 9) + 7;
    // vector<vector<int> > dp(size, vector<int>(size, 0));
    // if(s==""){
    //     return 0;
    // }
    // if(s[0]=='0'){
    //     dp[0][0] = 1;
    //     dp[0][1] = 0;
    // }else{
    //     dp[0][0] = 0;
    //     dp[0][1] = 1;
    // }
    // for (int i = 1; i < size; i++)
    // {
    //     if(s[i]=='0'){
    //         dp[i][0] = (dp[i - 1][1] + 2*dp[i - 1][0]%MOD)%MOD;
    //         dp[i][1] = (dp[i - 1][1])%MOD;
    //     }else{ //这个数为1
    //         dp[i][0] = (dp[i - 1][0])%MOD;
    //         dp[i][1] = (2*dp[i - 1][1]%MOD+dp[i - 1][0])%MOD;
    //     }
    // }
    // cout<<(dp[size-1][0] + dp[size-1][1]) % MOD<<endl;
    return 0;
}