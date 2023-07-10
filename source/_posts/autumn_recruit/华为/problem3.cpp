#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

int dx[4]={0, 0, 1, -1};
int dy[4]={1, -1, 0, 0};

int dfs(int x, int y, vector<vector<int>> &arr, vector<vector<int>> &vis, int index, unordered_map<int, vector<pair<int,int>>> &groups){
    int m=arr.size();
    int n=arr[0].size();

    if(x<0||x>=m||y<0||y>=n||vis[x][y]||arr[x][y]==0){
        return 0;
    }
    vis[x][y]=index;
    int num=0;

    for(int i=0;i<4;i++){
        int nextx=x+dx[i];
        int nexty=y+dy[i];
        if(x<0||x>=m||y<0||y>=n||vis[x][y]||arr[x][y]==0){
            if(arr[x][y]==0){
                groups[index].push_back({x, y}); //边缘
            }
            continue;
        }
        num +=dfs(nextx, nexty, arr, vis);
    }
    return num+1;
}


int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    vector<vector<int>> arr(m, vector<int>(n));
    vector<vector<int>> vis(m, vector<int>(n, 0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &arr[i][j]);
        }
    }
    int index=1; //组从1开始
    unordered_map<int, int> hash;
    unordered_map<int, vector<pair<int,int>>> groups;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(arr[i][j]==1&&!vis[i][j]){
                int num = dfs(i, j, arr, vis, index, groups);
                hash[index]=num;//得到每组的数量
                index++;
            }
        }
    }
    //如果只有一组或者0组
    if(index==2||index==1){
        if(hash[index]+2<=m*n){
            cout<<hash[index]+2<<endl;
        }else{
            cout<< m*n<<endl;
        }
    }

    //使用队列求出每两组之间的距离
    vector<vector<int>> dis(index, vector<int>(index, 0));
    //重新初始化vis
      for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            vis[i][j]=0;
        }
    }
    for(int i=1;i<index-1;i++){
        queue<vector<int>> q;
        for(int j=0;j<groups[i].size();j++){
            q.push({groups[i][j].first, groups[i][j].second, 0});
        }
        while(!q.empty()){
            auto [x, y, distance]=q.top();
            q.pop();
            for(int i=0;i<4;i++){
                int nextx=x+dx[i];
                int nexty=y+dy[i];
                if(x<0||x>=m||y<0||y>=n||vis[x][y]||arr[x][y]==1){
                    continue;
                }
                q.push({nextx, nexty, distance+1});
            }
        }

    }

    return 0;
}