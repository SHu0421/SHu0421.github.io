
#include<iostream>
#include<vector>
using namespace std;

0 i size-1
int findCombinationNumber(vector<int> arr, int target){

    int size = arr.size();
    vector<vector<int>> dp(size+1, vector<int>(target, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= size; i++)
    {
        for(int j = 0; j <= target;j++){
            dp[i][j] = dp[i - 1][j];
            if (j >= arr[i - 1])
            {
                dp[i][j] += dp[i - 1][j - arr[i-1]];
            }
        }
    }
    return dp[size][target];
}

int main(){
    vector<int> arr = {2, 3, 4, 7};
    int target = 7;
    int res = findCombinationNumber(arr, target);
    cout << res << endl;
    return 0;
}