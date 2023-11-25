#include <iostream>
#include <vector>
using namespace std;


// 主要思路：先使用vector记录每一天（0-9）可以参加的employee的数量有哪些；
//然后使用二重循环，枚举选择的两天，使得这两天能够参加的employee数量加起来最大，使用set去量两天重复的employee id
#include<set>
int solution(vector<string> &E) {
    // write your code in C++14 (g++ 6.2.0)
    vector<vector<int>> num(10);
    int n = E.size();
    for (int i = 0; i < n;i++){
        int len=E[i].size();
        for (int j = 0; j < len;j++){
            num[E[i][j] - '0'].push_back(i);
        }
    }
    int res = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10;j++){
            set<int> s;
            s.insert(num[i].begin(), num[i].end());
            s.insert(num[j].begin(), num[j].end());
            int tmp=s.size();
            res = max(res, tmp);
        }
    }
    return res;
}