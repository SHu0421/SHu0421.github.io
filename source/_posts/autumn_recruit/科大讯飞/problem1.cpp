#include<iostream>
#include<vector>

using namespace std;

int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    vector<vector<int>> arr(m, vector<int>(n, 0));
    vector<vector<int>> res(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n;j++){
            scanf("%d", &arr[i][j]);
        }
    }
    int num = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n;j++){
            scanf("%d", &num);
            int tmp = arr[i][j] + 2 * num - 255;
            if (tmp>0&&tmp<255){
                res[i][j] = tmp;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n;j++){
            printf("%d ", res[i][j]);
        }
         printf("\n");
    }
    return 0;
}
