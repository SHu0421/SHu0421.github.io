#include<vector>
#include<iostream>
using namespace std;


int n;
int dp[1000010];
int cnt[1000010];
int dep[1000010]; //深度，不是子树的个数， 根节点深度更大 dep[son]=dep[fa]+1

vector<vector<int> > edges(1000010 + 1);

void dfs(int index, int father) //用vis或者当前节点的father避免重复访问
{
    dep[index] = dep[father] + 1;
    for (int i = 0; i < edges[index].size(); i++)
    {
        if(edges[index][i]!=father){
            dfs(edges[index][i], index); //这个是先dfs再求，因为父亲要用孩子的size
            cnt[index] += cnt[edges[index][i]];
        }
    }

}





void dfs2(int index, int father) //用vis或者当前节点的father避免重复访问
{
    dep[index] = dep[father] + 1;
    for (int i = 0; i < edges[index].size(); i++)
    {
        if(edges[index][i]!=father){
           dp[edges[index][i]] = dp[index] + n - 2 * cnt[index]; //注意这个是先求孩子再DFS, 因为孩子要用父亲的fp
           dfs2(edges[index][i], index);
        }
    }

}



int main(){
    memset(dp, 0, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    memset(dep, 0, sizeof(dep));
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) //7条边
    {
        int p, q;
        scanf("%d %d", &p, &q);
        edges[p].push_back(q);
        edges[q].push_back(p);
    }
    dfs(1, 1);
    for (int i = 1;i<=n;i++){
        dp[1] += dep[i];//将每个之前计算的节点的深度相加
    }
    dfs2(1, 1);
    int max_res = INT_MIN;
    int ans = -1;
    for (int i = 1; i <= n; i++)
    {
        if(dp[i]>max_res){
            max_res = dp[i];
            ans = i;
        }
    }
    cout << ans << endl;
    return 0;
}