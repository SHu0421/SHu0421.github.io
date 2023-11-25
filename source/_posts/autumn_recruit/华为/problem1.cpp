#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n, m;
    scanf("%d", &n);
    vector<int> arr(n);
    int minnum=INT_MAX, maxnum=INT_MIN;
    for(int i=0;i<n;i++){
        minnum = min(minnum, arr[i]);
        maxnum = max(maxnum, arr[i]);
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    sort(arr.begin(), arr.end());
    int res=0;
    int res_remain=0;
    int ans=1;
    int left=0, right=1;
    while(right<n){
        while(left<right&&m<(right-left)*(arr[right]-arr[right-1])){
            m+=arr[right-1] - arr[left];
            left++;
            ans--;
        }

        m-=(right-left)*(arr[right]-arr[right-1]);
        ans++;
        if(ans>res){
            res=ans;
            res_remain=m;
        }else if(ans==res){
            if(m<res_remain){
                res_remain=m;
            }
        }
        // cout<<res<<" "<<m<<endl;
        right++;
    }
    cout<<res<<" "<<res_remain<<endl;

    return 0;
}
// 5
// 2 9 3 1 6
// 4