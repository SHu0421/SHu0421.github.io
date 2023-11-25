#include<iostream>
#include<vector>
#include<string>
using namespace std;


// 2 2 
// 0 1 
// 1 0

int main(){
    int m, t;
    scanf("%d%d", &m, &t);
    vector<vector<int> > matrix(m, vector<int>(m, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0;j<m;j++){
            scanf("%d", &matrix[i][j]);
        } 
    }

    vector<vector<int> > res(m*t, vector<int>(m*t, 0));
    for (int i = 0; i < m*t; i++)
    {
        for (int j = 0;j<m*t;j++){
            res[i][j] =matrix[i/t][j/t];
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}