#include<vector>
#include<string>
#include<unordered_set>
#include<string>
using namespace std;
vector<vector<string> > res;

// 需要四个数组，分别存储两个对角线+vis， 再加每行对应的具体列是什么
vector<string> generateBoard(int n, vector<int>& row_index){
    vector<string> ans;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        for (int j = 0; j < n;j++){
            if(j==row_index[i]){
                tmp+="Q";
            }else{
                tmp+=".";
            }
        }
        ans.push_back(tmp);
    }
    return ans;
}
void dfs(int n, int row, unordered_set<int> &diagnal1, unordered_set<int> &diagnal2, vector<int> &row_index, vector<int> &vis){
    if(row==n){
        vector<string> tmp = generateBoard(n, row_index);
        res.push_back(tmp);
        return;
    }
    for (int i = 0;i<n;i++){
        if(vis[i]!=-1){
            continue;
        }
        if(diagnal1.count(row+i)!=0){
            continue;
        }
        if(diagnal2.count(row-i)!=0){
            continue;
        }
        row_index[row] = i;
        vis[i]=1;
        diagnal1.insert(row + i);
        diagnal2.insert(row - i);
        dfs(n, row + 1, diagnal1, diagnal2, row_index, vis);
        diagnal1.erase(row + i);
        diagnal2.erase(row - i);
        vis[i]=-1;
    }

}
vector<vector<string> > solveNQueens(int n)
{

    unordered_set<int> diagnal1;
    unordered_set<int> diagnal2;
    vector<int> row_index(n);
    vector<int> vis(n, -1);
    dfs(n, 0, diagnal1, diagnal2, row_index, vis);
    return res;
}



//解数独， 和八皇后不一样的是，需要使用二维数组甚至三维数组来计算vis, 因为八皇后只有8个位置需要vis, 这个是每个位置都需要vis

class Solution {
public:
    bool line[9][10];
    bool column[9][10];
    bool matrix[3][3][10];
    bool flag=false;
    void dfs(vector<vector<int>> &points, int index, vector<vector<char>> &board){
        if(index==points.size()){
            flag=true;
            return;
        }
        vector<int> tmp=points[index];
        int x=tmp[0];
        int y=tmp[1];
        for(int i=1;i<=9;i++){
            if(line[x][i]==false&&column[y][i]==false&&matrix[x/3][y/3][i]==false){
                board[x][y]=i+'0';
                line[x][i]=true;
                column[y][i]=true;
                matrix[x/3][y/3][i]=true;
                dfs(points, index+1, board);
                if(flag){
                    return;
                }
                line[x][i]=false;
                column[y][i]=false;
                matrix[x/3][y/3][i]=false;
                board[x][y]='.';
            }
        }
    }
    void solveSudoku(vector<vector<char>>& board) {
        memset(line, false, sizeof(line));
        memset(column, false, sizeof(column));
        memset(matrix, false, sizeof(matrix));
        vector<vector<int>> points;
        int n=9;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]=='.'){
                    points.push_back({i, j});
                }else{
                    line[i][board[i][j]-'0']=true;
                    column[j][board[i][j]-'0']=true;
                    matrix[i/3][j/3][board[i][j]-'0']=true;
                }
            }
        }
    
        dfs(points, 0, board);
    }
};



//八皇后：位运算解法
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        auto solutions = vector<vector<string>>();
        auto queens = vector<int>(n, -1);
        solve(solutions, queens, n, 0, 0, 0, 0);
        return solutions;
    }

    void solve(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, int columns, int diagonals1, int diagonals2) {
        if (row == n) {
            auto board = generateBoard(queens, n);
            solutions.push_back(board);
        } else {
            int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));//因为只需要后面8位，而不是32位都需要
            while (availablePositions != 0) {
                int position = availablePositions & (-availablePositions);
                availablePositions = availablePositions & (availablePositions - 1);
                int column = __builtin_ctz(position);
                queens[row] = column;
                solve(solutions, queens, n, row + 1, columns | position, (diagonals1 | position) >> 1, (diagonals2 | position) << 1);
                queens[row] = -1;
            }
        }
    }

    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
};

