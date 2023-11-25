#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;


int main(){
    string s;
    cin >> s;
    int size = s.size();
    vector<int> presum(size+1, 0);
    for (int i = 1; i <= size; i++)
    {
        if(s[i-1]=='0'){
            presum[i] = presum[i - 1];
        }else{
             presum[i] = presum[i - 1]+1;
        }
    }
    bool flag = false;
    for (int len = size - 1; len >= 1; len--)
    {
        unordered_map<int, vector<vector<int>>> hash;
        for (int i = 1; i + len - 1 <= size; i++)
        {
            int j = i + len - 1;
            int tmp = presum[j] - presum[i - 1];
            hash[tmp].push_back({i, j});
            if (hash[tmp].size() >= 2)
            {
                cout << hash[tmp][0][0] << " " << hash[tmp][0][1] << " " << hash[tmp][1][0] << " " << hash[tmp][1][1] << endl;
                flag = true;
                break;
            }
        }
        if(flag){
            break;
        }
    }

    return 0;
}