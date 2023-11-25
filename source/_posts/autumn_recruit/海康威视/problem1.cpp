#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
    string str1;
    string str2;
    string str_all;
    cin >> str_all;
    int index=str_all.find(",");
    int tmp=str_all.size();
    str1 = " " + str_all.substr(0, index);
    str2 = " " + str_all.substr(index+1, tmp-1-index);
    int size1 = str1.size();
    int size2 = str2.size();
    vector<vector<int>> dp(size1, vector<int>(size2, 0));
    dp[0][1] = 1;
    dp[1][0] = 1;
    for (int i = 1; i < size1; i++)
    {
        for (int j = 1; j < size2;j++){
            if(str1[i]==str2[j]){
                dp[i][j] = dp[i - 1][j - 1];
            }else{
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j-1]), dp[i-1][j-1])+1;
            }
        }
    }
    cout<<dp[size1 - 1][size2 - 1]<<endl;

    return 0;
}