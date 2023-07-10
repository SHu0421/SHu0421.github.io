#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<unordered_map>
using namespace std;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> arr(n);
    unordered_map<int, vector<int> > hash;
    vector<int> vis(33, 0);
    vector<int> record(n, 1);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
        int tmp=arr[i];
        int index=0;
        while(tmp){
            if(tmp&1){
                vis[index]=1;
                hash[index].push_back(i);
            }
            tmp=tmp>>1;
            index++;
        }
    }
    int res=0;
    for(int i=32;i>=0;i--){
        if(vis[i]){
            // cout<<i<<endl;
            vector<int> tmp_arr=hash[i];
            int count=0;
            for(int j=0;j<tmp_arr.size();j++){
                if(record[tmp_arr[i]]){
                    count++;
                }
            }
            // cout<<count<<" "<<k<<endl;
            if(count>=k){
                res|=(1<<i);
                vector<int> new_record(n, 0);
                for(int j=0;j<tmp_arr.size();j++){
                    new_record[tmp_arr[i]]=1;
                }
                record=new_record;
            }
            
        }
    }
    cout<<res<<endl;
    return 0;
    
}