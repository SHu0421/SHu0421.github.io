#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int getCost(vector<int> &arr, int threshold){
    int size = arr.size();
    vector<int> dp(size, INT_MAX); //using the dp to the record the min cost from arr[0] to arr[x]
    for (int i = 0; i < size; i++)
    {
        priority_queue<int, vector<int>, less<int> > q;// using the Max-heap to recard the maxmum value in the window
        
        for (int j = i ; j >= 0; j--) // enumerate the start point of the window which inlcude value arr[i]
        {
            q.push(arr[j]);
            if (i - j < threshold) // check whether the window is within the limit
            {
                if(j>=1){
                    dp[i] = min(dp[i], dp[j-1] + q.top());
                }else{
                    dp[i] = min(dp[i], q.top());
                }
                
            }else{
                break;
            }
        }
    }

    return dp[size - 1];
}
int main(){
    // vector<int> arr = {1, 5, 2};
    // int t = 2;

    vector<int> arr = {1,  2};
    int t = 1;
    int res = getCost(arr, t);
    cout << res << endl;
    return 0;
}
