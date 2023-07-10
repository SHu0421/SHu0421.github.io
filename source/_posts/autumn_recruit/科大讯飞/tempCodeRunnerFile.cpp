#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;



vector<vector<int>> multiple_x(vector<vector<int>> A, vector<vector<int>> B){
    int m = A.size();
    int n = A[0].size();
    int p = B.size();
    int q = B[0].size();
    vector<vector<int>> res(m * p, vector<int>(n * q));
    for (int i = 0; i < m;i++){
        for (int j = 0; j < n;j++){
            for (int k = 0; k < p; k++){
                for (int t = 0; t < q; t++){
                    res[i * p + k][j * q + t] = A[i][j] * B[k][t];
                }
            }
        }
    }
    return res;
}

vector<vector<int>> multiple(vector<vector<int>> A, vector<vector<int>> B){
    int n = A.size();

    vector<vector<int>> res(n , vector<int>(n, 0));
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            for (int k = 0; k < n;k++){
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return res;
}

vector<vector<int>> F(int n){
    vector<vector<int>> res = vector<vector<int>>(2, vector<int>(2, 1));
    res[0][1] = 0;
    if(n==1){
        return res;
    }
    return multiple_x(res, F(n-1));
}


vector<vector<int>> B(int n){
    vector<vector<int>> I_2 = vector<vector<int>>(2, vector<int>(2, 0));
    I_2[0][0] = 1;
    I_2[1][1] = 1;
    if (n == 2)
    {
        return I_2;
    }
    vector < vector<int>> res = vector<vector<int>>(n, vector<int>(n, 0));
    vector < vector<int>> R_N = vector<vector<int>>(n, vector<int>(n, 0));
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if(j>=n){
            j = 1; 
        }
        R_N[i][j] = 1;
        j += 2;
    }
    vector<vector<int>> tmp = multiple_x(I_2, B(n / 2));
    res = multiple(R_N, tmp);
    // for (int i = 0; i < n;i++){
    //     for (int j = 0; j < n;j++){
    //         res[i][j] = R_N[i][j] * tmp[i][j];
    //     }
    // }
    return res;
}


int main(){
    int n;
    scanf("%d", &n);
    
    vector<vector<int>> F_N = F(n);
    int N = pow(2, n);
    vector<vector<int>> res = vector<vector<int>>(N, vector<int>(N, 0));
    vector<vector<int>> B_N = B(N);
    int size1 = F_N.size();
    int size2 = F_N[0].size();
    res = multiple(B_N, F_N);
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2;j++){
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }

    // vector<vector<int>> A = vector<vector<int>>(2, vector<int>(2, 0));
    // A[0][0] = 1;
    // A[0][1] = 2;
    // A[1][0] = 3;
    // A[1][1] = 4;

    // vector<vector<int>> B = vector<vector<int>>(2, vector<int>(2, 0));
    // B[0][0] = 5;
    // B[0][1] = 6;
    // B[1][0] = 7;
    // B[1][1] = 8;
    // vector<vector<int>> res= multiple_x(A, B);
    // int size1 = res.size();
    // int size2 = res[0].size();
    // for (int i = 0; i < size1; i++)
    // {
    //     for (int j = 0; j < size2;j++){
    //         cout << res[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}