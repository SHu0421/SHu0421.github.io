#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool dfs(vector<string>&matrix, vector<string>&target, int x, int y){
    int m = target.size();
    int n = target[0].size();
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            if(matrix[x+i][y+j]!=target[i][j]){
                return false;
            }
        }
    }
    return true;
}
int main(){
   
    int m, n;
    int x, y;

    scanf("%d%d", &m, &n);
    vector<string> matrix;
   for (int i = 0; i < m;i++){
       string tmp;
       cin >> tmp;
       matrix.push_back(tmp);
    }
    scanf("%d%d", &x, &y);
    vector<string> target;
    for (int i = 0; i < x;i++){
        string tmp;
        cin >> tmp;
        target.push_back(tmp);
    }
    int res = 0;
    // cout << x << " " << y << " " << m << " " << n << endl;
    for (int i = 0; i + x-1 <m; i++)
    {
        for (int j = 0;j+y-1<n;j++){
            // cout << matrix[i][j] << " " << target[0][0] << endl;
            if (matrix[i][j] == target[0][0])
            {
                if (dfs(matrix, target, i, j))
                {
                    res++;
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}