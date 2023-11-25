#include<iostream>
#include<vector>
using namespace std;

bool dfs(int x, int y, vector<vector<char> > &map, vector<vector<int> > &memo, vector<vector<int> > &vis){
    int n=map.size();
    int m=map[0].size();
    
    if(x<0||x>=n||y<0||y>=m||vis[x][y]){
        return false;
    }
    // cout<<x<<" "<<y<<" "<<memo[x][y]<<endl;
    if(map[x][y]=='O'){
        memo[x][y]=1;
        return true;
    }
    if(memo[x][y]!=-1){
        return memo[x][y];
    }
    int res=-1;
    vis[x][y]=1;
    if(map[x][y]=='.'){
        res=dfs(x-1,y,map,memo, vis)||dfs(x,y-1,map,memo, vis)||dfs(x+1,y,map,memo, vis)||dfs(x,y+1,map,memo, vis);
    }else if(map[x][y]=='U'){
        res=dfs(x-1,y,map,memo, vis);
    }else if(map[x][y]=='D'){
        res=dfs(x+1,y,map,memo, vis);
    }else if(map[x][y]=='L'){
        res=dfs(x,y-1,map,memo, vis);
    }else if(map[x][y]=='R'){
        res=dfs(x,y+1,map,memo, vis);
    }else{
        cout<<"input error"<<endl;
    }
    // cout<<x<<" "<<y<<" "<<memo[x][y]<<endl;
    memo[x][y]=res;
    return memo[x][y];
}
int main(){
    int m, n;
    scanf("%d%d", &n, &m);
    vector<vector<char> > map(n, vector<char>(m));
    for(int i=0;i<n;i++){
        string tmp;
        cin>>tmp;
        int index=0;
        for(int j=0;j<m;j++){
            map[i][j]=tmp[j];
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<map[i][j]<<"";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    vector<vector<int> > memo(n, vector<int>(m, -1));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(memo[i][j]==-1){
                vector<vector<int>> vis(n, vector<int>(m, 0));
                dfs(i,j, map, memo, vis);
            }
        }
    }
    int res=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(memo[i][j]==0){
                res++;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}