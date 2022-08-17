#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
int main(){
    int n, c;
    scanf("%d%d", &n, &c);
    unordered_map<int, int> total_num;
    unordered_map<int, int> cur_num;
    vector<int> arr(n);
    vector<int> vis(n, 0);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
        total_num[arr[i]]++;
    }
    for(int i=0;i<n;i++){
        if(cur_num[arr[i]]<total_num[arr[i]]/2+total_num[arr[i]]%2){
            cur_num[arr[i]]++;
            cout<<(i+1)<<" ";
            vis[i]=1;
        }
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        if(vis[i]==0){
            cout<<(i+1)<<" ";
        }
    }
    cout<<endl;

}