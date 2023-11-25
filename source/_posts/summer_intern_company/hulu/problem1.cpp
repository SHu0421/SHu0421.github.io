#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 15
// 1 2 3 -1 4 5 6 -1 -1 7 8 9 -1 -1 10

int res = 0;
void findTerminal(vector<int> &num, int index)
{
    int size = num.size();
    if(index>=size||num[index]==-1){
        return;
    }
    
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if ((left>=size||num[left]==-1)&&(right>=size||num[right]==-1)){
        res ++ ;
        return;
    }
    findTerminal(num, left);
    findTerminal(num, right);
}
int main(){
    int n;
    scanf("%d", &n);
    cout << n << endl;
    vector<int> num;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        num.push_back(tmp);
    }
    findTerminal(num, 0);
    cout << res << endl;
    return 0;
}