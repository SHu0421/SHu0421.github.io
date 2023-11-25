#include<iostream>
#include<vector>
using namespace std;


int res=0;
void dfs(int indexi, int indexj, vector<vector<int>>& arr, int ans){
    int m=arr.size();
    int n=arr[0].size();
    if(indexj>=n){
        indexi=indexi+1;
        indexj=0;
    }
    // cout<<indexi<<" "<<indexj<<" "<<ans<<endl;
    if(indexi<m){
        for(int j=indexj;j<n;j++){
            if(arr[indexi][j]==0&&(indexi==0||arr[indexi-1][j]==0)&&(j==0||arr[indexi][j-1]==0)&&(indexi==m-1||arr[indexi+1][j]==0)&&(j==n-1||arr[indexi][j+1]==0)){
                arr[indexi][j]=1;
                dfs(indexi, j+2, arr, ans+1);
                arr[indexi][j]=0;
            }
        }
        dfs(indexi+1, 0, arr, ans);
    }else{
        // cout<<ans<<endl;
        if(ans>res){
            res=ans;
            // cout<<res<<endl;
        }
        return;
    }

}

int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    vector<vector<int>> arr(m, vector<int>(n, 0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &arr[i][j]);
        }
    }
    int i=0;
    for(int j=0;j<n;j++){
        if(arr[i][j]==0&&(i==0||arr[i-1][j]==0)&&(j==0||arr[i][j-1]==0)&&(i==m-1||arr[i+1][j]==0)&&(j==n-1||arr[i][j+1]==0)){
            arr[i][j]=1;
            // cout<<"start:"<<i<<" "<<j<<endl;
            dfs(i, j+2, arr, 1);
            arr[i][j]=0;
        }
    }

    cout<<res<<endl;

    return 0;
}