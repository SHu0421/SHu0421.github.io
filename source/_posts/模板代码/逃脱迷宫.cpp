#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
// 使用dfs出错，使用bfs正确
int dfs(vector<vector<int> > &matrix, int x, int y, vector<vector<int> > &vis, vector<vector<int> > &d)
{
    int n = matrix.size(); //迷宫是一个正方形
    // if(d[x][y]!=-1){
    //     return d[x][y];
    // }
    d[x][y] = INT_MAX;
    for (int i = 0; i < 4; i++)
    {
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(nextx<0||nextx>=n||nexty<0||nexty>=n||vis[nextx][nexty]){
            continue;
        }
        vis[nextx][nexty] = 1;
        if(matrix[x][y]==1){
            d[x][y] = min(d[x][y], dfs(matrix, nextx, nexty, vis, d)+1);
        }else{
            d[x][y] = min(d[x][y], dfs(matrix, nextx, nexty, vis, d));
        }
       
        vis[nextx][nexty] = 0;
    }
    return d[x][y];
}


struct cmp{
    bool operator()(const vector<int>&a , vector<int>&b){
        return a[2] > b[2];
    }
};
int bfs(vector<vector<int> > &matrix, int x, int y, vector<vector<int> > &vis)
{

    int n = matrix.size(); //迷宫是一个正方形
    priority_queue<vector<int> , vector<vector<int> >, cmp> q;
    q.push({0, 0, 0});
    vis[0][0] = 1;
    while (!q.empty())
    {
        vector<int> cur = q.top();
        q.pop();
       for (int i = 0; i < 4; i++)
        {
            int nextx = cur[0] + dx[i];
            int nexty = cur[1] + dy[i];
            if(nextx<0||nextx>=n||nexty<0||nexty>=n||vis[nextx][nexty]){
                continue;
            }
            if(nextx==n-1&&nexty==n-1){
                return cur[2];
            }
            vis[nextx][nexty] = 1;
            if(matrix[nextx][nexty]==1){
                q.push({nextx, nexty, cur[2] + 1});
            }else{
                q.push({nextx, nexty, cur[2]});
            }
            
        }
    }
    return  -1;
}

int main(){
    int n;
    scanf("%d", &n);
    vector<vector<int> > matrix(n, vector<int>(n, 0));
    vector<vector<int> > d(n, vector<int>(n, INT_MAX));
     vector<vector<int> > vis(n, vector<int>(n, 0));
    d[n - 1][n - 1] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    vis[0][0] = 1;
    // int result = dfs(matrix, 0, 0, vis, d);
    int result = bfs(matrix, 0, 0, vis);
    cout << result << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n;j++){
    //         printf("%d ", d[i][j]);
    //     }
    //     printf("\n");
    // }
    return 0;
}

// example 1
// 3
// 0 1 1
// 0 1 1
// 0 1 0
// 1

// example 2
// 7
// 0 1 1 1 1 1 1
// 0 0 1 1 1 1 1
// 1 0 0 1 1 1 1
// 1 1 1 0 0 1 0
// 1 1 1 1 1 1 0
// 0 1 1 1 1 1 0
// 1 0 1 0 1 1 0
// 2