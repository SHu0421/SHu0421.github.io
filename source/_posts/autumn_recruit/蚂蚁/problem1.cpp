#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int main(){
    int n, k;
    vector<int> arr(n, 0);
    scanf("%d%d", &n, &k);
    unordered_map<int, int> hash;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        hash[arr[i]]++;
    }
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        while(hash[arr[i]]>1){
            int cur = arr[i];
            while(hash[cur]>=1){
                cur += k;
                res++;
            }
            hash[cur]++;
            hash[arr[i]]--;
        }
    }
    cout << res << endl;
    return 0;
}