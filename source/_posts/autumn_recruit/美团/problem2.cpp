#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    vector<int> arr(n);
    vector<int> preerr(n+1, 0);
    vector<int> posterr(n+1, 0);

    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
        if(arr[i]>=0){
            preerr[i+1]=preerr[i]+1;
        }else{
            preerr[i+1]=preerr[i];
        }
    }
    int res=n;
     for(int i=n-1;i>=0;i--){
        if(arr[i]<=0){
            posterr[i]=posterr[i+1]+1;
        }else{
            posterr[i]=posterr[i+1];
        }
        res=min(res, preerr[i]+posterr[i+1]);
    }
    cout<<res<<endl;
    return 0;
}