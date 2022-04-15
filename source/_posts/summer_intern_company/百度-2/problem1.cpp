#include<iostream>
#include<vector>
#include<string>
using namespace std;




int findMaxHuiWen(string s){
    int size=s.size();
    vector<vector<int> > dp(size, vector<int>(size, 1));
    vector<int> presum(size+1, 0);
    if(s==""){
        return 0;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        for (int j = i + 1; j <= size - 1;j++){
            dp[i][j] = 0;
            if (s[i] == s[j])
            {
                dp[i][j] = dp[i + 1][j - 1];
            }
        }
    }
    

    for (int i = 1; i <=size;i++){
        if(s[i-1]=='1'){
            presum[i] = presum[i - 1] + 1;
        }else{
            presum[i] = presum[i - 1] ;
        } 
    }

    for (int len = size; len >=2;len--){
        for (int i = 0; i + len <= size;i++){
            int j = i + len - 1;
            if (dp[i][j]&&presum[j+1]-presum[i]!=0&&(presum[j+1]-presum[i]!=len)){
                return len;
            }
        }
    }
    return 0;
}
// 111010010100
int main(){
    string s;
    cin >> s;
    int res = findMaxHuiWen(s);
    cout << res << endl;


    return 0;
}