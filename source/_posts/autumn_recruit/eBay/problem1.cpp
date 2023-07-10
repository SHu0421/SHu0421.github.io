#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<vector<int> > dp(8, vector<int>(6, 0));
    dp[0][0] = 1;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6;j++){
            if(i==3&&j==2){
                dp[i][j] = 0;
            }else{
                if(i-1>=0){
                    dp[i][j] += dp[i - 1][j];
                }
                if(j-1>=0){
                    dp[i][j] += dp[i][j - 1];
                }
            }   
        }
    }

    // for (int i = 0; i < 8;i++){
    //     cout << dp[0][i] << endl;
    // }
    // cout << dp[0][7] << endl;
    cout << dp[7][5] << endl;

    // int res=0;
    // cout << "hello world" << endl;
    // for (int i = 1; i <= 27; i++)
    // {
    //     int cur = i;
    //     while (cur >= 3 && cur % 3 == 0)
    //     {
    //         cur = cur/ 3;
    //         res++;
    //         // cout << cur<<" "<<res << endl;
    //     }
    // }
    // cout << res << endl;
    // long long nextp2 = 2, nextp3 = 3, nextp5 = 5;
    // int p2 = 0, p3 = 0, p5 = 0;
    // vector<int> tmp(90);
    // tmp[0] = 1;
    // for (int i = 1; i <= 89; i++)
    // {
    //     long long next = min(min(tmp[p2] * 2, tmp[p3]*3), tmp[p5] * 5);
    //     if(tmp[p2] * 2 ==next){
    //         p2++;
    //     }
    //     if(tmp[p3] * 3 ==next){
    //         p3++;
    //     }
    //     if(tmp[p5] * 5 ==next){
    //         p5++;
    //     }
    //     tmp[i] = next;
    //     if (i >= 1 && i <= 10)
    //     {
    //         cout << next << endl;
    //     }
    //     if(i==89){
    //         cout << next << endl;
    //     }
    // }

    // for (int i = 0; i < 4;i++){

    // }

    return 0;
}