#include<iostream>
#include<vector>
using namespace std;

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    vector<vector<int>> arr(m+1, vector<int>(n+1, 0));
    for (int i = 1; i <=m; i++)
    {
        for (int j = 1; j <=n;j++){
            scanf("%d", &arr[i][j]);
        }
    }
    int q;
    scanf("%d", &q);
    int t, x, y, h;
    int res = 0;
    vector<vector<int>> before(m+1, vector<int>(n+1, 0));
    for (int i = 0; i < q; i++)
    {
        scanf("%d %d %d %d", &t, &x, &y, &h);
        int tmp = 0;
        t -= 1;
        for (int a = -2; a <= 2; a++)
        {
            if(x+a>=1&&x+a<=m){
                tmp += min(arr[x + a][y]+t-before[x+a][y], h);
                arr[x + a][y] = max(0, arr[x + a][y]+t-before[x+a][y] - h);
                before[x + a][y] = t;
            }
            if(y+a>=1&&y+a<=n&&a!=0){
                tmp += min(arr[x][y+a]+t-before[x][y+a], h);
                arr[x][y+a] = max(0, arr[x][y+a]+t-before[x][y+a] - h);
                before[x][y+a] = t;
            }   
        }
        res += tmp;
        // cout << "tmp: "<<tmp << endl;
    }
    cout << res << endl;
    return 0;
}