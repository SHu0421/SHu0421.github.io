#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;

void dfs(int index, vector<vector<int>>&edges, vector<int> &vis, vector<int> &val, vector<int> &weight, int cur_val){
    vis[index]=1;
    for(int i=0;i<edges[index].size();i++){
        if(vis[edges[index][i]]==0){
            weight[edges[index][i]]=abs(cur_val+val[index]);
            dfs(edges[index][i], edges, vis, val, weight, cur_val+val[index]);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    vector<int> value(n+1, 0);
    vector<int> weight(n+1, 0);
    vector<int> vis(n+1, 0);
    vector<vector<int>> edges(n+1);
    string str;
    cin>>str;
    for(int i=1;i<=n;i++){
        if(str[i]=='R'){
            value[i]=1;
        }else if(str[i]=='B'){ 
            value[i]=-1;
        }
    }
    for(int i=1;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    dfs(1, edges, vis, value, weight, 0);
    int res=value[1];
    for(int i=1;i<=n;i++){
        // cout<<weight[i]<<endl;
        res+=weight[i];
    }
    cout<<res<<endl;
    return 0;
}