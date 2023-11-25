#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
using namespace std;


void dfs(int index, int n, vector<int>& res, set<int>& zhishu, bool &flag){
    if(index==n-1){
        flag = true;
        return;
    }
    for (int i = index; i < n;i++){
        if(zhishu.find(res[i]+index+1)==zhishu.end()){
            swap(res[index], res[i]);
            dfs(index + 1, n, res, zhishu, flag);
            if(flag){
                return;
            }
            swap(res[index], res[i]);
        }
    }
    return;
}

int main(){
    int n;
    scanf("%d", &n);
    vector<int> res(n);
    for (int i = 0; i < n; i++)
    {
        res[i] = i + 1;
    }
    //求n之内的质数
    vector<int> vis(n+1, 0);
    set<int> zhishu;
    for (int i = 2; i <= n; i++)
    {
        if(!vis[i]){
            zhishu.insert(i);
            for (int j = i*2; j <= n;j+=i){
                vis[j] = 1;
            }
        }
    }
    bool flag = false;
    dfs(0, n, res, zhishu, flag);
    for (int i = 0; i < n; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}